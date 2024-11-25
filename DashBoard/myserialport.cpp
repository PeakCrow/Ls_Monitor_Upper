#include "myserialport.h"


mySerialPort::mySerialPort()
{

    stopbits = OneStop;
    patitybit = NoParity;
    flowcontrol = NoFlowControl;
    databits = Data8;

    QThread *th_serial = nullptr;
    th_serial = new QThread();

    this->moveToThread(th_serial);
    connect(this,&mySerialPort::readyRead,this,&mySerialPort::readAll);
    th_serial->start();
}
mySerialPort::~mySerialPort()
{

//    if(mySerialPort::isOpen())
//        mySerialPort::close();
}

bool mySerialPort::open(QString Portname, int BaudRate)
{
    mySerialPort::setPortName(Portname);
    mySerialPort::setBaudRate(BaudRate);
    return mySerialPort::open(mySerialPort::ReadWrite);
}
/*
 *Function:
 * Parameter:
 * Return:
*/
void mySerialPort::refreshSerialPort()
{
    QList<QString> tmp;
    //QString tmp;

    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QString status;
        QString msg;
        //获取繁忙还是正常的串口状态
        status = info.isBusy() ? "BUSY " : "IDLE ";
        //配置串口显示内容，--串口号--状态--串口描述--生产商
        msg = info.portName() + "(" + status + info.description() + ")" + " " + info.manufacturer();
        tmp.append(msg);
    }
     //qDebug() << tmp;
    emit common_name(tmp);
    //return tmp;
}

bool mySerialPort::moreSetting(StopBits sb, Parity pa, FlowControl fc, DataBits db)
{
    databits = db;
    stopbits = sb;
    flowcontrol = fc;
    patitybit = pa;

    return  mySerialPort::setDataBits(databits) &&
            mySerialPort::setParity(patitybit) &&
            mySerialPort::setStopBits(stopbits) &&
            mySerialPort::setFlowControl(flowcontrol);
}



QByteArray mySerialPort::readAll()
{
    //qDebug() << "串口线程工作地址:" << QThread::currentThread();
    QByteArray tmp;
    tmp = QSerialPort::readAll();//读取IO设备中的串口数据
    if(!tmp.isEmpty()){
        RxCnt += static_cast<int64_t>(tmp.size());
        totalRxCnt += static_cast<int64_t>(tmp.size());//这两行是否功能重复?
    }
    qDebug() << "读取串口数据" << tmp;
    emit textdata_extract(tmp);
    return tmp;
}

void mySerialPort::serial_canshu_open(QString portname, qint32 baud)
{
    bool serial_status = false;
    serial_status = this->open(portname,baud);
    //emit serial_open_status(serial_status);
}

void mySerialPort::serial_close_status()
{
    this->close();
}
