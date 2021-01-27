#include <iostream>
#include <unistd.h>
#include <array>
#include "config.h"

// variables
std::string os;
std::string packageAmount;
std::string kernelVersion;

//method for executing a command and get the output
std::string exec(const char* cmd) {
    std::array<char, 32> buffer;
    std::string result;

    auto pipe = popen(cmd, "r");

    while(!feof(pipe)) {
        if(fgets(buffer.data(), 32, pipe) != nullptr) {
            result += buffer.data();
        }
    }

    return result;
}

void checkOS() {
    os = exec("cat /etc/os-release");
    kernelVersion = exec("uname -r");

    // check if the OS description contains the string "BSD"
    if(os.find("BSD") != std::string::npos) {
        // check if the OS description contains "FreeBSD"
        if(os.find("FreeBSD") != std::string::npos) {
            packageAmount = exec("pkg_info | wc -l");
            os = "FreeBSD/BSD";
            return;
        }
    // check if the OS description contains the string "Linux"
    } else if(os.find("Linux") != std::string::npos) {
        // check if the OS description contains "Gentoo"
        if(os.find("Gentoo") != std::string::npos) {
            packageAmount = exec("cd /var/db/pkg && ls -d */* | wc -l");
            os = "Gentoo/Linux";
            return;
        }
    }
    // if the method hasn't returned yet, set the variables to fallback ones, because there is no supported OS found. 
    packageAmount = exec("echo 0");
    os = "Unknown";
    std::cout << secondaryColor << "No supported OS found." << std::endl;
}

int main() {
    checkOS();

    if(!os.empty()) {
        if(displayHostname) {
            std::cout << secondaryColor << exec("echo $USER@$HOSTNAME");
        }

        if(displayOperatingSystem) {
            std::cout << primaryColor << " os ~ " << secondaryColor << os << std::endl; 
        }

        if(displayShell) {
            std::cout << primaryColor << " sh ~ " << secondaryColor << exec("echo $SHELL"); 
        }

        if(displayPackages) {
            std::cout << primaryColor << " pkgs ~ " << secondaryColor << packageAmount;
        }

        if(displayTerminal) {
            std::cout << primaryColor << " term ~ " << secondaryColor << exec("pstree -sA $$ | awk -F \"---\" '{print $2}'").substr(0, 10);
        }

        if(displayKernelVersion) {
           std::cout << primaryColor << " kernel ~ " << secondaryColor << kernelVersion;       
        }
    }


    return 0;
}
