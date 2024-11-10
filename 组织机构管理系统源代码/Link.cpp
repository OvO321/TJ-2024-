#include "Link.h"
#include "Node.h"



/*
 * @brief 构造函数，构造时为两个结点的连线集合添加连线
 * @param startNode  起始结点指针
 * @param endNode    结束结点指针
 */
Link::Link(Node *startNode,Node*terminalNode){
    this->startNode=startNode;
    this->terminalNode=terminalNode;
    this->startNode->addLink(this);
    this->terminalNode->addLink(this);
    setFlags(QGraphicsItem::ItemIsSelectable);
    setZValue(-0x3ffff);
    this->setColor(Qt::black);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    connectNodes();
}
/*
 * @brief 设置颜色
 * @param color 需要设置的颜色
 */
void Link::setColor(const QColor &color){
    this->color=color;
}
/*
 * @brief 设置颜色
 * @return item类型标识
 */
int Link::type(){
    return UserType+2;
}
/*
 * @brief 设置颜色
 * @return 连线颜色
 */
QColor Link::getColor(){
    return this->color;
}
/*
 * @brief 根据两个结点连线
 */
void Link::connectNodes(){
    //pos()返回相对于场景的位置
    QGraphicsLineItem::setLine(QLineF(startNode->pos(),terminalNode->pos()));
}
/*
 * @brief 析构函数 在两个端点中删除连线
 */
Link::~Link(){
    this->startNode->deleteLink(this);
    this->terminalNode->deleteLink(this);
}



/*
 * @brief 双击事件，显示颜色设置框
 * @param event :鼠标事件指针，存储了当前事件的信息
 */
void Link::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*event){
    QColor color=QColorDialog::getColor(Qt::green,event->widget(),tr("Set color"));
    if(color.isValid()){
        setColor(color);
    }
}

/*
 * @brief 判断直线和外接圆焦点位置
 * @param start
 * @param end
 * @param now
 * @return
 */
bool Link::graphLineContainsLine(QPointF start, QPointF end, QPointF now) {
    QLineF a(start, end);
    QLineF b(start, now);
    QLineF c(now, end);
    if (fabs(a.length() - b.length() - c.length()) < 1e-6){
        return true;
    }
    return false;
}
/*
 * @brief 绘制箭头函数
 * @param start 起始结点
 * @param end   末尾结点
 * @param painter 绘图指针
 */
void Link::paintArrow(Node *start, Node *end, QPainter *painter){
    QPointF startPoint = start->pos();
    QPointF terminalPoint = end->pos();
    QLineF lines(startPoint, terminalPoint);
    qreal length = (end->getRect().width()+end->getInternal()*2)/2;
    qreal dx;
    qreal dy;
    //和x轴垂直的情况
    if (fabs(lines.dx()) < 1e-6) {
        dx = 0;
        dy = length;
    }
    else {
        //斜率
        qreal k = lines.dy() / lines.dx();
        qreal base = sqrt(k * k + 1);
        dx = length / base;
        dy = length * k / base;
    }
    //直线和矩形的焦点坐标(用)
    QPointF offset(dx, dy);
    QPointF now;
    //和矩形有两个点相交，只取一个
    if (graphLineContainsLine(startPoint, terminalPoint, QPointF(terminalPoint + offset))) {
        now = QPointF(terminalPoint + offset);
    } else {
        now = QPointF(terminalPoint - offset);
    }

    QLineF arrowHead(now, startPoint);
    //箭头长度
    arrowHead.setLength(5 + end->getRect().width()/20);
    // 上方
    arrowHead.setAngle(arrowHead.angle() - 30);
    painter->drawLine(arrowHead);
    // 下方
    arrowHead.setAngle(arrowHead.angle() + 60);
    painter->drawLine(arrowHead);

}

/*
 * @brief 绘制函数
 * @param painter 绘图指针
 * @param option
 * @param widget
 */
void Link::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //设置起点和终点
    QPointF startPoint = startNode->pos();
    QPointF terminalPoint =  terminalNode->pos();
    QLineF lines(startPoint, terminalPoint);
    setLine(lines);
    //设置画笔样式
    QPen pen;
    pen.setWidth(3);
    // pen.setColor(this->getColor());
    //选中设置颜色
    if (option->state & QStyle::State_Selected){
        pen.setColor(QColor((color.red() + 125) % 255,
                            (color.green() ) % 255,
                            (color.blue() + 125) % 255)); // 选中时颜色变化
    }
    else{
        pen.setColor(color);
    }
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    //绘制连线
    painter->drawLine(line());
    //绘制箭头
    paintArrow(startNode, terminalNode, painter);
}


/*
 * @brief 确定绘制图形的边界
 * @return 表示图形边界的矩形
 */
QRectF Link::boundingRect()const{
    int w=this->startNode->getRect().width()+this->startNode->getInternal();
    //绘制区域的估计值
    qreal extra = (this->pen().width() + w);
    //p1:起点 p2:终点
    return QRectF(line().p1(),QSizeF(line().p2().x()-line().p1().x(),line().p2().y() - line().p1().y()))
        .normalized().adjusted(-extra,-extra,extra,extra);

}
