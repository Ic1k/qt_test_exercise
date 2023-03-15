#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "model/model.h"

namespace vega {
class Controller {
 public:
  Controller(Model *model) : model_(model) {}

 protected:
 private:
  Model *model_;
};
}  // namespace vega

#endif  // CONTROLLER_H_
