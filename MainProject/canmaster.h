#ifndef CANMASTER_H
#define CANMASTER_H

#include <QMainWindow>
#include <QScopedPointer>
QT_BEGIN_NAMESPACE
namespace Ui { class CANMaster; }
QT_END_NAMESPACE


class Communicate;

class QPushButton;
class QLabel;
class QComboBox;

class CANMaster : public QMainWindow
{
    Q_OBJECT

public:
    CANMaster(QWidget *parent = nullptr);
    ~CANMaster();

private:
    Ui::CANMaster *ui;
    QScopedPointer<Communicate>m_CommuniPtr;
    QComboBox* comboxDevType = nullptr;
    QComboBox* comboxDevChannel = nullptr;
    QPushButton* pbRefreshDev = nullptr;
    QComboBox* comboxModel = nullptr;
    QComboBox* comboxBaudRate = nullptr;

private:
    void InitGUI();
};
#endif // CANMASTER_H
