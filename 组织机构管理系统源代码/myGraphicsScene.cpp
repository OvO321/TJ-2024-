#include "myGraphicsScene.h"
#include <QMenu>
#include <QRectF>
#include <QGraphicsItem>
#include <QDebug>

/*
 * @brief 构造函数
 * @param size  场景尺寸
 * @param type  指向的结点类型
 * @param parent 父控件指针
 */
MyGraphicsScene::MyGraphicsScene(const QSizeF &size,  QObject *parent)
    : QGraphicsScene(QRectF(0, 0, size.width(), size.height()), parent){

}
/*
 * @brief 析构函数
 */
MyGraphicsScene::~MyGraphicsScene(){

}



/*
 * @brief 鼠标移动事件
 * @param event 事件指针
 */
// void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
//     QGraphicsScene::mouseMoveEvent(event);
// }
/*
 * @brief 鼠标放下事件
 * @param event 事件指针
 */
void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseReleaseEvent(event);
}
/*
 * @brief 滚轮事件
 * @param event 事件指针
 */
void MyGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event){
     QGraphicsScene::wheelEvent(event);
}
/*
 * @brief 开始拖拽事件
 * @param event 事件指针
 */
void MyGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
    event->accept();
    QGraphicsScene::dragEnterEvent(event);
}
/*
 * @brief 拖拽移动事件
 * @param event 事件指针
 */
void MyGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event){
    event->accept();
}
/*
 * @brief 放下事件
 * @param event 事件指针
 */
void MyGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event){
    event->acceptProposedAction();
    QGraphicsScene::dropEvent(event);
}
/*
 * @brief 绘制背景
 * @param painter 绘图指针
 * @param rect 绘制范围
 */
void MyGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect){
    //背景色
    painter->setBrush(QColor("#FFFFFF"));
    painter->setPen(QColor("#FFFFFF"));
    painter->drawRect(rect);

    int left = qFloor(rect.left());
    int right = qCeil(rect.right());
    int top = qFloor(rect.top());
    int bottom = qCeil(rect.bottom());
    //调整位置
    int _left = left - left % 10;
    int _top  = top  - top  % 10; /* 左上角第一个交叉点 */

    QVector<QLine> light_lines, dark_lines;
    int wh = 50;
    for (int i = _left; i <= right; i += 10){
        if(i % wh == 0)
            dark_lines.append(QLine(i, top, i, bottom));
        else
            light_lines.append(QLine(i, top, i, bottom));
    }

    for (int j = _top; j <= bottom; j += 10) {
        if(j % wh == 0)
            dark_lines.append(QLine(left, j, right, j));
        else
            light_lines.append(QLine(left, j, right, j));
    }

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawLines(light_lines);

    painter->setPen(QColor("#000000"));
    painter->drawLines(dark_lines);
}

