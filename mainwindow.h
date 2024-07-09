#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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
    void on_actionQuit_triggered();

    void on_action_triggered();


    void switchPage();

    void on_checkBox_6_stateChanged(int arg1);

    void on_action_2_triggered();


    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    void slot_getData();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();
    void on_pushbutton_save_clicked();
private:
    Ui::MainWindow *ui;
    QSerialPort* port;
    bool stopending=false;
    qint64 times=0;
};

#endif // MAINWINDOW_H
