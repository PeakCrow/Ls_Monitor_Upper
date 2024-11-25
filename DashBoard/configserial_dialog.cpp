#include "configserial_dialog.h"

configserial_dialog::configserial_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configserial_dialog)
{
    ui->setupUi(this);
//    setWindowTitle(tr("设置"));//采用纯中文会报错
//    setWindowOpacity(0.8);
    //配置数据位的首选项与可选项
    ui->comboBox_DataBit->addItem("5");
    ui->comboBox_DataBit->addItem("6");
    ui->comboBox_DataBit->addItem("7");
    ui->comboBox_DataBit->addItem("8");
    ui->comboBox_DataBit->setCurrentIndex(0);//首选项


    //配置停止位的首选项与可选项
    ui->comboBox_StopBit->addItem("1");
    ui->comboBox_StopBit->addItem("1.5");
    ui->comboBox_StopBit->addItem("2");
    ui->comboBox_StopBit->setCurrentIndex(0);//首选项

    //配置奇偶校验的首选项与可选项
    ui->comboBox_Parity->addItem("None");
    ui->comboBox_Parity->addItem("Odd");
    ui->comboBox_Parity->addItem("Even");
    ui->comboBox_Parity->addItem("Mark");
    ui->comboBox_Parity->addItem("Space");
    ui->comboBox_Parity->setCurrentIndex(0);//首选项

    //配置流控的首选项与可选项
    ui->comboBox_FlowControl->addItem("None");
    ui->comboBox_FlowControl->addItem("Hardware");
    ui->comboBox_FlowControl->addItem("Software");
    ui->comboBox_FlowControl->setCurrentIndex(0);//首选项
}

configserial_dialog::~configserial_dialog()
{
    delete ui;
}
QSerialPort::StopBits configserial_dialog::getStopBits()//返回串口停止位
{
    if(ui->comboBox_StopBit->currentText() == "1")
        return QSerialPort::OneStop;
    else if(ui->comboBox_StopBit->currentText() == "1.5")
        return QSerialPort::OneAndHalfStop;
    else if(ui->comboBox_StopBit->currentText() == "2")
        return QSerialPort::TwoStop;
    else
        return QSerialPort::OneStop;
}
QSerialPort::DataBits configserial_dialog::getDataBits()//数据位
{
    if(ui->comboBox_DataBit->currentText() == "5")
        return QSerialPort::Data5;
    else if(ui->comboBox_DataBit->currentText() == "6")
        return QSerialPort::Data6;
    else if(ui->comboBox_DataBit->currentText() == "7")
        return QSerialPort::Data7;
    else if(ui->comboBox_DataBit->currentText() == "8")
        return QSerialPort::Data8;
    else
        return QSerialPort::Data8;
}
QSerialPort::Parity configserial_dialog::getParity()//奇偶校验
{
    if(ui->comboBox_Parity->currentText() == "None")
        return QSerialPort::NoParity;
    else if(ui->comboBox_Parity->currentText() == "Odd")
        return QSerialPort::OddParity;
    else if(ui->comboBox_Parity->currentText() == "Even")
        return QSerialPort::EvenParity;
    else if(ui->comboBox_Parity->currentText() == "Mark")
        return QSerialPort::MarkParity;
    else if(ui->comboBox_Parity->currentText() == "Space")
        return QSerialPort::SpaceParity;
    else
        return QSerialPort::NoParity;
}
QSerialPort::FlowControl configserial_dialog::getFlowControl()//流控
{
    if(ui->comboBox_FlowControl->currentText() == "None")
        return QSerialPort::NoFlowControl;
    else if(ui->comboBox_FlowControl->currentText() == "Hardware")
        return QSerialPort::HardwareControl;
    else if(ui->comboBox_FlowControl->currentText() == "Software")
        return QSerialPort::SoftwareControl;
    else
        return QSerialPort::NoFlowControl;
}
void configserial_dialog::setStopBits(QSerialPort::StopBits stopbits)
{
    if(stopbits == QSerialPort::OneStop)
        ui->comboBox_StopBit->setCurrentIndex(0);
    else if(stopbits == QSerialPort::OneAndHalfStop)
        ui->comboBox_StopBit->setCurrentIndex(1);
    else if(stopbits == QSerialPort::TwoStop)
        ui->comboBox_StopBit->setCurrentIndex(2);
    else
        ui->comboBox_StopBit->setCurrentIndex(0);
}

void configserial_dialog::setDataBits(QSerialPort::DataBits databits)
{
    if(databits == QSerialPort::Data5)
        ui->comboBox_DataBit->setCurrentIndex(0);
    else if(databits == QSerialPort::Data6)
        ui->comboBox_DataBit->setCurrentIndex(1);
    else if(databits == QSerialPort::Data7)
        ui->comboBox_DataBit->setCurrentIndex(2);
    else if(databits == QSerialPort::Data8)
        ui->comboBox_DataBit->setCurrentIndex(3);
    else
        ui->comboBox_DataBit->setCurrentIndex(3);
}

void configserial_dialog::setParity(QSerialPort::Parity parity)
{
    if(parity == QSerialPort::NoParity)
        ui->comboBox_Parity->setCurrentIndex(0);
    else if(parity == QSerialPort::OddParity)
        ui->comboBox_Parity->setCurrentIndex(1);
    else if(parity == QSerialPort::EvenParity)
        ui->comboBox_Parity->setCurrentIndex(2);
    else if(parity == QSerialPort::MarkParity)
        ui->comboBox_Parity->setCurrentIndex(3);
    else if(parity == QSerialPort::SpaceParity)
        ui->comboBox_Parity->setCurrentIndex(4);
    else
        ui->comboBox_Parity->setCurrentIndex(0);
}

void configserial_dialog::setFlowControl(QSerialPort::FlowControl flowcontrol)
{
    if(flowcontrol == QSerialPort::NoFlowControl)
        ui->comboBox_FlowControl->setCurrentIndex(0);
    else if(flowcontrol == QSerialPort::HardwareControl)
        ui->comboBox_FlowControl->setCurrentIndex(1);
    else if(flowcontrol == QSerialPort::SoftwareControl)
        ui->comboBox_FlowControl->setCurrentIndex(2);
    else
        ui->comboBox_FlowControl->setCurrentIndex(0);
}
void configserial_dialog::on_buttonBox_accepted()
{
    ok = true;
    this->close();
}

void configserial_dialog::on_buttonBox_rejected()
{
    this->close();
}
