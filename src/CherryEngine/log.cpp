#include <ostream>

#include <CherryEngine/log.h>
#include "log/logbuf.h"


std::ostream info(new LogBuf(INFO));
std::ostream warning(new LogBuf(WARNING));
std::ostream error(new LogBuf(ERROR));
