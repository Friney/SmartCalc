#include "loanModel.h"

#include <cmath>
#include <vector>

void LoanModel::CalculateAnnuityLoan(const double& sum_loan,
                                     const int& loan_term,
                                     const double& interest_rate) {
  Reset();
  double monthly_interest_rate = interest_rate / (100 * 12);
  monthly_payment_ =
      sum_loan *
      (monthly_interest_rate * pow(1 + monthly_interest_rate, loan_term)) /
      (pow(1 + monthly_interest_rate, loan_term) - 1);
  total_payment_ = monthly_payment_ * loan_term;
  overpayment_ = total_payment_ - sum_loan;
}

void LoanModel::CalculateDifferentiatedLoan(const double& sum_loan,
                                            const int& loan_term,
                                            const double& interest_rate) {
  Reset();
  double monthly_interest_rate = interest_rate / (100 * 12);
  for (int i = 1; i <= loan_term; i++) {
    differentiated_payment_month_.push_back(CalculateDifferentiatedLoanForMonth(
        i, sum_loan, loan_term, monthly_interest_rate));
  }
  overpayment_ = total_payment_ - sum_loan;
}

double LoanModel::getOverpayment() { return overpayment_; }

double LoanModel::getTotalPayment() { return total_payment_; }

double LoanModel::getMonthlyPayment() { return monthly_payment_; }

std::vector<double> LoanModel::getDifferentiatedPaymentMonth() {
  return differentiated_payment_month_;
}
double LoanModel::CalculateDifferentiatedLoanForMonth(
    std::size_t mouth, double sum_loan, std::size_t loan_term,
    double monthly_interest_rate) {
  double differentiatedPayment =
      (sum_loan / loan_term) +
      (sum_loan - (sum_loan * (mouth - 1) / loan_term)) * monthly_interest_rate;
  total_payment_ += differentiatedPayment;
  return differentiatedPayment;
}

void LoanModel::Reset() {
  differentiated_payment_month_.clear();
  monthly_payment_ = 0;
  total_payment_ = 0;
  overpayment_ = 0;
}
