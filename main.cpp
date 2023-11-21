#include "calculate.hpp"
#include <iostream>

int main()
{
    using namespace std;
    CALCULATE::Calculate Calcu;
    Calcu.getInput('2');
    Calcu.getInput('*');
    Calcu.getInput('(');
    Calcu.getInput('3');
    Calcu.getInput('+');
    Calcu.getInput('5');
    Calcu.getInput(')');
    Calcu.getInput('+');
    Calcu.getInput('7');
    Calcu.getInput('/');
    Calcu.getInput('1');
    Calcu.getInput('-');
    Calcu.getInput('4');
    Calcu.getInput('=');
    cout << Calcu.getOperand();
}

