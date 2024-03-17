#include <QDate>
#include <vector>

#include "depositPresenter.h"

double DepositPresenter::CalculateDeposit(
    const double &precent_CB, const double &precent,
    const std::size_t &month_period, const double &sum,
    const QVector<QPair<QDate, double>> &replenishment_info,
    const QVector<QPair<QDate, double>> &withdraw_info, const QDate &start_date,
    const std::size_t &index_period, const bool &capitalization, double *tax,
    double *sum_precent, QVector<QDate> *result_data_q_vector,
    QVector<double> *result_precent_q_vector,
    QVector<double> *result_add_sum_q_vector,
    QVector<double> *result_final_sum_q_vector,
    QVector<QPair<int, double>> *result_tax_q_vector) {
  double final_sum;
  model_->CalculateDeposit(precent_CB, precent, month_period, sum,
                           replenishment_info, withdraw_info, start_date,
                           index_period, capitalization);
  final_sum = model_->getSum();
  *tax = model_->getTax();
  *sum_precent = model_->getSumPercent();
  if (result_data_q_vector != nullptr) {
    std::vector<QDate> result_data_std_vector = model_->getResultData();
    *result_data_q_vector = QVector<QDate>(result_data_std_vector.begin(),
                                           result_data_std_vector.end());
  }
  if (result_precent_q_vector != nullptr) {
    std::vector<double> result_precent_std_vector = model_->getResultPrecent();
    *result_precent_q_vector = QVector<double>(
        result_precent_std_vector.begin(), result_precent_std_vector.end());
  }
  if (result_add_sum_q_vector != nullptr) {
    std::vector<double> result_add_sum_std_vector = model_->getResultAddSum();
    *result_add_sum_q_vector = QVector<double>(
        result_add_sum_std_vector.begin(), result_add_sum_std_vector.end());
  }
  if (result_final_sum_q_vector != nullptr) {
    std::vector<double> result_final_sum_std_vector =
        model_->getResultFinalSum();
    *result_final_sum_q_vector = QVector<double>(
        result_final_sum_std_vector.begin(), result_final_sum_std_vector.end());
  }
  if (result_tax_q_vector != nullptr) {
    std::vector<std::pair<double, double>> result_tax_std_vector =
        model_->getResultTax();
    *result_tax_q_vector = QVector<QPair<int, double>>(
        result_tax_std_vector.begin(), result_tax_std_vector.end());
  }

  return final_sum;
}
