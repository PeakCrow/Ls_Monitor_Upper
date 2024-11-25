#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QtDebug>
#include <QString>
#include <QList>
#include <QMainWindow>
#include <QDesktopWidget>

//class MainWindow;

class mySerialPort:public QSerialPort
{
    Q_OBJECT
public:
    mySerialPort();
    ~mySerialPort();
    using QSerialPort::open;//保留父类的open函数并重载open函数
public slots:
    bool open(QString Portname,int BaudRate);
    void refreshSerialPort();
    //更多设置，任何一个设置失败均会返回false,包含有默认设置？
    bool moreSetting(StopBits stopbit = OneStop,Parity parity = NoParity,
                     FlowControl flowcontrol = NoFlowControl,DataBits databit = Data8);
    //工作函数
    QByteArray readAll();//读取串口数据
    void serial_canshu_open(QString portname,qint32 baud);
    void serial_close_status(void);
signals:
    void textdata_extract(const QByteArray data);//数据读取完毕后发送信号
    void common_name(QList<QString> tmp);
    void serial_open_status(bool);
private:
    StopBits stopbits;
    Parity patitybit;
    FlowControl flowcontrol;
    DataBits databits;
    int64_t RxCnt;//定义接收数据计数器
    int64_t totalRxCnt;//定义全部的接收数据计数器
//    QSerialPort *internal_Serial = new QSerialPort;//串口类
};

#endif // MYSERIALPORT_H
