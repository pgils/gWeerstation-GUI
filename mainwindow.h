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

private:
    Ui::MainWindow *ui;
    SerialReader *serialReader = nullptr;
};

#endif // MAINWINDOW_H
