#pragma once

#include <vector>

class __declspec(dllexport) BitUtils
{
public:
    static std::vector<char> XorSum(const std::vector<char> &left, const std::vector<char> &right);
};
