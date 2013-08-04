#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestUtils.h"

#include "Converter.h"

#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CryptoChallengeTest
{		
	TEST_CLASS(ConverterTest)
	{
	public:
		
		TEST_METHOD(ConverterTest1)
		{
			Assert::AreEqual("000000010000001000000011", converter::get_binary_string({ 1, 2, 3 }).c_str());
		}

		TEST_METHOD(ConverterTestBase16ToBytes1)
		{
			const auto test_str = "89AB";
			const std::vector<char> expected_bytes = { (char)0x89, (char)0xAB };

			Assert::IsTrue(TestUtils::VerifyArray(expected_bytes, converter::base16_to_bytes(test_str)));
		}

        TEST_METHOD(ConverterTestBase16ToBytes2)
        {
            Assert::ExpectException<std::runtime_error>([]() { converter::base16_to_bytes("ABC"); });
        }

        TEST_METHOD(ConverterTestBase64ToBytes1)
        {
            const auto test_str = "IDBA";
            const std::vector<char> expected = { (char) 0x20, (char) 0x30, (char) 0x40 };
            Assert::IsTrue(TestUtils::VerifyArray(expected, converter::base64_to_bytes(test_str)));
        }

        TEST_METHOD(ConverterTestBase64ToBytes2)
        {
            Assert::ExpectException<std::logic_error>([]() { converter::base64_to_bytes("A"); });
        }

        TEST_METHOD(ConverterTestBytesToBase16)
        {
            const auto expected = "DBA976";
            Assert::AreEqual(expected, converter::bytes_to_base16(converter::base16_to_bytes(expected)).c_str(), true);
        }

        TEST_METHOD(ConverterTestBytesToBase64)
        {
            const auto expected = "IDBA";
            Assert::AreEqual(expected, converter::bytes_to_base64(converter::base64_to_bytes(expected)).c_str(), true);
        }

        TEST_METHOD(ConverterTestMatasano1)
        {
            const auto given_base16 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
            const auto given_base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

            Assert::AreEqual(given_base64, converter::bytes_to_base64(converter::base16_to_bytes(given_base16)).c_str(), L"base16 to base64");
            Assert::AreEqual(given_base16, converter::bytes_to_base16(converter::base64_to_bytes(given_base64)).c_str(), true, L"base64 to base16");
        }

	private:

	};
}