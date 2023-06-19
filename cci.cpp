#include "cci.hpp"
#include <iostream>

int main0() {
    CCI<float> cci;

    for(unsigned i = 0; i < 10; i++)
        try {
            std::cout << (100 * i) << ":" << 
            cci.integrate(1e-6, 1 - 1e-6, 100 * i, 
                [](float x) { return log(x); })
            << std::endl;
        }catch(CCIException& e) {
            std::cout << e.what() << std::endl;
        }
    return 0;
}

int main(int argc, char **argv) {
    CCI<float> cci;

    try {
        std::cout << "SAI(f) = " <<
            cci.simpleadi(0, 2*M_PI, 100, [](float x) { return sin(x); })
            << std::endl;
        for(unsigned i = 0; i < cci.getconvn().size(); i++)
            std::cout << cci.getconvn()[i] << ", " 
                      << cci.getconv()[i] << std::endl;
    }catch(CCIException& e) {
        std::cout << e.what() << std::endl;
    }
}