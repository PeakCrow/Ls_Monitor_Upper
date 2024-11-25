#include "myqcustomplot.h"

Myqcustomplot::Myqcustomplot(QWidget *parent):QCustomPlot (parent)
{

    //setAutoDelete(true);
    //示例代码
//    QVector<double> x(101),y(101);
//    for(int i=0;i<101;i++){
//        x[i]=i/50.0-1;//设置x的范围为-1~1
//        y[i]=x[i]*x[i];
//    }
//    //创建画布,设置画布上的点数据
//    this->addGraph();
//    this->graph(0)->setData(x,y);
//    //设置坐标轴标签
//    this->xAxis->setLabel("x");
//    this->yAxis->setLabel("y");
//    //设置坐标轴范围，以便我们可以看到全部数据
//    this->xAxis->setRange(-1,1);
//    this->yAxis->setRange(0,1);
//    this->replot();

    //绘制四条线来显示传感器数据
    this->plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(this,"Sensor Data Display",QFont("sans",17,QFont::Bold));
    this->plotLayout()->addElement(0,0,title);
    this->yAxis->setLabel(tr("悬架位移"));
    //鼠标放在控件上可以显示提示信息
    this->setToolTip("Tip");
    //配置是否显示右上角的曲线名字
    this->legend->setVisible(true);
    //配置字体
    this->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QStringList lineNames;
    //lineNames << "front-left" << "front-left" << "front-right" << "left-after" << "right-after" << "right-after";
    lineNames << "front-left" << "front-right" << "left-after" << "right-after";
    //配置x轴线的数据
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    this->xAxis->setTicker(timeTicker);
    //显示默认的x轴线的长度--200ms
    this->xAxis->setRange(0.0,0.2);
    timeTicker->setTimeFormat("%zms");
    //timeTicker->setTickCount(123);
    timeTicker->setFieldWidth(QCPAxisTickerTime::tuMilliseconds,1);
    // add graphs with different line styles:--添加具有不同线条样式的图形，只使用了六个样式中的四个(枚举类型)
    for (int i=QCPGraph::lsLine; i<=QCPGraph::lsStepCenter; ++i)
    {
      //添加曲线
      this->addGraph();
      //使用QT中的强制类型转换，消除警告
      //pen.setColor(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80));
      //配置曲线的颜色
      pen.setColor(QColor(static_cast<int>(qSin(i*1+1.2)*80+80), static_cast<int>(qSin(i*0.3+0)*80+80), static_cast<int>(qSin(i*0.3+1.5)*80+80)));
      this->graph()->setPen(pen);
      //this->graph()->setName(lineNames.at(i-QCPGraph::lsNone));
      //at()这个函数一定要注意，目前遇到的软件崩溃的问题都是由此函数引起的
      this->graph()->setName(lineNames.at(i-QCPGraph::lsLine));
      //this->graph()->setLineStyle((QCPGraph::LineStyle)i);
      //使用QT中的强制类型转换，消除警告
      this->graph()->setLineStyle(static_cast<QCPGraph::LineStyle>(i));
      //this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
      //配置用于散步点的形状，每条曲线配置不同的形状
      this->graph()->setScatterStyle(QCPScatterStyle(static_cast<QCPScatterStyle::ScatterShape>(i),8));

      // generate data:--生成数据
//      QVector<double> x(15), y(15);
//      for (int j=0; j<15; ++j)
//      {
//        x[j] = j/15.0 * 5*3.14 + 0.01;
//        //y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
//        y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsLine)*5 + (QCPGraph::lsStepCenter)*5 + 2;
//      }
//      this->graph()->setData(x, y);
//      //使能重新调整绘图
//      this->graph()->rescaleAxes(true);
    }
    // zoom out a bit:--缩小一点
    this->yAxis->scaleRange(1.1, this->yAxis->range().center());
    this->xAxis->scaleRange(1.1, this->xAxis->range().center());
    // set blank axis lines:--设置空白轴线
    this->xAxis->setTicks(true);
    this->yAxis->setTicks(true);
    this->xAxis->setTickLabels(true);
    this->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:--使右上轴克隆左下轴
    this->axisRect()->setupFullAxesBox();
    //允许用户用鼠标拖拉、缩放、选择任一幅图
    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    connect(this,&QCustomPlot::legendDoubleClick,this,&Myqcustomplot::showAxes);//双击轴线标题和进行轴线显示的信号槽链接
    connect(this,&QCustomPlot::plottableClick,this,&Myqcustomplot::plotClickedMatchName);//单机轴线数据和轴线名字显示的信号槽链接
}

Myqcustomplot::~Myqcustomplot()
{
    //delete customPlot;
}
//槽函数
//双击轴线标题进行轴线图像显示
//但是无法显示到正中间位置
void Myqcustomplot::showAxes()
{
    //qDebug() << "showAxes";
    this->graph()->rescaleAxes(true);
    this->replot();
}
//槽函数
//单击轴线数据进行对应的标题标红显示
void Myqcustomplot::plotClickedMatchName(QCPAbstractPlottable * plot)
{
    //获取曲线的名字
    QString index = plot->name();
    //将四条曲线配置为黑色
    for (int i = 0;i < 4;i++) {
        this->legend->item(i)->setTextColor(Qt::black);
    }
    //通过曲线的名字判断曲线索引号，进行红色标注
    if(index == "right-after")
        //将曲线标题的名字配置为红色
        this->legend->item(3)->setTextColor(Qt::red);
    else if(index == "left-after")
        this->legend->item(2)->setTextColor(Qt::blue);
    else if(index == "front-right")
        this->legend->item(1)->setTextColor(Qt::yellow);
    else if(index == "front-left")
        this->legend->item(0)->setTextColor(Qt::green);
    //qDebug() << "MatchName" << plot->name();
}
//向曲线中添加数据

void Myqcustomplot::addSensorData(QVector<double> &x1,QVector<double> &x2,QVector<double> &x3,QVector<double> &x4,QVector<double> &fl_y,QVector<double> &fr_y,QVector<double> &la_y,QVector<double> &ra_y)
{
    this->graph(0)->addData(x1,fl_y);
    this->graph(1)->addData(x2,fr_y);
    this->graph(2)->addData(x3,la_y);
    this->graph(3)->addData(x4,ra_y);
    //使能重新调整绘图,自动设置最合适的显示范围
    this->graph()->rescaleAxes(true);
    this->replot();
}
