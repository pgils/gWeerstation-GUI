#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serialreader.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();
    void setValues(DataFrame data);
    double calcHumidity(uint16_t rawHumidity);
    double calcTemperature(uint16_t rawTemperature);

private:
    Ui::MainWindow *ui;
    SerialReader *serialReader = nullptr;
};

#endif // MAINWINDOW_H
