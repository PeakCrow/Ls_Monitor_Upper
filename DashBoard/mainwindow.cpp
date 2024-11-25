#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->vehicle_speed->setValue(33.3);//设置仪表盘的初始值
    ui->serial_baud->setCurrentText("115200");

    //qDebug() << "主线程工作地址:" << QThread::currentThread();
    //信号槽
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::vehicle_speed_value_add);//add按钮与仪表盘链接
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::vehicle_speed_value_abstruct);//subtract按钮与仪表盘链接
    connect(ui->horizontalSlider,&QSlider::sliderMoved,this,&MainWindow::vehicle_speed_value_slider);//滑动条与仪表盘链接
    connect(this,&MainWindow::vehicle_speed_value,ui->horizontalSlider,&QSlider::setValue);//仪表盘与滑动条链接

//    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::refresh_com);//刷新串口按钮与串口显示框链接,只有点击按钮才会刷新
    connect(ui->pushButton_3,&QPushButton::clicked,Serial,&mySerialPort::refreshSerialPort);
    //typedef QList<QString> stringmap;
    qRegisterMetaType<QList<QString>>("QList<QString>");
    connect(Serial,&mySerialPort::common_name,this,&MainWindow::refreshCom);

//    connect(ui->ActionSerialPort,&QAction::triggered,this,&MainWindow::ActionSerialPort_triggered);//手动链接串口设置按钮与窗口，在设计师界面中使用 转到槽 没有反映
    connect(ui->actionce,&QAction::triggered,this,&MainWindow::on_actionce_triggered);//测试多个菜单栏按钮 //手动链接
    connect(this,&MainWindow::serial_canshu,Serial,&mySerialPort::serial_canshu_open);
//    connect(Serial,&mySerialPort::serial_open_status,this,&MainWindow::serial_open_status);
    connect(this,&MainWindow::serial_close_status,Serial,&mySerialPort::serial_close_status);


    th_text_engine = new QThread();
    text_engine->moveToThread(th_text_engine);
    connect(th_text_engine,&QThread::finished,text_engine,&TextData_Extract_Engine::deleteLater);//线程结束后，将线程占用的内存进行释放
    connect(Serial,&mySerialPort::textdata_extract,text_engine,&TextData_Extract_Engine::appendAndparseData);//将串口类的数据解析信号与文本引擎类的数据解析槽函数进行链接
    th_text_engine->start();

    connect(text_engine,&TextData_Extract_Engine::dataparseover,this,&MainWindow::append_parse_data);//将数据解析类的解析完毕信号与主线程的添加数据显示槽函数进行链接
}
MainWindow::~MainWindow()
{
//    th_serial->quit();
//    th_serial->wait();
//    delete th_serial;
//    th_text_engine->quit();
//    th_text_engine->wait();
//    delete th_text_engine;

    delete Serial;
    delete text_engine;
    delete ui;
}
//槽函数
void MainWindow::vehicle_speed_value_add()
{
    static double val;
    val = ui->vehicle_speed->getValue();
    val+=5;
    ui->vehicle_speed->setValue(val);

    emit this->vehicle_speed_value(val);
}
//槽函数
void MainWindow::vehicle_speed_value_abstruct()
{
    static double val;
    val = ui->vehicle_speed->getValue();
    val -= 5;
    ui->vehicle_speed->setValue(val);
    emit this->vehicle_speed_value(val);
}
//槽函数
void MainWindow::vehicle_speed_value_slider(int val)
{
    //static double val;
    val = ui->horizontalSlider->value();
    ui->vehicle_speed->setValue(val);
    ui->batteryporgress->setValue(val);
}
/*
 * Function:槽函数
*/
void MainWindow::refresh_com()
{
    //refreshCom();
}
/*
 * Function:刷新串口
*/
void MainWindow::refreshCom(QList<QString> tmp)
{


//    QList<QString> tmp;
//    tmp = Serial->refreshSerialPort();//调用串口类的刷新函数

    QString portName = ui->comList->currentText().mid(0,ui->comList->currentText().indexOf('('));
    ui->comList->clear();//刷新串口状态，记录选择的串口条目,不然刷新会点击一次添加一次条目

    foreach(const QString &info,tmp)
    {
        ui->comList->addItem(info);//将串口条目添加到框中
    }

    if(ui->comList->count() == 0)
        ui->comList->addItem(tr("未找到可用串口，请尝试点击刷新串口按钮！"));

    ui->comList->setCurrentIndex(0);//恢复刷新前的选择,这样会在每次刷新后，将上一次的串口选择保留下来
    for(qint32 i = 0;i < ui->comList->count();i++)//不然每次刷新之后都会重新显示
    {
        if(ui->comList->itemText(i).startsWith(portName))
        {
            ui->comList->setCurrentIndex(i);
        }

    }
    //qDebug()<< "comList:"<<ui->comList->count();
}

//void MainWindow::serial_open_status(bool status)
//{
//    serial_status = status;
//}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    QMessageBox::Button btn = QMessageBox::question(this,"关闭窗口","您确定要关闭窗口吗？");
    if(btn == QMessageBox::Yes)
    {
        ev->accept();
    }else
    {
        ev->ignore();
    }
}

/* 槽函数 */
void MainWindow::ActionSerialPort_triggered()
{
    if(Serial->isOpen())
    {
        QMessageBox::information(this,tr("提示"),tr("请先关闭串口!"));
        return;
    }
    /* 创建串口设置对话框，前后要有空格，不然会报错 */
    configserial_dialog* p = new configserial_dialog(this);
    p->show();//使用show方法才会显示子窗口,非模态对话框，可以交互其他窗口
    p->setStopBits(Serial->stopBits());
    p->setDataBits(Serial->dataBits());
    p->setParity(Serial->parity());
    p->setFlowControl(Serial->flowControl());
    p->exec();//注释掉此行，可以触发下面的失败警告
    //对话框返回新配置并设置
    if(p->clickedOK())//点击弹出窗口的OK按钮时才会更新配置
    {   //虽然不会进入if判断体，但是会运行一次moreSetting函数达到更新串口参数配置的效果
        if(!Serial->moreSetting(p->getStopBits(),
                               p->getParity(),
                               p->getFlowControl(),
                               p->getDataBits()))//此函数将更新串口参数配置
        {
            QMessageBox::information(this, tr("提示"), tr("串口设置失败，请关闭串口重试"));
        }

    }
    //qDebug() << "secong window";
    delete p;
}
//槽函数
void MainWindow::on_actionce_triggered()
{
     qDebug() << "2secong window";
}

//槽函数
//向ui界面中的控件填充数据
void MainWindow::append_parse_data(QString property,double value)
{

    if(property == "batteryV")
        ui->batteryporgress->setValue(static_cast<int>(value));//进行强制类型转换(安全)
    else if(property == "vehicleK")
        ui->vehicle_speed->setValue(value);
    else if(property == "flY"){
        fl_y << static_cast<double>(value);
        x1_index++;
        x1 << x1_index;
    }
    else if(property == "frY"){
        fr_y << static_cast<double>(value);
        x2_index++;
        x2 << x2_index;
    }
    else if(property == "laY"){
        la_y << static_cast<double>(value);
        x3_index++;
        x3 << x3_index;
    }
    else if(property == "raY"){
        ra_y << static_cast<double>(value);
        x4_index++;
        x4 << x4_index;
    }
    else if(property == "batteryS"){
        ui->batterygauge->setValue(value);
    }
    ui->sensor_displace->addSensorData(x1,x2,x3,x4,fl_y,fr_y,la_y,ra_y);
    //qDebug() << text_engine->getproperty() << text_engine->getvalue();
}


void MainWindow::on_open_serial_clicked(bool checked)
{
    bool ok;

    QString portname = ui->comList->currentText().mid(0,ui->comList->currentText().indexOf('('));
    //serial.close();//这里直接切换串口号无法正常打开设备接收数据，先关闭掉在重新打开效果正常
    qint32 baud = ui->serial_baud->currentText().toInt(&ok);//使用界面按钮配置波特率

    //serial_status = Serial->open(portname,baud);

    if(checked){
        //if(serial_status){
            ui->open_serial->setText(tr("关闭串口"));
            ui->open_serial->setChecked(true);
        //}
        //else{
//            ui->open_serial->setText(tr("打开串口"));
//           ui->open_serial->setChecked(false);
//            QMessageBox::critical(this,tr("串口打开失败"),tr("检查下哪里搞错!"),QMessageBox::Ok);
        //}
            emit serial_canshu(portname,baud);
    }else{
        //Serial->close();
        ui->open_serial->setText(tr("打开串口"));
        ui->open_serial->setChecked(false);
        emit serial_close_status();
    }

    //qDebug() << portname << ":" << baud << serial_status << checked;
}


