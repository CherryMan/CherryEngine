#include <CherryEngine/log.h>


std::ostream info(new LogBuf(INFO));
std::ostream warning(new LogBuf(WARNING));
std::ostream error(new LogBuf(ERROR));

LogBuf::LogBuf(LogLevel lvl) : log_lvl(lvl) {
    curr_str.reserve(72);

    // Number of lines to output
    // before flushing
    switch (log_lvl) {

        case INFO:
            prefix = "[INFO] ";
            lines_to_flush = 5;
            break;

        case WARNING:
            prefix = "[WARNING] ";
            lines_to_flush = 2;
            break;

        case ERROR:
            prefix = "[ERROR] ";
            lines_to_flush = 1;
            break;
    }
}

int LogBuf::overflow(int c) {
    // Convert int to char
    char ch = (char) c;

    // If next char is a newline, output
    if (ch == '\n') {

        // TODO: more sophisticated method
        // involving logfiles and coloured output
        std::cout << prefix
                  << curr_str
                  << '\n';

        curr_str = "";

        if (lines_count == lines_to_flush) {
            std::cout << std::flush;
            lines_count = 0;
        }

    } else {
        curr_str += ch;
    }

    ++lines_count;

    return 0;
}


