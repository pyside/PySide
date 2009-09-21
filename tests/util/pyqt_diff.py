
'''Script to show the difference between PyQt4 and ours'''

import sys

from color import print_colored

def check_module_diff(module_name):
    '''Difference between PySide and PyQt4 versions of qt bindings.
    Returns a tuple with the members present only on PySide and only on PyQt4'''
    boost_module = getattr(__import__('PySide.' + module_name), module_name)
    orig_module = getattr(__import__('PyQt4.' + module_name), module_name)

    boost_set = set(dir(boost_module))
    orig_set = set(dir(orig_module))

    return sorted(boost_set - orig_set), sorted(orig_set - boost_set)


def main(argv=None):
    if argv is None:
        argv = sys.argv

    module_name = argv[1] if len(argv) >= 2 else 'QtCore'

    only_boost, only_orig = check_module_diff(module_name)

    print_colored('Only on Boost version')
    print only_boost

    print_colored('Only on SIP version')
    print only_orig

if __name__ == '__main__':
    main()
