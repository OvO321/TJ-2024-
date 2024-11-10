#ifndef MYVIEW_H
#define MYVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QAction>
#include <QTransform>
#include "Node.h"
#include "person.h"

/*
 * @brief 绘图视图类
 */
class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QWidget *parent=nullptr);
    //放大视图
    void viewZoomIn();
    //缩小视图
    void viewZoomOut();
    //重置视图
    void viewZoomReset();
    //获取结点数
    int getNodeCount();
    //设置结点数
    void setNodeCount(int);
    //获取当前场景的鼠标坐标
    QPointF getMousePos();
    //获取结点树
    QSet<Node*>& getNodeTree();
    //获取转换值
    QTransform &getTransform();
    //自动增加id值
    void atuoIncrement();
    //获取id值
    int getID();
    //获取人员表
    QVector<Person>& getPersonTable();
    //重新设置人员表
    void resetPersonTable(QVector<QPair<QString,QPair<QString,QString>>> info);
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    // //右键菜单
    // void contextMenuEvent(QContextMenuEvent *event);

private slots:


private:
    //计数器，用来分配结点id
    int idCount;

    //视图内的结点个数
    int nodeCount;

    //存储结点情况
    QSet<Node*> nodeTree;
    QTransform transform;
    //鼠标位置
    QPointF mousePos;
    //人员表
    QVector<Person> personTable;
};


#endif // MYVIEW_H
