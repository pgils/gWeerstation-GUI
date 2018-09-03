#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialPort(new QSerialPort(this))
{
    ui->setupUi(this);

    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    openSerialPort();
}

void MainWindow::openSerialPort()
{
    serialPort->setPortName(ui->txtPort->text());
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if(serialPort->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Connect success!"), "Connection succeeded.");
    } else
    {
        QMessageBox::critical(this, tr("Connect failed!"), "Connection failed.");
    }
}

void MainWindow::readData()
{
    char buf;
    serialPort->read(&buf, 1);
    ui->lblTempVal->setText(QString::number(buf));
}
