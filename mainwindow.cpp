#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "com_port.h"
#include <QPushButton>
#include <sysinfoapi.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TW_Datashow->setColumnCount(5);
    connect(ui->PB_Send, &QPushButton::clicked, this, &MainWindow::slot_buttonSendData);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_NewData(const QByteArray& data, unsigned int& Time, const QString from, const QString to, const int size)
{
  Time = GetTickCount() - Time;
  QString str, str2;
  str.setNum(size);
  str2.setNum(Time);
    ui->TW_Datashow->setRowCount(ui->TW_Datashow->rowCount() + 1);
    int row_num = ui->TW_Datashow->rowCount() - 1;
    QTableWidgetItem *itemOne = new QTableWidgetItem(QString::fromUtf8(data));
        QTableWidgetItem *itemTwo = new QTableWidgetItem(from);
            QTableWidgetItem *itemThree = new QTableWidgetItem(to);
                QTableWidgetItem *itemFourth = new QTableWidgetItem(str);
                   QTableWidgetItem *itemFivth = new QTableWidgetItem(str2);
    ui->TW_Datashow->setItem(row_num, 0, itemOne);
    ui->TW_Datashow->setItem(row_num, 1, itemTwo);
    ui->TW_Datashow->setItem(row_num, 2, itemThree);
    ui->TW_Datashow->setItem(row_num, 3, itemFourth);
    ui->TW_Datashow->setItem(row_num, 4, itemFivth);
}

void MainWindow::slot_buttonSendData()
{
  unsigned int Time;

  const QByteArray arr = ui->textEdit->toPlainText().toUtf8();
  Time= GetTickCount();
  emit sig_WriteNewData(arr, Time, "From ui", "To comp", arr.size());
}



