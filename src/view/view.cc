#include "view.h"

#include "ui_mainwindow.h"

View::View(CalculatePresenter *cp, LoanPresenter *lp,
           DepositPresenter *dp, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::View),
      calculate_presenter(cp),
      loan_presenter(lp),
      deposit_presenter(dp) {
  ui->setupUi(this);
  ui->date_add_or_del->setDate(QDate::currentDate());
  ui->date_start_deposit->setDate(QDate::currentDate());
  QScrollBar *scrollBar = new QScrollBar(Qt::Orientation::Vertical, this);
  ui->listWidget_result_data->setVerticalScrollBar(scrollBar);
  ui->listWidget_result_precent->setVerticalScrollBar(scrollBar);
  ui->listWidget_result_add_sum->setVerticalScrollBar(scrollBar);
  ui->listWidget_result_final_sum->setVerticalScrollBar(scrollBar);
  connect(scrollBar, SIGNAL(valueChanged(int)), this,
          SLOT(on_scroll_bar_value_changed(int)));
  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_x, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_e, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_mult, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_div, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_sin, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_asin, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_cos, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_acos, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_tan, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_atan, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_ln, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_log, SIGNAL(clicked()), this,
          SLOT(input_text_button_with_bracket()));
  connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(input_text_button()));
  connect(ui->button_bracket_opening, SIGNAL(clicked()), this,
          SLOT(input_text_button()));
  connect(ui->button_bracket_closing, SIGNAL(clicked()), this,
          SLOT(input_text_button()));
}

View::~View() { delete ui; }

void View::input_text_button() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->label_input->text() == "0") {
    ui->label_input->setText(button->text());
  } else {
    ui->label_input->setText(ui->label_input->text() + button->text());
  }
}

void View::on_button_sqrt_clicked() {
  if (ui->label_input->text() == "0") {
    ui->label_input->setText("sqrt(");
  } else {
    ui->label_input->setText(ui->label_input->text() + "sqrt(");
  }
}

void View::input_text_button_with_bracket() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->label_input->text() == "0") {
    ui->label_input->setText(button->text() + "(");
  } else {
    ui->label_input->setText(ui->label_input->text() + button->text() + "(");
  }
}

void View::on_button_clear_clicked() { ui->label_input->setText("0"); }

void View::on_button_backspace_clicked() {
  QString string = ui->label_input->text();
  if (string.length() == 1 ||
      (string.length() == 2 && string.first(1) == "-")) {
    ui->label_input->setText("0");
  } else if (string.right(3) == ui->button_ln->text() + "(" ||
             string.right(3) == ui->button_mod->text()) {
    string = string.remove(string.length() - 3, 3);
    if (string.length() == 0) {
      ui->label_input->setText("0");
    } else {
      ui->label_input->setText(string);
    }
  } else if (string.right(5) == ui->button_acos->text() + "(" ||
             string.right(5) == ui->button_asin->text() + "(" ||
             string.right(5) == ui->button_atan->text() + "(" ||
             string.right(5) == "sqrt(") {
    string = string.remove(string.length() - 5, 5);
    if (string.length() == 0) {
      ui->label_input->setText("0");
    } else {
      ui->label_input->setText(string);
    }
  } else if (string.right(4) == ui->button_cos->text() + "(" ||
             string.right(4) == ui->button_sin->text() + "(" ||
             string.right(4) == ui->button_tan->text() + "(" ||
             string.right(4) == ui->button_log->text() + "(") {
    string = string.remove(string.length() - 4, 4);
    if (string.length() == 0) {
      ui->label_input->setText("0");
    } else {
      ui->label_input->setText(string);
    }
  } else {
    string = string.remove(string.length() - 1, 1);
    if (string.length() == 0) {
      ui->label_input->setText("0");
    } else {
      ui->label_input->setText(string);
    }
  }
}

void View::on_button_eq_clicked() {
  std::string string_in = ui->label_input->text().toStdString();
  double x;
  bool x_ok;
  x = ui->line_x->text().toDouble(&x_ok);
  QString str_out;
  if (x_ok) {
    double answer = calculate_presenter->Calculations(string_in, x, &str_out);
    if (str_out == Q_NULLPTR) {
      str_out = QString().setNum(answer, 'g', 7);
    }
  } else {
    str_out = "Некорректное выражение";
  }
  ui->line_output->setText(str_out);
}

void View::on_button_draw_graph_clicked() {
  ui->widget_graph->clearGraphs();
  double x_min = 0, x_max = 0, y_min = 0, y_max = 0;
  bool is_normal_coordinates;
  QPair<QVector<double>, QVector<double>> coordinates;
  std::string string = ui->line_input_graph->text().toStdString();
  std::string string_input = ui->line_input_graph->text().toStdString();
  QString string_output;
  x_max = ui->line_max_x->text().toDouble(&is_normal_coordinates);
  if (is_normal_coordinates) {
    x_min = ui->line_min_x->text().toDouble(&is_normal_coordinates);
  }
  if (is_normal_coordinates) {
    y_max = ui->line_max_y->text().toDouble(&is_normal_coordinates);
  }
  if (is_normal_coordinates) {
    y_min = ui->line_min_y->text().toDouble(&is_normal_coordinates);
  }
  if (x_min < x_max && y_min < y_max && is_normal_coordinates) {
    ui->label_check_correct->setText("");
    ui->widget_graph->xAxis->setRange(x_min, x_max);
    ui->widget_graph->yAxis->setRange(y_min, y_max);
    coordinates = calculate_presenter->GraphCoordinates(string_input, x_min,
                                                         x_max, &string_output);
  } else {
    string_output = "Некорректные области";
  }
  if (string_output == Q_NULLPTR) {
    ui->widget_graph->addGraph();
    ui->widget_graph->graph(0)->addData(coordinates.first, coordinates.second);
    ui->widget_graph->replot();
    ui->widget_graph->setInteraction(QCP::iRangeZoom, true);
    ui->widget_graph->setInteraction(QCP::iRangeDrag, true);
  } else {
    ui->label_check_correct->setText(string_output);
  }
  coordinates.first.clear();
  coordinates.second.clear();
}

void View::on_button_funk_with_calc_clicked() {
  ui->line_input_graph->setText(ui->label_input->text());
}

void View::on_button_loan_calc_clicked() {
  ui->label_error_loan->setText("");
  ui->listWidget_monthly_pay->clear();
  int loan_term = 0, time_index = 0, loan_index = 0;
  double sum_loan, interest_rate, monthly_payment, total_payment = 0,
                                                   overpayment = 0;
  bool is_normal_numbers;
  sum_loan = ui->line_sum_loan->text().toDouble(&is_normal_numbers);
  if (is_normal_numbers) {
    loan_term = ui->line_time_loan->text().toInt(&is_normal_numbers);
  }
  if (is_normal_numbers) {
    interest_rate = ui->line_precent_loan->text().toDouble(&is_normal_numbers);
  }
  time_index = ui->comboBox_time->currentIndex();
  if (time_index == 1) {
    loan_term *= 12;
  }
  if (is_normal_numbers && loan_term > 0 && sum_loan > 0 && interest_rate > 0) {
    loan_index = ui->comboBox_type_loan->currentIndex();
    if (loan_index == 0) {
      total_payment = loan_presenter->CalculateAnnuityLoan(
          sum_loan, loan_term, interest_rate, &monthly_payment, &overpayment);
      ui->listWidget_monthly_pay->addItem(
          QString().setNum(monthly_payment, 'f', 2));
      ui->line_total_pay->setText(QString().setNum(total_payment, 'f', 2));
      ui->line_overpay->setText(QString().setNum(overpayment, 'f', 2));
    } else {
      QVector<double> monthly_differentiated_pay;
      total_payment = loan_presenter->CalculateDifferentiatedLoan(
          sum_loan, loan_term, interest_rate, &monthly_differentiated_pay,
          &overpayment);
      for (int i = 0; i < loan_term; ++i) {
        ui->listWidget_monthly_pay->addItem(
            "Месяц " + QString().setNum(i + 1) + ": " +
            QString().setNum(monthly_differentiated_pay[i], 'f', 2));
      }
      ui->line_total_pay->setText(QString().setNum(total_payment, 'f', 2));
      ui->line_overpay->setText(QString().setNum(overpayment, 'f', 2));
    }
  } else {
    ui->label_error_loan->setText("Некорректные данные");
  }
}

void View::on_comboBox_time_currentIndexChanged(int index) {
  int loan_term;
  bool is_normal_numbers;
  loan_term = ui->line_time_loan->text().toInt(&is_normal_numbers);
  if (is_normal_numbers) {
    if (index == 0) {
      loan_term *= 12;
      ui->line_time_loan->setText(QString().number(loan_term));
    } else {
      loan_term /= 12;
      ui->line_time_loan->setText(QString().number(loan_term));
    }
  } else {
    ui->line_time_loan->setText("");
  }
}

void View::on_comboBox_type_loan_currentIndexChanged(int index) {
  ui->listWidget_monthly_pay->clear();
  ui->line_total_pay->setText("");
  ui->line_overpay->setText("");
  if (index == 0) {
    ui->listWidget_monthly_pay->setMaximumHeight(35);
  } else {
    ui->listWidget_monthly_pay->setMaximumHeight(300000);
  }
}

void View::on_button_del_replenishment_clicked() {
  int index = ui->listWidget_replenishment_date->currentIndex().row();
  delete ui->listWidget_replenishment_date->item(index);
  delete ui->listWidget_replenishment_sum->item(index);
}

void View::on_button_del_withdraw_clicked() {
  int index = ui->listWidget_withdraw_date->currentIndex().row();
  delete ui->listWidget_withdraw_date->item(index);
  delete ui->listWidget_withdraw_sum->item(index);
}

void View::on_button_clear_replenishment_clicked() {
  ui->listWidget_replenishment_date->clear();
  ui->listWidget_replenishment_sum->clear();
}

void View::on_button_clear_withdraw_clicked() {
  ui->listWidget_withdraw_date->clear();
  ui->listWidget_withdraw_sum->clear();
}

void View::on_button_add_date_clicked() {
  int index;
  double sum;
  bool is_normal_numbers;
  index = ui->comboBox__add_or_del->currentIndex();
  sum = ui->line_sum_add_or_del->text().toDouble(&is_normal_numbers);
  QString string_date = ui->date_add_or_del->text();
  if (is_normal_numbers) {
    if (index == 0) {
      ui->listWidget_replenishment_date->addItem(string_date);
      ui->listWidget_replenishment_sum->addItem(QString().number(sum));
    } else {
      ui->listWidget_withdraw_date->addItem(string_date);
      ui->listWidget_withdraw_sum->addItem(QString().number(sum));
    }
  }
}

void View::on_comboBox_time_deposit_currentIndexChanged(int index) {
  int loan_term;
  bool is_normal_numbers;
  loan_term = ui->line_time_deposit->text().toInt(&is_normal_numbers);
  if (is_normal_numbers) {
    if (index == 0) {
      loan_term *= 12;
      ui->line_time_deposit->setText(QString().number(loan_term));
    } else {
      loan_term /= 12;
      ui->line_time_deposit->setText(QString().number(loan_term));
    }
  } else {
    ui->line_time_deposit->setText("");
  }
}

void View::on_checkBox_stateChanged(int arg1) {
  if (arg1 == Qt::Checked) {
    ui->comboBox_period_peyment->removeItem(8);
  } else {
    ui->comboBox_period_peyment->addItem("В конце срока");
  }
}

void View::on_scroll_bar_value_changed(int value) {
  ui->listWidget_result_data->verticalScrollBar()->setValue(value);
  ui->listWidget_result_precent->verticalScrollBar()->setValue(value);
  ui->listWidget_result_add_sum->verticalScrollBar()->setValue(value);
  ui->listWidget_result_final_sum->verticalScrollBar()->setValue(value);
}

void View::on_button_deposit_calc_clicked() {
  ui->listWidget_result_data->clear();
  ui->listWidget_result_precent->clear();
  ui->listWidget_result_add_sum->clear();
  ui->listWidget_result_final_sum->clear();
  ui->listWidget_result_tax->clear();
  ui->line_sum_in_end->clear();
  ui->line_sum_precent->clear();
  ui->line_tax->clear();
  ui->label_error_deposit->setText("");
  double precent = 0, sum = 0, sum_precent = 0;
  int month_period = 0, index_periud = 0;
  bool ok_deposit = true;
  int count_replenishment = ui->listWidget_replenishment_date->count(),
      count_withdraw = ui->listWidget_withdraw_date->count();
  QVector<QPair<QDate, double>> replenishment_date;
  QVector<QPair<QDate, double>> withdraw_date;
  QStringList result_data;
  QStringList result_precent;
  QStringList result_add_sum;
  QStringList result_final_sum;
  QStringList result_tax;
  index_periud = ui->comboBox_period_peyment->currentIndex();
  QDate curent_date =
      QDate().fromString(ui->date_start_deposit->text(), "dd.MM.yyyy");
  double precent_CB = ui->line_precent_CB->text().toDouble(&ok_deposit) / 100.0;
  bool capitalization = ui->checkBox->isChecked();
  if (ok_deposit) {
    precent = ui->line_precent_deposit->text().toDouble(&ok_deposit) / 100.0;
  }
  if (ok_deposit) {
    sum = ui->line_sum_deposit->text().toDouble(&ok_deposit);
  }
  if (ok_deposit) {
    month_period = ui->line_time_deposit->text().toInt(&ok_deposit);
  }
  if (ok_deposit && month_period > 0) {
    if (count_replenishment > 0) {
      for (int i = 0; i < count_replenishment; ++i) {
        replenishment_date.append(QPair<QDate, double>(
            QDate::fromString(
                ui->listWidget_replenishment_date->item(i)->text(),
                "dd.MM.yyyy"),
            ui->listWidget_replenishment_sum->item(i)->text().toDouble()));
      }
    }
    if (count_withdraw > 0) {
      for (int i = 0; i < count_withdraw; ++i) {
        withdraw_date.append(QPair<QDate, double>(
            QDate::fromString(ui->listWidget_withdraw_date->item(i)->text(),
                              "dd.MM.yyyy"),
            ui->listWidget_withdraw_sum->item(i)->text().toDouble()));
      }
    }
    double tax = 0;
    int time_index = ui->comboBox_time->currentIndex();
    if (time_index == 1) {
      month_period *= 12;
    }

    QVector<QDate> result_data_q_vector;
    QVector<double> result_precent_q_vector;
    QVector<double> result_add_sum_q_vector;
    QVector<double> result_final_sum_q_vector;
    QVector<QPair<int, double>> result_tax_q_vector;
    sum = deposit_presenter->CalculateDeposit(
        precent_CB, precent, month_period, sum, replenishment_date,
        withdraw_date, curent_date, index_periud, capitalization, &tax,
        &sum_precent, &result_data_q_vector, &result_precent_q_vector,
        &result_add_sum_q_vector, &result_final_sum_q_vector,
        &result_tax_q_vector);
    qsizetype size;
    size = result_data_q_vector.size();
    for (qsizetype i = 0; i < size; ++i) {
      result_data.append(result_data_q_vector[i].toString("dd.MM.yyyy"));
    }

    size = result_precent_q_vector.size();
    for (qsizetype i = 0; i < size; ++i) {
      result_precent.append(
          QString().setNum(result_precent_q_vector[i], 'f', 2));
    }
    size = result_add_sum_q_vector.size();
    for (qsizetype i = 0; i < size; ++i) {
      if (result_add_sum_q_vector[i] == 0) {
        result_add_sum.append("");
      } else {
        result_add_sum.append(
            QString().setNum(result_add_sum_q_vector[i], 'f', 2));
      }
    }
    size = result_final_sum_q_vector.size();
    for (qsizetype i = 0; i < size; ++i) {
      result_final_sum.append(
          QString().setNum(result_final_sum_q_vector[i], 'f', 2));
    }
    size = result_tax_q_vector.size();
    for (qsizetype i = 0; i < size; ++i) {
      result_tax.append(
          QString().number(result_tax_q_vector[i].first) + " " +
          QString().setNum(result_tax_q_vector[i].second, 'f', 2) +
          " 1 декабря " + QString().number(result_tax_q_vector[i].first + 1));
    }

    ui->listWidget_result_data->addItems(result_data);
    ui->listWidget_result_precent->addItems(result_precent);
    ui->listWidget_result_add_sum->addItems(result_add_sum);
    ui->listWidget_result_final_sum->addItems(result_final_sum);
    ui->listWidget_result_tax->addItems(result_tax);
    ui->line_sum_in_end->setText(QString().number(sum, 'f', 2));
    ui->line_sum_precent->setText(QString().number(sum_precent, 'f', 2));
    ui->line_tax->setText(QString().number(tax, 'f', 2));
  } else {
    ui->label_error_deposit->setText("Некорректные данные");
  }
}
