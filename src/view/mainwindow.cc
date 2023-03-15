#include "view/mainwindow.h"

#include "ui_mainwindow.h"


namespace vega {
MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), ui(new Ui::MainWindow) {
  ui->setupUi(this);




qDebug()<<QSqlDatabase::drivers()<<"drivers\n";
      QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
      db.setDatabaseName("DEVICE");
      db.setHostName("172.17.0.2");
      db.setPort(3306);
      db.setUserName("root");
      db.setPassword("root");
      if(!db.open())
      {
          qDebug() << "open fail\n" << db.lastError().driverText() << "\n";

      } else { qDebug() << "open succefull\n"; }



}



void MainWindow::on_btn_add_clicked()
{

    qDebug()<<"Insert ";

}

MainWindow::~MainWindow() { delete ui; }
};  // namespace vega
