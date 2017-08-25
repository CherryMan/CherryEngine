#pragma once

#include <iostream>
#include <sstream>
#include <streambuf>


extern std::ostream status;
extern std::ostream warning;
extern std::ostream error;

enum LogLevel {
    STATUS,
    WARNING,
    ERROR,
};

class LogBuf : public std::streambuf {

public:
    LogBuf(LogLevel lvl);

    int overflow(int c);

    const LogLevel log_lvl;

private:
    std::string curr_str = "";

    unsigned short lines_count = 0;
    unsigned short lines_to_flush;

    // TODO: remove once better logging implemented
    std::string prefix;
};
