#include "stdafx.h"
#include "CppUnitTest.h"

#include "Converter.h"

#include <string>
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TestUtils
{
public:
    static bool VerifyArray(const std::string &hex_expected, const std::string &hex_actual)
    {
        const auto expected = converter::base16_to_bytes(hex_expected);
        const auto actual = converter::base16_to_bytes(hex_actual);

        return VerifyArray(expected, actual);
    }

    static bool VerifyArray(const std::string &hex_expected, const std::vector<char> &bytes_actual)
    {
        const auto expected = converter::base16_to_bytes(hex_expected);

        return VerifyArray(expected, bytes_actual);
    }

    template<class T>
    static bool VerifyArray(const T& expected, const T& actual)
    {
        if (expected.size() != actual.size())
        {
            std::stringstream ss;
            ss << "expected size " << expected.size() << " didn't match actual size " << actual.size() << std::endl;
            failed(ss.str());
            return false;
        }
        for (size_t i = 0; i < std::min(expected.size(), actual.size()); ++i)
        {
            std::stringstream ss;
            ss << "[" << i << "]:" << converter::get_string_from_byte(actual[i]) << std::endl;
            Logger::WriteMessage(ss.str().c_str());
            if (expected[i] != actual[i])
            {
                std::stringstream ss;
                ss << "At index " << i << ": expected " << converter::get_string_from_byte(expected[i]) << ", saw " << converter::get_string_from_byte(actual[i]) << std::endl;
                failed(ss.str());
                return false;
            }
        }
        return true;
    }

private:
    static void failed(std::string && msg)
    {
        std::wstring real_msg { begin(msg), end(msg) };
        Assert::IsTrue(false, real_msg.c_str());
    }
};