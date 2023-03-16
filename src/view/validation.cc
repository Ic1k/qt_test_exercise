#include "validation.h"

#include <QDebug>

#include "ui_validation.h"

Validation::Validation(vega::Controller *controller, QDialog *parent)
    : QDialog(parent),
      ui(new Ui::Validation),
      controller_(controller)

       {
  ui->setupUi(this);

}

Validation::~Validation() {
  delete ui;
}





