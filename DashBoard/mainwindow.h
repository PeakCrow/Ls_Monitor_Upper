#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myserialport.h"
#include "ui_mainwindow.h"
#include "ui_configserial_dialog.h"
#include <QMessageBox>
#include "configserial_dialog.h"
#include <QDesktopWidget>
#include <QPainter>
#include <QBitmap>
#include <QTimer>
#include "textdata_extract_engine.h"
#include "myqcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    //使用普通函数也可以作为槽函数
    void vehicle_speed_value_add(void);
    void vehicle_speed_value_abstruct(void);
    void vehicle_speed_value_slider(int val);
    void refresh_com(void);//串口刷新槽函数
    void ActionSerialPort_triggered(void);//串口配置按钮触发
    void on_actionce_triggered(void);

    void append_parse_data(QString property,double value);//向ui中填充数据
    void on_open_serial_clicked(bool checked);//打开串口按钮
    void refreshCom(QList<QString> tmp);//刷新串口
//    void serial_open_status(bool status);
protected:
    void closeEvent(QCloseEvent * ev);//重写关闭窗口事件函数
signals:
    void vehicle_speed_value(double val);
    void text_appendData(const QByteArray &str);//串口数据发送文本解析信号
    void serial_canshu(QString,qint32);
    void serial_close_status();
private:
    Ui::MainWindow *ui;
    mySerialPort *Serial = new mySerialPort;//串口类
    TextData_Extract_Engine * text_engine = new TextData_Extract_Engine;//文本解析器类

    QThread *th_text_engine = nullptr;
    QTimer *timer;//定时器用来计时
    //位移传感器数据显示所需的变量
    QVector<double> fl_y,fr_y,la_y,ra_y;
    QVector<double> x1,x2,x3,x4;
    int16_t x1_index = 0,x2_index = 0,x3_index = 0,x4_index = 0;
    //bool serial_status = false;
};

#endif // MAINWINDOW_H
