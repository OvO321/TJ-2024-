#ifndef LINK_H
#define LINK_H


#include <QLabel>
#include <QLineEdit>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QColor>
#include <QColorDialog>
#include <QPen>
#include "Node.h"
//避免嵌套出现未声明问题
class Node;
/*
 * @brief 连线类
 */
class Link :public QObject,public QGraphicsLineItem{
    Q_OBJECT
public:
    //由上至下为start到terminal
    Link(Node* startNode,Node*terminalNode);
    //析构函数
    ~Link();
    //设置颜色
    void setColor(const QColor &color);
    //获取颜色
    QColor getColor();
    //添加两个结点之间的连线
    void connectNodes();
    //实际绘制函数
    void paintArrow(Node* start, Node* end, QPainter* painter);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    //重载绘图函数
    bool graphLineContainsLine(QPointF start, QPointF end, QPointF now);
    //绘图范围
    QRectF boundingRect()const override;
protected:
    //双击事件
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*event) override;
    int type();


private:
    //起始结点
    Node *startNode;
    //终端结点
    Node *terminalNode;
    //线条和箭头颜色
    QColor color;
    int length;
};



#endif // LINK_H
