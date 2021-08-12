#ifndef CALCULATE_H
    #define CALCULATE_H

    #include <string>
    #include <vector>
    #include <regex>

    class PerformCalculation
    {
        public :
            static std :: string GetResult(std :: string toCalc);

        private : 
            static std :: string EvaluateExpression(std :: string expression);
            static std :: string Add(int num1, int num2);
            static std :: string Minus(int num1, int num2);
            static std :: string Multiply(int num1, int num2);
            static std :: string Divide(int num1, int num2);

            static std :: vector<std :: string> GetRegMatches(std :: string expression, std :: regex reg);
            static std :: string ReplaceSubstring(std :: string expression, std :: string toReplace, std :: string replaceWith);
    };

#endif