import os
import sys
import shutil
import unittest
import py3kcompat as py3k

orig_path = os.path.join(os.path.dirname(__file__))
workdir = os.getcwd()
src = os.path.join(orig_path, 'test_module_template.py')
dst = os.path.join(workdir, 'test_module.py')
shutil.copyfile(src, dst)
sys.path.append(workdir)

def reload_module(moduleName):
    if py3k.IS_PY3K:
        import imp
        imp.reload(moduleName)
    else:
        reload(moduleName)

def increment_module_value():
    modfile = open(dst, 'a')
    modfile.write('Sentinel.value += 1' + os.linesep)
    modfile.flush()
    modfile.close()
    if not sys.dont_write_bytecode:
        if py3k.IS_PY3K:
            import imp
            cacheFile = imp.cache_from_source(dst)
        else:
            cacheFile = dst + 'c'
        os.remove(cacheFile)

class TestModuleReloading(unittest.TestCase):

    def testModuleReloading(self):
        '''Test module reloading with on-the-fly modifications.'''

        import test_module
        self.assertEqual(test_module.Sentinel.value, 10)

        increment_module_value()
        reload_module(sys.modules['test_module'])
        self.assertEqual(test_module.Sentinel.value, 11)

        reload_module(sys.modules['test_module'])
        self.assertEqual(test_module.Sentinel.value, 11)

        increment_module_value()
        reload_module(sys.modules['test_module'])
        self.assertEqual(test_module.Sentinel.value, 12)

if __name__ == "__main__":
    unittest.main()


