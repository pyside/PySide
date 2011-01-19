import os
import sys
import shutil
import unittest

orig_path = os.path.join(os.path.dirname(__file__))
workdir = os.getcwd()
src = os.path.join(orig_path, 'test_module_template.py')
dst = os.path.join(workdir, 'test_module.py')
shutil.copyfile(src, dst)
sys.path.append(workdir)

def increment_module_value():
    modfile = open(dst, 'a')
    modfile.write('MyQWidget.value += 1' + os.linesep)
    modfile.flush()
    modfile.close()
    os.remove(dst + 'c')

class TestModuleReloading(unittest.TestCase):

    def testModuleReloading(self):
        '''Test module reloading with on-the-fly modifications.'''

        import test_module
        self.assertEqual(test_module.MyQWidget.value, 10)

        increment_module_value()
        reload(sys.modules['test_module'])
        self.assertEqual(test_module.MyQWidget.value, 11)

        reload(sys.modules['test_module'])
        self.assertEqual(test_module.MyQWidget.value, 11)

        increment_module_value()
        reload(sys.modules['test_module'])
        self.assertEqual(test_module.MyQWidget.value, 12)

if __name__ == "__main__":
    unittest.main()


