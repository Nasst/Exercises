#include <string>
#include <utility>
#include <vector>

// Solution to https://www.codewars.com/kata/52e864d1ffb6ac25db00017f
// Prioritizes legilibility over compactness.

const std::string left_associative_operantions = "+-/*";

const std::string precedence_level_0 = "-+";
const std::string precedence_level_1 = "*/";

const std::string digits = "0123456789";

bool is_digit(char c);

bool is_left_associative(char operation);

enum class Comparison { Lower, Equal, Higher };

Comparison precedence_comparison(
    int nested_level1, char op1, int nested_level2, char op2);

std::string to_postfix(const std::string &infix) {
    auto nested_level = 0;
    auto result_string = std::string();
    // this is a stack of (operator, nested level) pairs
    auto operator_stack = std::vector<std::pair<char, int>>();
    for(auto it : infix)
    {
        // no switch statement, switch statements bad, this isn't much better
        // but oh well
        if(it == '(')
            nested_level += 1;
        else if(it == ')')
            nested_level -= 1;
        else if(is_digit(it))
            result_string.push_back(it);
        // from now on, we know we're dealing with an operator
        else
        {
            while(!operator_stack.empty())
            {
                auto last_op = operator_stack.back().first;
                auto last_nested_level = operator_stack.back().second;
                auto comparison_result = precedence_comparison(
                    nested_level, it, last_nested_level, last_op);
                if(comparison_result == Comparison::Lower
                    || (comparison_result == Comparison::Equal && is_left_associative(it)))
                {
                    operator_stack.pop_back();
                    result_string.push_back(last_op);
                }
                else
                    break;
            }
            operator_stack.emplace_back(std::make_pair(it, nested_level));
        }
    }
    // We may still have operators left on the stack.
    while(!operator_stack.empty())
    {
        result_string.push_back(operator_stack.back().first);
        operator_stack.pop_back();
    }
    return result_string;
}

bool is_in_string(const std::string &str, char c)
    { return str.find_first_of(c) != std::string::npos; }

bool is_digit(char c)
    { return is_in_string(digits, c); }

bool is_left_associative(char operation)
    { return is_in_string(left_associative_operantions, operation); }

int precedence_level(char operation)
{
    if(is_in_string(precedence_level_0, operation))
        return 0;
    else if(is_in_string(precedence_level_1, operation))
        return 1;
    else
        return 2;
}

Comparison precedence_comparison(
    int nested_level1, char op1, int nested_level2, char op2)
{
    if(nested_level1 < nested_level2)
        return Comparison::Lower;
    else if(nested_level1 > nested_level2)
        return Comparison::Higher;
    else
    {
        if(precedence_level(op1) < precedence_level(op2))
            return Comparison::Lower;
        else if(precedence_level(op1) > precedence_level(op2))
            return Comparison::Higher;
        else
            return Comparison::Equal;
    }
}
