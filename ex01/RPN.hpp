
#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <list>

class RPN
{
    private:
        std::list<int> _stack;
        std::string _expression;
        RPN();
    public:
        RPN(const std::string &expression);
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
        bool isValidExpression(const std::string &expression);
        int calculate(int a, int b, std::string &op);
        int operate();
};
#endif
