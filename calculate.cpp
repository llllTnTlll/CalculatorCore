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

float Calculate::getNumStackValue() {
	float n = numStack.top();
	numStack.pop();
	return n;
}

void Calculate::clrStack() {
	while (!optStack.empty())
		optStack.pop();
	while (!numStack.empty())
		numStack.pop();
}

bool Calculate::isNumber(const std::string& str) {
	// ���ַ�����������
	if (str.empty()) {
		return false;
	}

	// �����ַ�����'-'��'+'��ʼ
	size_t start = 0;
	if (str[0] == '-' || str[0] == '+') {
		start = 1;
	}

	bool hasDigit = false; // ���ڱ���Ƿ��Ѿ�����������
	bool hasDot = false;   // ���ڱ���Ƿ��Ѿ�������С����

	for (size_t i = start; i < str.size(); ++i) {
		if (std::isdigit(str[i])) {
			hasDigit = true;
		}
		else if (str[i] == '.' && !hasDot) {
			hasDot = true;
		}
		else {
			return false; // �����������ֻ��ظ���С���㣬����false
		}
	}
	return hasDigit; // ���ٰ���һ�����ֲ�����Ч����
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
			numStack.push(std::stof(word));
		}
		else {
			char opt = word[0];
			switch (opt) {
			case '+': {
				if (numStack.size() >= 2) {
					float n2 = getNumStackValue();
					float n1 = getNumStackValue();
					numStack.push(n1 + n2);
				}
				else {
					return false;
				}
				break;
			}
			case '-': {
				if (numStack.size() >= 2) {
					float n2 = getNumStackValue();
					float n1 = getNumStackValue();
					numStack.push(n1 - n2);
				}
				else {
					return false;
				}
				break;
			}
			case '*': {
				if (numStack.size() >= 2) {
					float n2 = getNumStackValue();
					float n1 = getNumStackValue();
					numStack.push(n1 * n2);
				}
				else {
					return false;
				}
				break;
			}
			case '/': {
				if (numStack.size() >= 2) {
					float n2 = getNumStackValue();
					float n1 = getNumStackValue();
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
	if (std::isdigit(opt) || opt == '.') {
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

