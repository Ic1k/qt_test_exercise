#ifndef SELECT_H
#define SELECT_H

#include <QDebug>
#include <QDialog>




class Select : public QDialog {
  Q_OBJECT

 public:
  explicit Select(QString value, QDialog *parent = nullptr);
  ~Select();

 protected:
 private slots:

 private:
  QString value_;
};

#endif  // SELECT_H
