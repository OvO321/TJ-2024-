#include "Node.h"
#include "Link.h"


/*
 * @brief 构造函数
 * @param parentWidget 父控件
 * @param id 结点标识符
 * @param rect 图形项矩形
 * @param name 结点名(部门名)
 * @param map  结点图片类型
 */
Node::Node(MyView*parentWidget,int id,QRectF rect,QString name,int type){
    //设置标识号
    this->parentWidget=parentWidget;
    this->id=id;
    this->parent=nullptr;
    //设置部门名
    this->departmentName=name;
    //设置背景颜色
    this->bgColor=Qt::white;
    //可以移动和选择
    setFlags(ItemIsMovable|ItemIsSelectable);
    //设置背景色为白色
    QPixmap map = QPixmap(":/images/Department-icons/department"+QString::number(type)+".png");
    QImage image=map.toImage();
    QPainter painter(&image);
    painter.setCompositionMode(QPainter::CompositionMode_Darken);
    painter.fillRect(image.rect(), QColor(Qt::white));
    this->itemMap=QPixmap::fromImage(image);
    //
    // this->itemMap = map;
    //设置类型，决定图片
    this->imgType=type;
    bgColor=Qt::white;
    //获取图片尺寸
    this->itemSize = QSizeF(rect.width(),rect.height());
    //设置坐标
    this->currentScenePos = rect.topLeft();
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    //启动itemChange事件
    setFlag(ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
    //设置添加位置
    this->setPos(this->currentScenePos);
    this->setZValue(1);

}
/*
 * @brief 析构函数，删除相关联的所有连线
 */
Node::~Node(){
    foreach (Link *link, Links) {
        delete link;
    }
}

/*
 * @brief 返回类型标识值
 * @return item类型标识
 */
int Node::type(){
    return UserType+1;
}
/*
 * @brief 设置部门名
 * @param name:部门名
 */
void Node::setDepartmentName(QString &name){
    //可能改变项的大小，需要重新调整图形大小
    prepareGeometryChange();
    this->departmentName=name;
    update();
}
/*
 * @brief 返回部门名
 * @return 部门名
 */
QString Node::getDepartmentName() const{
    return this->departmentName;
}



/*
 * @brief 设置人员-职位信息
 * @param 人员-职位信息
 */
void Node::setPersonInfo(QVector<QPair<QString,QPair<QString,QString>>> info){
    this->personInfo=info;
}
/*
 * @brief 返回人员-职位信息
 * @return (人员-职位)数组
 */
QVector<QPair<QString,QPair<QString,QString>>> Node::getPersonInfo() const{
    return this->personInfo;
}


/*
 * @brief 添加连线
 * @param link 连线指针
 */
void Node::addLink(Link*link){
    this->Links.insert(link);
}

/*
 * @brief 删除连线
 * @param link 连线指针
 */
void Node::deleteLink(Link*link){
    this->Links.remove(link);
}

/*
 * @brief 获取图形项矩形
 * @return 表示图形的矩形
 */
QRectF Node::getRect() const{
    // QPointF centerPos(0,0);
    QRectF rect(0, 0,this->itemSize.width(), this->itemSize.height());
    //调整原点为自身中心
    rect.translate(-rect.center());
    return rect;
}
/*
 * @brief 获取间隔长度
 * @return 间隔长度
 */
int Node::getInternal() const{
    return this->internal;
}

/*
 * @brief 获取类型
 * @return 结点类型
 */
int Node::getType()const{
    return this->imgType;
}
/*
 * @brief 获取父结点
 * @return 父结点
 */
Node* Node::getParentNode()const{
    return this->parent;
}
/*
 * @brief 设置父结点
 * @param node 父结点
 */
void Node::setParentNode(Node*node){
    this->parent=node;
}
/*
 * @brief 获取连线集合
 * @return  连线集合
 */
QSet<Link*> Node::getLinks(){
    return this->Links;
}

/*
 * @brief 增加孩子结点
 * @param node 增加的结点
 */
void Node::addChild(Node *node){
    this->children.insert(node);
    // this->children.append(node);
}

/*
 * @brief 删除孩子结点
 * @param node 增加的结点
 */
void Node::removeChild(Node *node){
    this->children.remove(node);
}


/*
 * @brief 检测两个结点之间是否连线
 * @param node 另一个结点
 */
Link* Node::isConnect(Node*node){
    if(node==nullptr){
        return nullptr;
    }
    else{
        for(Link* link1: this->Links){
            for(Link* link2:node->getLinks()){
                if(link1==link2){
                    return link1;
                }
            }
        }
    }
    return nullptr;
}


/*
 * @brief 确定绘制图形的边界
 * @return 表示图形边界的矩形
 */
 QRectF Node::boundingRect() const{
    QRectF rect = this->getRect();
    //设置边框范围
    rect.adjust(-this->internal, -this->internal, this->internal, this->internal);
    return  rect;
}


/*
 * @brief 绘制函数
 * @param painter 绘图指针
 * @param option
 * @param widget
 */
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //反锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    //绘制部门名
    painter->setFont(QFont("Arial", this->internal/2+2));
    painter->setPen(QPen(Qt::black));
    QRectF rect=this->getRect();
    rect.adjust(-this->internal,-this->internal,this->internal,this->internal);
    painter->drawText(rect,Qt::AlignBottom|Qt::AlignHCenter,this->departmentName);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    //绘制图形
    painter->drawPixmap(this->getRect(), this->itemMap, this->itemMap.rect());
    if (option->state&QStyle::State_Selected){
        QRectF rect = this->getRect();
        // 边框颜色
        QColor color = QColor(Qt::gray);
        // 绘制虚线
        painter->setPen(QPen(color, 0, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        rect.adjust(-this->internal, -this->internal, this->internal, this->internal);
        painter->drawRect(rect);
    }
}

/*
 * @brief 图形项改变后调用
 * @param change 改变类型
 * @param value
 * @return
 */
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value){
    // qDebug()<<change;
    if (change == QGraphicsItem::ItemSelectedChange){
        //每次图形项大小改变重新绘制
        prepareGeometryChange();
    }
    //项改变后连接线重新绘制
    if(change==ItemPositionChange){
        foreach (Link *link, this->Links) {
            link->connectNodes();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
/*
 * @brief 双击事件打开属性对话框
 * @param event : 存储事件信息
 */
void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*event){
    // qDebug()<<"double";
    QVector<QPair<QString,QPair<QString,QString>>> info;
    QPair<QString,QPair<QString,QString>> pair;
    auto t=parentWidget->getPersonTable();
    for(int i=0;i<t.size();i++){
        qDebug()<<t[i].personName;
        qDebug()<<t[i].id;
    }
    //获取属性信息
    QStringList list=PropertiesDialog::getStrings(this,event->widget(),this->parentWidget->getPersonTable(),false);
    if(!list.isEmpty()){
        this->setDepartmentName(list[0]);
        //list[1]不做处理
        info.clear();
        int rowCount=list[2].toInt();
        //设置表格
        for(int i=0;i<rowCount;i++){
            pair.first=list[3+i*3];
            pair.second.first=list[3+i*3+1];
            pair.second.second=list[3+i*3+2];
            info.append(pair);
        }
        this->setPersonInfo(info);
        this->parentWidget->resetPersonTable(info);
    }
}






