#include "select.h"

Select::Select(QString deviceName_, vega::SelectController *selectController,
               QDialog *parent)
    : QDialog(parent),
      selectController_(selectController),
      deviceName(deviceName_)

{
  // Заголовок и список процессов.
  QLabel *labelDevice = new QLabel(this);
  labelDevice->setText(deviceName);
  labelDevice->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  QListWidget *listProcess = new QListWidget;
  connect(listProcess, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(onProcessListClicked(QListWidgetItem *)));

  // Заполнение списка процессов
  selectController_->fillListProcess(listProcess, deviceName);

  //  Левая часть формы. Заголовок и список процессов.
  QVBoxLayout *leftLayout = new QVBoxLayout();
  leftLayout->addWidget(labelDevice);
  leftLayout->addWidget(listProcess);

  // Правая, верхняя часть формы.  Список прошивок и инструкций
  QTabWidget *tabWidget = new QTabWidget;
  listPdf = new QListWidget;
  listBin = new QListWidget;
  tabWidget->addTab(listPdf, "Инструкции");
  tabWidget->addTab(listBin, "Прошивки");

  // Правая, нижняя часть формы.
  QPushButton *btn_upload = new QPushButton("Загрузить файл", this);
  QPushButton *btn_download = new QPushButton("Скачать файл", this);
  connect(btn_upload, &QPushButton::clicked, this, &Select::uploadFile);
  connect(btn_download, &QPushButton::clicked, this, &Select::downloadFile);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(btn_upload);
  buttonLayout->addStretch();
  buttonLayout->addWidget(btn_download);

  QVBoxLayout *rightLayout = new QVBoxLayout();
  rightLayout->addWidget(tabWidget);
  rightLayout->addLayout(buttonLayout);

  // Объединенная форма.
  QHBoxLayout *centralLayout = new QHBoxLayout();
  centralLayout->addLayout(leftLayout);
  centralLayout->addLayout(rightLayout);
  this->setLayout(centralLayout);
}
// Разблокировка основного окна
void Select::closeEvent(QCloseEvent *event) { event->accept(); }

// Выбор элемента списка процессов
void Select::onProcessListClicked(QListWidgetItem *item) {
  processName = item->text();

  // Заполнение списка PDF и BIN
  selectController_->fillListPdfBin(listPdf, listBin, deviceName, processName);
}

// Кнопка загрузки файла
void Select::uploadFile() {
  // Диалоговое окно, получение полного адреса файла.
  QString pathFile =
      QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                   tr("PDF Files (*.pdf);;BIN Files (*.bin)"));
  // Получение имени файла
  QStringList parts = pathFile.split("/");
  QString fileName = parts.at(parts.size() - 1);

  if (fileName != "") {
    selectController_->insertFilesToData(deviceName, processName, fileName);
    selectController_->fillListPdfBin(listPdf, listBin, deviceName,
                                      processName);
  }
}

void Select::downloadFile() {
  QString FileName =
      QFileDialog::getSaveFileName(this, "Open a file", QDir::homePath(), "");
  if (!FileName.isNull() && !FileName.isEmpty()) {
    qDebug() << FileName;
  }
}

Select::~Select() {}
