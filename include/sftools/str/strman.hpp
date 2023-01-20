#ifndef _SFT_STR_STRMAN_HPP
#define _SFT_STR_STRMAN_HPP

#include <string>
#include <vector>


void to_lowers(std::string& data);

void split_str(const std::string& str, const char delimiter, std::vector<std::string>& out);


#endif