#!/bin/bash

g++ ./src/efetch.c

if [ "$EUID" -ne 0 ] 
then
    echo "You must run this command as root"
else
    # if the command is ran by root, install under /bin/efetch
    echo "Installing under /bin/efetch"

    # delete /bin/efetch if it exists
    if [ -f "/bin/efetch" ] 
    then
        echo "Deleting old /bin/efetch file"
        rm -rf /bin/efetch
    fi

    echo "Making new symlink for /bin/efetch"
    # make a new symlink for efetch
    ln ./a.out /bin/efetch
    rm -rf ./a.out
    echo "Finished."
fi
