#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialReader = new SerialReader();
    connect(serialReader, &SerialReader::dataReceived, this, &MainWindow::setValues);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serialReader;
}

void MainWindow::on_btnConnect_clicked()
{
    if( ! serialReader->isSerialPortOpen())
    {
        if( ! serialReader->openSerialPort(ui->txtPort->text()))
        {
            QMessageBox::information(this, tr("Serial connect"), "Connection failed.");
        }
        else
        {
            ui->btnConnect->setText("Disconnect");
        }
    }
    else
    {
        serialReader->closeSerialPort();
        ui->btnConnect->setText("Connect ");
    }
}

/*
 * Calculate the relative humidity
 * based on the formula given in the Si7021 datasheet
 */
double MainWindow::calcHumidity(uint16_t rawHumidity)
{
    return ((125.0*rawHumidity)/65536)-6;
}

/*
 * Calculate the temperature in degrees celsius
 * based on the formula given in the Si7021 datasheet
 */
double MainWindow::calcTemperature(uint16_t rawTemperature)
{
    return ((175.72*rawTemperature)/65536)-46.85;
}

void MainWindow::setValues(DataFrame data)
{
    ui->lblDataReceivedVal->setText(data.timestamp);
    ui->lblTempVal->setText(QString::number(calcTemperature(data.temperature), 'f', 2));
    ui->lblHumidityVal->setText((QString::number(calcHumidity(data.humidity), 'f', 2)));
}
