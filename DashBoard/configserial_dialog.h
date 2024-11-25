#ifndef CONFIGSERIAL_DIALOG_H
#define CONFIGSERIAL_DIALOG_H

#include <QDialog>
#include "ui_configserial_dialog.h"
#include <QSerialPort>
#include <QList>
#include <QStringList>

namespace Ui {
class configserial_dialog;
}

class configserial_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit configserial_dialog(QWidget *parent = nullptr);
    ~configserial_dialog();
    //以下为返回函数
    QSerialPort::StopBits getStopBits(void);//返回停止位
    QSerialPort::DataBits getDataBits(); //返回数据位
    QSerialPort::Parity getParity(); //返回校验位
    QSerialPort::FlowControl getFlowControl(); //返回流控
    //以下为配置函数
    void setStopBits(QSerialPort::StopBits stopbits);//配置停止位
    void setDataBits(QSerialPort::DataBits databits);//配置数据位
    void setParity(QSerialPort::Parity parity);//配置校验位
    void setFlowControl(QSerialPort::FlowControl flowcontrol);//配置流控
    bool clickedOK(){
        return ok;
    }
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::configserial_dialog *ui;
    bool ok = false;
};

#endif // CONFIGSERIAL_DIALOG_H
