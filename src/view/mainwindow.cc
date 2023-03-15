#include "view/mainwindow.h"

#include "ui_mainwindow.h"

namespace vega {
MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }
};  // namespace vega
