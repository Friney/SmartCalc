#ifndef CPP3_SMART_CALC_LOAN_CONTROLLER_H_
#define CPP3_SMART_CALC_LOAN_CONTROLLER_H_

#include <QVector>
#include <cmath>
#include <vector>

#include "../models/loanModel.h"
class LoanPresenter {
 public:
  LoanPresenter(LoanModel* m) : model_(m) {}
  double CalculateAnnuityLoan(const double& sum_loan, const int& loan_term,
                              const double& interest_rate,
                              double* monthly_payment = nullptr,
                              double* overpayment = nullptr);
  double CalculateDifferentiatedLoan(const double& sum_loan,
                                     const int& loan_term,
                                     const double& interest_rate,
                                     QVector<double>* monthly_payment = nullptr,
                                     double* overpayment = nullptr);

 private:
  LoanModel* model_;
};

#endif  // CPP3_SMART_CALC_LOAN_CONTROLLER_H_