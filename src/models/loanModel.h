#ifndef CPP3_SMART_CALC_LOAN_MODEL_H_
#define CPP3_SMART_CALC_LOAN_MODEL_H_

#include <cmath>
#include <vector>

class LoanModel {
 public:
  void CalculateAnnuityLoan(const double& sum_loan, const int& loan_term,
                            const double& interest_rate);
  void CalculateDifferentiatedLoan(const double& sum_loan, const int& loan_term,
                                   const double& interest_rate);
  double getOverpayment();
  double getTotalPayment();
  double getMonthlyPayment();
  std::vector<double> getDifferentiatedPaymentMonth();

 private:
  std::vector<double> differentiated_payment_month_;
  double monthly_payment_;
  double total_payment_;
  double overpayment_;
  double CalculateDifferentiatedLoanForMonth(std::size_t mouth, double sum_loan,
                                             std::size_t loan_term,
                                             double monthly_interest_rate);
  void Reset();
};

#endif  // CPP3_SMART_CALC_LOAN_MODEL_H_