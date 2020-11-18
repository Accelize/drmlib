# coding=utf-8
"""
Intel OPAE driver for Accelize DRM Python library

Requires "libopae-c" library from Intel OPAE-C:
https://opae.github.io/latest/docs/fpga_api/prog_guide/readme.html
"""
from ctypes import (
    cdll as _cdll, POINTER as _POINTER, byref as _byref, c_uint32 as _c_uint32,
    c_uint64 as _c_uint64, c_int as _c_int, c_void_p as _c_void_p), c_int8 as _c_int8
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
        pci_info = _run("lspci | grep accel | cut -d':' -f 1 | tail -n %d" % self._fpga_slot_id, shell=True,
            stderr=_STDOUT, stdout=_PIPE, universal_newlines=True, check=False)
        if pci_info.returncode:
            raise RuntimeError(pci_info.stdout)
        pci_slot = pci_info.stdout.strip()
        # Prog FPGA Board
        program_fpga = _run('fpgaconf -B 0x%s %s' % (pci_slot, fpga_image), shell=True,
            stderr=_STDOUT, stdout=_PIPE, universal_newlines=True, check=False)
        if program_fpga.returncode:
            raise RuntimeError(program_fpga.stdout)

    def _reset_fpga(self):
        """
        Reset FPGA including FPGA image.
        """
        pass

    def _init_fpga(self):
        """
        Initialize FPGA handle with driver library.
        """
        fpga_properties = None
        fpga_get_properties = self._fpga_library.fpgaGetProperties
        fpga_get_properties.argtypes = (_c_void_p, _POINTER((_c_void_p))
        fpga_get_properties.restype = _c_int
        if fpga_get_properties(None, _byref(fpga_properties)):
            raise RuntimeError(
                "Unable to create properties object")
        print('Created properties object')

        fpga_properties_set_object_type = self._fpga_library.fpgaPropertiesSetObjectType
        fpga_get_properties.argtypes = (_c_void_p, _c_int)
        fpga_get_properties.restype = _c_int
        if fpga_properties_set_object_type(fpga_properties, 1):
            raise RuntimeError(
                "Unable to set object type")
        print('Set object type')

        fpga_properties_set_guid = self._fpga_library.fpgaPropertiesSetGUID
        fpga_properties_set_guid.argtypes = (_c_void_p, _c_int8 * 16)
        fpga_properties_set_guid.restype = _c_int
        guid = uuid.UUID('{850ADCC2-6CEB-4B22-9722-D43375B61C66}')
        if fpga_properties_set_guid(fpga_properties, guid.bytes):
            raise RuntimeError(
                "Unable to set GUID")
        print('Set GUID')

    def _get_read_register_callback(self):
        """
        Read register callback.

        Returns:
            function: Read register callback
        """
        '''
        fpga_pci_peek = self._fpga_library.fpga_pci_peek
        fpga_pci_peek.restype = _c_int  # return code
        fpga_pci_peek.argtypes = (
            _c_int,  # handle
            _c_uint64,  # offset
            _POINTER(_c_uint32)  # value
        )
        self._fpga_read_register = fpga_pci_peek
        '''

        def read_register(register_offset, returned_data, driver=self):
            """
            Read register.

            Args:
                register_offset (int): Offset
                returned_data (int pointer): Return data.
                driver (accelize_drm.fpga_drivers._aws_f1.FpgaDriver):
                    Keep a reference to driver.
            """
            '''
            with driver._fpga_read_register_lock():
                return driver._fpga_read_register(
                    driver._fpga_handle,
                    driver._drm_ctrl_base_addr + register_offset,
                    returned_data)
            '''
            return -1

        return read_register

    def _get_write_register_callback(self):
        """
        Write register callback.

        Returns:
            function: Write register callback
        """
        '''
        fpga_pci_poke = self._fpga_library.fpga_pci_poke
        fpga_pci_poke.restype = _c_int  # return code
        fpga_pci_poke.argtypes = (
            _c_int,  # handle
            _c_uint64,  # offset
            _c_uint32  # value
        )
        self._fpga_write_register = fpga_pci_poke
        '''
        def write_register(register_offset, data_to_write, driver=self):
            """
            Write register.

            Args:
                register_offset (int): Offset
                data_to_write (int): Data to write.
                driver (accelize_drm.fpga_drivers._aws_f1.FpgaDriver):
                    Keep a reference to driver.
            """
            '''
            with driver._fpga_write_register_lock():
                return driver._fpga_write_register(
                    driver._fpga_handle,
                    driver._drm_ctrl_base_addr + register_offset,
                    data_to_write)
            '''
            pass

        return write_register
