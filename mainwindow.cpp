#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QProcess>
#include<QFileDialog>
#include<QDebug>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->abtn, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->bbtn, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->dbtn,&QPushButton::clicked,this,&MainWindow::switchPage);
     connect(ui->cbtn,&QPushButton::clicked,this,&MainWindow::switchPage);
     connect(ui->firstbtn,&QPushButton::clicked,this,&MainWindow::switchPage);
     connect(ui->prebtn,&QPushButton::clicked,this,&MainWindow::switchPage);
     connect(ui->nextbtn,&QPushButton::clicked,this,&MainWindow::switchPage);
      connect(ui->lastbtn,&QPushButton::clicked,this,&MainWindow::switchPage);

      QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
      ui->comboBox->clear();
      for(auto port : portList)
      {
          ui->comboBox->addItem(port.portName());
      }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_action_triggered()
{
    QProcess *mprocess;
    mprocess =new QProcess();
    mprocess->start("calc");
}

void MainWindow::switchPage()
{
   QPushButton *button =qobject_cast<QPushButton*>(sender());
   if(button==ui->abtn)
       ui->stackedWidget->setCurrentIndex(3);
   else if(button==ui->bbtn)
           ui->stackedWidget->setCurrentIndex(1);
   else if(button==ui->cbtn)
           ui->stackedWidget->setCurrentIndex(2);
   else if(button==ui->dbtn)
           ui->stackedWidget->setCurrentIndex(0);
   else if(button==ui->firstbtn)
           ui->stackedWidget_2->setCurrentIndex(0);
   else if(button==ui->prebtn)
            if(ui->stackedWidget_2->currentIndex()!=0)
           ui->stackedWidget_2->setCurrentIndex( ui->stackedWidget_2->currentIndex()-1);
    else ui->stackedWidget_2->setCurrentIndex(3);
   else if(button==ui->nextbtn)
       if(ui->stackedWidget_2->currentIndex()!=3)
            ui->stackedWidget_2->setCurrentIndex(ui->stackedWidget_2->currentIndex()+1);
    else ui->stackedWidget_2->setCurrentIndex(0);
   else if(button==ui->lastbtn)
           ui->stackedWidget_2->setCurrentIndex(3);
}


void MainWindow::on_checkBox_6_stateChanged(int arg1)
{

    if(ui->checkBox_6->isChecked())
        {
            // 设置背景为黑色，字体为白色
            ui->textBrowser->setStyleSheet("background-color: black; color: white;");

            // 获取当前文本
            QString currentText = ui->textBrowser->toPlainText();

            // 为当前文本设置白色字体
            ui->textBrowser->setHtml("<font color='white'>" + currentText + "</font>");
        }
        else
        {
            // 恢复默认样式
            ui->textBrowser->setStyleSheet("");

            // 恢复默认字体颜色
            QString currentText = ui->textBrowser->toPlainText();
            ui->textBrowser->setHtml("<font color='black'>" + currentText + "</font>");
        }

}

void MainWindow::on_action_2_triggered()
{

    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    ui->comboBox->clear();
    for(auto port : portList)
    {
        ui->comboBox->addItem(port.portName());
    }
    ui->textBrowser->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->comboBox_4->setCurrentIndex(0);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
    ui->checkBox->setChecked(false);
    ui->checkBox_11->setChecked(false);
    ui->checkBox_12->setChecked(false);
    ui->checkBox_13->setChecked(false);
    ui->checkBox_22->setChecked(false);
    ui->lineEdit->setText("1000");
    ui->lineEdit_2->setText("1000");

}


void MainWindow::on_pushButton_9_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "All Files (*);;Text Files (*.txt)");
          // 检查是否有选择文件
          if (!filePath.isEmpty()) {
              // 显示文件路径到文本浏览器
              ui->textBrowser_2->setText(filePath);
          }
          times=0;
          ui->progressBar->setValue(0);
}

bool port_on=true;
void MainWindow::on_pushButton_clicked()
{
if(port_on==true)
{   ui->pushButton->setText("关闭串口");
    port_on=false;
    port = nullptr;
    port = new QSerialPort();

    port->setParity(ui->comboBox_2->currentIndex() == 0 ? (QSerialPort::Parity)0 : (QSerialPort::Parity)(ui->comboBox_2->currentIndex() + 1));//奇偶校验
    port->setBaudRate(ui->comboBox_5->currentText().toInt());
    port->setDataBits((QSerialPort::DataBits)ui->comboBox_3->currentText().toInt());
    port->setPortName(ui->comboBox->currentText());
    port->setStopBits((QSerialPort::StopBits)(ui->comboBox_4->currentIndex() + 1));
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->open(QIODevice::ReadWrite);
    connect(port,&QSerialPort::readyRead, this, &MainWindow::slot_getData);

}
else{
    ui->pushButton->setText("打开串口");
        port_on=true;
        port->close();
}

}

void MainWindow::slot_getData()
{
    ui->textBrowser->append("接收：" + port->read(port->bytesAvailable()));

}

void MainWindow::on_pushButton_8_clicked()
{   if(port_on==false){
    port->write(ui->textEdit->toPlainText().toUtf8());
    if(ui->textEdit->toPlainText()!=NULL)
    {
        ui->textBrowser->append("发送:"+ui->textEdit->toPlainText());
    }
    else
        ui->textBrowser->append("----------------------请先输入内容--------------------------");
    ui->textEdit->clear();
    }
    else
        ui->textBrowser->setText("----------------------请先打开串口--------------------------");
}




void MainWindow::on_pushButton_10_clicked()
{    stopending=false;

    if(port_on==false){
        QFile file(ui->textBrowser_2->toPlainText());
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {

            ui->textBrowser->append("无法打开文件: " + file.errorString());
            return;
        }
      int    fileSize = file.size();
     ui->progressBar->setMaximum((int)fileSize);
     ui->progressBar->setValue(0);
     QTextStream in(&file);
     QString line;
     int sentSize = 0;
     while(!in.atEnd()) {
                 if(stopending) {
                     ui->textBrowser->append("发送已停止");
                     file.close();
                     return;
                 }
                 QString line = in.readLine();
                 if(!line.isEmpty())
                 {

                     QByteArray data=line.toUtf8();


                     port->write(data);


                     sentSize += line.size();
                     ui->progressBar->setValue(sentSize);
                     qDebug()<<sentSize<<"一共"<<fileSize;
                     ui->progressBar->setValue(fileSize);
                     ui->textBrowser->append("发送: " + line);
                 }
                 else
                 {

                     ui->textBrowser->append("数据为空");
                 }
                 }
        times=times+1;
        ui->textBrowser->append(QString("-----这是第%1次发送数据----------").arg(times));
        QCoreApplication::processEvents();
        file.close();
        ui->textEdit->clear();

}
        else
            ui->textBrowser->setText("----------------------请先打开串口--------------------------");
}

void MainWindow::on_pushButton_11_clicked()
{
    stopending=true;
}
void MainWindow::on_pushbutton_save_clicked()
{

}
