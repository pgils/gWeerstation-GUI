#include "serialreader.h"
#include <QDateTime>

SerialReader::SerialReader(QObject *parent) :
    QObject(parent),
    serialPort(new QSerialPort(this))
{
    connect(serialPort, &QSerialPort::readyRead, this, &SerialReader::readData);
    data = { "N/A", 0x00, 0x00, 0x00 };

}

SerialReader::~SerialReader()
{
    delete serialPort;
}

bool SerialReader::openSerialPort(QString port)
{
    serialPort->setPortName(port);
    serialPort->setBaudRate(QSerialPort::Baud38400);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    return serialPort->open(QIODevice::ReadOnly);

}

void SerialReader::closeSerialPort()
{
    serialPort->close();
}

bool SerialReader::isSerialPortOpen()
{
    return serialPort->isOpen();
}

void SerialReader::readData()
{
    if (serialPort->bytesAvailable() < 4)
        return;

    //get current date and time
    QDateTime dateTime = QDateTime::currentDateTime();
    data.timestamp = dateTime.toString("hh:mm:ss.zzz");

    char buf[4];
    serialPort->read(buf, 4);
    data.temperature	= (buf[3] << 8)|(buf[2]);
    data.humidity		= (buf[1] << 8)|(buf[0] & 0xFF); // &0xFF b/c otherwise the whole array is referenced..?

    emit dataReceived(data);
}

