#ifndef SHAPESVIEW_H
#define SHAPESVIEW_H

#include <QWidget>
#include "zalshapes.h"
#include <qpixmap.h>

class zal_shape::assistant;


class ShapesView : public QWidget
{
    Q_OBJECT
public:
    explicit ShapesView(QWidget *parent = 0);


    virtual void paint();
signals:

public slots:
    void updateZoomOut();
    void updateZoomIn();

private:
      zal_shape::assistant* _assistant;
      QPixmap *_pMain,*_pMove;

};

#endif // SHAPESVIEW_H
