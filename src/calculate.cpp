#include <calculate.h>
#include <iostream>

std :: string PerformCalculation :: GetResult(std :: string toCalc) 
{
    std :: regex bracReg("(\\([^\\(\\)]+\\))");

    bool foundExp;

    do 
    {
        std :: vector<std :: string> subExps = GetRegMatches(toCalc, bracReg);
        foundExp = false;

        while (subExps.size() > 0) 
        {
            foundExp = true;

            std :: string subExp = subExps[subExps.size() - 1];

            //strips brackets from sub expression to evaluate
            std :: string toEvaluate = subExp;
            toEvaluate = toEvaluate.replace(toEvaluate.length() - 1, 1, "");
            toEvaluate = toEvaluate.replace(0, 1, "");

            std :: cout << toEvaluate << std :: endl;
            std :: string subExpResult = EvaluateExpression(toEvaluate);
            
            //replaces sub-expression with result
            toCalc = ReplaceSubstring(toCalc, subExp, subExpResult);

            subExps.pop_back();
        }

    } while (foundExp);

    return toCalc;
}

std :: string PerformCalculation :: EvaluateExpression(std :: string expression) 
{
    return "b";
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

std :: vector<std :: string> PerformCalculation :: GetRegMatches(std :: string expression, std :: regex reg) 
{
    auto expBegin = std :: sregex_iterator(expression.begin(), expression.end(), reg);
    auto expEnd = std :: sregex_iterator();

    std :: vector<std :: string> results;
 
    for (std :: sregex_iterator i = expBegin; i != expEnd; ++i)
    {
        std :: smatch match = *i;
        results.push_back(match.str());
    }

    return results;
}

std :: string PerformCalculation :: ReplaceSubstring(std :: string expression, std :: string toReplace, std :: string replaceWith) 
{
    int startPos = expression.find(toReplace);
    int lenToReplace = toReplace.length();

    expression.replace(startPos, lenToReplace, replaceWith);

    return expression;
}