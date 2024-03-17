#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "../presenters/calculatePresenter.h"
#include "../presenters/depositPresenter.h"
#include "../presenters/loanPresenter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(CalculatePresenter *cp, LoanPresenter *lp,
       DepositPresenter *dp, QWidget *parent = nullptr);
  ~View();

 private:
  Ui::View *ui;
  CalculatePresenter *calculate_presenter;
  LoanPresenter *loan_presenter;
  DepositPresenter *deposit_presenter;

 private slots:
  void input_text_button();
  void input_text_button_with_bracket();
  void on_scroll_bar_value_changed(int value);
  void on_button_clear_clicked();
  void on_button_backspace_clicked();
  void on_button_sqrt_clicked();
  void on_button_eq_clicked();
  void on_button_draw_graph_clicked();
  void on_button_funk_with_calc_clicked();
  void on_button_loan_calc_clicked();
  void on_comboBox_time_currentIndexChanged(int index);
  void on_comboBox_type_loan_currentIndexChanged(int index);
  void on_button_add_date_clicked();
  void on_button_del_replenishment_clicked();
  void on_button_del_withdraw_clicked();
  void on_button_clear_replenishment_clicked();
  void on_button_clear_withdraw_clicked();
  void on_comboBox_time_deposit_currentIndexChanged(int index);
  void on_checkBox_stateChanged(int arg1);
  void on_button_deposit_calc_clicked();
};
#endif  // MAINWINDOW_H
