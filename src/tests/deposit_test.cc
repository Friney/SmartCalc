#include <QDate>
#include <QVector>
#include <iostream>

#include "../presenters/depositPresenter.h"
#include "../models/depositModel.h"
#include "gtest/gtest.h"

class TestDeposit : public testing::Test {
 public:
  TestDeposit() : controller(&model) {}
  DepositModel model;
  DepositPresenter controller;
  QVector<QPair<QDate, double>> replenishment_date;
  QVector<QPair<QDate, double>> withdraw_date;
  double precent = 0, sum = 0, sum_precent = 0, tax = 0;
  int month_period = 0, index_periud = 0;
  QVector<QDate> result_data_q_vector;
  QVector<double> result_precent_q_vector;
  QVector<double> result_add_sum_q_vector;
  QVector<double> result_final_sum_q_vector;
  QVector<QPair<int, double>> result_tax_q_vector;
  QDate start_date;
};

TEST_F(TestDeposit, calculate_deposit) {
  start_date = QDate::fromString("10.02.2024", "dd.MM.yyyy");
  sum = controller.CalculateDeposit(
      0.16, 0.05, 15, 1000000000, replenishment_date, withdraw_date, start_date,
      7, false, &tax, &sum_precent, &result_data_q_vector,
      &result_precent_q_vector, &result_add_sum_q_vector,
      &result_final_sum_q_vector, &result_tax_q_vector);
  ASSERT_EQ(1000000000, (int)sum);
  ASSERT_EQ(8066126, (int)tax);
  ASSERT_EQ(62207126, (int)sum_precent);
  ASSERT_TRUE(QDate::fromString("10.02.2024", "dd.MM.yyyy") ==
              result_data_q_vector[0]);
  ASSERT_TRUE(QDate::fromString("10.02.2025", "dd.MM.yyyy") ==
              result_data_q_vector[1]);
  ASSERT_TRUE(QDate::fromString("10.05.2025", "dd.MM.yyyy") ==
              result_data_q_vector[2]);
  ASSERT_EQ(0, (int)result_precent_q_vector[0]);
  ASSERT_EQ(50015345, (int)result_precent_q_vector[1]);
  ASSERT_EQ(12191780, (int)result_precent_q_vector[2]);
  ASSERT_EQ(1000000000, (int)result_add_sum_q_vector[0]);
  ASSERT_EQ(0, (int)result_add_sum_q_vector[1]);
  ASSERT_EQ(0, (int)result_add_sum_q_vector[2]);
  ASSERT_EQ(1000000000, (int)result_final_sum_q_vector[0]);
  ASSERT_EQ(1000000000, (int)result_final_sum_q_vector[1]);
  ASSERT_EQ(1000000000, (int)result_final_sum_q_vector[2]);
  ASSERT_EQ(2025, result_tax_q_vector[0].first);
  ASSERT_EQ(8066126, (int)result_tax_q_vector[0].second);
}

TEST_F(TestDeposit, calculate_deposit_with_capitalization) {
  start_date = QDate::fromString("10.02.2024", "dd.MM.yyyy");
  sum = controller.CalculateDeposit(
      0.16, 0.05, 15, 1000000000, replenishment_date, withdraw_date, start_date,
      7, true, &tax, &sum_precent, &result_data_q_vector,
      &result_precent_q_vector, &result_add_sum_q_vector,
      &result_final_sum_q_vector, &result_tax_q_vector);
  ASSERT_EQ(1062816902, (int)sum);
  ASSERT_EQ(8145397, (int)tax);
  ASSERT_EQ(62816902, (int)sum_precent);
  ASSERT_TRUE(QDate::fromString("10.02.2024", "dd.MM.yyyy") ==
              result_data_q_vector[0]);
  ASSERT_TRUE(QDate::fromString("10.02.2025", "dd.MM.yyyy") ==
              result_data_q_vector[1]);
  ASSERT_TRUE(QDate::fromString("10.05.2025", "dd.MM.yyyy") ==
              result_data_q_vector[2]);
  ASSERT_EQ(0, (int)result_precent_q_vector[0]);
  ASSERT_EQ(50015345, (int)result_precent_q_vector[1]);
  ASSERT_EQ(12801556, (int)result_precent_q_vector[2]);
  ASSERT_EQ(1000000000, (int)result_add_sum_q_vector[0]);
  ASSERT_EQ(50015345, (int)result_add_sum_q_vector[1]);
  ASSERT_EQ(12801556, (int)result_add_sum_q_vector[2]);
  ASSERT_EQ(1000000000, (int)result_final_sum_q_vector[0]);
  ASSERT_EQ(1050015345, (int)result_final_sum_q_vector[1]);
  ASSERT_EQ(1062816902, (int)result_final_sum_q_vector[2]);
  ASSERT_EQ(2025, result_tax_q_vector[0].first);
  ASSERT_EQ(8145397, (int)result_tax_q_vector[0].second);
}

TEST_F(TestDeposit, calculate_deposit_with_replenishment_and_withdraw) {
  start_date = QDate::fromString("10.02.2024", "dd.MM.yyyy");
  replenishment_date.append(QPair<QDate, double>(
      QDate::fromString("17.02.2024", "dd.MM.yyyy"), 500000));
  withdraw_date.append(QPair<QDate, double>(
      QDate::fromString("07.02.2025", "dd.MM.yyyy"), 1500000));
  sum = controller.CalculateDeposit(
      0.16, 0.05, 15, 1000000, replenishment_date, withdraw_date, start_date, 7,
      false, &tax, &sum_precent, &result_data_q_vector,
      &result_precent_q_vector, &result_add_sum_q_vector,
      &result_final_sum_q_vector, &result_tax_q_vector);
  ASSERT_EQ(0, (int)sum);
  ASSERT_EQ(3, result_data_q_vector.size());
  ASSERT_TRUE(QDate::fromString("10.02.2024", "dd.MM.yyyy") ==
              result_data_q_vector[0]);
  ASSERT_TRUE(QDate::fromString("17.02.2024", "dd.MM.yyyy") ==
              result_data_q_vector[1]);
  ASSERT_TRUE(QDate::fromString("07.02.2025", "dd.MM.yyyy") ==
              result_data_q_vector[2]);
  ASSERT_EQ(1000000, (int)result_add_sum_q_vector[0]);
  ASSERT_EQ(500000, (int)result_add_sum_q_vector[1]);
  ASSERT_EQ(-1500000, (int)result_add_sum_q_vector[2]);
  ASSERT_EQ(1000000, (int)result_final_sum_q_vector[0]);
  ASSERT_EQ(1500000, (int)result_final_sum_q_vector[1]);
  ASSERT_EQ(0, (int)result_final_sum_q_vector[2]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
