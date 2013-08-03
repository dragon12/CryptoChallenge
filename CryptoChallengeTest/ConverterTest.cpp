#include "stdafx.h"
#include "CppUnitTest.h"

#include "Converter.h"

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

	};
}