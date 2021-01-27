#include "color.h"

// color scheme
static const Color::Modifier primaryColor(Color::FG_DEFAULT);
static const Color::Modifier secondaryColor(Color::FG_BLUE);

// toggleable fields
// the hostname is retrieved using $HOSTNAME
static const bool displayHostname(true);

// the kernel version is retrieved using 'uname -r'
static const bool displayKernelVersion(true);

// the operating system is checked using the `/etc/relases` file
static const bool displayOperatingSystem(true);

// the shell is retrieved using $SHELL
static const bool displayShell(true);

// the amount of packages is OS-specific
static const bool displayPackages (true);

// the terminal is retrieved using a pstree command and piping it through awk
static const bool displayTerminal(true);
