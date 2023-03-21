#ifndef SELECT_CONTROLLER_H_
#define SELECT_CONTROLLER_H_

#include <QListWidget>

#include "model/model.h"

namespace vega {
class SelectController {
 public:
  SelectController(Model *model) : model_(model) {}
  void fillListProcess(QListWidget *listProcess, QString deviceName) {
    model_->fillListProcess(listProcess, deviceName);
  }
  void fillListPdfBin(QListWidget *listPdf, QListWidget *listBin,
                      QString deviceName, QString processName) {
    model_->fillListPdfBin(listPdf, listBin, deviceName, processName);
  }
  void insertFilesToData(QString deviceName, QString processName,
                         QString fileName) {
    model_->insertFilesToData(deviceName, processName, fileName);
  }

 private:
  Model *model_;
};
}  // namespace vega

#endif  // SELECT_CONTROLLER_H_
