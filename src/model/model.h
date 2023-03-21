#ifndef MODEL_H_
#define MODEL_H_

#include <QDebug>
#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace vega {

class Model {
 public:
  Model() {}

  void connectdb(QSqlDatabase *db);
  void fillListDevices(QListWidget *listWidget);
  void fillListProcess(QListWidget *listProcess, QString deviceName);
  void fillListPdfBin(QListWidget *listPdf, QListWidget *listBin,
                      QString deviceName, QString processName);
  void insertFilesToData(QString deviceName, QString processName,
                         QString fileName);
  int getdeviceId(QString deviceName);
  int getprocessId(QString processName);
  int getfilesId();

 private:
};
}  // namespace vega

#endif  // CALCMODEL_H_
