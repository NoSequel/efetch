<h1 align="center">efetch</h1>
<p align="center">is a system information tool written in C++</p><br>

``efetch`` was written by me to learn more about the C/C++ programming language, currently support for multiple operating systems is lacking, however it is pretty easy to add more operating systems. If you wish, you can open a [PR](https://github.com/NoSequel/efetch/pulls) to add more support and/or clean up code.

## OS Support
Currently we support 2 OS' (1 untested).
* Linux:
    - Gentoo/Linux (Portage)
* BSD:
    - FreeBSD/BSD (pkg)

## Configuration
It is possible to edit the primary colors inside of the ``main.c`` file (``primary`` and ``secondary`` colors).

## Installation
* ### Building

    It is possible to build this using ``g++``:
       
       - g++ ./main.c

* ### Creating a symlink

    Using ``ln`` you can make a symlink so you can execute this program anywhere, for example:
       
       - ln ./a.out /bin/efetch
