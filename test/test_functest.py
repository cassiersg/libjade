"""
Checks that the functional test program (functest) can be successfully built
and executed for every scheme/implementation.
"""

import os
import platform
import unittest

import pytest

import helpers
import libjade


@pytest.mark.parametrize(
    'implementation,test_dir,impl_path, init, destr',
    [(impl, *helpers.isolate_test_files(impl.path(), 'test_functest_'))
     for impl in libjade.Scheme.all_supported_implementations()],
    ids=[str(impl) for impl in libjade.Scheme.all_supported_implementations()],
)
@helpers.filtered_test
def test_functest(implementation, impl_path, test_dir,
                  init, destr):
    init()
    dest_dir = os.path.join(test_dir, 'bin')
    helpers.make('functest',
                 TYPE=implementation.scheme.type,
                 SCHEME=implementation.scheme.name,
                 IMPLEMENTATION=implementation.name,
                 SCHEME_DIR=impl_path,
                 DEST_DIR=dest_dir,
                 working_dir=os.path.join(test_dir, 'test'))
    helpers.run_subprocess(
        [os.path.join(dest_dir, 'functest_{}_{}{}'.format(
            implementation.scheme.name,
            implementation.name,
            '.exe' if os.name == 'nt' else ''
        ))],
    )
    destr()


@pytest.mark.parametrize(
    'implementation,test_dir,impl_path, init, destr',
    [(impl,
      *helpers.isolate_test_files(impl.path(), 'test_functest_sanitizers_'))
     for impl in libjade.Scheme.all_supported_implementations()],
    ids=[str(impl) for impl in libjade.Scheme.all_supported_implementations()],
)
@helpers.skip_windows()
@helpers.filtered_test
def test_functest_sanitizers(implementation, impl_path, test_dir,
                             init, destr):
    dest_dir = os.path.join(test_dir, 'bin')
    env = None
    if (implementation.scheme.name == "sphincs-sha256-192s-robust"
            and 'CI' in os.environ
            and implementation.name == "clean"
            and 'clang' in os.environ.get('CC', '')):
        raise unittest.SkipTest("Clang makes this test use too much RAM")
    if platform.machine() == 'ppc' and 'clang' in os.environ.get('CC', 'gcc'):
        raise unittest.SkipTest("Clang does not support ASAN on ppc")
    elif platform.machine() in ['armv7l', 'aarch64']:
        env = {'ASAN_OPTIONS': 'detect_leaks=0'}
    elif platform.system() == 'Darwin':
        raise unittest.SkipTest('ASAN is not reliable on OSX')
    else:
        print("Supported platform: {}".format(platform.machine()))

    init()

    helpers.make('clean-scheme', 'functest',
                 TYPE=implementation.scheme.type,
                 SCHEME=implementation.scheme.name,
                 IMPLEMENTATION=implementation.name,
                 EXTRAFLAGS=(
                     '-g -fsanitize=address,undefined '
                     '-fno-sanitize-recover=undefined '
                     # TODO(JMS) Remove explicit -latomic if/when gcc fixes:
                     # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81358
                     '-Wno-unused-command-line-argument -latomic'),
                 SCHEME_DIR=impl_path,
                 DEST_DIR=dest_dir,
                 working_dir=os.path.join(test_dir, 'test'),
                 env=env)
    helpers.run_subprocess(
        [os.path.join(dest_dir, 'functest_{}_{}{}'.format(
            implementation.scheme.name,
            implementation.name,
            '.exe' if os.name == 'nt' else ''
        ))],
        env=env,
    )
    destr()


if __name__ == '__main__':
    import sys
    pytest.main(sys.argv)
