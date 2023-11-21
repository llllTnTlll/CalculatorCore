/*
 * calculate.cpp
 *
 *  Created on: Nov 15, 2023
 *      Author: zhiyuan
 */

#include "calculate.hpp"


void Calculate::addToSuffix(char& c) {
	suffix += c;
	if (c != ' ') {
		suffix += ' ';
	}
}

void Calculate::addToSuffix(std::string& str) {
	suffix += str;
	if (!str.empty()) {
		suffix += ' ';
	}
}

double Calculate::getNumStackValue() {
	double n = numStack.top();
	numStack.pop();
	return n;
}

void Calculate::clrStack() {
	while (!optStack.empty())
		optStack.pop();
	while (!numStack.empty())
		numStack.pop();
}

bool Calculate::isNumber(std::string& str) {
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

int Calculate::getLevel(char& opt) const {
	switch (opt) {
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
	return -1;
}

bool Calculate::doCalcu() {
	clrStack();

	size_t startPos = 0;
	size_t spacePos = suffix.find(' ', startPos);
	while (spacePos != std::string::npos) {
		std::string word = suffix.substr(startPos, spacePos - startPos);
		if (isNumber(word)) {
			numStack.push(std::stod(word));
		}
		else {
			char opt = word[0];
			switch (opt) {
			case '+': {
				if (numStack.size() >= 2) {
					double n2 = getNumStackValue();
					double n1 = getNumStackValue();
					numStack.push(n1 + n2);
				}
				else {
					return false;
				}
				break;
			}
			case '-': {
				if (numStack.size() >= 2) {
					double n2 = getNumStackValue();
					double n1 = getNumStackValue();
					numStack.push(n1 - n2);
				}
				else {
					return false;
				}
				break;
			}
			case '*': {
				if (numStack.size() >= 2) {
					double n2 = getNumStackValue();
					double n1 = getNumStackValue();
					numStack.push(n1 * n2);
				}
				else {
					return false;
				}
				break;
			}
			case '/': {
				if (numStack.size() >= 2) {
					double n2 = getNumStackValue();
					double n1 = getNumStackValue();
					numStack.push(n1 / n2);
				}
				else {
					return false;
				}
				break;
			}
			}
		}
		startPos = spacePos + 1;
		spacePos = suffix.find(' ', startPos);
	}
	if (numStack.size() == 1) {
		operand = std::to_string(numStack.top());
		clrStack();
		return true;
	}
	return false;
}

void Calculate::getInput(char opt) {
	//�������ַ���δ��ɵ�״̬����д�����ֻ�����
	if (std::isdigit(opt)) {
		operand += opt;
	}
	else {
		//����������˵����һ���������������
		addToSuffix(operand);
		operand = "";
		//��Ϊ�Ⱥſ�ʼ����
		if (opt == '=') {
			while (!optStack.empty()) {
				addToSuffix(optStack.top());
				optStack.pop();
			}
			doCalcu();
		}
		//������ֱ����ջ
		else if (opt == '(') {
			optStack.push(opt);
		}
		//�����ų�ջ��������
		else if (opt == ')') {
			while (optStack.top() != '(') {
				addToSuffix(optStack.top());
				optStack.pop();
			}
			optStack.pop();
		}
		//��Ϊ������
		else {
			while (!optStack.empty() && getLevel(opt) <= getLevel(optStack.top())) {
				addToSuffix(optStack.top());
				optStack.pop();
			}
			optStack.push(opt);
		}
	}
}

std::string Calculate::getOperand() const {
	std::string o = operand;
	return o;
}

void Calculate::setOperand(std::string s) {
	operand = s;
}

