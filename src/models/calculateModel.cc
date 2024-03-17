#define _USE_MATH_DEFINES
#include "calculateModel.h"

#include <cmath>
#include <iomanip>
#include <map>
#include <stack>
#include <string_view>

void CalculateModel::Calculations(const std::string &string_input,
                                  const double &x) {
  if (string_input.empty()) {
    throw std::logic_error("string_input is empty");
  }
  polish_notation_.clear();
  StacksClearing();
  std::string_view string_input_view(string_input);
  ConvertToPolishNotation(string_input_view);
  FinalAccount(x);
  answer_ = stack_operand_.top();
  stack_operand_.pop();
}

void CalculateModel::DoPolishNotationString(const std::string &string_input) {
  polish_notation_.clear();
  std::string_view string_input_view(string_input);
  ConvertToPolishNotation(string_input_view);
}

void CalculateModel::Account(const double &x) {
  if (polish_notation_.empty()) {
    throw std::logic_error("polish_notation is empty");
  }
  StacksClearing();
  FinalAccount(x);
  answer_ = stack_operand_.top();
  stack_operand_.pop();
}

void CalculateModel::PushOperandInString(const double &value) {
  std::ostringstream number;
  number << std::setprecision(7) << std::fixed << value;
  polish_notation_ += number.str() + " ";
}

void CalculateModel::PushSymbolInString(const char &symbol) {
  polish_notation_ += symbol;
  polish_notation_ += " ";
}

std::size_t CalculateModel::getOperationPriority(const char &operand) {
  std::size_t priority = 4;
  if (operand == '-' || operand == '+') {
    priority = 2;
  }
  if (operand == '*' || operand == '/' || operand == 'm') {
    priority = 3;
  }
  return priority;
}

void CalculateModel::HandleSymbolOperation(char &symbol) {
  if (symbol != '(' && symbol != ')') {
    while (!stack_operator_.empty() && stack_operator_.top() != '(' &&
           stack_operator_.top() != ')' &&
           getOperationPriority(symbol) <=
               getOperationPriority(stack_operator_.top())) {
      char tmp = stack_operator_.top();
      stack_operator_.pop();
      PushSymbolInString(tmp);
    }
  }
  if (symbol != ')') {
    stack_operator_.push(symbol);
  } else {
    while (!stack_operator_.empty() &&
           (symbol = stack_operator_.top()) != '(') {
      stack_operator_.pop();
      PushSymbolInString(symbol);
    }
    stack_operator_.pop();
    if (!stack_operator_.empty()) {
      symbol = stack_operator_.top();
      stack_operator_.pop();
      if (symbol > 0 && symbol < 10) {
        PushSymbolInString(symbol);
      } else {
        stack_operator_.push(symbol);
      }
    }
  }
}

std::size_t CalculateModel::getTypeSymbol(const char &symbol) {
  std::size_t type = 0;
  if (it_is_digit_) {
    if (((symbol >= '0' && symbol <= '9') || symbol == '-' || symbol == '+' ||
         symbol == 'x')) {
      type = 1;
    } else if (symbol == '(') {
      type = 3;
    } else if (symbol == 's' || symbol == 'c' || symbol == 't' ||
               symbol == 'a' || symbol == 'l') {
      type = 5;
    }
  } else {
    if ((symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' ||
         symbol == '^')) {
      type = 2;
    } else if (symbol == 'm') {
      type = 6;
    } else if (symbol == ')') {
      type = 4;
    }
  }

  return type;
}

double CalculateModel::PerformOperation(const char &symbol, double &oper_1,
                                        double &oper_2) {
  double res = 0;
  if (symbol == '+') {
    res = oper_2 + oper_1;
  } else if (symbol == '-') {
    res = oper_2 - oper_1;
  } else if (symbol == '*') {
    res = oper_2 * oper_1;
  } else if (symbol == '/' || symbol == 'm') {
    if (oper_1 == 0) {
      throw std::logic_error("Деление на 0");
    } else {
      if (symbol == '/') {
        res = oper_2 / oper_1;
      } else {
        res = fmod(oper_2, oper_1);
      }
    }
  } else if (symbol == '^') {
    res = pow(oper_2, oper_1);
  } else if (symbol == 1) {
    res = cos(oper_1);
  } else if (symbol == 2) {
    res = sin(oper_1);
  } else if (symbol == 3) {
    if (fmod(abs(oper_1), M_PI) != 0 && fmod(abs(oper_1), M_PI_2) == 0) {
      throw std::logic_error(
          "Область определения tan(x) x не равен (pi/2)*x + pi*k");
    }
    res = tan(oper_1);
  } else if (symbol == 4 || symbol == 5) {
    if (oper_1 < -1 || oper_1 > 1) {
      if (symbol == 4) {
        throw std::logic_error("Область определения acos от -1 до 1");
      } else {
        throw std::logic_error("Область определения asin от -1 до 1");
      }
    } else {
      if (symbol == 4) {
        res = acos(oper_1);
      } else {
        res = asin(oper_1);
      }
    }
  } else if (symbol == 6) {
    res = atan(oper_1);
  } else if (symbol == 7) {
    if (oper_1 < 0) {
      throw std::logic_error("Калькулятор не поддерживает мнимые числа");
    } else {
      res = sqrt(oper_1);
    }
  } else if (symbol == 8 || symbol == 9) {
    if (oper_1 <= 0) {
      throw std::logic_error("Логарифм от отрицательного числа");
    } else {
      if (symbol == 8) {
        res = log(oper_1);
      } else {
        res = log10(oper_1);
      }
    }
  }
  return res;
}

void CalculateModel::ProcessOperation(const char &symbol) {
  double oper_1 = 0, oper_2 = 0, res = 0;
  if (symbol > 0 && symbol < 10) {
    oper_1 = stack_operand_.top();
    stack_operand_.pop();
  } else {
    oper_1 = stack_operand_.top();
    stack_operand_.pop();
    if (stack_operand_.empty()) {
      throw std::invalid_argument("Ошибка ввода");
    }
    oper_2 = stack_operand_.top();
    stack_operand_.pop();
  }
  res = PerformOperation(symbol, oper_1, oper_2);
  stack_operand_.push(res);
}

void CalculateModel::FinalAccount(const double &x) {
  std::string::iterator it = polish_notation_.begin();
  char symbol;
  while (it != polish_notation_.end()) {
    symbol = *it;
    if (symbol == ' ') {
    } else {
      if (*(it + 1) == ' ' && !(*it == 'x')) {
        it_is_digit_ = false;
      } else {
        it_is_digit_ = true;
      }
      if (getTypeSymbol(symbol) == 1) {
        if (symbol == 'x') {
          stack_operand_.push(x);
        } else if ((*(it + 1) == 'x')) {
          if (symbol == '-') {
            stack_operand_.push(-x);
          } else {
            stack_operand_.push(x);
          }
          ++it;
        } else {
          std::size_t size;
          stack_operand_.push(std::stof(it.base(), &size));
          it += size;
        }
      } else {
        ProcessOperation(symbol);
      }
    }
    ++it;
  }
}

std::size_t CalculateModel::getFunctionTypeChecking(
    std::size_t &operation_length, const std::string_view &str_view,
    std::size_t &index) {
  static const std::map<std::string, FunctionInfo> functions = {
      {"cos", {1, 3}}, {"tan", {3, 3}}, {"ln", {8, 2}}, {"log", {9, 3}}, {"sin", {2, 3}}, {"sqrt", {7, 4}}, {"acos", {4, 4}}, {"asin", {5, 4}}, {"atan", {6, 4}}, {"mod", {10, 3}}};

  for (const auto &kv : functions) {
    if (str_view.compare(index, kv.first.length(), kv.first) == 0) {
      operation_length = kv.second.length;
      return kv.second.type;
    }
  }

  operation_length = 0;
  return 0;
}

void CalculateModel::ParseNumber(const std::string_view &string_input,
                                 std::size_t &index) {
  double operand;
  if (string_input[index] == 'x') {
    PushSymbolInString('x');
  } else if ((string_input[index + 1] == 'x' &&
              (string_input[index] == '+' || string_input[index] == '-'))) {
    polish_notation_ += string_input[index];
    polish_notation_ += string_input[index + 1];
    polish_notation_ += " ";
    ++index;
  } else {
    std::size_t size;
    operand = std::stod(std::string(string_input.substr(index)), &size);
    index += size - 1;
    PushOperandInString(operand);
  }
}

void CalculateModel::ParseFuctionWithOneOperand(
    const std::string_view &string_input, std::size_t &index) {
  std::size_t function_type, operation_length;
  char symbol;
  if ((function_type = getFunctionTypeChecking(operation_length, string_input,
                                               index)) != 0) {
    index += operation_length;
    symbol = function_type;
    stack_operator_.push(symbol);
    if ((symbol = string_input[index]) == '(') {
      ++count_unclosed_bracket_;
      stack_operator_.push(symbol);
    } else {
      throw std::logic_error("Ошибка ввода");
    }
  } else {
    throw std::logic_error("Ошибка ввода");
  }
}

void CalculateModel::HandleNonNumberSymbol(const std::size_t type, char symbol,
                                           const std::string_view &string_input,
                                           std::size_t &index) {
  if (type == 2) {
    it_is_digit_ = true;
  } else if (type == 3) {
    ++count_unclosed_bracket_;
  } else if (type == 4) {
    --count_unclosed_bracket_;
  } else if (type == 6) {
    ParseFuctionMod(string_input, index);
  }
  HandleSymbolOperation(symbol);
}

void CalculateModel::ParseFuctionMod(const std::string_view &string_input,
                                     std::size_t &index) {
  std::size_t operation_length;
  if (getFunctionTypeChecking(operation_length, string_input, index)) {
    index += operation_length - 1;
    it_is_digit_ = true;
  } else {
    throw std::logic_error("Ошибка ввода");
  }
}

void CalculateModel::ConvertToPolishNotation(
    const std::string_view &string_input) {
  std::size_t type, index = 0;
  count_unclosed_bracket_ = 0;
  char symbol;
  it_is_digit_ = true;
  while ((symbol = string_input[index]) != '\0') {
    if (symbol == '\t' || symbol == ' ') {
    } else {
      if (!(type = getTypeSymbol(symbol))) {
        throw std::logic_error("Ошибка ввода");
      } else {
        if (type == 1) {
          it_is_digit_ = false;
          if (symbol == '+' || symbol == '-') {
            if (!((string_input[index + 1] >= '0' &&
                   string_input[index + 1] <= '9') ||
                  string_input[index + 1] == 'x' ||
                  string_input[index + 1] == '(')) {
              throw std::logic_error("Ошибка ввода");
            }
            if (string_input[index + 1] == '(') {
              // ParseNumber()
              // ParseNumber()
              // ++count_unclosed_bracket_;
              PushOperandInString(-1);
              HandleNonNumberSymbol(2, '*', string_input, index);
              HandleNonNumberSymbol(3, '(', string_input, index);
              ++index;
            }
          }
          ParseNumber(string_input, index);
        } else if (type == 5) {
          ParseFuctionWithOneOperand(string_input, index);
        } else {
          HandleNonNumberSymbol(type, symbol, string_input, index);
        }
      }
    }
    ++index;
  }
  if (count_unclosed_bracket_ != 0) {
    throw std::logic_error("Ошибка ввода");
  }
  while (!stack_operator_.empty()) {
    PushSymbolInString(stack_operator_.top());
    stack_operator_.pop();
  }
}

void CalculateModel::StacksClearing() {
  while (!stack_operator_.empty()) {
    stack_operator_.pop();
  }
  while (!stack_operand_.empty()) {
    stack_operand_.pop();
  }
}