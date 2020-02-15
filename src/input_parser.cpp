#include <algorithm>
#include "input_parser.h"

InputParser::InputParser(int &argc, char *argv[])
{
    for (int i{1}; i < argc; ++i)
        this->tokens.push_back(std::string(argv[i]));
}

const std::string &InputParser::getStr(const std::string &option)
{
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end())
    {
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}

bool InputParser::exists(const std::string &option)
{
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}
