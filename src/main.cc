#include <QApplication>

#include "controller/controller.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication qapp(argc, argv);

  vega::Model model;
  vega::Controller controller(&model);
  vega::MainWindow main_windom(&controller);
  main_windom.show();
  return qapp.exec();
}
