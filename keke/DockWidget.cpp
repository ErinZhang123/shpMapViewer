#include "DockWidget.h"
#include "ui_DockWidget.h"
#include "zalshapes.h"

DockWidget::DockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockWidget)
{
    ui->setupUi(this);
}

DockWidget::~DockWidget()
{
    delete ui;
}

void DockWidget::updateListview()
{
    ui->listWidget->clear();


    for(int i = 0; i<zal_shape::Shapes::getGlobalData()->size(); i++)
    {
        QString name =
                QString::fromStdString(
                    zal_shape::Shapes::getGlobalData()->at(i)->getName());

        ui->listWidget->insertItem(i, name);

    }
}
