#include "controller/controller.h"
#include "model/model.h"
#include "view/mainview.h"

int main(int argc, char *argv[]) {
  QApplication q(argc, argv);
  vega::Model model;
  vega::Controller controller(&model);
  MainView mainView(&controller);
  mainView.show();
  return q.exec();
}
