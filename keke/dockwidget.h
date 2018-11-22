#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <vector>

namespace Ui {
class DockWidget;
}

class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockWidget(QWidget *parent = 0);
    ~DockWidget();

    void updateListview();

private:
    Ui::DockWidget *ui;
};
#endif // DOCKWIDGET_H
