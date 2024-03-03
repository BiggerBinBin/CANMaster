#include "canmaster.h"
#include "ui_canmaster.h"
#include "communicate.h"
CANMaster::CANMaster(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CANMaster)
{
    ui->setupUi(this);
    m_CommuniPtr.reset(new Communicate);
    DeviceParameter d;
    m_CommuniPtr.data()->openDevice(d);
}

CANMaster::~CANMaster()
{
    delete ui;
}

