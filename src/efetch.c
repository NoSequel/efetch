#include <iostream>
#include <unistd.h>
#include <array>
#include <regex>
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

    return result;
}

void checkOS() {
    os = exec("cat /etc/os-release");
    kernelVersion = exec("echo -n \"$(uname -r)\"");

    // begin OS name checking
    // BSD operating systems
    if(os.find("FreeBSD") != std::string::npos) {
        os = "FreeBSD"; 
    // linux distros
    } else if(os.find("Gentoo") != std::string::npos) {
        os = "Gentoo";
    } else if(os.find("Arch") != std::string::npos) {
        os = "Arch Linux";
    } else if(os.find("Void") != std::string::npos) {
        os = "Void Linux";
    } else if(os.find("Ubuntu") != std::string::npos) {
        os = "Ubuntu";
    } else if(os.find("Manjaro") != std::string::npos) {
        os = "Manjaro";
    } else if(os.find("Debian") != std::string::npos) {
       os = "Debian";
    } else {
        // if the method hasn't returned yet, set the variables to fallback ones, because there is no supported OS found. 
        os = osName;
    }
}

// gets all packages for all supported operating systems
std::string getPackages() {
    std::string packages = "";

    if(access("/usr/bin/emerge", 0) == 0) {
       packages.append(exec("echo -n $(cd /var/db/pkg && ls -d */* | wc -l)"));
       packages.append(" (emerge) ");
    }

    if(access("/usr/bin/pacman", 0) == 0) {
       packages.append(exec("echo -n $(pacman -Qq | wc -l)"));
       packages.append(" (pacman) ");
    }

    if(access("/usr/bin/xbps-install", 0) == 0) {
        packages.append(exec("echo -n $(xbps-query -l | wc -l)"));
        packages.append(" (xbps) ");
    }

    if(access("/usr/sbin/pkg_info", 0) == 0) {
        packages.append(exec("echo -n $(pkg_info | wc -l)"));
        packages.append(" (pkg) ");
    }

    if(access("/usr/bin/dpkg-query", 0) == 0) {
        packages.append(exec("echo -n $(dpkg-query -f '.\n' -W | wc -l)"));
        packages.append(" (dpkg) ");
    }

    // fallback for if no package manager could be found, lists all programs
    // installed under /usr/bin
    if(packages.empty() && access("/usr/bin", 0) == 0) {
        packages.append(exec("echo -n $(ls /usr/bin | wc -l)"));
    }

    return packages;
}

// method to handle the printing of the information
void print(const char* str1, const char* str2) {
    if(str1 && str1[0]) {
        std::cout << primaryColor << " " << str1 << " ~ ";
    }

    std::cout << secondaryColor << str2 << resetColor << std::endl;
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
            print("sh", std::regex_replace(exec("printf $SHELL"), std::regex("\\/bin/"), "").c_str());
        }

        if(displayPackages) {
            print("pkgs", getPackages().c_str());
        }

        if(displayKernelVersion) {
            print("kernel", kernelVersion.c_str());
        }
    }


    return 0;
}
