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
    const auto test_str = "IDBA";
    std::cout << converter::get_binary_string(converter::base64_to_bytes(test_str)) << std::endl;
}

