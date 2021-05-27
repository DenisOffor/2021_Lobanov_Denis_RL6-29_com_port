#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidgetItem>

#include "test_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void slot_NewData(const QByteArray&, unsigned int& Time, const QString from, const QString to, const int size);
    void slot_buttonSendData();
signals :
    void sig_WriteNewData(const QByteArray& data, unsigned int& Time, const QString from, const QString to, const int size);


};
#endif // MAINWINDOW_H
