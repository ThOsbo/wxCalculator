#include <calculate.h>

std :: string PerformCalculation :: GetResult(std :: string toCalc) 
{
    std :: regex bracReg("\\([^\\(\\)]+\\)");
    toCalc = std :: regex_replace(toCalc, bracReg, "[$&]");

    return EvaluateExpression(toCalc);
}

std :: string PerformCalculation :: EvaluateExpression(std :: string expression) 
{
    std :: regex numReg("\\d+(\\.\\d+)?");

    return std :: regex_replace(expression, numReg, "[$&]");
}

std :: string PerformCalculation :: Add(int num1, int num2) 
{
    return std :: to_string(num1 + num2);
}

std :: string PerformCalculation :: Minus(int num1, int num2) 
{
    return std :: to_string(num1 - num2);
}

std :: string PerformCalculation :: Multiply(int num1, int num2) 
{
    return std :: to_string(num1 * num2);
}

std :: string PerformCalculation :: Divide(int num1, int num2) 
{
    return std :: to_string(num1 / num2);
}