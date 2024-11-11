#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab10_2/Lab10_2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest)
    {
    public:

        TEST_METHOD(BinSearch_FindsStudent)
        {
            const int N = 4;
            Student students[N] = {
                {"Ivanov", I, KN, 5, 4},
                {"Petrov", II, IT, 4, 5},
                {"Sidorov", III, ME, 3, 3}
            };
            students[1].markProgramming = 5;
            students[2].markNumericalMethods = 4;
            students[3].markPedagogy = 4;


            int index = BinSearch(students, N, "Ivanov", KN, I);
            Assert::AreEqual(0, index);
        }

        TEST_METHOD(BinSearch_DoesNotFindStudent)
        {
            const int N = 4;
            Student students[N] = {
                {"Ivanov", I, KN, 5, 4},
                {"Petrov", II, IT, 4, 5},
                {"Sidorov", III, ME, 3, 3}
            };
            students[1].markProgramming = 5;
            students[2].markNumericalMethods = 4;
            students[3].markPedagogy = 4;


            int index = BinSearch(students, N, "Ivanov", IT, I);
            Assert::AreEqual(-1, index);
        }
    };
}
