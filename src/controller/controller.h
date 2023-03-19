#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "model/model.h"

namespace vega {
class Controller {
 public:
  Controller(Model *model) : model_(model) {}
  void connectdb(  QSqlDatabase *db){
      db_=db;
      model_->connectdb(db_);}


 protected:
 private:
  Model *model_;
  QSqlDatabase *db_;
};
}  // namespace vega

#endif  // CONTROLLER_H_
