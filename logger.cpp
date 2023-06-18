#include "logger.hpp"

std::string CTF::Styles::compose(Styles::Style s, Styles::Color c) {
    std::stringstream str;
    str << "\033[" << s << ";" << c << "m";
    return str.str();
}

CTF::LoggingRegion::LoggingRegion(
            Styles::Color color,
            Styles::Style style,
            std::initializer_list<std::string> keywords,
            std::ostream& stream)
            : color(color), style(style), 
                stream(stream) {
    for(auto kword : keywords)
        this->keywords.push_back(kword);
}

void CTF::LoggingRegion::write(std::string s) {
        stream << CTF::Styles::compose(style, color) 
            << s
            << CTF::Styles::compose(CTF::Styles::Regular, 
                                    CTF::Styles::White)
            << std::endl;
}

bool CTF::LoggingRegion::checkkey(std::string s) {
    for(auto& key : keywords)
        if(!key.compare(s))
            return true;
    return false;
}

bool CTF::LoggingRegion::log(std::string key, std::string s) {
    bool c = checkkey(key);
    if(c)
        write(s);
    return c;
}