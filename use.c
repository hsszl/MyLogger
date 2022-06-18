#include <stdio.h>
#include "logger.h"

int main() {
    init("try", INFO);
    trace("trace");
    debug("debug");
    info("info");
    warning("warning");
    error("error");
    exception("exception");
}
