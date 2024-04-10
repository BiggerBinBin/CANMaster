#ifndef MODELDATAMANAGE_H
#define MODELDATAMANAGE_H

#include <QWidget>
#include "ModelDataManage_global.h"
namespace Ui {
class ModelDataManage;
}

class MODELDATAMANAGE_EXPORT ModelDataManage : public QWidget
{
    Q_OBJECT

public:
    explicit ModelDataManage(QWidget *parent = nullptr);
    ~ModelDataManage();

private:
    Ui::ModelDataManage *ui;
};

#endif // MODELDATAMANAGE_H
