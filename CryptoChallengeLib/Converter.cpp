
#include "stdafx.h"

#include "Converter.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <cctype>

const char converter::base16 [] = { "0123456789abcdef" };
const char converter::base64 [] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };

std::string converter::get_binary_string(const std::vector<char> &bytes)
{
	std::stringstream result;
	for (auto c : bytes)
	{
		result << get_string_from_byte(c);
	}
	return result.str();
}

std::string converter::get_string_from_byte(char b)
{
	std::stringstream result;
	for (auto i = 7; i >= 0; --i)
	{
		result << ((b >> i) & 0x1);
	}
	return result.str();
}

std::vector<char> converter::base16_to_bytes(const std::string &hex_str)
{
	std::vector<char> result;

	const auto end_str = end(hex_str);
	auto iter = begin(hex_str);

	//if it's an odd length then special case to deal with first character
	if (hex_str.size() % 2 == 1)
	{
		result.push_back(base16_to_byte(*iter++));
	}
	for (; iter < end_str; iter += 2)
	{
		result.push_back((base16_to_byte(*iter) << 4) | base16_to_byte(*(iter + 1)));
	}
	return result;
}

char converter::base16_to_byte(char c)
{
    const auto lc = std::tolower(c);
	return (lc >= '0' && lc <= '9') ? (lc - '0') : (lc - 'a' + 10);
}

std::vector<char> converter::base64_to_bytes(const std::string &hex_str)
{
	std::vector<char> result;
	for (auto i : hex_str)
	{
		if (i == '+')
		{
            result.push_back(62);
		}
        else if (i == '/')
        {
            result.push_back(63);
        }
		if (i >= '0' && i <= '9')
		{
			result.push_back(i - '0');
		}
		else
		{
			result.push_back(std::tolower(i) - 'a' + 10);
		}
	}
	return result;
}

std::string converter::bytes_to_base16(const std::vector<char> &bytes)
{
	std::stringstream result;
	for (auto c : bytes)
	{
		result << (base16[(c >> 4) & 0xF]);
		result << (base16[c & 0xF]);
	}
	return result.str();
}

std::string converter::bytes_to_base64(const std::vector<char> &bytes)
{
	std::stringstream result;

	//3 bytes are 4 characters
	for (auto char_iter = begin(bytes); char_iter < end(bytes); char_iter += 3)
	{
		int triple = (*char_iter) << 16;
		if (std::distance(char_iter, end(bytes)) > 1)
		{
			triple |= (*(char_iter + 1)) << 8;
		}
		if (std::distance(char_iter, end(bytes)) > 2)
		{
			triple |= *(char_iter + 2);
		}
		result << base64[(triple >> 18) & 0x3F];
		result << base64[(triple >> 12) & 0x3F];
		result << base64[(triple >> 6) & 0x3F];
		result << base64[triple & 0x3F];
	}
	return result.str();
}
