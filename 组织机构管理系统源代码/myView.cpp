#include "MyView.h"
#include <QDebug>
#include <QScrollBar>



/*
 * @brief 构造函数
 * @param parent 父控件指针
 */
MyView::MyView(QWidget *parent)
    : QGraphicsView(parent){
    this->idCount=0;
    //清空结点树
    this->nodeTree.clear();
    mousePos=QPoint(500.0,500.0);

}

/*
 * @brief 获取当前视图结点数
 * @return  当前视图结点数
 */
int MyView::getNodeCount(){
    return (int)this->nodeTree.size();
}


/*
 * @brief 获取当前视图结点集
 * @return  结点集
 */
QSet<Node*>& MyView::getNodeTree(){
    return this->nodeTree;
}
/*
 * @brief 获取当前视图鼠标位置
 * @return  当前鼠标位置
 */
QPointF MyView::getMousePos(){
    return this->mousePos;
}
/*
 * @brief 滚轮事件，调整视角
 * @param  滚轮事件指针
 */
void MyView::wheelEvent(QWheelEvent *event){
    // qDebug()<<"wheelEvent";
    if(event->modifiers() == Qt::ControlModifier){
        QPointF cursorPos = event->position();
        QPointF scenePos=event->position();
        //滚轮向上，放大
        if(event->angleDelta().y()>0){
            viewZoomIn();
        //滚轮向下，缩小
        }else if(event->angleDelta().y()<0){
            viewZoomOut();
        }
        QPointF viewPoint = this->transform.map(scenePos);
        //设置滚动条的数值
        if(this->horizontalScrollBar()->isVisible()){
            this->horizontalScrollBar()->setValue(int(viewPoint.x() - cursorPos.x()));
        }

        if(this->verticalScrollBar()->isVisible()){
            this->verticalScrollBar()->setValue(int(viewPoint.y() - cursorPos.y()));
        }
    }
}
/*
 * @brief 鼠标按下事件
 * @param  事件指针
 */
void MyView::mousePressEvent(QMouseEvent *event){
    QGraphicsView::mousePressEvent(event);
}
/*
 * @brief 键盘按下事件
 * @param  事件指针
 */
void MyView::keyPressEvent(QKeyEvent *event){
    QGraphicsView::keyPressEvent(event);
}
/*
 * @brief 视图按比例缩小
 */
void MyView::viewZoomOut(){
    //水平缩小最大比例
    if(this->transform.m11()/1.1<0.5)
        return;
    //按比例缩小
    this->transform.scale(1/1.1,1/1.1);
    this->setTransform(this->transform);
    // qDebug()<<"zoom Out"<<this->transform.m11();

}
/*
 * @brief 鼠标移动事件
 * @param  事件指针
 */
void MyView::mouseMoveEvent(QMouseEvent *event){
    QPoint posOffset = event->pos();
    this->mousePos=this->mapToScene(posOffset);
    setMouseTracking(true);
    // qDebug()<<"Mouse Move :"<<this->mousePos;
    // this->mousePos=posOffset;
    QGraphicsView::mouseMoveEvent(event);
}
/*
 * @brief 视图按比例放大
 */
void MyView::viewZoomIn(){
    //水平放大最大比例
    if(this->transform.m11()*1.1>2.0)
        return;
    //按110%放大
    this->transform.scale(1.1,1.1);
    this->setTransform(this->transform);
    // qDebug()<<"zoom out"<<this->transform.m11();
}
/*
 * @brief 视图恢复比例
 */
void MyView::viewZoomReset(){
    this->transform.reset();
    this->setTransform(this->transform);
}


/*
 * @brief 获取转换值
 */
QTransform& MyView::getTransform(){
    return this->transform;
}

/*
 * @brief 自动增加id值
 */
void MyView::atuoIncrement(){
    this->idCount++;
}

/*
 * @brief 获取id值，使用随机数
 */
int MyView::getID(){
    return this->idCount;
}

/*
 * @brief 获取人员表
 */
QVector<Person>& MyView::getPersonTable(){
    return this->personTable;
}

/*
 * @brief 重新调整人员表
 * @param info:工号-人员-职位表
 */
void MyView::resetPersonTable(QVector<QPair<QString,QPair<QString,QString>>> info){
    int infoSize=(int)info.size();
    for (int i = 0; i < infoSize; i++) {
        int isRepeat=false;
        foreach (auto iter, this->personTable) {
            //有重复项，退出
            if(iter.id==info[i].first){
                isRepeat=true;
                break;
            }
        }
        if(!isRepeat){
            this->personTable.append({info[i].first,info[i].second.first});
        }
    }
}
