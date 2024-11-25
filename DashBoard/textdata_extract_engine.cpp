#include "textdata_extract_engine.h"

TextData_Extract_Engine::TextData_Extract_Engine(QObject *parent) : QObject(parent)
{
//    QByteArray str = "Monitor_batteryV:234.5\n";//测试字符串示例
//        appendAndparseData(str);

}

QString TextData_Extract_Engine::getproperty()
{
    if(!strlist.isEmpty())
        return strlist.at(1);
    else
        return " ";

}

double TextData_Extract_Engine::getvalue()
{
    bool ok;
    if(!strlist.isEmpty())
        return strlist.at(2).toDouble(&ok);
    else {
        return 0.0;
    }
}



void TextData_Extract_Engine::appendAndparseData(const QByteArray &buffer)
{
    //qDebug() << "数据解析线程工作地址:" << QThread::currentThread();
    QRegularExpression regmatch;
    QString pattern = PACK_PREFIX_REG + PACK_PROPERTY_REG + PACK_SPLIT_REG + PACK_VALUE_REG + PACK_TAIL_REG;
    regmatch.setPattern(pattern);
    QRegularExpressionMatch regmatchstr = regmatch.match(buffer,0);//进行正则匹配，从0位置开始
    strlist = regmatchstr.capturedTexts();//将捕获的字符串数据作为函数返回值
    emit this->dataparseover(this->getproperty(),this->getvalue());//数据解析完成后发送信号
    bool ok;
    if(!strlist.isEmpty())
        qDebug() << strlist.at(1)  << strlist.at(2).toDouble(&ok);

}
