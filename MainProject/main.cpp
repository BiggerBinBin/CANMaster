#include "canmaster.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CANMaster w;
    w.setAttribute(Qt::WA_DeleteOnClose,true);
    w.show();
    return a.exec();
}
