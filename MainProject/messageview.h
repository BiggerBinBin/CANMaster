#ifndef MESSAGEVIEW_H
#define MESSAGEVIEW_H

#include <QObject>
#include <QTabWidget>
#include <QSharedPointer>
class MessageView : public QObject
{
    Q_OBJECT
public:
    MessageView(QObject* parent=nullptr);
    QTabWidget* getTabWidget(){return tabWidget;}
private:
    QTabWidget* tabWidget;
private:
    void initWidget();
};

#endif // MESSAGEVIEW_H
