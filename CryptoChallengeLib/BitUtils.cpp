
#include "stdafx.h"

#include "BitUtils.h"

std::vector<char> BitUtils::XorSum(const std::vector<char> &left, const std::vector<char> &right)
{
    if (left.size() != right.size())
    {
        throw std::logic_error("Length of left not the same as length of right");
    }

    std::vector<char> result (begin(left), end(left));
    for (size_t i = 0; i < right.size(); ++i)
    {
        result[i] ^= right[i];
    }

    return result;
}
