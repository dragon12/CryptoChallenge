#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestUtils.h"

#include "Converter.h"
#include "BitUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CryptoChallengeTest
{
	TEST_CLASS(BitUtilsTest)
	{
	public:
		
		TEST_METHOD(XorTest1)
		{
            const auto inputHex = converter::base16_to_bytes("AAAA");
            Assert::IsTrue(TestUtils::VerifyArray("0000", BitUtils::XorSum(inputHex, inputHex)));
		}

        TEST_METHOD(XorTest2)
        {
            const auto leftInput = converter::base16_to_bytes("1111");
            const auto rightInput = converter::base16_to_bytes("2222");

            Assert::IsTrue(TestUtils::VerifyArray("3333", BitUtils::XorSum(leftInput, rightInput)));
        }

        TEST_METHOD(XorTest3)
        {
            const auto leftInput = converter::base16_to_bytes("333333");
            const auto rightInput = converter::base16_to_bytes("222222");

            Assert::IsTrue(TestUtils::VerifyArray("111111", BitUtils::XorSum(leftInput, rightInput)));
        }

        TEST_METHOD(XorTestMatasano2)
        {
            const auto left =  converter::base16_to_bytes("1c0111001f010100061a024b53535009181c");
            const auto right = converter::base16_to_bytes("686974207468652062756c6c277320657965");
            const auto expectedOutput = "746865206b696420646f6e277420706c6179";

            Assert::AreEqual(expectedOutput, converter::bytes_to_base16(BitUtils::XorSum(left, right)).c_str());
        }
	};
}