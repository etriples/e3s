#ifndef E3S_TOOLSET_HPP
#define E3S_TOOLSET_HPP

#include "e3s.hpp"
#include "e3s_shuttle.hpp"


std::vector<std::string> e3s_toolset_tokenize(const std::string& str, const char del);

bool e3s_toolset_is_number(const std::string& str);

bool e3s_toolset_is_shuttle_id(const std::string& str);

std::string e3s_toolset_path_parser(const std::string& path);

void e3s_toolset_fatal_exit(std::string explanation);

bool e3s_toolset_is_park_slot(uint8_t park_slot);

std::wstring e3s_toolset_to_wstring(const std::string& str);


#endif