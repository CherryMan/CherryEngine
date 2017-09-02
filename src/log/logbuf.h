#pragma once

#include <streambuf>

enum LogLevel {
    INFO,
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
