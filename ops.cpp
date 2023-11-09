#include "ops.h"
#include <iostream>

static std::stack<char> optstack;
static std::stack<double> numstack;

static int level(char opt)
{
	switch (opt) 
	{
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case ')':
		return 3;
	}
}

template <typename T>
static void clrStack(std::stack<T>& stack) {
	while (!stack.empty())
		stack.pop();
}

static bool isNumber(const std::string& str) {
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool transfer(std::string& before, std::string& after) {

	for (int i = 0; i <= before.length(); ++i) {
		//若为数字直接填入后缀表达式
		char c = before[i];
		if (isdigit(c)) {
			after += c;
			after += ' ';
		}

		//若为左括号入栈
		else if (c == '(') {
			optstack.push(c);
		}

		//若为右括号则出栈至左括号
		else if (c == ')') {
			while (optstack.top() != '(') {
				after += optstack.top();
				after += ' ';
				optstack.pop();
			}
			optstack.pop();
		}

		//若为操作符 
		else {
			while (!optstack.empty() && level(c) <= level(optstack.top())) {
				after += optstack.top();
				after += ' ';
				optstack.pop();
			}
			optstack.push(c);
		}
	}
	clrStack<char>(optstack);
	return true;
}

bool caculate(std::string& before) {
	using namespace std;
	string after;
	transfer(before, after);

	size_t startPos = 0;
	size_t spacePos = after.find(' ', startPos);

	while (spacePos != string::npos) {

		string word = after.substr(startPos, spacePos - startPos);
		if (isNumber(word)){
			try {
				numstack.push(stof(word));
			}
			catch (const invalid_argument& e) {
				cerr << "Invalid argument: " << e.what() << endl;
				break;
			}
			catch (const out_of_range& e) {
				cerr << "Out of range: " << e.what() << endl;
				break;
			}
			catch (...) {
				cerr << "Unexpected error occurred." << endl;
				break;
			}
		}
		else {
			char opt = word[0];
			switch(opt) {
			case '+': {
				if (numstack.size() >= 2) {
					double n2 = getStackValue(numstack);
					double n1 = getStackValue(numstack);
					numstack.push(n1 + n2);
				}
				else {
					return false;
				}
				break;
			}
			case '-': {
				if (numstack.size() >= 2) {
					double n2 = getStackValue(numstack);
					double n1 = getStackValue(numstack);
					numstack.push(n1 - n2);
				}
				else {
					return false;
				}
				break;
			}
			case '*': {
				if (numstack.size() >= 2) {
					double n2 = getStackValue(numstack);
					double n1 = getStackValue(numstack);
					numstack.push(n1 * n2);
				}
				else {
					return false;
				}
				break;
			}
			case '/': {
				if (numstack.size() >= 2) {
					double n2 = getStackValue(numstack);
					double n1 = getStackValue(numstack);
					numstack.push(n1 / n2);
				}
				else {
					return false;
				}
				break;
			}
			}
		}
		startPos = spacePos + 1;
		spacePos = after.find(' ', startPos);
	}

	if (numstack.size() == 1) {
		cout << numstack.top();
		clrStack<double>(numstack);
		return true;
	}
	else {
		cerr << "Invalid expression: Not enough operators or too many operands." << endl;
		return false;
	}
}

