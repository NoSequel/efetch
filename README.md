<img src="https://raw.githubusercontent.com/NoSequel/efetch/main/screenshots/screenshot1.png" width="40%" align="right">
<h1 align="center">efetch</h1>
<p align="center">is a system information tool written in C++</p><br>

``efetch`` was written by me to learn more about the C/C++ programming language, currently support for multiple operating systems is lacking, however it is pretty easy to add more operating systems. If you wish, you can open a [PR](https://github.com/NoSequel/efetch/pulls) to add more support and/or clean up code.

## OS Support
Currently we support 4 OS' (3 untested).
* Linux:
    - Gentoo/Linux (Emerge)
    - Arch/Linux (Pacman)
    - Void/Linux (xbps)
* BSD:
    - FreeBSD/BSD (pkg)

## Configuration
There is a ``config.h`` file included with the source code where you can toggle certain fields and edit the current color scheme.

## Installation
  - You are able to run the ``compile.sh`` script in order to update and/or install ``efetch``
