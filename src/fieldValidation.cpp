/**
 * Provides functionality for validating and processing user inputs
 * @author Lachlan Charteris
*/

#include <string>
#include <vector>

/**
 * Validates if an equation is typed correctly
 * @param equation The equation to process
 * @return The results of the equation in the form of a 
*/
std::string validateEquationLogic(std::string equation) {
  float result = 0;
  std::vector<std::string> components, special = {"sin", "cos", "tan", "e", "pi", "sqrt"};
  std::string operators = "^*/+-%", openBrackets = "({[", closeBrackets = ")}]";
  return "Equation Validation Not Yet Supported";
}

/**
 * Validates whether a string is purely numerical or not
 * @param input The input string to be validated
*/
std::string validateNumeric(std::string input) {
  for (char c : input)
    if (c != '-' && c != '.' && !isdigit(c)) 
      return "Input Must Be Numeric";
  return "";
}

/**
 * Returns true if there are equally distributed parenthesis within the equation
 * @param input The input equation in the form of a string
 * @return True if brackets match
*/
std::string validateBrackets(std::string input) {
  std::string parenthesis = "";
  for (char c : input) {
    if (c == '(') parenthesis += c;
    else if (c == ')') {
      if (parenthesis.empty()) return "Too Many Trailing Brackets";
      else parenthesis.pop_back();
    }
  }
  return parenthesis.empty() ? "" : "Too Many Leading Brackets";
}