#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <QSharedPointer>
#include "GlobalDataStruct.h"
#include "../DeviceIO/deviceio.h"
class Communicate : public QObject
{
    Q_OBJECT
public:
    explicit Communicate(QObject *parent = nullptr);
    //Using this function to open CAN or LIN Devices
    bool openDevice(const DeviceParameter &param);
    QStringList devList(){return className;}
public:
    QStringList className={"peakCAN","CANalyst","Kvaser","ZLGCAN","PLIN","ZMLIN"};
signals:

private:
    bool readDevName(QString path);
private:
    //QThread *runReceiveMes=nullptr;
    QSharedPointer<DeviceIO>m_sharedPtrDev;
};

#endif // COMMUNICATE_H
