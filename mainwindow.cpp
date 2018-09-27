#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QtSql>
#include <QSqlQuery>
#include <QtDebug>



QSqlDatabase db;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void connectDB(){
    db = QSqlDatabase::addDatabase( "QMYSQL" );

    db.setHostName( "pellevangils.nl" );
    db.setUserName( "max" );
    db.setPassword( "ByM0MK11M9igHzf6" );
    db.setDatabaseName( "gwsTestData" );

}
void MainWindow::on_pushButton_clicked(){
    int Temperature = 0;
    int Humidity = 0;
    int Pressure = 0;
    ui->listWidget->clear();
    QString measurement = ui->comboBox->currentText();
    QDate date = ui->calendarWidget->selectedDate();
    QString datum = date.toString("yyyy-MM-dd");
    QString TestQuery = QString("SELECT %1 FROM  tblData WHERE date >= '%2 00:00:00' AND date < '%2 23:59:59'")
                            .arg(measurement, datum);
   connectDB();

   //ui->listWidget->addItem(TestQuery);

    if( !db.open() )
    {
      qDebug() << db.lastError();
    qFatal( "Failed to connect." );
  }
    else{
        QSqlQuery query(TestQuery);
        Temperature = QString::compare(measurement,"Temperature");
        Humidity = QString::compare(measurement,"Humidity");
        Pressure = QString::compare(measurement,"Pressure");
        QString outputData;
        QString data;
         while (query.next()) {
            data = query.value(0).toString();

            if(Temperature == 0){
                outputData = QString("%1 °C").arg(data);
            }
            else if(Humidity == 0){
                 outputData = QString("%1 %").arg(data);
            }
            else if(Pressure == 0){
                 outputData = QString("%1 atm").arg(data);
            }
            else{
                qDebug()<<"Error getting value";
            }
            ui->listWidget->addItem(outputData);
                        }
        }
}

//WHERE date >= 00-00-%2 AND date < 59-23-%2"
