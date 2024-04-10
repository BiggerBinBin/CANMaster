#ifndef CANMASTER_H
#define CANMASTER_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class CANMaster; }
QT_END_NAMESPACE

//calss declaration
class Communicate;
class QPushButton;
class QLabel;
class QComboBox;
class MessageView;
class QTextBrowser;
class ModelDataManage;

class CANMaster : public QMainWindow
{
    Q_OBJECT

public:
    CANMaster(QWidget *parent = nullptr);
    ~CANMaster();

private:
    Ui::CANMaster *ui;

    //CAN/LIN devices ptr
    QScopedPointer<Communicate>m_CommuniPtr;

    //top bar widdets
    QComboBox* comboxDevType = nullptr;
    QComboBox* comboxDevChannel = nullptr;
    QPushButton* pbRefreshDev = nullptr;
    //select model button
    QComboBox* comboxModel = nullptr;
    //select baudtate button
    QComboBox* comboxBaudRate = nullptr;
    //open device button
    QPushButton* pbOpenDevice = nullptr;
    //platform select button
    QComboBox* comboxPlatform = nullptr;
    //open model data manage ui
    QPushButton* pbModelManage = nullptr;

    //show receive/transmit can message
    MessageView* messageview;
    //log show browser
    QTextBrowser* logBrower = nullptr;

    //global model data manager class
    QScopedPointer<ModelDataManage>modelManage;

    static QStringList platform;
    static QStringList baudRate;

private:
    void InitGUI();
    void ConnectWidget();
    void initLogger();
    void destroyLogger();
private slots:
    void on_comboxDevType_IndexChanged(int index);
    void on_comboxDevChannel_IndexChanged(int index);
    void on_pbRefreshDev_Clicked(bool b);
    void on_comboxBaudRate_IndexChanged(int index);
    void on_pbOpenDevice_Clicked(bool b);
    void on_comboxPlatform_IndexChanged(int index);
    void on_pbModelManage_clicked(bool b);

    //log slot function
    void logSlot(QString str, int level);

};
#endif // CANMASTER_H
