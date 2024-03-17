#ifndef CPP3_SMART_CALC_DEPOSIT_CONTROLLER_H_
#define CPP3_SMART_CALC_DEPOSIT_CONTROLLER_H_

#include <QDate>
#include <vector>

#include "../models/depositModel.h"

class DepositPresenter {
 public:
  DepositPresenter(DepositModel *model) : model_(model){};
  double CalculateDeposit(
      const double &precent_CB, const double &precent,
      const std::size_t &month_period, const double &sum,
      const QVector<QPair<QDate, double>> &replenishment_info,
      const QVector<QPair<QDate, double>> &withdraw_info,
      const QDate &start_date, const std::size_t &index_period,
      const bool &capitalization, double *tax = nullptr,
      double *sum_precent = nullptr,
      QVector<QDate> *result_data_q_vector = nullptr,
      QVector<double> *result_precent_q_vector = nullptr,
      QVector<double> *result_add_sum_q_vector = nullptr,
      QVector<double> *result_final_sum_q_vector = nullptr,
      QVector<QPair<int, double>> *result_tax_q_vector = nullptr);

 private:
  DepositModel *model_;
};

#endif  // CPP3_SMART_CALC_DEPOSIT_CONTROLLER_H_