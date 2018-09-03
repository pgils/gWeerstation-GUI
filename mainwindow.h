#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>

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
    void openSerialPort();
    void readData();

    void on_btnConnect_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort = nullptr;
};

#endif // MAINWINDOW_H
