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
            static std :: string Add(std :: string expression);
            static std :: string Minus(std :: string expression);
            static std :: string Multiply(std :: string expression);
            static std :: string Divide(std :: string expression);

            static std :: vector<std :: string> GetRegMatches(std :: string expression, std :: regex reg);
            static std :: string ReplaceSubstring(std :: string expression, std :: string toReplace, std :: string replaceWith);
    };

#endif