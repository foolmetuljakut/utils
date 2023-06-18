#include <iostream>

#include "logger.hpp"
using namespace CTF;

#include "connector/reader.hpp"
#include "connector/writer.hpp"

int main(int argc, char **argv) {
    LoggingRegion r(Styles::Blue, Styles::Regular, 
        {"A", "B"}, std::cout);

    r.log("A", "lolA");
    r.log("B", "lolB");
    r.log("C", "lolC");
    return 0;
}