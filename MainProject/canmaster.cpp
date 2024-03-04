#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
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
    InitGUI();
}

CANMaster::~CANMaster()
{
    delete ui;
}

void CANMaster::InitGUI()
{

    //top tools bar
    QLabel* labelSeletcDev = new QLabel(this);
    labelSeletcDev->setText(tr("SelectDevType:"));
    this->comboxDevType = new QComboBox(this);
    this->comboxDevChannel = new QComboBox(this);
    this->pbRefreshDev = new QPushButton(this);
    this->pbRefreshDev->setText(tr("Refresh"));
    this->comboxBaudRate = new QComboBox(this);
    this->comboxModel = new QComboBox(this);
    QHBoxLayout* topToolsBarLayout = new QHBoxLayout(this);

    topToolsBarLayout->addWidget(labelSeletcDev);
    topToolsBarLayout->addWidget(comboxDevType);
    topToolsBarLayout->addWidget(comboxDevChannel);
    topToolsBarLayout->addWidget(pbRefreshDev);
    topToolsBarLayout->addWidget(comboxBaudRate);
    topToolsBarLayout->addWidget(comboxModel);

    QHBoxLayout*midleLayout = new QHBoxLayout(this);
    QHBoxLayout*secondLayout = new QHBoxLayout(this);
    QHBoxLayout*BottomLayout = new QHBoxLayout(this);
    QVBoxLayout *globalLayout = new QVBoxLayout(this);
    globalLayout->addLayout(topToolsBarLayout);
    globalLayout->addLayout(secondLayout);
    globalLayout->addLayout(midleLayout);
    globalLayout->addLayout(BottomLayout);
    globalLayout->setStretch(0,1);
    globalLayout->setStretch(1,5);
    globalLayout->setStretch(2,5);
    globalLayout->setStretch(3,5);
    this->centralWidget()->setLayout(globalLayout);

}

