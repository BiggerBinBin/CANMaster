#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextBrowser>
#include <QDir>
#include "canmaster.h"
#include "ui_canmaster.h"
#include "communicate.h"
#include "modeldatamanage.h"
#include <messageview.h>
#include <QsLog.h>
#include <QsLogDest.h>
using namespace QsLogging;
//static variate assignment
QStringList CANMaster::baudRate = {"100k/s","125k/s","250k/s","500k/s","1000k/s","9600b/s","19200b/s"};
QStringList CANMaster::platform = {"2kW","3kW","4kW","5kW","6kW","7kW","8kW","10kW","15kW","19kW","20kW","25kW"};

CANMaster::CANMaster(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CANMaster)
{
    ui->setupUi(this);
    m_CommuniPtr.reset(new Communicate);
//    DeviceParameter d;
//    m_CommuniPtr.data()->openDevice(d);
    InitGUI();
    initLogger();
    this->setWindowState(Qt::WindowMaximized);
    QLOG_INFO()<<"Welcome to use CANMaster!";


}

CANMaster::~CANMaster()
{
    delete ui;
    destroyLogger();
    if(!modelManage.isNull())
    {
        modelManage->close();
    }
}
/*
 * Initialte main user interface
*/
void CANMaster::InitGUI()
{

    //******************top tools bar

    //devcies group
    QLabel* labelSeletcDev = new QLabel(this);
    labelSeletcDev->setText(tr("SelectDevType:"));
    this->comboxDevType = new QComboBox(this);
    QLabel* labelChannel = new QLabel(this);
    labelChannel->setText(tr(" Channel:"));
    this->comboxDevChannel = new QComboBox(this);
    this->pbRefreshDev = new QPushButton(this);
    this->pbRefreshDev->setText(tr("<-RefreshDev"));

    QLabel* labelBaudRate = new QLabel(this);
    labelBaudRate->setText(tr("BaudRate:"));
    this->comboxBaudRate = new QComboBox(this);
    this->pbOpenDevice = new QPushButton(this);
    this->pbOpenDevice->setText(tr("ConnectDev"));
    QHBoxLayout* devLayout = new QHBoxLayout(this);
    devLayout->addWidget(labelSeletcDev);
    devLayout->addWidget(comboxDevType);
    devLayout->addWidget(labelChannel);
    devLayout->addWidget(comboxDevChannel);
    devLayout->addWidget(pbRefreshDev);
    devLayout->addWidget(labelBaudRate);
    devLayout->addWidget(comboxBaudRate);
    devLayout->addWidget(pbOpenDevice);
    QGroupBox* devGrounp = new QGroupBox(this);
    devGrounp->setLayout(devLayout);

    //model group
    this->comboxPlatform = new QComboBox(this);
    this->comboxModel = new QComboBox(this);
    QHBoxLayout* modelLayout = new QHBoxLayout(this);
    modelLayout->addWidget(new QLabel(tr("Platform:")));
    modelLayout->addWidget(comboxPlatform);
    modelLayout->addWidget(new QLabel(tr(" Model:")));
    modelLayout->addWidget(comboxModel);
    QGroupBox* modelGrounp = new QGroupBox(this);
    modelGrounp->setLayout(modelLayout);

    pbModelManage = new QPushButton(this);
    pbModelManage->setText(tr("ProcolManage"));
    connect(pbModelManage,&QPushButton::clicked,this,&CANMaster::on_pbModelManage_clicked);


    QHBoxLayout* topToolsBarLayout = new QHBoxLayout(this);
    topToolsBarLayout->addWidget(modelGrounp);
    topToolsBarLayout->addWidget(devGrounp);
    topToolsBarLayout->addSpacerItem(new QSpacerItem(100,10,QSizePolicy::MinimumExpanding));
    topToolsBarLayout->addWidget(pbModelManage);

    QStringList devList = m_CommuniPtr.data()->devList();
    for(auto x:devList)
    {
        this->comboxDevType->addItem(x);
        //set item data
        this->comboxDevType->setItemData(this->comboxDevType->count()-1,QVariant(x));
    }
    for(QString x:baudRate)
    {
        this->comboxBaudRate->addItem(x);
        int baud =  x.left(x.length()-2).toInt();
        //set item data,it's very useful to get item data
        this->comboxBaudRate->setItemData(this->comboxBaudRate->count()-1,baud);
    }
    this->comboxPlatform->addItems(platform);

    //************End top bar*********************//

    //************second right*******************//
    messageview = new MessageView(this);
    logBrower = new QTextBrowser(this);
    QVBoxLayout* secondRightLayout = new QVBoxLayout(this);
    secondRightLayout->addWidget(messageview->getTabWidget());
    secondRightLayout->addWidget(logBrower);


    QHBoxLayout*midleLayout = new QHBoxLayout(this);
    QHBoxLayout*secondLayout = new QHBoxLayout(this);
    QHBoxLayout*BottomLayout = new QHBoxLayout(this);

    QVBoxLayout*secondLeftLayout = new QVBoxLayout(this);
    secondLeftLayout->addLayout(midleLayout);
    secondLeftLayout->addLayout(secondLayout);
    secondLeftLayout->addLayout(BottomLayout);

    //The interface on the left and right sides below
    QHBoxLayout* downMidelLayout = new QHBoxLayout(this);
    downMidelLayout->addLayout(secondLeftLayout);
    downMidelLayout->addLayout(secondRightLayout);
    downMidelLayout->setStretch(0,8);
    downMidelLayout->setStretch(1,2);

    //global layout
    QVBoxLayout *globalLayout = new QVBoxLayout(this);
    globalLayout->addLayout(topToolsBarLayout);
    globalLayout->addLayout(downMidelLayout);

    globalLayout->setStretch(0,1);
    globalLayout->setStretch(1,10);

    this->centralWidget()->setLayout(globalLayout);

    ConnectWidget();

}
/*
 * build all widgets slot function connecting from ui
*/
void CANMaster::ConnectWidget()
{
    connect(comboxDevType,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&CANMaster::on_comboxDevType_IndexChanged);
    connect(comboxDevChannel,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&CANMaster::on_comboxDevChannel_IndexChanged);
    connect(comboxBaudRate,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&CANMaster::on_comboxBaudRate_IndexChanged);
    connect(comboxPlatform,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&CANMaster::on_comboxPlatform_IndexChanged);
    connect(pbRefreshDev,&QPushButton::clicked,this,&CANMaster::on_pbRefreshDev_Clicked);
    connect(pbOpenDevice,&QPushButton::clicked,this,&CANMaster::on_pbOpenDevice_Clicked);

}

void CANMaster::on_comboxDevType_IndexChanged(int index)
{
    QLOG_INFO()<<"comboxDevType Index"<<index;
}

void CANMaster::on_comboxDevChannel_IndexChanged(int index)
{
     QLOG_INFO()<<"comboxDevChannel Index"<<index;
}

void CANMaster::on_pbRefreshDev_Clicked(bool b)
{
 QLOG_INFO()<<"pbRefreshDev Index"<<b;
}

void CANMaster::on_comboxBaudRate_IndexChanged(int index)
{
 QLOG_INFO()<<"on_comboxBaudRate Index"<<index;
}

void CANMaster::on_pbOpenDevice_Clicked(bool b)
{
 QLOG_INFO()<<"pbOpenDevice Index"<<b;
}

void CANMaster::on_comboxPlatform_IndexChanged(int index)
{
    QLOG_INFO()<<"comboxPlatform Index"<<index;
}

void CANMaster::on_pbModelManage_clicked(bool b)
{
    if(modelManage.isNull())
    {
        modelManage.reset(new ModelDataManage);
    }
    modelManage->show();
}
void CANMaster::initLogger()
{
    Logger& logger = Logger::instance();    //初始化
    logger.setLoggingLevel(QsLogging::InfoLevel);  //设置写入等级
    QString logsfile = QApplication::applicationDirPath() + "/logs";
    QDir dir(logsfile);
    if (!dir.exists())
    {
        dir.mkpath(logsfile);
    }
    //设置log位置为exe所在目录
    const QString pp = logsfile + "/log.txt";
    //const QString sLogPath(QDir(QCoreApplication::applicationDirPath()).filePath("/logs/log.txt"));

    // 2. 添加两个destination
    //这个是文件流，搞到文件里面去的
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
        pp, EnableLogRotation, MaxSizeBytes(1024 * 1024 * 100), MaxOldLogCount(100)));
    //这个是调试时输出的
    DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
    //DestinationPtr functorDestination(DestinationFactory::MakeFunctorDestination(&logFunction));

    //这样和槽函数连接
    DestinationPtr sigsSlotDestination(DestinationFactory::MakeFunctorDestination(this, SLOT(logSlot(QString, int))));
    //添加debug流向
    logger.addDestination(debugDestination);
    //添加文件流向
    logger.addDestination(fileDestination);
    //logger.addDestination(functorDestination);
    //添加槽函数流向
    logger.addDestination(sigsSlotDestination);


}

void CANMaster::destroyLogger()
{
    Logger::destroyInstance();
}
void CANMaster::logSlot(QString str, int level)
{
    if (QsLogging::Level::WarnLevel == level)
    {
        str = "<font color=\"#f1c232\">" + str + "</font>";
    }
    else if (QsLogging::Level::InfoLevel == level)
    {
        str = "<font color=\"#6aa84f\">" + str + "</font>";
    }
    else if (QsLogging::Level::ErrorLevel == level)
    {
        str = "<font color=\"#980000\">" + str + "</font>";
    }
    if(logBrower)
        logBrower->append(str);
}
