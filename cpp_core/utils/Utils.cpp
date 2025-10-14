#include "Utils.hpp"

std::string Utils::formatTime(time_t t) {
    struct tm* timeinfo = localtime(&t);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buf);
}

std::string Utils::intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string Utils::toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::list<std::string> Utils::split(const std::string& str, char delim) {
    std::list<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}
