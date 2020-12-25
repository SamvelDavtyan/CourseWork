#include "Expression.h"
#include <string>
#include <math.h>
#define pi 3.1415926535897932384626433832795
#define e 2.7182818284

using namespace std;

// checking whether a string is a constant and getting the size of the constant
size_t IsConst(string potencial_const, size_t index = 0)
{
	if (potencial_const[index] == 'p' && potencial_const[index + 1] == 'i') //pi size=2
		return 2;
	else if (potencial_const[index] == 'e') //e size=1
		return 1;
	return 0;
}

// checking whether the entered number is correct
bool IsCorrectNumber(string number)
{
	size_t count_of_signs = 0;
	for (int i = 0; i < number.size(); i++)
	{
		if (number[i] == ',')
			count_of_signs++;
	}
	if (count_of_signs > 1) return false;
	else return true;
}

// checking whether a string is an operator
bool IsOperator(string potencial_operaor, size_t index = 0)
{
	if (potencial_operaor[index] == ')' || potencial_operaor[index] == '(')
		return false;
	return (!isalpha(potencial_operaor[index]) && !isdigit(potencial_operaor[index]));
}

// checking whether a string is a number
bool IsNumber(string potencial_number)
{
	if ((potencial_number[0] >= '0' && potencial_number[0] <= '9') || (potencial_number[0] == '-' && potencial_number[1] >= '0' && potencial_number[1] <= '9') || IsConst(potencial_number))
	{
		if(IsCorrectNumber(potencial_number))
			return true;
	}		
	return false;
}

// checking whether a string is a function and getting the size of the function
size_t IsFunction(string potencial_function, size_t index = 0)
{
	if (potencial_function[index] == 's' && potencial_function[index + 1] == 'i' && potencial_function[index + 2] == 'n') //sin size=3
		return 3;
	else if (potencial_function[index] == 'c' && potencial_function[index + 1] == 'o' && potencial_function[index + 2] == 's') //cos size=3
		return 3;
	else if (potencial_function[index] == 't' && potencial_function[index + 1] == 'g') //tg size=2
		return 2;
	else if (potencial_function[index] == 'c' && potencial_function[index + 1] == 't' && potencial_function[index + 2] == 'g') //ctg size=3
		return 3;
	else if (potencial_function[index] == 'l' && potencial_function[index + 1] == 'n') //ln size=2
		return 2;	
	else if (potencial_function[index] == 'l' && potencial_function[index + 1] == 'o' && potencial_function[index + 2] == 'g') //log size=3
		return 3;	
	else if (potencial_function[index] == 's' && potencial_function[index + 1] == 'q' && potencial_function[index + 2] == 'r' && potencial_function[index + 3] == 't') //sqrt size=4
		return 4;
	else if (potencial_function[index] == 's' && potencial_function[index + 1] == 'q' && potencial_function[index + 2] == 'r') //sqr size=3
		return 3;
	return 0;
}

// getting operator priority
size_t priority_of_operators(string oper)
{
	if (IsNumber(oper) || IsFunction(oper, 0) || IsConst(oper, 0) || (oper[0] == '+' || oper[0] == '-'))
		return 0;
	if (oper[0] == '*' || oper[0] == '/')
		return 1;
	return 2;
}

// getting the prefix form of a record
void Expression::prefix_form(string infix)
{
	parts_of_expression(infix);
	List string_stack;
	for (size_t i = 0; i < example.GetSize(); i++)
	{
		if (IsNumber(example.at(i)) || IsFunction(example.at(i)))
			decision.push_back(example.at(i));
		else if (IsOperator(example.at(i)))
		{
			if (string_stack.isEmpty())
				string_stack.push_front(example.at(i));
			else if (string_stack.top() == "(")
				string_stack.push_front(example.at(i));
			else if (priority_of_operators(example.at(i)) >= priority_of_operators(string_stack.top()))
				string_stack.push_front(example.at(i));
			else
			{
				while (!string_stack.isEmpty() && string_stack.top() != "(" && priority_of_operators(example.at(i)) < priority_of_operators
				(string_stack.top()))
				{
					decision.push_back(string_stack.top());
					string_stack.pop_front();
				}
				string_stack.push_front(example.at(i));
			}
		}
		else if (example.at(i) == "(")
			string_stack.push_front(example.at(i));
		else if (example.at(i) == ")")
		{
			while (!string_stack.isEmpty() && string_stack.top() != "(")
			{
				decision.push_back(string_stack.top());
				string_stack.pop_front();
			}
			string_stack.pop_front();
		}
	}
	while (!string_stack.isEmpty())
	{
		decision.push_back(string_stack.top());
		string_stack.pop_front();
	}
	decision.reverse();
	example.clear();
}

//Output of an expression in the prefix form of a record
string Expression::print_expression()
{
	if (decision.GetSize() == 0)
	{
		decision.clear();
		throw "Error! Expression is empty.";
	}
	string result;
	for (size_t i = 0; i < decision.GetSize(); i++)
		result += decision.at(i) + " ";
	if (result.size() != 0)
		result.pop_back();
	return result;
}

// splitting an expression into parts
void Expression::parts_of_expression(string example)
{
	string tmp;
	int check;
	size_t check_frac;
	for (int i = 0; i < example.size(); i++)
	{
		tmp.clear();
		check = 0;
		if (example[i] == ' ')
			continue;
		while (((example[i] >= '0' && example[i] <= '9') || (example[i] == ',')) && i < example.size())
		{
			tmp += example[i];
			i++;
		}
		if (tmp.size() != 0)
		{
			this->example.push_back(tmp);
			i--;
			continue;
		}
		if (example[i] == '(')
			tmp += ")";
		if (example[i] == ')')
			tmp += "(";
		if (IsOperator(example,i))
			tmp += example[i];
		if (tmp.size() != 0)
		{
			this->example.push_back(tmp);
			continue;
		}
		size_t size_fun = IsFunction(example, i);
		if (size_fun > 0)
		{
			for (size_t index_fun = i; index_fun < i + size_fun; index_fun++) 
				tmp.push_back(example[index_fun]);
			size_fun--;
			do
			{
				size_fun++;
				if (example[i + size_fun] == '(')
					check++;
				if (example[i + size_fun] == ')')
					check--;
				tmp += example[i + size_fun];				
			} while (check != 0 && example.size() > i + size_fun);
			if (check != 0)
				throw "Error! Incorrect input.";
			this->example.push_back(tmp);
			i += size_fun;
			continue;
		}
		size_t size_const = IsConst(example , i); 
		if (size_const>0)
		{
			for (size_t index_const = i; index_const < i + size_const; index_const++)
				tmp.push_back(example[index_const]);
			this->example.push_back(tmp);
			i += size_const - 1;
			continue;
		}
		throw "Error! Unknown symbols.";		
	}
	for (size_t i = 0; i < this->example.GetSize(); i++)
	{
		string temp;
		if (i == 0 && this->example.at(i) == "-" && this->example.at(i + 1) != ")" && !IsFunction(this->example.at(i + 1)) && !IsOperator(this->example.at(i + 1)))
		{
			temp += this->example.at(i) + this->example.at(i + 1);
			this->example.remove(i + 1);
			this->example.set(i, temp);
		}
		else if (i == 0 && this->example.at(i) == "-" && (this->example.at(i + 1) == ")" || IsFunction(this->example.at(i + 1))))
		{
			this->example.push_front("0");
			i++;
		}
		else if (this->example.at(i) == ")" && i + 1 < this->example.GetSize() && this->example.at(i + 1) == "-" && !IsFunction(this->example.at(i + 2)))
		{
			temp += this->example.at(i + 1) + this->example.at(i + 2);
			this->example.remove(i + 1);
			this->example.set(i + 1, temp);
		}
		else if (this->example.at(i) == ")" && i + 1 < this->example.GetSize() && this->example.at(i + 1) == "-" && IsFunction(this->example.at(i + 2)))
		{
			this->example.insert("0", i + 1);
		}
	}
	this->example.reverse();
}

// getting the result when calculating a function
string to_Function(string function)
{
	string fun, arg;
	double result = 0, number;
	char check = 0;
	for (size_t i = 0; i < function.size() - 1; i++)
	{
		if (function[i] == '(' && check == 0)
		{
			check++;
			continue;
		}
		if (check)
			arg += function[i];
		else fun += function[i];
	}
	
	if (arg == "pi")
		number = pi;
	else if (arg == "e")
		number = e; 
	else if ((arg != "pi") && (arg != "e"))
	{
		Expression Argument;
		Argument.prefix_form(arg);
		arg = Argument.get_result();
		number = stod(arg);		
	}
	else number = stod(arg);
	if (fun == "cos") result = cos(number);
	else if (fun == "sin") result = sin(number);
	else if (fun == "tg") result = tan(number);
	else if (fun == "ctg") result = 1 / tan(number);
	else if (fun == "ln") result = log(number);
	else if (fun == "log") result = log10(number);
	else if (fun == "sqrt") result = sqrt(number);
	else if (fun == "sqr") result = pow(number, 2);
	else throw "Error! Incorrect function or argument.";
	return to_string(result);
}

// getting the result of expressions with a single operator
string to_Operator(string oper, string number1, string number2)
{
	double result = 0, num1, num2;
	if (number1 == "pi")
		num1 = pi;
	else if (number1 == "e")
		num1 = e;
	else num1 = stod(number1);
	if (number2 == "pi")
		num2 = pi;
	else if (number2 == "e")
		num2 = e;
	else num2 = stod(number2);
	if (oper == "+") result = num1 + num2;
	if (oper == "-") result = num1 - num2;
	if (oper == "*") result = num1 * num2;
	if (oper == "/") result = num1 / num2;
	if (oper == "^") result = pow(num1, num2);
	return to_string(result);
}

// finding the result
string Expression::get_result()
{
	string result;
	size_t check = 0;
	if (decision.GetSize() == 0)
		result = "0";
	else if (decision.GetSize() == 1)
	{
			if (IsFunction(decision.at(0)))
				decision.set(0, to_Function(decision.at(0)));
			else if (IsConst(decision.at(0)))
				if (decision.at(0) == "pi")
					result = to_string(pi);
				else result = to_string(e);
			else if (decision.at(0) == "-pi")
				result = to_string(-1 * pi);
			else if (decision.at(0) == "-e")
				result = to_string(-1 * e);
			else if (IsNumber(decision.at(0)))
				result = decision.at(0);
			else
			{
				decision.print_to_console();
				decision.clear();
				throw "Error! Incorrect function.";
			}
	}
	else if (decision.GetSize() == 2)
	{
		if ((decision.at(0) != "-" && decision.at(0) != "+") || (IsNumber(decision.at(1))))
		{
			decision.print_to_console();
			decision.clear();
			throw "Error! Extra operator.";
		}
		if (IsFunction(decision.at(1)) && decision.at(0) == "-")
		{
			decision.set(0, to_string(-1 * stod(to_Function(decision.at(1)))));
		}
		else if (IsFunction(decision.at(1)) && decision.at(0) == "+")
		{
			decision.set(0, to_Function(decision.at(1)));
		}
		decision.pop_back();
	}
	else
		while (decision.GetSize() > 1)
		{
			check = 0;
			for (size_t i = 0; i < decision.GetSize(); i++)
			{
				if (decision.GetSize() - i >= 3 && IsOperator(decision.at(i)) && IsNumber(decision.at(i + 1)) && IsNumber(decision.at(i + 2)))
				{
					decision.set(i, to_Operator(decision.at(i), decision.at(i + 1), decision.at(i + 2)));
					decision.remove(i + 1);
					decision.remove(i + 1);
					check++;
				}
				else if (IsFunction(decision.at(i)))
				{
					decision.set(i, to_Function(decision.at(i)));
					check++;
				}
				else if (decision.GetSize() == 2 && IsFunction(decision.at(1)) && decision.at(0) == "-")
				{
					check++;
					decision.set(0, to_string(-1 * stod(to_Function(decision.at(1)))));
					decision.pop_back();
				}
			}
			if (check == 0)
			{
				decision.clear();
				throw "Error! Extra operator or number.";
			}
		}
	result = decision.at(0);
	decision.clear();
	return result;
}