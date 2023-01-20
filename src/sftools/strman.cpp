#include "sftools/str/strman.hpp"
#include <algorithm>


void to_lowers(std::string& data){
    std::transform(data.begin(), data.end(), data.begin(), 
        [](unsigned char c){ return tolower(c); });
}


void split_str(const std::string& str, const char delimiter, std::vector<std::string>& out){
    std::string tmp = "";

    for(char c : str){
        if(c == delimiter){
            out.push_back(tmp);
            tmp = "";
        }else{
            tmp += c;
        }
    }

    if(tmp != "") out.push_back(tmp);
}


