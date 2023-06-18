#ifndef logger_hpp
#define logger_hpp

#include <iostream>

#include <string>
#include <sstream>
#include <vector>
#include <ostream>

namespace CTF {
    namespace Styles {
        enum Style {
            Regular = 0,
            Bold = 1,
            Italic = 3,
            Underline = 4
        };

        enum Color {
            Gray = 30,
            Orange = 31,
            Green = 32,
            Yellow = 33,
            Blue = 34,
            Purple = 35,
            Cyan = 36,
            White = 37
        };

        std::string compose(Styles::Style s, Styles::Color c);
    };

    class LoggingRegion {
        std::vector<std::string> keywords;
        std::ostream& stream;
        Styles::Color color;
        Styles::Style style;

        void write(std::string s);
    public:
        LoggingRegion(
            Styles::Color color,
            Styles::Style style,
            std::initializer_list<std::string> keywords,
            std::ostream& stream);
        
        bool checkkey(std::string s);
        bool log(std::string key, std::string s);
    };

    class Logger {
        // something like this
        // static auto dbg = LoggingRegion(Styles::Blue, Styles::Regular, 
        // {"A", "B"}, std::cout);
    };
};


#endif //logger_hpp