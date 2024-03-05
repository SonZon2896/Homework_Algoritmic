#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <optional>
#include <ModifyBinarySearch/ModifyBinarySearch.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SearchTest
{
	TEST_CLASS(SearchTest)
	{
	public:
		
		TEST_METHOD(SearchingVectorInt)
		{
			std::vector<int> VectorInt(100);
			for (size_t i = 0; i < VectorInt.size(); ++i)
				VectorInt[i] = (i + 1) * 5;

			size_t result = 0;
			Assert::AreEqual(true, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), VectorInt[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), VectorInt[result]).value());

			result = 99;
			Assert::AreEqual(true, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), VectorInt[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), VectorInt[result]).value());

			result = 55;
			Assert::AreEqual(true, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), VectorInt[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), VectorInt[result]).value());

			Assert::AreEqual(false, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), 505).has_value());
			Assert::AreEqual(false, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), 0).has_value());
			Assert::AreEqual(false, ModifyBinarySearch(&VectorInt.front(), &VectorInt.back(), 101).has_value());
		}

		TEST_METHOD(SearchingVectorDouble)
		{
			std::vector<double> VectorDouble(100);
			for (size_t i = 0; i < VectorDouble.size(); ++i)
				VectorDouble[i] = (double)(i + 1) / 100;

			size_t result = 0;
			Assert::AreEqual(true, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), VectorDouble[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), VectorDouble[result]).value());

			result = 99;
			Assert::AreEqual(true, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), VectorDouble[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), VectorDouble[result]).value());

			result = 55;
			Assert::AreEqual(true, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), VectorDouble[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), VectorDouble[result]).value());

			Assert::AreEqual(false, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), 1.01).has_value());
			Assert::AreEqual(false, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), 0).has_value());
			Assert::AreEqual(false, ModifyBinarySearch(&VectorDouble.front(), &VectorDouble.back(), 0.151).has_value());
		}

		TEST_METHOD(SearchingArrayInt)
		{
			int ArrayInt[100];
			for (size_t i = 0; i < 100; ++i)
				ArrayInt[i] = (i + 1) * 5;

			size_t result = 0;
			Assert::AreEqual(true, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], ArrayInt[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], ArrayInt[result]).value());
			
			result = 99;
			Assert::AreEqual(true, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], ArrayInt[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], ArrayInt[result]).value());

			result = 55;
			Assert::AreEqual(true, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], ArrayInt[result]).has_value());
			Assert::AreEqual(result, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], ArrayInt[result]).value());

			Assert::AreEqual(false, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], 505).has_value());
			Assert::AreEqual(false, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], 0).has_value());
			Assert::AreEqual(false, ModifyBinarySearch(&ArrayInt, &ArrayInt[99], 101).has_value());
		}
	};
}
