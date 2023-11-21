#include "calculate.hpp"
#include <iostream>

int main()
{
    using namespace std;
    Calculate Calcu;
    Calcu.getInput('2');
    Calcu.getInput('.');
    Calcu.getInput('3');
    Calcu.getInput('+');
    Calcu.getInput('4');
    Calcu.getInput('=');
    cout << Calcu.getOperand();
}

