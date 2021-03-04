#include <iostream>
#include <unistd.h>
#include <array>
#include "config.h"

// variables
std::string os;
std::string kernelVersion;

//method for executing a command and get the output
std::string exec(const char* cmd) {
    std::array<char, 16> buffer;
    std::string result;

    auto pipe = popen(cmd, "r");

    while(!feof(pipe)) {
        if(fgets(buffer.data(), 16, pipe) != nullptr) {
            result += buffer.data();
        }
    }

    return result.substr(0, 24);
}

void checkOS() {
    os = exec("cat /etc/os-release");
    kernelVersion = exec("echo -n \"$(uname -r)\"");

    // check if the OS description contains the string "BSD"
    if(os.find("BSD") != std::string::npos) {
        // check if the OS description contains "FreeBSD"
        if(os.find("FreeBSD") != std::string::npos) {
            os = "FreeBSD/BSD";
            return;
        }
    // check if the OS description contains the string "Linux"
    } else if(os.find("Linux") != std::string::npos) {
        // check if the OS description contains "Gentoo"
        if(os.find("Gentoo") != std::string::npos) {
            os = "Gentoo/Linux";
            return;

        // check if the OS description contains "Arch"
        } else if(os.find("Arch") != std::string::npos) {
            os = "Arch/Linux";
            return;

        // check if the OS description contains "Void"
        } else if(os.find("Void") != std::string::npos) {
            os = "Void/Linux";
            return;
        }
    }

    // if the method hasn't returned yet, set the variables to fallback ones, because there is no supported OS found. 
    os = osName;
}

// gets all packages for all supported operating systems
int getPackages() {
    int packages = 0;

    if(access("/usr/bin/emerge", 0) == 0) {
       packages += atoi(exec("cd /var/db/pkg && ls -d */* | wc -l").c_str());
    }

    if(access("/usr/bin/pacman", 0) == 0) {
       packages += atoi(exec("pacman -Qq | wc -l").c_str());
    }

    if(access("/usr/bin/xbps-install", 0) == 0) {
        packages += atoi(exec("xbps-query -l | wc -l").c_str());
    }

    if(access("/usr/sbin/pkg_info", 0) == 0) {
        packages += atoi(exec("pkg_info | wc -l"))
    }

    // fallback for if no package manager could be found, lists all programs
    // installed under /usr/bin
    if(packages == 0 && access("/usr/bin", 0) == 0) {
        packages += atoi(exec("ls /usr/bin | wc -l").c_str());
    }

    return packages;
}

// method to handle the printing of the information
void print(const char* str1, const char* str2) {
    if(str1 && str1[0]) {
        std::cout << primaryColor << " " << str1 << " ~ ";
    }

    std::cout << secondaryColor << str2 << std::endl;
}

int main() {
    checkOS();

    if(!os.empty()) {
        if(displayHostname) {
            print("", exec("echo -n $USER@$HOSTNAME").c_str());
        }

        if(displayOperatingSystem) {
            print("os", os.c_str());
        }

        if(displayShell) {
            print("sh", exec("printf $SHELL").c_str());
        }

        if(displayPackages) {
            print("pkgs", std::to_string(getPackages()).c_str());
        }

        if(displayKernelVersion) {
            print("kernel", kernelVersion.c_str());
        }
    }


    return 0;
}
