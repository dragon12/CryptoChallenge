// CryptoChallenge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Converter.h"

#include <iostream>
#include <string>

template<typename T>
std::ostream &operator <<(std::ostream &os, const std::vector<T> &v) {
	using namespace std;
	copy(v.begin(), v.end(), ostream_iterator<T>(os, ""));
	return os;
}

int main(int argc, char argv [])
{
	std::cout << "hi" << std::endl;

	std::string hex_str{ "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" };
	std::cout << "hex : 0x" << hex_str << std::endl;

	const auto bytes = converter::base16_to_bytes(hex_str);
	std::cout << "t : " << converter::get_binary_string(bytes) << std::endl;
	std::cout << "size of bytes: " << bytes.size() << std::endl;

	std::cout << "back to hex: 0x" << converter::bytes_to_base16(bytes) << std::endl;

	std::cout << "in base64: " << converter::bytes_to_base64(bytes) << std::endl;
	std::cout << "hex to base64 to hex: " << converter::bytes_to_base16(converter::base64_to_bytes(converter::bytes_to_base64(converter::base16_to_bytes(hex_str)))) << std::endl;
}

