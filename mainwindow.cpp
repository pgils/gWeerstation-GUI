#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QtSql>
#include <QSqlQuery>
#include <QtDebug>



QSqlDatabase db;

void connectDB(){
    db = QSqlDatabase::addDatabase( "QMYSQL" );

    db.setHostName( "pellevangils.nl" );
    db.setUserName( "max" );
    db.setPassword( "ByM0MK11M9igHzf6" );
    db.setDatabaseName( "gwsTestData" );

//        db.setHostName( "localhost" );
//        db.setUserName( "root" );
//        db.setPassword( "password" );
//        db.setDatabaseName( "test" );



}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

   connectDB();

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(showCurrentData()));
    timer->start(1000);


}

MainWindow::~MainWindow()
{
    delete ui;
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
        float devision;
         while (query.next()) {
            devision = (query.value(0).toFloat());
            data.setNum(devision/10);


            if(Temperature == 0){
                outputData = QString("%1 °C").arg(data );
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
    db.close();
}

void MainWindow::showCurrentData(){


   QString Temperature = QString("SELECT Temperature FROM  tblData ORDER BY date LIMIT 1");
   QString Humidity = QString("SELECT Humidity FROM  tblData ORDER BY date LIMIT 1");
   QString Pressure = QString("SELECT Pressure FROM  tblData ORDER BY date LIMIT 1");


   QString data;
   QString outputData;
ui->listWidget_2->clear();
qDebug()<<"f1";

   if( !db.open() )
   {
     qDebug() << db.lastError();
   qFatal( "Failed to connect." );
 }
   else{
       QSqlQuery queryT(Temperature);
         queryT.next();
           data = queryT.value(0).toString();
           outputData = QString("Temperature is %1 °C").arg(data);

           ui->listWidget_2->addItem(outputData);

           QSqlQuery queryH(Humidity);
             queryH.next();
               data = queryH.value(0).toString();
               outputData = QString("Humidity is %1 %").arg(data);
               ui->listWidget_2->addItem(outputData);

               QSqlQuery queryP(Pressure);
                 queryP.next();
                   data = queryP.value(0).toString();
                   outputData = QString("Pressure is %1 atm").arg(data);
                   ui->listWidget_2->addItem(outputData);
      }
   db.close();
       }




