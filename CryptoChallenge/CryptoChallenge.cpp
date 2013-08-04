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
    const auto hex_in = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::cout << "hex string: " << hex_in << std::endl;
    std::cout << "base64 string: " << converter::base16_to_base64(hex_in) << std::endl;
}

