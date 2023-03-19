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

 protected:
 private:
};
}  // namespace vega

#endif  // CALCMODEL_H_
