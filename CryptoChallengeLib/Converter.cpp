
#include "stdafx.h"

#include "Converter.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <cctype>

const char converter::base16 [] = { "0123456789abcdef" };
const char converter::base64 [] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };

const char converter::base64_to_byte_lookup [] = {
/*0  */    0, 0, 0, 0, 0, 0, 0, 0,
/*8  */    0, 0, 0, 0, 0, 0, 0, 0,
/*16 */    0, 0, 0, 0, 0, 0, 0, 0,
/*24 */    0, 0, 0, 0, 0, 0, 0, 0,
/*32 */    0, 0, 0, 0, 0, 0, 0, 0,
/*40 */    0, 0, 0, 0, 0, 0, 0, 0,
/*48 */    0, 0, 0, 0, 0, 0, 0, 0,
/*56 */    0, 0, 0, 0, 0, 0, 0, 0,
/*64 */    0, 0, 0, 0, 0, 0, 0, 0,
/*72 */    0, 0, 0, 0, 0, 0, 0, 0,
/*80 */    0, 0, 0, 0, 0, 0, 0, 0,
/*88 */    0, 0, 0, 0, 0, 0, 0, 0,
/*96 */    0, 0, 0, 0, 0, 0, 0, 0,

};

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
        std::stringstream ss;
        ss << "odd size passed as hex_str: " << hex_str.size() << std::endl;
        throw std::runtime_error(ss.str());
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

static char base64_to_byte(char c)
{
    if      (c == '+') return 62;
    else if (c == '/') return 63;
    else if (c >= 'a')  return c - 'a' + 26;
    else if (c >= 'A')  return c - 'A' + 0;
    else                return c - '0' + 52;
}

std::vector<char> converter::base64_to_bytes(const std::string &str)
{
    //make sure it's a multiple of 4
    if ((str.size() % 4) != 0)
    {
        throw std::logic_error("We don't handle non-multiples of 4 chars yet");
    }

    std::vector<char> result;

    //4 characters maps to 3 bytes, 6 bytes each
    for (auto iter = begin(str); iter != end(str); iter += 4)
    {
        result.push_back(
                    ((base64_to_byte(*iter) << 2) & 0xFC) //all 6 bits of char0
                  | ((base64_to_byte(*(iter + 1)) >> 4) & 0x3)  //top 2 bits of char1
                  );
        result.push_back(
                    (base64_to_byte(*(iter + 1)) & 0xF) << 4    //3:0 of char1
                  | ((base64_to_byte(*(iter + 2)) >> 2) & 0xF)  //5:2 of char2
                  );
        result.push_back(
                    ((base64_to_byte(*(iter + 2)) & 0x3) << 6) //1:0 of char2
                  | base64_to_byte(*(iter + 3))//5:0 of char3
            );
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
