#ifndef SMART_CALC_DEPOSIT_MODEL_H_
#define SMART_CALC_DEPOSIT_MODEL_H_

#include <QDate>
#include <vector>

class DepositModel {
 public:
  void CalculateDeposit(const double &precent_CB, const double &precent,
                        const std::size_t &month_period, const double &sum,
                        const QVector<QPair<QDate, double>> &replenishment_info,
                        const QVector<QPair<QDate, double>> &withdraw_info,
                        const QDate &start_date,
                        const std::size_t &index_periud,
                        const bool &capitalization);
  std::vector<QDate> getResultData();
  std::vector<double> getResultPrecent();
  std::vector<double> getResultAddSum();
  std::vector<double> getResultFinalSum();
  std::vector<std::pair<double, double>> getResultTax();
  double getSum();
  double getSumPercent();
  double getTax();

 private:
  std::size_t index_periud_;
  std::size_t time_periud_;
  std::vector<QDate> result_data_;
  std::vector<double> result_precent_;
  std::vector<double> result_add_sum_;
  std::vector<double> result_final_sum_;
  std::vector<std::pair<double, double>> result_tax_;
  double sum_;
  double sum_precent_;
  double tax_;
  enum enum_periud_ { enum_every_day, enum_day, enum_mounth };
  void setIndexAndTimePeriod(const std::size_t &index_periud);
  bool HaveWithdrawOrRreplenishment(
      const QDate &interest_start_date, const int &day,
      const std::size_t kCountWithdraw, const std::size_t kCountReplenishment,
      double &sum_add, const QVector<QPair<QDate, double>> &replenishment_info,
      const QVector<QPair<QDate, double>> &withdraw_info);
  void Reset();
  bool NeedReplenishmentOfBalance(const int &day, const int &count_day,
                                  const QDate &interest_start_date,
                                  const QDate &current_date,
                                  const std::size_t &month_period,
                                  const std::size_t &difference_day);
  double CalculateDifferentDay(const QDate &interest_start_date,
                               const int &end_day_in_start_mounth);
  void CalculateTaxAndRecord(const int &year, double &income_in_year,
                             const double &not_tax_sum);
  void HandleSumPrecent(const bool &capitalization, double &sum_add,
                        double &sum_precent_accrued);
};

#endif  // SMART_CALC_DEPOSIT_MODEL_H_