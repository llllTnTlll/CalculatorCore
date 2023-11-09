#ifndef INFIX2SUFFIX_H_
#define INFIX2SUFFIX_H_

#include <stack>
#include <string>
#include <sstream>
#include <vector>

//将中缀表达式转换为后缀表达式
bool transfer(std::string& before, std::string& after);
//计算api
bool caculate(std::string& after);

//返回运算符优先级
static int level(char opt);
//清空指定的栈
template <typename T>
static void clrStack(std::stack<T>& stack);
//出栈
inline double getStackValue(std::stack<double>& s) {
	double n = s.top();
	s.pop();
	return n;
}

#endif // !INFIX2SUFFIX_H_

