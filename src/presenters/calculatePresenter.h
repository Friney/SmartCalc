#ifndef CPP3_SMART_CALC_CALCULATE_CONTROLLER_H_
#define CPP3_SMART_CALC_CALCULATE_CONTROLLER_H_

#define _USE_MATH_DEFINES
#include <QString>
#include <QVector>
#include <cmath>
#include <iomanip>
#include <map>
#include <stack>
#include <string_view>

#include "../models/calculateModel.h"

class CalculatePresenter {
 public:
  CalculatePresenter(CalculateModel *m) : model_(m){};
  double Calculations(const std::string &string_input, const double &x,
                      QString *error_message = nullptr);
  QPair<QVector<double>, QVector<double>> GraphCoordinates(
      const std::string &string_input, const double &x_min, const double &x_max,
      QString *error_message = nullptr);

 private:
  CalculateModel *model_;
};

#endif  // CPP3_SMART_CALC_CALCULATE_CONTROLLER_H_