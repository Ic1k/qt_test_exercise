#ifndef MODEL_H_
#define MODEL_H_

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
namespace vega {

class Model {
 public:
  Model() {}

  void connectdb(QSqlDatabase *db);


//  struct idData {
//      int value1;
//      int value2;
//      int value3;
//  };

 protected:
 private:


};
}  // namespace vega

#endif  // CALCMODEL_H_
