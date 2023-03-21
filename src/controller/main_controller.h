#ifndef MAIN_CONTROLLER_H_
#define MAIN_CONTROLLER_H_

#include "model/model.h"

namespace vega {
class MainController {
 public:
  MainController(Model *model) : model_(model) {}
  void connectdb(QSqlDatabase *db) { model_->connectdb(db); }
  void fillListDevices(QListWidget *listWidget) {
    model_->fillListDevices(listWidget);
  }

 private:
  Model *model_;
};
}  // namespace vega

#endif  // MAIN_CONTROLLER_H_
