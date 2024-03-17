#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <map>
#include <stack>
#include <string_view>

#include "calculatePresenter.h"

double CalculatePresenter::Calculations(const std::string &string_input,
                                        const double &x,
                                        QString *error_message) {
  try {
    model_->Calculations(string_input, x);
    return model_->getAnswer();
  } catch (const std::exception &e) {
    *error_message = e.what();
    return 0;
  }
}

QPair<QVector<double>, QVector<double>> CalculatePresenter::GraphCoordinates(
    const std::string &string_input, const double &x_min, const double &x_max,
    QString *error_message) {
  QPair<QVector<double>, QVector<double>> coordinates;
  int n;
  double h, answer, x;
  try {
    model_->DoPolishNotationString(string_input);
    model_->Account(0.5);
    n = 50000;
    h = (x_max - x_min) / n;
    x = x_min;
    for (int i = 0; i < n + 1; ++i) {
      if (x <= x_max) {
        try {
          model_->Account(x);
          answer = model_->getAnswer();
          coordinates.first.push_back(x);
          coordinates.second.push_back(answer);
        } catch (const std::exception &e) {
          coordinates.first.push_back(x);
          coordinates.second.push_back(qQNaN());
        }
        x += h;
      }
    }
    return coordinates;
  } catch (const std::exception &e) {
    coordinates.first.clear();
    coordinates.second.clear();
    *error_message = e.what();
    return coordinates;
  }
}