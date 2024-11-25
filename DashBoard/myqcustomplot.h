#ifndef MYQCUSTOMPLOT_H
#define MYQCUSTOMPLOT_H

#include "qcustomplot.h"
#include <QDebug>
#include <QRunnable>

class Myqcustomplot : public QCustomPlot
{
private:
    //QCustomPlot *customPlot = new QCustomPlot();

public:
    Myqcustomplot(QWidget *parent = nullptr);
    ~Myqcustomplot();

    //进行数据的添加
    void addSensorData(QVector<double> &x1,QVector<double> &x2,QVector<double> &x3,QVector<double> &x4,QVector<double> &fl_y,QVector<double> &fr_y,QVector<double> &la_y,QVector<double> &ra_y);//添加四个传感器的数据
    void showAxes(void);
    void plotClickedMatchName(QCPAbstractPlottable * plot);
};

#endif // MYQCUSTOMPLOT_H

