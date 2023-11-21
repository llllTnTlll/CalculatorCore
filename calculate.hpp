/*
 * calculate.h
 *
 *  Created on: Nov 15, 2023
 *      Author: zhiyuan
 */

#ifndef INC_CALCULATE_HPP_
#define INC_CALCULATE_HPP_

#include <stack>
#include <string>

class Calculate {
	private:
		std::string suffix;            //后缀表达式
		std::string operand;           //显示在屏幕上的数

		std::stack<char> optStack;
		std::stack<double> numStack;

		void addToSuffix(char& c);
		void addToSuffix(std::string& str);

		double getNumStackValue();
		void clrStack();
		bool isNumber(std::string& str);

		int getLevel(char& opt) const;
		bool doCalcu();
	public:
		//获取输入内容
		void getInput(char opt);
		//获取当前数字缓存区内容
		std::string getOperand() const;
		//设置当前数字缓存区内容
		void setOperand(std::string s);
};

#endif /* INC_CALCULATE_HPP_ */
