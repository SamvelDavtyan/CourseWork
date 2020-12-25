#include <iostream>
#include <fstream>
#include "Expression.h"

using namespace std;

int main()
{
	Expression expression;
	string s;
	cout << "Hello! Welcome to the calculator program.\nEnter the expression you want to calculate: ";
	getline(cin, s);
	try 
	{
		expression.prefix_form(s);
		cout << "The entered expression in the prefix form of the entry: " << expression.print_expression() << endl;
		cout << "The result of the calculation: " << expression.get_result() << endl;
	}
	catch (const char* error)
	{
		cout << error << endl;
	}	
}