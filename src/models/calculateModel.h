#ifndef SMART_CALC_CALCULATE_MODEL_H_
#define SMART_CALC_CALCULATE_MODEL_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <map>
#include <stack>
#include <string_view>

class CalculateModel {
 public:
  void Calculations(const std::string &string_input, const double &x);
  void DoPolishNotationString(const std::string &string_input);
  void Account(const double &x);
  double getAnswer() { return answer_; }

 private:
  std::stack<double> stack_operand_;
  std::stack<char> stack_operator_;
  std::string polish_notation_;
  std::size_t count_unclosed_bracket_;
  double answer_;
  bool it_is_digit_;
  struct FunctionInfo {
    std::size_t type;
    std::size_t length;
  };
  void PushOperandInString(const double &value);
  void PushSymbolInString(const char &symbol);
  std::size_t getOperationPriority(const char &operand);
  void HandleSymbolOperation(char &symbol);
  std::size_t getTypeSymbol(const char &symbol);
  double PerformOperation(const char &symbol, double &oper_1, double &oper_2);
  void ProcessOperation(const char &symbol);
  void FinalAccount(const double &x);
  std::size_t getFunctionTypeChecking(std::size_t &operation_length,
                                      const std::string_view &str_view,
                                      std::size_t &index);
  void ParseNumber(const std::string_view &string_input, std::size_t &index);
  void ParseFuctionWithOneOperand(const std::string_view &string_input,
                                  std::size_t &index);
  void HandleNonNumberSymbol(const std::size_t type, char symbol,
                             const std::string_view &string_input,
                             std::size_t &index);
  void ParseFuctionMod(const std::string_view &string_input,
                       std::size_t &index);
  void ConvertToPolishNotation(const std::string_view &string_input);
  void StacksClearing();
};

#endif  // SMART_CALC_CALCULATE_MODEL_H_