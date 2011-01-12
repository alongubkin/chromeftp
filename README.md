ChromeFTP
=========

A complete FTP client extension for Google Chrome.

Technical Details
-----------------

This extension uses a NPAPI plugin for accessing the underlying OS file system and socket, as this is not possible with HTML5 alone. It is wrriten with C++ using the [Boost][2] library. The NPAPI plugin exposes methods to the extension JavaScript with [Nixysa][3] - a framework for generating glue code for NPAPI plugins.


Contributing
------------

1. Fork it.
2. Create a branch.
3. Commit your changes.
4. Push to the branch.
5. Create an [issue][1] with a link to your branch.
6. Enjoy a refreshing Coke and wait.

License
-------

Copyright (C) 2011 Alon Gubkin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

[1]: http://github.com/alongubkin/chromeftp/issues
[2]: http://www.boost.org/
[3]: http://code.google.com/p/nixysa/
