#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QColor>
#include <QSet>
#include <QObject>
#include <QTransform>
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QInputDialog>
#include "Link.h"
#include "propertiesdialog.h"
#include "myView.h"
class MyView;
class Link;
/*
 * @brief 部门类(结点类)
 */
class Node :public QObject,public QGraphicsItem{
    Q_OBJECT
    // Q_DECLARE_TR_FUNCTIONS(Node)
public:
    Node(MyView*parentWidget,int id,QRectF rect=QRectF(0,0,50,50),QString name="",int type=1);
    ~Node();
    //获取绘制矩形
    QRectF getRect() const;
    //设置部门
    void setDepartmentName(QString &name);
    //获取部门
    QString getDepartmentName() const;
    //获取图元类型
    int getType() const;
    //获取虚线框和实际图片之间的距离
    int getInternal() const;
    //添加连线
    void addLink(Link*link);
    //设置父节点
    void setParentNode(Node*node);
    //获取父节点
    Node* getParentNode() const;
    //设置工号:人员-职位表
    void setPersonInfo(QVector<QPair<QString,QPair<QString,QString>>> info);
    //获取工号:人员-职位表
    QVector<QPair<QString,QPair<QString,QString>>> getPersonInfo()const;
    //添加孩子结点
    void addChild(Node *node);
    //移除孩子结点
    void removeChild(Node*node);
    //删除连线
    void deleteLink(Link*link);
    //获取连线
    QSet<Link*> getLinks();
    //判断和另一个结点是否相连
    Link* isConnect(Node*node);
private:
    MyView*parentWidget;
    //唯一标识的结点号
    int id;
    //图片类型
    int imgType;
    //部门名
    QString departmentName;
    //工号:人员职务->名称信息
    QVector<QPair<QString,QPair<QString,QString>>> personInfo;
    //父节点
    Node *parent;
    //孩子结点列表
    QSet<Node*> children;
    //背景颜色
    QColor bgColor;
    //连线列表
    QSet<Link*>Links;
    QColor brushColor;
    //图形大小
    QSizeF itemSize;
    //选中后虚线矩形与实际图形的大小
    int internal=12;
    //保存的图形
    QPixmap itemMap;
    QTransform transform;
    //场景中的坐标(左上角)
    QPointF currentScenePos;
    QPointF pressScenePos;

protected:
    //绘图需要重载的函数
    //确定绘图范围
    QRectF boundingRect() const override;
    //实际绘图函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    //双击事件
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*event);
    //绘图项发生改变调用
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    //获取类型
    int type();
};


#endif // NODE_H
