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

void MainWindow::setValues(DataFrame data)
{
    ui->lblDataReceivedVal->setText(data.timestamp);
    ui->lblTempVal->setText(QString::number(data.temperature));
}
