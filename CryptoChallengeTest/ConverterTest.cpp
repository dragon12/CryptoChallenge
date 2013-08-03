#include "stdafx.h"
#include "CppUnitTest.h"

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

			Assert::IsTrue(verifyArray(expected_bytes, converter::base16_to_bytes(test_str)));
		}

	private:
		template<class T>
		static bool verifyArray(const T& expected, const T& actual)
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

        static void failed(std::string && msg)
        {
            std::wstring real_msg { begin(msg), end(msg) };
            Assert::IsTrue(false, real_msg.c_str());
        }
	};
}