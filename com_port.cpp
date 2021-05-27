#include "com_port.h"
#include <sysinfoapi.h>

com_port::com_port()
{
    this_port = new QSerialPort();
}

com_port::~com_port()
{
    Close();
    delete this_port;
}

bool com_port::Open(const QString &name_port)
{
  this_port->setPortName(name_port);
  bool status = this_port->open(QIODevice::ReadWrite);
  assert(status == true);


  int status_error = SetUp();
  emit sig_Opened(name_port, status_error);

  connect(this_port, &QSerialPort::readyRead, this, &com_port::slot_GetData);

  return (status_error == 0 ? true : false);
}

void com_port::Close()
{
    this_port->close();
}

int com_port::SetUp()
{
    int status_error = 0;
    status_error =  this_port->setBaudRate(QSerialPort::Baud115200) == false ? (1 << 0) :
                    this_port->setDataBits(QSerialPort::Data8) == false ? (1 << 1) :
                    this_port->setFlowControl(QSerialPort::NoFlowControl) == false ? (1 << 2) :
                    this_port->setParity(QSerialPort::NoParity) == false ? (1 << 3) :
                    this_port->setStopBits(QSerialPort::OneStop) == false ? (1 << 4) : 0;

   if (!this_port->isOpen()) {
       status_error = 0xFF;
   }
   return status_error;
}

void com_port::Write(const QByteArray &data, unsigned int& Time)
{
    if (!this_port->isOpen()) {
        return;
    }

    emit sig_DataInBuffer(data, Time, "From ui", "To comp", data.size());
    this_port->write(data);

}

QByteArray com_port::Read()
{
    return buffer;
}

void com_port::slot_GetData()
{
  unsigned int Time = GetTickCount();
    buffer = this_port->readAll();
    emit sig_DataInBuffer(buffer, Time, "From comp", "To Table Widget", buffer.size());
}

void com_port::slot_SendData(const QByteArray &data, unsigned int& Time)
{
   Write(data, Time);
}
