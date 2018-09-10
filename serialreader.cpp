#include "serialreader.h"
#include <QDateTime>

SerialReader::SerialReader(QObject *parent) :
    QObject(parent),
    serialPort(new QSerialPort(this))
{
    connect(serialPort, &QSerialPort::readyRead, this, &SerialReader::readData);
    data = { "N/A", 0, 0, 0 };

}

SerialReader::~SerialReader()
{
    delete serialPort;
}

bool SerialReader::openSerialPort(QString port)
{
    serialPort->setPortName(port);
    serialPort->setBaudRate(QSerialPort::Baud9600);
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
    //get current date and time
    QDateTime dateTime = QDateTime::currentDateTime();
    data.timestamp = dateTime.toString("hh:mm:ss.zzz");

    char buf;
    serialPort->read(&buf, 1);
    data.temperature = buf;

    emit dataReceived(data);
}

