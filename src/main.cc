#include "controller/main_controller.h"
#include "controller/select_controller.h"
#include "model/model.h"
#include "view/mainview.h"

int main(int argc, char *argv[]) {
  QApplication q(argc, argv);
  vega::Model model;
  vega::MainController mainController(&model);
  vega::SelectController selectController(&model);
  MainView mainView(&mainController,&selectController);
  mainView.show();
  return q.exec();
}
