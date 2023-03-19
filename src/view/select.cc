#include "select.h"



Select::Select(QString value, QDialog *parent)
    : QDialog(parent),
      value_(value)

{
qDebug() << value_;
}

Select::~Select() {}
