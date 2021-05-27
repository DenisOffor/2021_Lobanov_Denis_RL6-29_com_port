#ifndef COM_PORT_H
#define COM_PORT_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QDebug>
#include <assert.h>

class com_port : public QObject
{
    Q_OBJECT
private :
    QSerialPort *this_port;
    QByteArray buffer;

public:
    com_port();
    ~com_port();

    bool Open(const QString& name_port);
    void Close();
    int SetUp();

    void Write(const QByteArray &data, unsigned int& Time);
    QByteArray Read();


signals :
    void sig_Opened(const QString& port_name, int status_error);
    void sig_DataInBuffer(const QByteArray&, unsigned int& Time, const QString from, const QString to, const int size);
public slots:
    void slot_GetData();
    void slot_SendData(const QByteArray& data, unsigned int& time);

};

#endif // COM_PORT_H
