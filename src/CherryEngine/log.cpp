#include <ostream>

#include <CherryEngine/log.h>
#include "log/logbuf.h"


std::ostream info(new LogBuf(INFO));
std::ostream warn(new LogBuf(WARN));
std::ostream error(new LogBuf(ERROR));
