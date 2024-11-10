#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QDrag>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QKeyEvent>
#include "Node.h"

/*
 * @brief 绘图场景类
 */
class MyGraphicsScene: public QGraphicsScene{

    Q_OBJECT
public:
    MyGraphicsScene(const QSizeF &size, QObject *parent = nullptr);
    ~MyGraphicsScene();
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:

};









#endif // MYGRAPHICSSCENE_H
