"""
  This script is based on Python2.6 Ubuntu package script:
  Copyright (C) 2009 Matthias Klose <doko@debian.org>
  Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public License
  version 2.1 as published by the Free Software Foundation. Please
  review the following information to ensure the GNU Lesser General
  Public License version 2.1 requirements will be met:
  http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
   02110-1301 USA
"""
#! /usr/bin/python

import formatter, htmllib
import os, sys, re

class PyHTMLParser(htmllib.HTMLParser):
    pages_to_include = set(('index.html', 'PySide/QtHelp/index.html', 'PySide/QtSvg/index.html',
                        'PySide/QtGui/index.html', 'PySide/QtNetwork/index.html', 'PySide/QtWebKit/index.html',
                        'PySide/QtUiTools/index.html', 'PySide/QtXml/index.html', 'PySide/QtCore/index.html',
                        'PySide/QtScriptTools/index.html', 'PySide/QtOpenGL/index.html', 'PySide/QtScript/index.html',
                        'PySide/QtSql/index.html', 'howto-build/index.html'))

    def __init__(self, formatter, basedir, fn, indent, parents=set()):
        htmllib.HTMLParser.__init__(self, formatter)
        self.basedir = basedir
        self.dir, self.fn = os.path.split(fn)
        self.data = ''
        self.parents = parents
        self.link = {}
        self.indent = indent
        self.last_indent = indent - 1
        self.sub_indent = 0
        self.sub_count = 0
        self.next_link = False

    def process_link(self):
        new_href = os.path.join(self.dir, self.link['href'])
        text = self.link['text']
        indent = self.indent + self.sub_indent
        if self.last_indent == indent:
            print '%s</sub>' % ('  ' * self.last_indent)
            self.sub_count -= 1
        print '%s<sub link="%s" name="%s">' % ('  ' * indent, new_href, text)
        self.sub_count += 1
        self.last_indent = self.indent + self.sub_indent

    def start_li(self, attrs):
        self.sub_indent += 1
        self.next_link = True

    def end_li(self):
        indent = self.indent + self.sub_indent
        if self.sub_count > 0:
            print '%s</sub>' % ('  ' * self.last_indent)
            self.sub_count -= 1
            self.last_indent -= 1
        self.sub_indent -= 1

    def start_a(self, attrs):
        self.link = {}
        for attr in attrs:
            self.link[attr[0]] = attr[1]
        self.data = ''

    def end_a(self):
        process = False
        text = self.data.replace('\t', '').replace('\n', ' ').replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
        self.link['text'] = text
        # handle a tag without href attribute
        try:
            href = self.link['href']
        except KeyError:
            return

        abs_href = os.path.join(self.basedir, href)
        if abs_href in self.parents:
            return
        if href.startswith('..') or href.startswith('http:') \
               or href.startswith('mailto:') or href.startswith('news:'):
            return
        if href in ('', 'about.html', 'modindex.html', 'genindex.html', 'glossary.html',
                    'search.html', 'contents.html', 'download.html', 'bugs.html',
                    'license.html', 'copyright.html'):
            return

        if self.link.has_key('class'):
            if self.link['class'] in ('biglink'):
                process = True
            if self.link['class'] in ('reference external'):
                if self.next_link:
                    process = True
                    next_link = False

        if process == True:
            self.process_link()
            if href in self.pages_to_include:
                self.parse_file(os.path.join(self.dir, href))

    def finish(self):
        if self.sub_count > 0:
            print '%s</sub>' % ('  ' * self.last_indent)

    def handle_data(self, data):
        self.data += data

    def parse_file(self, href):
        # TODO basedir bestimmen
        parent = os.path.join(self.basedir, self.fn)
        self.parents.add(parent)
        parser = PyHTMLParser(formatter.NullFormatter(),
                              self.basedir, href, self.indent + 1,
                              self.parents)
        text = file(self.basedir + '/' + href).read()
        parser.feed(text)
        parser.finish()
        parser.close()
        if parent in self.parents:
            self.parents.remove(parent)

class PyIdxHTMLParser(htmllib.HTMLParser):
    def __init__(self, formatter, basedir, fn, indent):
        htmllib.HTMLParser.__init__(self, formatter)
        self.basedir = basedir
        self.dir, self.fn = os.path.split(fn)
        self.data = ''
        self.link = {}
        self.indent = indent
        self.active = False
        self.indented = False
        self.nolink = False
        self.header = ''
        self.last_letter = 'Z'
        self.last_text = ''

    def process_link(self):
        new_href = os.path.join(self.dir, self.link['href'])
        text = self.link['text']
        if not self.active:
            return
        if text.startswith('['):
            return
        if self.link.get('rel', None) in ('prev', 'parent', 'next', 'contents', 'index'):
            return
        if self.indented:
            text = self.last_text + ' ' + text
        else:
            # Save it in case we need it again
            self.last_text = re.sub(' \([\w\-\.\s]+\)', '', text)
        indent = self.indent
        print '%s<function link="%s" name="%s"/>' % ('  ' * indent, new_href, text)

    def start_dl(self, attrs):
        if self.last_text:
            # Looks like we found the second part to a command
            self.indented = True

    def end_dl(self):
        self.indented = False

    def start_dt(self, attrs):
        self.data = ''
        self.nolink = True

    def end_dt(self):
        if not self.active:
            return
        if self.nolink == True:
            # Looks like we found the first part to a command
            self.last_text = re.sub(' \([\w\-\.\s]+\)', '', self.data)
            self.nolink = False

    def start_h2(self, attrs):
        for k, v in attrs:
            if k == 'id':
                self.header = v
                if v == '_':
                    self.active = True

    def start_td(self, attrs):
        self.indented = False
        self.last_text = ''

    def start_table(self, attrs):
        pass

    def end_table(self):
        if self.header == self.last_letter:
            self.active = False

    def start_a(self, attrs):
        self.nolink = False
        self.link = {}
        for attr in attrs:
            self.link[attr[0]] = attr[1]
        self.data = ''

    def end_a(self):
        text = self.data.replace('\t', '').replace('\n', ' ').replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
        self.link['text'] = text
        # handle a tag without href attribute
        try:
            href = self.link['href']
        except KeyError:
            return
        self.process_link()

    def handle_data(self, data):
        self.data += data

def main():
    base = sys.argv[1]
    fn = sys.argv[2]

    parser = PyHTMLParser(formatter.NullFormatter(), base, fn, indent=0)
    print '<?xml version="1.0" encoding="iso-8859-1"?>'
    print '<book title="PySide %s Documentation" name="PySide" version="%s" link="index.html">' % (sys.argv[3], sys.argv[3])
    print '<chapters>'
    parser.parse_file(fn)
    print '</chapters>'

    print '<functions>'

    fn = 'genindex.html'
    parser = PyIdxHTMLParser(formatter.NullFormatter(), base, fn, indent=1)
    text = file(base + '/' + fn).read()
    parser.feed(text)
    parser.close()

    print '</functions>'
    print '</book>'

main()

