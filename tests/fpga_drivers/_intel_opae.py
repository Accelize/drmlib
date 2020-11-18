# coding=utf-8
"""
Intel OPAE driver for Accelize DRM Python library

Requires "libopae-c" library from Intel OPAE-C:
https://opae.github.io/latest/docs/fpga_api/prog_guide/readme.html
"""
from ctypes import (
    cdll as _cdll, POINTER as _POINTER, byref as _byref, c_uint32 as _c_uint32,
    c_uint64 as _c_uint64, c_int as _c_int, c_void_p as _c_void_p, c_int8 as _c_int8)
from subprocess import run as _run, PIPE as _PIPE, STDOUT as _STDOUT
from os.path import basename as _basename
from re import match as _match
from threading import Lock as _Lock
import uuid

from tests.fpga_drivers import FpgaDriverBase as _FpgaDriverBase

__all__ = ['FpgaDriver']


class FpgaDriver(_FpgaDriverBase):
    """
    Generates functions to use AWS FPGA F1 with accelize_drm.DrmManager.

    Args:
        fpga_slot_id (int): FPGA slot ID.
        fpga_image (str): AGFI or AFI to use to program FPGA.
        drm_ctrl_base_addr (int): DRM Controller base address.
        log_dir (path-like object): Unused with this driver.
    """
    _name = _match(r'_(.+)\.py', _basename(__file__)).group(1)

    @staticmethod
    def _get_driver():
        """
        Get FPGA driver

        Returns:
            ctypes.CDLL: FPGA driver.
        """
        # Load AWS FPGA library
        fpga_library = _cdll.LoadLibrary("libopae-c.so")
        return fpga_library

    @staticmethod
    def _get_lock():
        """
        Get a lock on the FPGA driver
        """
        return _Lock
    """
    def __del__(self):
        fpga_properties = _c_void_p()
        fpga_destroy_properties = self._fpga_library.fpgaDestroyProperties
        fpga_destroy_properties.argtypes = (_c_void_p, _POINTER(_c_void_p))
        fpga_destroy_properties.restype = _c_int
        if fpga_destroy_properties(None, _byref(fpga_properties)):
            raise RuntimeError("Unable to create properties object")
    """
    def _clear_fpga(self):
        """
        Clear FPGA
        """
        pass

    def _program_fpga(self, fpga_image):
        """
        Program the FPGA with the specified image.

        Args:
            fpga_image (str): FPGA image.
        """
        # Get FPGA Boards Info
        pci_info = _run("lspci | grep accel", shell=True,
            stderr=_STDOUT, stdout=_PIPE, universal_newlines=True, check=False)
        if pci_info.returncode:
            raise RuntimeError(pci_info.stdout)
        pci_info = pci_info.stdout.strip().split('\n')
        pci_slot = _match(r'([^:]+):.*', pci_info[self._fpga_slot_id]).group(1)
        # Prog FPGA Board
        program_fpga = _run('fpgaconf -B 0x%s %s' % (pci_slot, fpga_image), shell=True,
            stderr=_STDOUT, stdout=_PIPE, universal_newlines=True, check=False)
        if program_fpga.returncode:
            raise RuntimeError(program_fpga.stdout)

    def _reset_fpga(self):
        """
        Reset FPGA including FPGA image.
        """
        fpga_reset = self._fpga_library.fpgaReset
        fpga_reset.argtypes = (_c_void_p)
        fpga_reset.restype = _c_int
        if self._fpga_handle:
            if fpga_reset(self._fpga_handle):
                raise RuntimeError("Unable to reset AFC")

    def _init_fpga(self):
        """
        Initialize FPGA handle with driver library.
        """
        self._fpga_handle = _c_void_p(None)
        fpga_properties = _c_void_p(None)
        fpga_get_properties = self._fpga_library.fpgaGetProperties
        fpga_get_properties.argtypes = (_c_void_p, _POINTER(_c_void_p))
        fpga_get_properties.restype = _c_int
        if fpga_get_properties(None, _byref(fpga_properties)):
            raise RuntimeError("Unable to create properties object")

        fpga_properties_set_object_type = self._fpga_library.fpgaPropertiesSetObjectType
        fpga_get_properties.argtypes = (_c_void_p, _c_int)
        fpga_get_properties.restype = _c_int
        if fpga_properties_set_object_type(fpga_properties, 1):
            raise RuntimeError("Unable to set object type")

        fpga_properties_set_guid = self._fpga_library.fpgaPropertiesSetGUID
        fpga_properties_set_guid.argtypes = (_c_void_p, _c_int8 * 16)
        fpga_properties_set_guid.restype = _c_int
        guid = uuid.UUID('{850ADCC2-6CEB-4B22-9722-D43375B61C66}')
        c_guid = (_c_int8*16)(*list(guid.bytes))
        if fpga_properties_set_guid(fpga_properties, c_guid):
            raise RuntimeError("Unable to set GUID")

        fpga_enumerate = self._fpga_library.fpgaEnumerate
        fpga_enumerate.argtypes = (_POINTER(_c_void_p), _c_uint32,
                _POINTER(_c_void_p), _c_uint32, _POINTER(_c_uint32))
        fpga_enumerate.restype = _c_int
        afc_token = _c_void_p()
        num_matches = _c_uint32(0)
        if fpga_enumerate(_byref(fpga_properties), 1, _byref(afc_token), 1, _byref(num_matches)):
            raise RuntimeError("Unable to enumerate AFCs")
        if num_matches.value < 1:
            raise RuntimeError("AFC not found")

        fpga_open = self._fpga_library.fpgaOpen
        fpga_open.argtypes = (_c_void_p, _POINTER(_c_void_p), _c_int)
        fpga_open.restype = _c_int
        if fpga_open(afc_token, _byref(self._fpga_handle), 0):
            raise RuntimeError("Unable to open AFC")

        fpga_map_mmio = self._fpga_library.fpgaMapMMIO
        fpga_map_mmio.argtypes = (_c_void_p, _c_uint32, _POINTER(_POINTER(_c_uint64)))
        fpga_map_mmio.restype = _c_int
        if fpga_map_mmio(self._fpga_handle, 0, None):
            raise RuntimeError("Unable to map MMIO")
        print('MMIO mapped')

    def _get_read_register_callback(self):
        """
        Read register callback.

        Returns:
            function: Read register callback
        """
        fpga_read_mmio32 = self._fpga_library.fpgaReadMMIO32
        fpga_read_mmio32.argtypes = (_c_void_p, _c_uint32, _c_uint64, _POINTER(_c_uint32))
        fpga_read_mmio32.restype = _c_int
        self._fpga_read_register = fpga_read_mmio32

        def read_register(register_offset, returned_data, driver=self):
            """
            Read register.

            Args:
                register_offset (int): Offset
                returned_data (int pointer): Return data.
                driver (accelize_drm.fpga_drivers._aws_f1.FpgaDriver):
                    Keep a reference to driver.
            """
            with driver._fpga_read_register_lock():
                return driver._fpga_read_register(
                    driver._fpga_handle, 0,
                    driver._drm_ctrl_base_addr + register_offset * 4,
                    returned_data)
            return -1

        return read_register

    def _get_write_register_callback(self):
        """
        Write register callback.

        Returns:
            function: Write register callback
        """
        fpga_write_mmio32 = self._fpga_library.fpgaWriteMMIO32
        fpga_write_mmio32.argtypes = (_c_void_p, _c_uint32, _c_uint64, _c_uint32)
        fpga_write_mmio32.restype = _c_int
        self._fpga_write_register = fpga_write_mmio32

        def write_register(register_offset, data_to_write, driver=self):
            """
            Write register.

            Args:
                register_offset (int): Offset
                data_to_write (int): Data to write.
                driver (accelize_drm.fpga_drivers._aws_f1.FpgaDriver):
                    Keep a reference to driver.
            """
            with driver._fpga_write_register_lock():
                return driver._fpga_write_register(
                    driver._fpga_handle, 0,
                    driver._drm_ctrl_base_addr + register_offset * 4,
                    data_to_write)

        return write_register
