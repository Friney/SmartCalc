#include <QString>
#include <QVector>
#include <iostream>

#include "../presenters/calculatePresenter.h"
#include "../models/calculateModel.h"
#include "gtest/gtest.h"

class TestCalculate : public testing::Test {
 public:
  TestCalculate() : controller(&model) {}
  CalculateModel model;
  CalculatePresenter controller;
  std::string string_input;
  QString string_output;
  QPair<QVector<double>, QVector<double>> coordinates;
  double answer;
};

TEST_F(TestCalculate, a_lot_of_brackets) {
  string_input = "(((((((((((((((((((1)))))))))))))))))))";
  answer = controller.Calculations(string_input, 1);
  ASSERT_EQ(answer, 1);
}

TEST_F(TestCalculate, correct_calculations) {
  string_input = "(sin(x) - x^2 ++1)";
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_EQ(answer, 1);
  ASSERT_TRUE(string_output == nullptr);
  string_input = "cos(x)^2+sin(x)^2+asin(0)";
  answer = controller.Calculations(string_input, 1);
  ASSERT_EQ(answer, 1);
  string_input = "x mod (x + 1) + tan(0)";
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_EQ(answer, 0);
  ASSERT_TRUE(string_output == nullptr);
  string_input = "sqrt(4)";
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_EQ(answer, 2);
  ASSERT_TRUE(string_output == nullptr);
  string_input = "log(100)";
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_EQ(answer, 2);
  ASSERT_TRUE(string_output == nullptr);
  string_input = "acos(1)+atan(0)";
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_EQ(answer, 0);
  ASSERT_TRUE(string_output == nullptr);
  string_input = "ln(2.72) * 10";
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_EQ((int)answer, 10);
  ASSERT_TRUE(string_output == nullptr);
}

TEST_F(TestCalculate, error_calculations) {
  string_input = "(sin() - x^2 ++1)";
  string_output.clear();
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_TRUE(string_output != nullptr);
  ASSERT_ANY_THROW(model.Calculations(string_input, 0));
  string_input = "asin(5)";
  string_output.clear();
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_TRUE(string_output != nullptr);
  string_input = "acos(5)";
  string_output.clear();
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_TRUE(string_output != nullptr);
  ASSERT_ANY_THROW(model.Calculations(string_input, 0));
  string_input = "1/0";
  string_output.clear();
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_TRUE(string_output != nullptr);
  ASSERT_ANY_THROW(model.Calculations(string_input, 0));
  string_input = "ln(-1)";
  string_output.clear();
  answer = controller.Calculations(string_input, 0, &string_output);
  ASSERT_TRUE(string_output != nullptr);
  ASSERT_ANY_THROW(model.Calculations(string_input, 0));
}

TEST_F(TestCalculate, graph_calculations) {
  string_input = "x";
  string_output.clear();
  coordinates = controller.GraphCoordinates(string_input, 0, 5, &string_output);
  ASSERT_TRUE(string_output == nullptr);
  std::size_t size = coordinates.first.size();
  for (std::size_t i = 0; i < size; ++i) {
    ASSERT_EQ(coordinates.first[i], coordinates.second[i]);
  }
  string_output.clear();
  string_input = "sqrt(x)";
  string_output.clear();
  coordinates =
      controller.GraphCoordinates(string_input, -0.1, 16.1, &string_output);
  ASSERT_TRUE(string_output == nullptr);
  size = coordinates.first.size();
  for (std::size_t i = 0; i < size; ++i) {
    if (coordinates.first[i] == 0) {
      ASSERT_EQ(coordinates.second[i], 0);
    }
    if (coordinates.first[i] == 1) {
      ASSERT_EQ(coordinates.second[i], 1);
    }
    if (coordinates.first[i] == 4) {
      ASSERT_EQ(coordinates.second[i], 2);
    }
    if (coordinates.first[i] == 16) {
      ASSERT_EQ(coordinates.second[i], 4);
    }
  }
  string_input = "x/";
  string_output.clear();
  coordinates = controller.GraphCoordinates(string_input, 0, 5, &string_output);
  ASSERT_TRUE(string_output != nullptr);
  string_input = "1*-";
  coordinates =
      controller.GraphCoordinates(string_input, 0.5, 1.5, &string_output);
  ASSERT_TRUE(string_output != nullptr);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
