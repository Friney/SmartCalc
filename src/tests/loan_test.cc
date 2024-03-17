#include <QVector>

#include "../presenters/loanPresenter.h"
#include "../models/loanModel.h"
#include "gtest/gtest.h"

class TestLoan : public testing::Test {
 public:
  TestLoan() : controller(&model) {}
  LoanModel model;
  LoanPresenter controller;
  QVector<double> monthly_payment_differentiated;
  double total_payment, overpayment, monthly_payment;
};

TEST_F(TestLoan, annuity_loan) {
  total_payment = controller.CalculateAnnuityLoan(
      1000000000, 12, 5, &monthly_payment, &overpayment);
  ASSERT_EQ(85607481, (int)monthly_payment);
  ASSERT_EQ(27289781, (int)overpayment);
  ASSERT_EQ(1027289781, (int)total_payment);
  total_payment = controller.CalculateAnnuityLoan(10000, 12, 5);
  ASSERT_EQ(10272, (int)total_payment);
}

TEST_F(TestLoan, differentiated_loan) {
  total_payment = controller.CalculateDifferentiatedLoan(
      1000000000, 4, 5, &monthly_payment_differentiated, &overpayment);
  ASSERT_EQ(254166666, (int)monthly_payment_differentiated[0]);
  ASSERT_EQ(253125000, (int)monthly_payment_differentiated[1]);
  ASSERT_EQ(252083333, (int)monthly_payment_differentiated[2]);
  ASSERT_EQ(251041666, (int)monthly_payment_differentiated[3]);
  ASSERT_EQ(10416666, (int)overpayment);
  ASSERT_EQ(1010416666, (int)total_payment);
  total_payment = controller.CalculateDifferentiatedLoan(1000000000, 15, 5);
  ASSERT_EQ(1033333333, (int)total_payment);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
