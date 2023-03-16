#include "view/mainwindow.h"

#include "ui_mainwindow.h"


namespace vega {
MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), ui(new Ui::MainWindow) {
  ui->setupUi(this);




      qDebug()<<QSqlDatabase::drivers()<<"drivers\n";
      db = QSqlDatabase::addDatabase("QMYSQL");
      db.setDatabaseName("device");
      db.setHostName("172.17.0.2");
      db.setPort(3306);
      db.setUserName("root");
      db.setPassword("root");
      if(!db.open())
      {
          qDebug() << "open fail\n" << db.lastError().driverText() << "\n";

      } else { qDebug() << "open succefull\n"; }

      model = new QSqlTableModel(this);
      model->setEditStrategy(QSqlTableModel::OnManualSubmit);
      ui->tableView->setModel(model);

      model->setTable("devices");
      model->select();

}



void MainWindow::on_btn_edit_clicked(){
    va_ = new Validation(controller_);
    va_->resize(800, 300);
    va_->exec();
}


MainWindow::~MainWindow() { delete ui; }
};  // namespace vega
