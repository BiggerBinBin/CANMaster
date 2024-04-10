#include "messageview.h"

MessageView::MessageView(QObject*parent):QObject(parent)
{
    initWidget();
}

void MessageView::initWidget()
{
    tabWidget = (new QTabWidget);
    tabWidget->addTab(new QWidget(),QIcon(),QString(tr("Receive/Transmit")));
    tabWidget->addTab(new QWidget(),QIcon(),QString(tr("Detailed")));
}

