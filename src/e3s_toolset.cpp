#include "../include/e3s_toolset.hpp"

std::vector<std::string> e3s_toolset_tokenize(const std::string& str, const char del) {

    std::vector<std::string> tokens;

    std::stringstream check(str);

    std::string intermediate;

    while(std::getline(check, intermediate, del))
    {
        tokens.push_back(intermediate);
    }
    
    return tokens;
}


bool e3s_toolset_is_number(const std::string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    
    return true;
}


bool e3s_toolset_is_shuttle_id(const std::string& str) {
    return (e3s_toolset_is_number(str) && str.size() == 1 && stoi(str) > 0 && stoi(str) < 7);
}


std::string e3s_toolset_path_parser(const std::string& path) {
    return path.substr(path.rfind('/') + 1);
}


bool e3s_toolset_is_park_slot(uint8_t park_slot){
    if(park_slot > 0 and park_slot < 7)
        return true;
    else
        return false;
}


void e3s_toolset_fatal_exit(std::string explanation){
    std::cout << "Fatal Error: " << explanation << std::endl;
    exit(EXIT_FAILURE);
}

std::wstring e3s_toolset_to_wstring(const std::string& str)
{
    std::wstring wideString = 
        std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
    return wideString;
}
