#include <iostream>
#include <unistd.h>
#include <array>
#include "color.h"

// variables
std::string os;
std::string packageAmount;
std::string kernelVersion;

// color scheme
Color::Modifier primary(Color::FG_DEFAULT);
Color::Modifier secondary(Color::FG_BLUE);

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

    // check if the string contains the string "BSD"
    if(os.find("BSD") != std::string::npos) {
        if(os.find("FreeBSD") != std::string::npos) {
            packageAmount = exec("pkg_info | wc -l");
            os = "FreeBSD/BSD";
        }
    } else if(os.find("Linux") != std::string::npos) {
        if(os.find("Gentoo") != std::string::npos) {
            packageAmount = exec("cd /var/db/pkg && ls -d */* | wc -l");
            os = "Gentoo/Linux";
        }
    }
}

int main() {
    checkOS();

    if(!os.empty()) {
        std::cout << secondary << exec("echo $USER@$HOSTNAME");
        std::cout << primary << " os ~ " << secondary << os << std::endl; 
        std::cout << primary << " sh ~ " << secondary << exec("echo $SHELL"); 
        std::cout << primary << " pkgs ~ " << secondary << packageAmount;
        std::cout << primary << " term ~ " << secondary << exec("pstree -sA $$ | awk -F \"---\" '{print $2}'").substr(0, 10);
        std::cout << primary << " kernel ~ " << secondary << kernelVersion;       
    }


    return 0;
}
