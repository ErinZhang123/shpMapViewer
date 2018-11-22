#ifndef SHAPESVIEW_H
#define SHAPESVIEW_H

#include <QWidget>
#include "zalshapes.h"
#include <qpixmap.h>



namespace Ui {
class ShapesView;
}
class ShapesView : public QWidget
{
    Q_OBJECT
public:
    explicit ShapesView(QWidget *parent = 0);
   ~ShapesView();

    virtual void paintEvent(QPaintEvent *);
    void updateWhenDataChanged();
signals:

public slots:
    void updateZoomOut();
    void updateZoomIn();
    void updateZoomAuto();
//    virtual void mousePressEvent(QMouseEvent *);
//    virtual void mouseMoveEvent(QMouseEvent *);
//    virtual void mouseReleaseEvent(QMouseEvent *);

private:
     Ui::ShapesView *ui;
      zal_shape::assistant* _assistant;
      QPixmap *_pMain,*_pMove;
      void flushBkg(QPainter* painter);
      QPoint _ref_mouse_point, _cur_mouse_point;

      bool _mouse_moving;
      bool _mouse_left_pressed;
      bool _pan;
};

#endif // SHAPESVIEW_H
