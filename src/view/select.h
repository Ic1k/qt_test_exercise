#ifndef SELECT_H
#define SELECT_H

#include <QCloseEvent>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTabBar>
#include <QtWidgets>

class Select : public QDialog {
  Q_OBJECT

 public:
  explicit Select(QString value, QDialog *parent = nullptr);
  ~Select();

 protected:
  void closeEvent(QCloseEvent *event);

 private slots:
  void onProcessListClicked(QListWidgetItem *item);
  void uploadFile();
  void downloadFile();

 private:
  QString deviceName;
  QString processName;
  QListWidget *listPdf;
  QListWidget *listBin;
  QListWidget *listProcess;
};

#endif  // SELECT_H
