#pragma once
#include "List.h"

using namespace std;

class Expression {

public:
	void prefix_form(string infix);
	string get_result();
	string print_expression();
private:
	List decision;
	List example;

	void parts_of_expression(string example);
};