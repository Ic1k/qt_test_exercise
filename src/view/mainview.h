#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtWidgets>

#include "../controller/controller.h"
#include "select.h"

class MainView : public QWidget {
  Q_OBJECT

 public:
  MainView(vega::Controller *controller, QWidget *parent = nullptr);
  ~MainView();

 private:
  void checkConnectdb();
  void fillQlist();

  vega::Controller *controller_;
  QSqlDatabase db;
  QSqlTableModel *model;
  QListWidget *listWidget;

 private slots:
  void closeApp();
  void openWindomSelect();
};

#endif  // MAINVIEW_H
