#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseProgram/List.cpp"
#include "../CourseProgram/Expression.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_CourseWork
{
	TEST_CLASS(TestNewFunctionsForList)
	{
	public:
		TEST_METHOD(ReverseTest1)
		{
			List test;
			test.push_back("a");
			test.push_back("b");
			test.push_back("c");
			test.reverse();
			Assert::IsTrue(test.at(0) == "c");
		}
		TEST_METHOD(ReverseTest2)
		{
			List test;
			try
			{
				test.reverse();
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Linked list is empty.");
			}
		}
		TEST_METHOD(TopTest1)
		{
			List test;
			test.push_back("a");
			test.push_back("b");
			test.push_back("c");
			Assert::IsTrue(test.top() == "a");
		}
		TEST_METHOD(TopTest2)
		{
			List test;
			try
			{
				test.top();
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Stack is empty.");
			}
		}

	};
	TEST_CLASS(TestExpression)
	{
		Expression Prefix; 
		TEST_METHOD(PrefixFormTest1)
		{
			Prefix.prefix_form("2+5");
			string test = "+ 2 5";		
			Assert::AreEqual(Prefix.print_expression(), test);
		}
		TEST_METHOD(PrefixFormTest2)
		{
			Prefix.prefix_form("(5+3)*(2+3)");
			string test = "* + 5 3 + 2 3";
			Assert::AreEqual(Prefix.print_expression(), test);
		}
		TEST_METHOD(PrefixFormTest3)
		{
			Prefix.prefix_form("tg(5)+3");
			string test = "+ tg(5) 3";
			Assert::AreEqual(Prefix.print_expression(), test);
		}
		TEST_METHOD(PrefixFormTest4)
		{
			Prefix.prefix_form("-6+5");
			string test = "+ -6 5";
			Assert::AreEqual(Prefix.print_expression(), test);
		}
		TEST_METHOD(PrefixFormTest5)
		{
			Prefix.prefix_form("tg(pi/2)+3");
			string test = "+ tg(pi/2) 3";
			Assert::AreEqual(Prefix.print_expression(), test);
		}
		TEST_METHOD(PrefixFormTest6)
		{
			Prefix.prefix_form("pi*e");
			string test = "* pi e";
			Assert::AreEqual(Prefix.print_expression(), test);
		}
		TEST_METHOD(PrefixFormTest7)
		{
			Prefix.prefix_form("5*25*125*625");
			string test = "* * * 5 25 125 625";
			Assert::AreEqual(Prefix.print_expression(), test);
		}
		TEST_METHOD(IncorrectPrefixFormTest1)
		{
			try
			{
				Prefix.prefix_form("tg(23");
			}
			catch (const char* error)
			{
				Assert::IsTrue(1);
			}
		}
		TEST_METHOD(IncorrectPrefixFormTest2)
		{
			try
			{
				Prefix.prefix_form("tg(23)+++3");
			}
			catch (const char* error)
			{
				Assert::IsTrue(1);
			}
		}
		TEST_METHOD(IncorrectPrefixFormTest3)
		{
			try
			{
				Prefix.prefix_form("avc");
			}
			catch (const char* error)
			{
				Assert::IsTrue(1);
			}
		}
		TEST_METHOD(GetResultTest1)
		{
			string test = "4.000000";
			Prefix.prefix_form("2+2");
			Assert::AreEqual(Prefix.get_result(), test);
		}
		TEST_METHOD(GetResultTest2)
		{
			string test = "-1.000000";
			Prefix.prefix_form("cos(pi)");
			Assert::AreEqual(Prefix.get_result(), test);
		}
		TEST_METHOD(GetResultTest3)
		{
			string test = "40.000000";
			Prefix.prefix_form("(5+3)*(2+3)");
			Assert::AreEqual(Prefix.get_result(), test);
		}
		TEST_METHOD(GetResultTest4)
		{
			string test = "1.000000";
			Prefix.prefix_form("sin(pi/2)");
			Assert::AreEqual(Prefix.get_result(), test);
		}
		TEST_METHOD(GetResultTest5)
		{
			string test = "2.000000";
			Prefix.prefix_form("sin(pi/2) + cos(0)");
			Assert::AreEqual(Prefix.get_result(), test);
		}
		TEST_METHOD(GetResultTest6)
		{
			string test = "1.000000";
			Prefix.prefix_form("sqr(2*5)-99");
			Assert::AreEqual(Prefix.get_result(), test);
		}
		TEST_METHOD(GetResultTest7)
		{
			string test = "1.000000";
			Prefix.prefix_form("5^(cos(pi)+3)*4*ln(e)-198/2");
			Assert::AreEqual(Prefix.get_result(), test);
		}
	};
	
}