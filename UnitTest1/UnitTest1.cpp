#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>
#include "../ap12.11.1/ap12.11.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1211
{
    TEST_CLASS(UnitTest1211)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            Elem* exp = nullptr;
            initializeLibrary(exp);     
            Book book = { "UDC1", "Author1", "Title1", 2021, 1 };
            Elem* newElem = new Elem;
            newElem->book = book;
            newElem->next = nullptr;
            newElem->prev = nullptr;
            exp = newElem;

            removeBook(exp);

            assert(exp == nullptr);
        }
    };
}

