#ifndef TEXTDATA_EXTRACT_ENGINE_H
#define TEXTDATA_EXTRACT_ENGINE_H

#include <QObject>
#include <QRegularExpression>//添加正则表达式类
#include <QDebug>
#include <QString>
#include <QRunnable>
#include <QThread>

class TextData_Extract_Engine : public QObject
{
    Q_OBJECT
public:
    explicit TextData_Extract_Engine(QObject *parent = nullptr);
public:
    QString getproperty();//得到数据属性
    double getvalue();//得到数据数值
    //工作函数
    void appendAndparseData(const QByteArray &buffer);//添加和解析数据
signals:
    void dataparseover(QString property,double value);

private:
    QString property;//数据包的属性
    double value;//数据包的数值
    QStringList strlist;//用来保存正则表达式匹配出来的数据包，包括属性与数值
    QByteArray m_data_pack;
    //正则表达式配置
    const QString PACK_PREFIX_REG = "^Monitor_";//配置前缀
    const QString PACK_PROPERTY_REG = "([a-zA-Z]+)";//配置属性
    const QString PACK_SPLIT_REG = "[:]";//配置分隔符，冒号
    const QString PACK_VALUE_REG = "(\\d+[.]?\\d+)";//配置数值
    const QString PACK_TAIL_REG = "\r?\n";//配置尾
};

#endif // TEXTDATA_EXTRACT_ENGINE_H
