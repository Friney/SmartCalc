#include <QApplication>

#include "models/calculateModel.h"
#include "models/depositModel.h"
#include "models/loanModel.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QLocale::setDefault(QLocale(QLocale::Russian));
  setlocale(LC_NUMERIC, "C");
  CalculateModel calculate_model;
  DepositModel deposit_model;
  LoanModel loan_model;
  CalculatePresenter calculate_controller(&calculate_model);
  DepositPresenter deposit_controller(&deposit_model);
  LoanPresenter loan_controller(&loan_model);
  View view(&calculate_controller, &loan_controller, &deposit_controller);
  view.setWindowTitle("SmartCalc");
  view.show();
  return a.exec();
}
