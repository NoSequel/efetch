#include "color.h"

// color scheme
static const Color::Modifier primaryColor(Color::FG_DEFAULT);
static const Color::Modifier secondaryColor(Color::FG_BLUE);
static const Color::Modifier resetColor(Color::FG_WHITE);

// toggleable fields
static const bool displayHostname(true);
static const bool displayKernelVersion(true);
static const bool displayOperatingSystem(true);
static const bool displayShell(true);
static const bool displayPackages(true);

// fallback variables if no OS was found
static const char* osName("Unknown");
