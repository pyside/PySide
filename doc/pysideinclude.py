#
# This code is a modified version of the code found in sphinx distribution
# the same license of sphinx distribution applies to this file as well.
#

import os
import sys
import codecs
from os import path

from docutils import nodes
from docutils.parsers.rst import Directive, directives

from sphinx import addnodes
from sphinx.util import parselinenos

class PySideInclude(Directive):
    """
    Like ``.. include:: :literal:``, but only warns if the include file is
    not found, and does not raise errors.  Also has several options for
    selecting what to include.
    """

    has_content = False
    required_arguments = 1
    optional_arguments = 0
    final_argument_whitespace = False
    option_spec = {
        'linenos': directives.flag,
        'tab-width': int,
        'language': directives.unchanged_required,
        'encoding': directives.encoding,
        'pyobject': directives.unchanged_required,
        'lines': directives.unchanged_required,
        'start-after': directives.unchanged_required,
        'end-before': directives.unchanged_required,
        'prepend': directives.unchanged_required,
        'append': directives.unchanged_required,
        'snippet': directives.unchanged_required,
    }

    def run(self):
        document = self.state.document
        filename = self.arguments[0]
        if not document.settings.file_insertion_enabled:
            return [document.reporter.warning('File insertion disabled',
                                              line=self.lineno)]
        env = document.settings.env
        if filename.startswith('/') or filename.startswith(os.sep):
            rel_fn = filename[1:]
        else:
            docdir = path.dirname(env.doc2path(env.docname, base=None))
            rel_fn = path.join(docdir, filename)
        try:
            fn = path.join(env.srcdir, rel_fn)
        except UnicodeDecodeError:
            # the source directory is a bytestring with non-ASCII characters;
            # let's try to encode the rel_fn in the file system encoding
            rel_fn = rel_fn.encode(sys.getfilesystemencoding())
            fn = path.join(env.srcdir, rel_fn)

        if 'pyobject' in self.options and 'lines' in self.options:
            return [document.reporter.warning(
                'Cannot use both "pyobject" and "lines" options',
                line=self.lineno)]

        encoding = self.options.get('encoding', env.config.source_encoding)
        codec_info = codecs.lookup(encoding)
        try:
            f = codecs.StreamReaderWriter(open(fn, 'U'),
                    codec_info[2], codec_info[3], 'strict')
            lines = f.readlines()
            f.close()
        except (IOError, OSError):
            return [document.reporter.warning(
                'Include file %r not found or reading it failed' % filename,
                line=self.lineno)]
        except UnicodeError:
            return [document.reporter.warning(
                'Encoding %r used for reading included file %r seems to '
                'be wrong, try giving an :encoding: option' %
                (encoding, filename))]

        objectname = self.options.get('pyobject')
        if objectname is not None:
            from sphinx.pycode import ModuleAnalyzer
            analyzer = ModuleAnalyzer.for_file(fn, '')
            tags = analyzer.find_tags()
            if objectname not in tags:
                return [document.reporter.warning(
                    'Object named %r not found in include file %r' %
                    (objectname, filename), line=self.lineno)]
            else:
                lines = lines[tags[objectname][1]-1 : tags[objectname][2]-1]

        linespec = self.options.get('lines')
        if linespec is not None:
            try:
                linelist = parselinenos(linespec, len(lines))
            except ValueError, err:
                return [document.reporter.warning(str(err), line=self.lineno)]
            lines = [lines[i] for i in linelist]

        startafter = self.options.get('start-after')
        endbefore  = self.options.get('end-before')
        prepend    = self.options.get('prepend')
        append     = self.options.get('append')
        snippet    = self.options.get('snippet')

        if snippet:
            startafter = "//![%s]" % snippet
            endbefore = "//![%s]" % snippet

        if startafter is not None or endbefore is not None:
            use = not startafter
            res = []
            for line in lines:
                if not use and startafter and startafter in line:
                    use = True
                elif use and endbefore and endbefore in line:
                    use = False
                    break
                elif use:
                    if not line.startswith("//!"):
                        res.append(line)
            lines = res

        if prepend:
           lines.insert(0, prepend + '\n')
        if append:
           lines.append(append + '\n')

        text = ''.join(lines)
        if self.options.get('tab-width'):
            text = text.expandtabs(self.options['tab-width'])
        retnode = nodes.literal_block(text, text, source=fn)
        retnode.line = 1
        retnode.attributes['line_number'] = self.lineno
        if self.options.get('language', ''):
            retnode['language'] = self.options['language']
        if 'linenos' in self.options:
            retnode['linenos'] = True
        document.settings.env.note_dependency(rel_fn)
        return [retnode]

def setup(app):
    app.add_directive('pysideinclude', PySideInclude)
