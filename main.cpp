#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include "com_port.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    com_port *my_com_this;
    my_com_this = new com_port;
    my_com_this->Open("COM5");

    QObject::connect(my_com_this, &com_port::sig_DataInBuffer, &w, &MainWindow::slot_NewData);
    QObject::connect(&w, &MainWindow::sig_WriteNewData, my_com_this, &com_port::slot_SendData);


    return a.exec();
}
