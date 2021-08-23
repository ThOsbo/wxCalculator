#include <calculate.h>

std :: string PerformCalculation :: GetResult(std :: string toCalc) 
{
    std :: regex bracReg(R"(\([^()]+\))");

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

            std :: string subExpResult = EvaluateExpression(toEvaluate);
            
            //replaces sub-expression with result
            toCalc = ReplaceSubstring(toCalc, subExp, subExpResult);

            subExps.pop_back();
        }

    } while (foundExp);

    toCalc = EvaluateExpression(toCalc);

    return toCalc;
}

std :: string PerformCalculation :: EvaluateExpression(std :: string expression) 
{
    std :: regex divReg(R"(\-?\d+(\.\d+)?\/\-?\d+(\.\d+)?)");

    expression = PerformOperations(expression, divReg, &Divide);

    std :: regex multReg(R"(\-?\d+(\.\d+)?x\-?\d+(\.\d+)?)");

    expression = PerformOperations(expression, multReg, &Multiply);

    std :: regex minusReg(R"(\-?\d+(\.\d+)?\-\-?\d+(\.\d+)?)");

    expression = PerformOperations(expression, minusReg, &Minus);

    std :: regex plusReg(R"(\-?\d+(\.\d+)?\+\-?\d+(\.\d+)?)");

    expression = PerformOperations(expression, plusReg, &Add);

    return expression;
}

std :: string PerformCalculation :: PerformOperations(std :: string expression, std :: regex opReg, std :: string (*PerformOperation)(std :: string)) 
{
    bool foundExp;

    do 
    {
        std :: vector<std :: string> subExps = GetRegMatches(expression, opReg);
        foundExp = false;

        while (subExps.size() > 0) 
        {
            foundExp = true;

            std :: string subExp = subExps[subExps.size() - 1];
            std :: string subExpResult = PerformOperation(subExp);
            
            //replaces sub-expression with result
            expression = ReplaceSubstring(expression, subExp, subExpResult);

            subExps.pop_back();
        }

    } while (foundExp);

    return expression;
}

std :: string PerformCalculation :: Add(std :: string expression) 
{
    int divPos = expression.find("+");

    long double num1 = std :: stof(expression.substr(0, divPos));
    long double num2 = std :: stof(expression.substr(divPos + 1, expression.length() - divPos));

    std :: string result = std :: to_string(num1 + num2);

    return result;
}

std :: string PerformCalculation :: Minus(std :: string expression) 
{
    int divPos = expression.find("-");

    long double num1 = std :: stof(expression.substr(0, divPos));
    long double num2 = std :: stof(expression.substr(divPos + 1, expression.length() - divPos));

    std :: string result = std :: to_string(num1 - num2);

    return result;
}

std :: string PerformCalculation :: Multiply(std :: string expression) 
{
    int divPos = expression.find("x");

    long double num1 = std :: stof(expression.substr(0, divPos));
    long double num2 = std :: stof(expression.substr(divPos + 1, expression.length() - divPos));

    std :: string result = std :: to_string(num1 * num2);

    return result;
}

std :: string PerformCalculation :: Divide(std :: string expression) 
{
    int divPos = expression.find("/");

    long double num1 = std :: stof(expression.substr(0, divPos));
    long double num2 = std :: stof(expression.substr(divPos + 1, expression.length() - divPos));

    std :: string result = std :: to_string(num1 / num2);

    return result;
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