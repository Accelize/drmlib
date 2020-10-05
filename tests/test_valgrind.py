# -*- coding: utf-8 -*-
"""
Test DRM Library with bad arguments. Make sure errors are detected and reported as expected.
"""
import pytest
from re import search, IGNORECASE
from flask import request as _request
from json import dumps
from os.path import join, isfile

from tests.proxy import get_context, set_context


@pytest.mark.skip(reason='Not ready yet')
@pytest.mark.minimum
def test_normal_usage(accelize_drm, request, exec_func, live_server, tmpdir):
    """Check memory leak with valgrind"""
    if 'aws' not in accelize_drm.pytest_fpga_driver_name:
        pytest.skip("C unit-tests are only supported with AWS driver.")

    # Set initial context on the live server
    nb_running = 2
    healthPeriod = 2

    context = {'healthPeriod':healthPeriod}
    set_context(context)
    assert get_context() == context

    # Create C/C++ executable
    exec_func._conf_json['licensing']['url'] = _request.url + request.function.__name__
    exec_func._conf_json.save()
    driver = accelize_drm.pytest_fpga_driver[0]
    valgrind_log_file = join(accelize_drm.pytest_artifacts_dir, 'valgrind.log')
    exec_lib = exec_func.load('unittests', driver._fpga_slot_id, valgrind_log_file)

    # Run executable
    p = tmpdir.join('params.json')
    p.write('{"nb_running":%d}' % nb_running)     # Save exec parameters to file
    exec_lib.run(request.function.__name__, p)
    print('exec_lib=', str(exec_lib))
    assert exec_lib.returncode == 0
    assert search(r'DRM session \S{16} started', exec_lib.stdout, IGNORECASE)
    assert search(r'DRM session \S{16} stopped', exec_lib.stdout, IGNORECASE)
    assert search(r'\[\s*(error|critical)\s*\]', exec_lib.stdout, IGNORECASE) is None
    assert exec_lib.asyncmsg is None
    assert isfile(valgrind_log_file)
    with open(valgrind_log_file, 'rt') as f:
        content = f.read()
    print('valgrind_log_file=', valgrind_log_file)
