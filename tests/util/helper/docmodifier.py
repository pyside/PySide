
'''Helper metaclass do 'decorate' docstrings from base test case classes'''

import types


def copy_func(func):
    '''Helper function to copy a function object (except docstring)'''
    return types.FunctionType(func.func_code, func.func_globals, func.func_name,
                              func.func_defaults, func.func_closure)


class DocModifier(type):
    '''Metaclass for modifiying method documentation.

    It allows the managed class to modify the method documentation, adding
    prefixes and suffixes to a given set of methods.

    For example, you have some unittest.TestCases that run on different set
    of data. These methods could be written once in a base class and the
    inheriting class just setup different setUp/tearDown methods with the
    proper data. To differentiate the methods when using docstrings, you
    can add a suffix or prefix to the docstring.

    Variables in the implementing class:

    doc_prefix - The prefix to the docstring
    doc_suffix - The suffix to the docstring
    doc_filter - The function to filter the methods. If not provided, this
                 no docstrings are changed.'''

    def __new__(mcs, name, bases, dct):

        # FIXME currently we have to define doc_filter on each subclass
        filter_function = dct.get('doc_filter')
        if not filter_function:
            filter_function = lambda x: False

        for base in bases:
            for attr in [x for x in base.__dict__ if filter_function(x)]:
                original = getattr(base, attr)

                if original.__doc__:
                    copy = copy_func(original)
                    copy.__doc__ = (dct.get('doc_prefix', '') +
                                    original.__doc__ +
                                    dct.get('doc_suffix', ''))
                    dct[attr] = copy

        return type.__new__(mcs, name, bases, dct)

    def __init__(mcs, name, bases, dct):
        super(DocModifier, mcs).__init__(name, bases, dct)


if __name__ == '__main__':

    # tests
    class BaseTest(object):
        __metaclass__ = DocModifier

        def testBase(self):
            '''base'''

        def testWithoutDoc(self):
            pass

    class Implementing(BaseTest):

        doc_filter = lambda x: x.startswith('test')
        doc_prefix = 'prefix'
        doc_suffix = 'suffix'

    class OnlyPrefix(BaseTest):

        doc_filter = lambda x: x.startswith('test')
        doc_prefix = 'prefix'

    class OnlySuffix(BaseTest):

        doc_filter = lambda x: x.startswith('test')
        doc_suffix = 'suffix'

    assert(Implementing.testBase.__doc__ == 'prefixbasesuffix')
    assert(Implementing.testWithoutDoc.__doc__ == None)
    assert(OnlySuffix.testBase.__doc__ == 'basesuffix')
    assert(OnlySuffix.testWithoutDoc.__doc__ == None)
    assert(OnlyPrefix.testBase.__doc__ == 'prefixbase')
    assert(OnlyPrefix.testWithoutDoc.__doc__ == None)
