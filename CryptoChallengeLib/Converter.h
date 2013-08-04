
#pragma once

#include <vector>
#include <sstream>
#include <iostream>

class __declspec(dllexport) converter
{
public:
	static std::string get_binary_string(const std::vector<char> &bytes);
    static std::string get_string_from_byte(char b);

	static std::vector<char> base16_to_bytes(const std::string &hex_str);
	static std::vector<char> base64_to_bytes(const std::string &hex_str);

	static std::string bytes_to_base16(const std::vector<char> &bytes);
	static std::string bytes_to_base64(const std::vector<char> &bytes);

private:
	static char base16_to_byte(char c);

private:
	static const char base16 [];
	static const char base64 [];

    static const char base64_to_byte_lookup [];
};
