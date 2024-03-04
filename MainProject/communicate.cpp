#include <QPushButton>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include <QApplication>
#include "communicate.h"
#include "../DeviceIO/RegisterDevClass.h"

Communicate::Communicate(QObject *parent) : QObject(parent)
{
    //Using this static function register reflect class first
    RegisterDevReflect::RegisterReflect();
    QString path = QApplication::applicationDirPath()+"/Config/className.json";
    readDevName(path);
}

bool Communicate::openDevice(const DeviceParameter &param)
{

    if(param.devType>=className.size())
    {
        return false;
    }
    QJsonObject obj;
    obj.insert("ch",param.devChannel);
    obj.insert("bundRate",param.baudRate);
    obj.insert("devModel",param.devModel);

    m_sharedPtrDev.reset(static_cast<DeviceIO*>(CReflectClass<DeviceIO>::createObject(QByteArray(className.at(param.devType).toUtf8()),nullptr)));
    m_sharedPtrDev.data()->enumDevice();
    return m_sharedPtrDev.data()->openDevice(obj);

}

bool Communicate::readDevName(QString path)
{
    QFile file(path);
    if(!file.exists())
    {
        return false;
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        //QMessageBox::warning(NULL, QObject::tr("warning"), QObject::tr("数据不存在，初始化数据失败"));
        return false;
    }
    //Using text stream to read data
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();
    QJsonParseError err;
    //string convert to QJsonDocument
    QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8(),&err);
    //has something error
    if(err.error != QJsonParseError::NoError)
    {
        qDebug()<<"QJsonParseError: "<<err.errorString();
        return false;
    }

    QJsonObject jobj = jdoc.object();
    if(!jobj["className"].isArray())
        return false;

     QJsonArray jarr = jobj["className"].toArray();
     className.clear();
     for(int i=0;i<jarr.size();i++)
     {
        className.append(jarr.at(i).toString());
     }

}
