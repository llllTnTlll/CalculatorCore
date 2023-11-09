#ifndef INFIX2SUFFIX_H_
#define INFIX2SUFFIX_H_

#include <stack>
#include <string>
#include <sstream>
#include <vector>

//����׺���ʽת��Ϊ��׺���ʽ
bool transfer(std::string& before, std::string& after);
//����api
bool caculate(std::string& after);

//������������ȼ�
static int level(char opt);
//���ָ����ջ
template <typename T>
static void clrStack(std::stack<T>& stack);
//��ջ
inline double getStackValue(std::stack<double>& s) {
	double n = s.top();
	s.pop();
	return n;
}

#endif // !INFIX2SUFFIX_H_

