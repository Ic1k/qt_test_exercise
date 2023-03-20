#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtWidgets>

#include "../controller/main_controller.h"
#include "../controller/select_controller.h"


class MainView : public QWidget {
  Q_OBJECT

 public:
  MainView(vega::MainController *mainController, vega::SelectController *SelectController, QWidget *parent = nullptr);
  ~MainView();

 private:
  void checkConnectdb();
  void fillQlist();

  vega::MainController *mainController_;
  vega::SelectController *selectController_;
  QSqlDatabase db;
  QSqlTableModel *model;
  QListWidget *listWidget;

 private slots:
  void closeApp();
  void openWindomSelect();
};

#endif  // MAINVIEW_H
