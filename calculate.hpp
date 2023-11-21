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
		std::string suffix;            //��׺���ʽ
		std::string operand;           //��ʾ����Ļ�ϵ���

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
		//��ȡ��������
		void getInput(char opt);
		//��ȡ��ǰ���ֻ���������
		std::string getOperand() const;
		//���õ�ǰ���ֻ���������
		void setOperand(std::string s);
};

#endif /* INC_CALCULATE_HPP_ */
