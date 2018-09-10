#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QSerialPort>

struct DataFrame {
    QString timestamp;
    double temperature;
    double humidity;
    double pressure;
};


class SerialReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialReader(QObject *parent = nullptr);
    virtual ~SerialReader();

signals:
    void dataReceived(struct DataFrame data);
public slots:
    bool openSerialPort(QString port);
    bool isSerialPortOpen();
    void closeSerialPort();
private slots:
    void readData();

private:
    QSerialPort *serialPort = nullptr;
    DataFrame data;
};

#endif // SERIALREADER_H
