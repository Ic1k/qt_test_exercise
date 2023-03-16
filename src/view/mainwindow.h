#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QFile>

#include "validation.h"
#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace vega {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();


private slots:
    void on_btn_edit_clicked();





 private:
  Controller *controller_;
  QSqlDatabase db;
QSqlTableModel *model;
  Ui::MainWindow *ui;
  Validation *va_{nullptr};
};

}  // namespace vega
#endif  // MAINWINDOW_H
