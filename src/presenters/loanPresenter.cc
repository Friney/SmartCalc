#include <QVector>
#include <cmath>
#include <vector>

#include "loanPresenter.h"

double LoanPresenter::CalculateAnnuityLoan(const double& sum_loan,
                                           const int& loan_term,
                                           const double& interest_rate,
                                           double* monthly_payment,
                                           double* overpayment) {
  double total_payment;
  model_->CalculateAnnuityLoan(sum_loan, loan_term, interest_rate);
  if (monthly_payment != nullptr) {
    *monthly_payment = model_->getMonthlyPayment();
  }
  if (overpayment != nullptr) {
    *overpayment = model_->getOverpayment();
  }
  total_payment = model_->getTotalPayment();
  return total_payment;
}

double LoanPresenter::CalculateDifferentiatedLoan(
    const double& sum_loan, const int& loan_term, const double& interest_rate,
    QVector<double>* monthly_differentiated, double* overpayment) {
  double total_payment;
  std::vector<double> monthly_differentiated_pay_std_vector;
  model_->CalculateDifferentiatedLoan(sum_loan, loan_term, interest_rate);
  total_payment = model_->getTotalPayment();
  if (overpayment != nullptr) {
    *overpayment = model_->getOverpayment();
  }
  if (monthly_differentiated != nullptr) {
    monthly_differentiated_pay_std_vector =
        model_->getDifferentiatedPaymentMonth();
    *monthly_differentiated =
        QVector<double>(monthly_differentiated_pay_std_vector.begin(),
                        monthly_differentiated_pay_std_vector.end());
  }
  return total_payment;
}
