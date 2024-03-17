#include "depositModel.h"

#include <QDate>
#include <vector>

void DepositModel::CalculateDeposit(
    const double &precent_CB, const double &precent,
    const std::size_t &month_period, const double &sum,
    const QVector<QPair<QDate, double>> &replenishment_info,
    const QVector<QPair<QDate, double>> &withdraw_info, const QDate &start_date,
    const std::size_t &index_periud, const bool &capitalization) {
  setIndexAndTimePeriod(index_periud);
  Reset();
  sum_ = sum;
  std::size_t day_in_year, difference_day = 0;
  const int kCountReplenishment = replenishment_info.size(),
            kCountWithdraw = withdraw_info.size();
  double sum_add, income_in_year = 0, sum_precent_accrued = 0,
                  not_tax_sum = 1000000 * precent_CB;
  bool need_out_inf, change_balance, replenishment_of_balance;
  QDate interest_start_date = start_date, current_date = interest_start_date;
  int end_day_in_start_mounth = current_date.day(),
      count_day = current_date.daysTo(current_date.addMonths(month_period)),
      year;
  for (int day = 0; day < count_day + 1 && sum_ > 0.001; ++day) {
    need_out_inf = false;
    sum_add = 0;
    if (day == 0) {
      sum_add = sum_;
      sum_ = 0;
      need_out_inf = true;
    } else {
      day_in_year = current_date.daysInYear();
      sum_precent_accrued += sum_ * precent / (double)day_in_year;
      if (day == count_day) {
        need_out_inf = true;
      }
    }
    change_balance = HaveWithdrawOrRreplenishment(
        interest_start_date, day, kCountWithdraw, kCountReplenishment, sum_add,
        replenishment_info, withdraw_info);
    replenishment_of_balance =
        NeedReplenishmentOfBalance(day, count_day, interest_start_date,
                                   current_date, month_period, difference_day);
    if (need_out_inf || change_balance || replenishment_of_balance) {
      if (replenishment_of_balance || need_out_inf) {
        interest_start_date = current_date;
        difference_day =
            CalculateDifferentDay(interest_start_date, end_day_in_start_mounth);
        income_in_year += sum_precent_accrued;
      }
      result_data_.push_back(current_date);
      if (replenishment_of_balance) {
        HandleSumPrecent(capitalization, sum_add, sum_precent_accrued);
      } else {
        result_precent_.push_back(0);
      }
      sum_ += sum_add;
      result_add_sum_.push_back(sum_add);
      result_final_sum_.push_back(sum_);
    }
    year = current_date.year();
    if (year != current_date.addDays(1).year() || day == count_day) {
      CalculateTaxAndRecord(year, income_in_year, not_tax_sum);
      income_in_year = 0;
    }
    current_date = current_date.addDays(1);
  }
}

std::vector<QDate> DepositModel::getResultData() { return result_data_; }

std::vector<double> DepositModel::getResultPrecent() { return result_precent_; }

std::vector<double> DepositModel::getResultAddSum() { return result_add_sum_; }

std::vector<double> DepositModel::getResultFinalSum() {
  return result_final_sum_;
}

std::vector<std::pair<double, double>> DepositModel::getResultTax() {
  return result_tax_;
}

double DepositModel::getSum() { return sum_; }

double DepositModel::getSumPercent() { return sum_precent_; }

double DepositModel::getTax() { return tax_; }

void DepositModel::setIndexAndTimePeriod(const std::size_t &index_periud) {
  if (index_periud == 0) {
    index_periud_ = enum_every_day;
    time_periud_ = 1;
  } else if (index_periud == 1) {
    index_periud_ = enum_day;
    time_periud_ = 7;
  } else {
    if (index_periud == 2) {
      time_periud_ = 1;
    } else if (index_periud == 3) {
      time_periud_ = 2;
    } else if (index_periud == 4) {
      time_periud_ = 3;
    } else if (index_periud == 5) {
      time_periud_ = 4;
    } else if (index_periud == 6) {
      time_periud_ = 6;
    } else if (index_periud == 7) {
      time_periud_ = 12;
    }
    index_periud_ = enum_mounth;
  }
}
bool DepositModel::HaveWithdrawOrRreplenishment(
    const QDate &interest_start_date, const int &day,
    const std::size_t kCountWithdraw, const std::size_t kCountReplenishment,
    double &sum_add, const QVector<QPair<QDate, double>> &replenishment_info,
    const QVector<QPair<QDate, double>> &withdraw_info) {
  bool need_out_inf = false;
  double replenishment = 0, withdraw = 0;
  QDate current_date = interest_start_date;
  current_date = current_date.addDays(day);
  if (kCountReplenishment > 0) {
    for (std::size_t i = 0; i < kCountReplenishment; ++i) {
      if (replenishment_info[i].first == current_date) {
        replenishment = replenishment_info[i].second;
        sum_add += replenishment;
        need_out_inf = true;
      }
    }
  }
  if (kCountWithdraw > 0) {
    for (std::size_t i = 0; i < kCountWithdraw; ++i) {
      if (withdraw_info[i].first == current_date) {
        withdraw = withdraw_info[i].second;
        sum_add -= withdraw;
        need_out_inf = true;
      }
    }
  }
  return need_out_inf;
}

void DepositModel::Reset() {
  result_add_sum_.clear();
  result_data_.clear();
  result_final_sum_.clear();
  result_precent_.clear();
  result_tax_.clear();
  sum_ = 0;
  tax_ = 0;
  sum_precent_ = 0;
}

bool DepositModel::NeedReplenishmentOfBalance(
    const int &day, const int &count_day, const QDate &interest_start_date,
    const QDate &current_date, const std::size_t &month_period,
    const std::size_t &difference_day) {
  bool replenishment_of_balance =
      index_periud_ == enum_every_day || day == count_day ||
      interest_start_date.addMonths(month_period) == current_date ||
      (index_periud_ == enum_day &&
       interest_start_date.addDays(time_periud_) == current_date) ||
      (index_periud_ == enum_mounth &&
       interest_start_date.addMonths(time_periud_).addDays(difference_day) ==
           current_date);
  return replenishment_of_balance;
}

double DepositModel::CalculateDifferentDay(const QDate &interest_start_date,
                                           const int &end_day_in_start_mounth) {
  double difference_day;
  if (interest_start_date.daysInMonth() >= end_day_in_start_mounth) {
    difference_day = 0;
  } else {
    difference_day =
        end_day_in_start_mounth - interest_start_date.daysInMonth();
  }
  return difference_day;
}

void DepositModel::CalculateTaxAndRecord(const int &year,
                                         double &income_in_year,
                                         const double &not_tax_sum) {
  if (income_in_year - not_tax_sum >= 0.009) {
    double now_tax;
    income_in_year -= not_tax_sum;
    now_tax = income_in_year * 0.13;
    tax_ += now_tax;
    result_tax_.push_back(std::pair<int, double>(year, now_tax));
  }
}

void DepositModel::HandleSumPrecent(const bool &capitalization, double &sum_add,
                                    double &sum_precent_accrued) {
  sum_precent_ += sum_precent_accrued;
  result_precent_.push_back(sum_precent_accrued);
  if (capitalization) {
    sum_add += sum_precent_accrued;
  }
  sum_precent_accrued = 0;
}
