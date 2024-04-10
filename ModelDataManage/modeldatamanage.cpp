#include "modeldatamanage.h"
#include "ui_modeldatamanage.h"

ModelDataManage::ModelDataManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelDataManage)
{
    ui->setupUi(this);
}

ModelDataManage::~ModelDataManage()
{
    delete ui;
}
