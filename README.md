ChromeFTP
=========

A complete FTP client extension for Google Chrome.

Technical Details
-----------------

This extension uses a NPAPI plugin for accessing the underlying OS file system and socket, as this is not possible with pure HTML5. The NPAPI plugin is wrriten in C++ using the [Boost][2] library. It exposes methods to the extension JavaScript with [Nixysa][3] - a framework for generating glue code for NPAPI plugins.

Compilation
-----------

You will need a few things to download and compile the plugin:

 - Git ([Linux][6], [Windows][7], [Mac][8])
 - [SCons][4]
 - [Boost][5]

After installing those, open terminal/console and execute:

    cd ~
    git clone git://github.com/alongubkin/chromeftp.git chromeftp
    cd chromeftp/plugin
    scons

To add the extension to Chrome, follow the following steps:

 1. Click on the wrench icon on Chrome ![Wrench](http://code.google.com/chrome/extensions/images/toolsmenu.gif) and choose **Tools > Extensions** (On Mac, use **Windows > Extension**).
 2. If **Developer mode** has a + by it, click the + to add developer information to the page. The + changes to a -, and more buttons and information appear.
 3. Click the **Load unpacked extension** button. 
 4. In the file dialog, navigate to <chromeftp directory>/extension and click **OK**.

Contributing
------------

1. Fork it.
2. Create a branch.
3. Commit your changes.
4. Push to the branch.
5. Create an [issue][1] with a link to your branch.

Thakns!

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
[4]: http://www.scons.org/
[5]: http://www.boost.org/doc/libs/1_45_0/more/getting_started/index.html
[6]: http://help.github.com/linux-git-installation/
[7]: http://help.github.com/win-git-installation/
[8]: http://help.github.com/mac-git-installation/
