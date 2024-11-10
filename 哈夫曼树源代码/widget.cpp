#include "widget.h"
#include "./ui_widget.h"
#include "HuffmanTree.h"



/*
 * ToDo: 1.美化绘图效果(doing)
 *
 *
*/

/*
 * @brief 构造函数
 * @param parent  父组件指针
 * @param ui      Qt designer指针，指向图形设计界面
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget){
    ui->setupUi(this);
    //界面不能被放大或缩小
    this->setMaximumSize(QSize(this->width(),this->height()));
    this->setMinimumSize(QSize(this->width(),this->height()));
    //初始设置不可选择
    this->ui->ensureButton->setEnabled(false);
    this->ui->exportPhotoButton->setEnabled(false);
    this->ui->exportTableButton->setEnabled(false);
    this->ui->deleteButton->setEnabled(false);
    //绘图模块
    int posX=this->ui->graph->pos().x();
    int posY=this->ui->graph->pos().y();
    int height=this->ui->graph->height();
    int width=this->ui->graph->width();
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(posX,posY, width, height);
    widget = new QWidget(scrollArea);
    scrollArea->setWidget(widget);
    widget->setGeometry(posX, posY, width, height);
    //注册事件过滤器
    widget->installEventFilter(this);
    //设置背景色
    widget->setStyleSheet("background-color:white;");


    //频率表
    ui->keyWordTable->setColumnCount(3);
    QStringList header;
    header<<"序号"<<"关键字"<<"频率";
    ui->keyWordTable->setHorizontalHeaderLabels(header);
    //表头不能拖动
    ui->keyWordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->keyWordTable->setColumnWidth(0,140);
    ui->keyWordTable->setColumnWidth(1,140);
    //在前两个标题宽度确定的情况下，最后一个宽度由总长度减去前两个标题宽度
    ui->keyWordTable->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    //隐藏默认显示的序号
    ui->keyWordTable->verticalHeader()->setVisible(false);
    header.clear();
    // ui->keyWordTable->setStyleSheet("QTableWidget::item{alignment:center}");
    //编码表
    ui->encoderTable->setColumnCount(3);
    header<<"序号"<<"关键字"<<"编码";
    ui->encoderTable->setHorizontalHeaderLabels(header);
    ui->encoderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->encoderTable->setColumnWidth(0,120);
    ui->encoderTable->setColumnWidth(1,120);
    ui->encoderTable->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->encoderTable->verticalHeader()->setVisible(false);
    // //添加快捷键
    ui->ensureButton->setShortcut(Qt::Key_Enter);

}

/*
 * @brief 析构函数，删除ui
 *
 */
Widget::~Widget(){
    delete ui;
}

/*
 * @brief 反转字符串
 * @param str  输入字符串
 */
void Widget::reverseString(QString &str){
    QString subStr;
    int length=(int)str.size();
    for(int i=length-1;i>=0;i--){
        subStr+=str[i];
    }
    str=subStr;
}


/*
 * @brief 记录输入字符的频率
 * @param str  输入字符串
 */
void Widget::recordFrequency(const QString &str){
    //清空之前写入的字符和构造的哈夫曼树
    this->num.clear();
    this->huffmanTree.clear();
    //哈希表 字符->频率
    QHash<QString, int> map;
    for (auto x : str) {
        //如果没找到，就插入哈希表中
        if (map.contains(x)==false) {
            map.insert(x,1);
        }
        //否则频率+1
        else{
            map[x]+=1;
        }
    }
    auto iter = map.constBegin();
    //插入数组中
    for (; iter != map.constEnd(); iter++) {
        this->num.append({iter.key(),iter.value()});
    }
}


/*
 * @brief 在当前的哈夫曼树中找出权值最小和此小的两个结点的位置
 * @param leftChild  左孩子结点位置
 * @param rightChild 右孩子结点位置
 *        左孩子权值<=右孩子权值
 */
void Widget::select(int &leftChild,int &rightChild){
    int minV = 0x3fffff;
    int pos = -1;
    //获取哈夫曼树的结点个数
    int n=(int)this->huffmanTree.size();
    //找出最小权值的位置
    for (int i = 0; i < (int)n; i++) {
        if(this->huffmanTree[i]->weight<minV&&!this->huffmanTree[i]->isSelected) {
            minV = this->huffmanTree[i]->weight;
            pos = i;
        }
    }
    leftChild = pos;
    this->huffmanTree[leftChild]->isSelected = true;
    //找出次小权值的位置
    minV = 0x3fffff;
    pos = -1;
    for (int i = 0; i < n; i++) {
        if (this->huffmanTree[i]->weight < minV&&i!=leftChild&&!this->huffmanTree[i]->isSelected) {
            minV = this->huffmanTree[i]->weight;
            pos = i;
        }
    }
    rightChild = pos;
    this->huffmanTree[rightChild]->isSelected = true;
    //左结点权值<=右结点权值
    if(this->huffmanTree[leftChild]->weight>this->huffmanTree[rightChild]->weight){
        int tmp=leftChild;
        leftChild=rightChild;
        rightChild=tmp;
    }

}


/*
 * @brief 根据输入的文本或关键字构造哈夫曼树
 */
void Widget::construct(){
    //关键字个数
    int n = (int)this->num.size();
    //添加哈夫曼树的结点，前n个为叶子结点
    for (int i = 0; i < n; i++) {
        this->huffmanTree.append(new HuffmanTree(true,false,this->num[i].second,
                                                 this->num[i].first,-1,-1,-1,i));
    }
    //按照算法生成的总结点数量
    int m = 2 * n - 1;
    int leftChild = -1;
    int rightChild = -1;
    //每次遍历当前的所有结点，找到最小的两个结点，生成它的
    //双亲结点，为它的孩子结点记录双亲，为它自己记录左右孩子位置(左小于等于右)
    for (int i = n; i < m; i++) {
        //获取最小的两个结点
        select(leftChild, rightChild);
        //获取权值的和
        int weight = this->huffmanTree[leftChild]->weight + this->huffmanTree[rightChild]->weight;
        //添加该双亲结点
        this->huffmanTree.append(new HuffmanTree(false,false,weight,
                                                 "-1",-1,leftChild,rightChild,i));
        //设置两个孩子结点的双亲结点
        huffmanTree[leftChild]->parent = i;
        huffmanTree[rightChild]->parent = i;
    }
    //生成后哈夫曼树后获取根节点
    setRoot();
}

/*
 * @brief 对哈夫曼树进行编码
 */
void Widget::encoder(){
    //清除原先的编码表
    this->encoderList.clear();
    //当前位置
    int now = 0;
    //双亲当前位置
    int parent = 0;
    //关键字个数
    int n=(int)this->num.size();
    this->encoderList.resize(n);
    for (int i = 0; i < n;i++) {
        now = i;
        //只要不是根结点
        while (this->huffmanTree[now]->parent != -1) {
            parent = this->huffmanTree[now]->parent;
            //左孩子置0
            if (this->huffmanTree[parent]->leftChild == now) {
                this->encoderList[i].append("0");
            }
            //右孩子置1
            else{
                this->encoderList[i].append("1");
            }
            now = parent;
        }
        //反转字符串
        reverseString(this->encoderList[i]);
    }
}

/*
 * @brief 槽函数，点击确认后生成图片和填充表格
 */
void Widget::on_ensureButton_clicked(){
    //获取输入文本
    QString s=ui->textInput->text();
    //记录频率和关键字
    recordFrequency(s);
    //构造哈夫曼树
    construct();
    //对哈夫曼树进行编码
    encoder();
    //插入编码表
    insertEncoderTable();
    //插入关键字表
    insertKeyWordTable();
    setUpdatesEnabled(true);
    //这里如果设置update，不一定会立即执行paint，不能及时更新
    //滚动区域大小，无法设置滚动条居中
    this->widget->repaint();
    //设置滚动条居中
    int value=this->scrollArea->horizontalScrollBar()->maximum();
    this->scrollArea->horizontalScrollBar()->setValue(value/2);
}

/*
 * @brief 事件过滤器函数，需要处理子控件的绘图事件，且子控件需要
 * 先使用注册函数才能生效
 */
bool Widget::eventFilter(QObject *obj, QEvent *event){
    // qDebug()<<event->type();
    //对象为Widget时，进行绘制事件，绘制函数为paint，绘制返回完成的信号
    if((obj == this->widget &&event->type() == QEvent::Paint)){
        paint();
    }
    return QWidget::eventFilter(obj,event);
}

/*
 * @brief 绘制哈夫曼树
 */
void Widget::paint(){
    //绘图对象
    QPainter painter(this->widget);
    //设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //绘图区域
    QRect rect=this->widget->rect();
    //先序遍历绘制
    if(root!=nullptr){
        int x=0;
        int y=0;
        int w=0;
        int h=0;
        //获取绘图区域原点和宽度、高度
        rect.getRect(&x,&y,&w,&h);
        painter.setViewport(x,y,w,h);
        //最大深度
        int maxDeepth=getMaxDeepth();
        //根据最大深度，计算出最左/最右结点和中心结点(根结点之间)的距离，也是实际绘图宽度的一半
        int startMove=1;
        startMove=qPow(2,maxDeepth-1);
        //水平间距
        int diameter=30;
        //垂直距离
        //需要根据最大深度进行调整
        int addNum=maxDeepth>5?(maxDeepth-5)*10:0;
        int height=60+addNum;
        //绘图起始横坐标
        int posX=w/2-diameter/2+x;
        //绘图起始总坐标
        int posY=20+y;
        //视图宽度和高度
        int viewWidth=this->ui->graph->width();
        int viewHeight=this->ui->graph->height();
        //如果实际的宽度或高度超出当前视图范围
        //重新调整视图区域大小
        if(diameter*(startMove*2)*2>viewWidth||height*(maxDeepth+2)>viewHeight){
             this->widget->resize(diameter*(startMove*2)*2,height*(maxDeepth+2));
        }
        else{
            this->widget->resize(viewWidth,viewHeight);
        }
        drawNode(painter,posX,posY,root->pos,diameter,height,startMove,1);
    }
}



/*
 * @brief 获取当前哈夫曼树的最大深度
 * @return 当前哈夫曼树最大深度
 *        0: 还未构建哈夫曼树
 *        其他:最大深度
 */
int Widget::getMaxDeepth(){
    //最大深度
    int maxDeepth=0;
    QQueue<HuffmanTree*> queue;
    queue.append(this->root);
    //BFS获取最大深度
    while (!queue.isEmpty()) {
        int n=queue.size();
        maxDeepth++;
        for(int i=0;i<n;i++){
            HuffmanTree*pHf=queue.dequeue();
            if(pHf->leftChild!=-1){
                queue.append(this->huffmanTree[pHf->leftChild]);
            }
            if(pHf->rightChild!=-1){
                queue.append(this->huffmanTree[pHf->rightChild]);
            }
        }
    }
    return maxDeepth;
}


/*
 * @brief 绘制结点
 * @param painter 绘图对象
 * @param posX    绘图点x坐标
 * @param posY    绘图点y坐标
 * @param i        当前在num/huffmanTree数组中的位置
 * @param diameter 水平间距以及矩形长宽和圆形直径
 * @param height   垂直距离
 * @param n        当前两个结点之间的水平距离
 * @param deepth   当前深度
 */
void Widget::drawNode(QPainter &painter,int posX, int posY, int i,int diameter,int height,int n,int deepth){
    //权值
    int weight=this->huffmanTree[i]->weight;
    //关键字
    QString keyWord=this->huffmanTree[i]->keyWord;
    //当前数字长度
    int len=(int)QString::number(weight).length();
    //
    QPen pen;
    //写出权值
    //自适应字体大小，设置字体为 Arial
    QFont font("Arial", diameter/(len+1));
    painter.setFont(font);
    painter.drawText(posX+0.2*diameter,posY+diameter*0.6,QString::number(weight));
    //下一次两个结点(该结点和它的子结点)之间的水平距离
    int next=n/2;
    //剩余字符设置固定大小
    font.setPointSize(diameter/2);
    painter.setFont(font);
    //如果是叶子结点，写出关键字
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    if(this->huffmanTree[i]->isLeaf){
        painter.drawEllipse(posX,posY,diameter,diameter);
        pen.setWidth(1);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(posX+0.2*diameter,posY+diameter*1.8,keyWord);
    }
    //否则是方框
    else{
        painter.drawRect(posX,posY,diameter,diameter);
    }
    pen.setWidth(4);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    if (this->huffmanTree[i]->leftChild != -1) {
        //画左边线
        painter.drawLine(posX+diameter/2,posY+diameter,posX-n*diameter+diameter*0.5,posY+height);
        //画数字
        pen.setWidth(1);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(posX-n*diameter/2+diameter/2-6,posY+diameter/2+height/2,"0");
        drawNode(painter,posX-n*diameter,posY+height,this->huffmanTree[i]->leftChild,diameter,height,next,deepth+1);
    }
    if (this->huffmanTree[i]->rightChild != -1) {
        //画右边线
        painter.drawLine(posX+diameter/2,posY+diameter,posX+n*diameter+diameter*0.5,posY+height);
        //画数字
        pen.setWidth(1);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(posX+n*diameter/2+diameter/2+2,posY+diameter/2+height/2,"1");
        drawNode(painter,posX+n*diameter,posY+height,this->huffmanTree[i]->rightChild,diameter,height,next,deepth+1);
    }

}

/*
 * @brief 设置当前哈夫曼树的根结点
 */
void Widget::setRoot(){
    this->root=nullptr;
    for (auto x : this->huffmanTree) {
        if (x->parent == -1) {
            root = x;
            break;
        }
    }
}



/*
 * @brief 槽函数，产生随机数
 * @param arg1  当前文本字符串
 */
void Widget::on_textInput_textChanged(const QString &arg1){
    //至少有两种字符才可以编码
    //哈希表 字符->频率
    QHash<QString, int> map;
    for (auto x : arg1) {
        //如果没找到，就插入哈希表中
        if (map.contains(x)==false) {
            map.insert(x,1);
        }
        //否则频率+1
        else{
            map[x]+=1;
        }
    }
    auto iter = map.constBegin();
    int count=0;
    this->ui->deleteButton->setEnabled(!arg1.isEmpty());
    //插入数组中
    for (; iter != map.constEnd(); iter++) {
        count++;
    }
    if(count<2){
        this->ui->ensureButton->setEnabled(false);
        this->ui->exportTableButton->setEnabled(false);
    }
    else{
        this->ui->ensureButton->setEnabled(true);
        this->ui->exportPhotoButton->setEnabled(true);
        this->ui->exportTableButton->setEnabled(true);
    }
}

/*
 * @brief 槽函数，清空文本框和表格内容
 *
 */
void Widget::on_clearButton_clicked(){
    //清空文本编辑框
    this->ui->textInput->clear();
    //清空编码栏
    while (ui->encoderTable->rowCount() > 0) {
        ui->encoderTable->removeRow(0);
    }
    //清空num
    this->num.clear();
    QStringList header;
    header<<"序号"<<"关键字"<<"编码";
    ui->encoderTable->setHorizontalHeaderLabels(header);
    header.clear();
    //清空频率栏
    while (ui->keyWordTable->rowCount() > 0) {
        ui->keyWordTable->removeRow(0);
    }
    header<<"序号"<<"关键字"<<"频率";
    ui->keyWordTable->setHorizontalHeaderLabels(header);
}



/*
 * @brief 槽函数，导入文件
 *
 */
void Widget::on_importTextButton_clicked(){
    //获取上传文件路径
    QString str=QFileDialog::getOpenFileName(this,"导入文件","","*txt");
    //判断非空
    if(str.isEmpty()){
        return;
    }
    // auto dataPath=QApplication::applicationDirPath();
    // auto importPath=dataPath+str.section("/",-1);
    //打开文件
    QFile file(str);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"错误","无法导入文件");
        return ;
    }
    //获取文件内容
    QTextStream in(&file);
    this->ui->textInput->setText(in.readAll());

}



/*
 * @brief 插入编码列表数据
 *
 */
void Widget::insertEncoderTable(){
    //获取当前关键字的个数
    int n=(int)this->encoderList.size();
    int nCount=0;
    QTableWidgetItem *item[3];
    //清除原先存在的表格
    while (ui->encoderTable->rowCount() > 0) {
        ui->encoderTable->removeRow(0);
    }
    // ui->encoderTable->clear();
    QStringList header;
    header<<"序号"<<"关键字"<<"编码";
    ui->encoderTable->setHorizontalHeaderLabels(header);
    for(int i=0;i<n;i++){
        //获取当前行数
        nCount=ui->encoderTable->rowCount();
        //在该位置插入
        ui->encoderTable->insertRow(nCount);
        item[0]=new QTableWidgetItem(QString("%1").arg(i+1));
        //设置不可编辑
        item[0]->setFlags(item[0]->flags() & ~Qt::ItemIsEditable);
        item[0]->setTextAlignment(Qt::AlignCenter);
        ui->encoderTable->setItem(i,0,item[0]);

        item[1]=new QTableWidgetItem(this->num[i].first);
        item[1]->setFlags(item[1]->flags() & ~Qt::ItemIsEditable);
        item[1]->setTextAlignment(Qt::AlignCenter);
        ui->encoderTable->setItem(i,1,item[1]);

        item[2]=new QTableWidgetItem(this->encoderList[i]);
        item[2]->setFlags(item[2]->flags() & ~Qt::ItemIsEditable);
        item[2]->setTextAlignment(Qt::AlignCenter);
        ui->encoderTable->setItem(i,2,item[2]);
        // qDebug()<<nCount;
    }
    // qDebug()<<"End";
}



/*
 * @brief 插入关键字频率列表数据
 *
 */
void Widget::insertKeyWordTable(){
    //获取当前关键字的个数
    int n=(int)this->num.size();
    int nCount=0;
    QTableWidgetItem *item[3];
    //清除原先存在的表格
    while (ui->keyWordTable->rowCount() > 0) {
        ui->keyWordTable->removeRow(0);
    }
    // ui->encoderTable->clear();
    QStringList header;
    header<<"序号"<<"关键字"<<"频率";
    ui->keyWordTable->setHorizontalHeaderLabels(header);
    for(int i=0;i<n;i++){
        //获取当前行数
        nCount=ui->keyWordTable->rowCount();
        //在该位置插入一行
        ui->keyWordTable->insertRow(nCount);
        item[0]=new QTableWidgetItem(QString("%1").arg(i+1));
        //设置不可编辑
        //设置内容
        item[0]->setFlags(item[0]->flags() & ~Qt::ItemIsEditable);
        item[0]->setTextAlignment(Qt::AlignCenter);
        ui->keyWordTable->setItem(i,0,item[0]);
        //关键字和频率可以修改
        item[1]=new QTableWidgetItem(this->num[i].first);
        item[1]->setFlags(item[1]->flags());
        item[1]->setTextAlignment(Qt::AlignCenter);
        ui->keyWordTable->setItem(i,1,item[1]);

        item[2]=new QTableWidgetItem(QString::number(this->num[i].second));
        item[2]->setFlags(item[2]->flags());
        item[2]->setTextAlignment(Qt::AlignCenter);
        ui->keyWordTable->setItem(i,2,item[2]);
        // qDebug()<<nCount;
    }
}


/*
 * @brief 槽函数，保存已经生成的关键字-编码表，
 * 保存路径可以自由选择
 *
 */

void Widget::on_exportTableButton_clicked(){
    //获取保存路径
    QString filepath=QFileDialog::getSaveFileName(this,tr("保存表格"),".",tr(" (*.xlsx)"));
    //如果保存路径不为空
    if(!filepath.isEmpty()){
        QAxObject *excel = new QAxObject(this);
        //连接Excel控件
        excel->setControl("Excel.Application");
        //不显示窗体
        excel->dynamicCall("SetVisible (bool Visible)","false");
        //不显示任何警告信息。
        excel->setProperty("DisplayAlerts", false);
        //获取工作簿集合
        QAxObject *workBooks = excel->querySubObject("WorkBooks");
        //新建一个工作簿
        workBooks->dynamicCall("Add");
        //获取当前工作簿
        QAxObject *workBook = excel->querySubObject("ActiveWorkBook");
        //获取工作表集合
        QAxObject *workSheets = workBook->querySubObject("Sheets");
        //获取工作表集合的工作表1，即sheet1
        QAxObject *workSheet = workSheets->querySubObject("Item(int)",1);
        //设置表头值
        for(int i=1;i<ui->encoderTable->columnCount()+1;i++){
            //设置设置某行某列
            QAxObject *Range = workSheet->querySubObject("Cells(int,int)", 1, i);
            Range->dynamicCall("SetValue(const QString &)",ui->encoderTable->horizontalHeaderItem(i-1)->text());
        }
        //设置表格数据
        for(int i = 1;i<ui->encoderTable->rowCount()+1;i++){
            for(int j = 1;j<ui->encoderTable->columnCount()+1;j++){
                QAxObject *Range = workSheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)",ui->encoderTable->item(i-1,j-1)->data(Qt::DisplayRole).toString());
            }
        }
        workBook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath
        workBook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        qDebug() << "\n导出成功！！！";
    }
}

/*
 * @brief 槽函数，保存已经生成的哈夫曼树图片，
 * 保存路径可以自由选择
 *
 */
void Widget::on_exportPhotoButton_clicked(){
    //获取保存路径
    QString filepath=QFileDialog::getSaveFileName(this,tr("保存图片"),".",tr(" (*.png)"));
    if(!filepath.isEmpty()){
        //设置实际图片大小
        this->scrollArea->rect();
        QRect rect(this->widget->rect());
        //返回图片
        QPixmap image=this->widget->grab(rect);
        //按照保存路径保存图片
        image.save(filepath);
    }

}


/*
 * @brief 槽函数，如果关键字或频率更改，对应的表格和图形进行更改
 * @param item 当前选择项
 *        输入数据后需要按一次Enter
 */
void Widget::on_keyWordTable_itemActivated(QTableWidgetItem *item){
    // this->ui->keyWordTable->blockSignals(true);
    int row=item->row();
    int column=item->column();
    qDebug()<<"currentRow= "<<row;
    qDebug()<<"currentColumn= "<<column;

    QString content=item->text();
    //更改关键字
    if(column==1){
        this->num[row].first=content;
    }
    //更改频率
    else if(column==2){
        this->num[row].second=content.toInt();
    }
    else{
    }
    QString str;
    this->ui->textInput->clear();
    str=getStringFromNum();
    qDebug()<<str;
    this->ui->textInput->setText(str);
    this->huffmanTree.clear();
    //构造哈夫曼树
    construct();
    //对哈夫曼树进行编码
    encoder();
    //插入编码表
    insertEncoderTable();
    setUpdatesEnabled(true);
    //这里如果设置update，不一定会立即执行paint，不能及时更新
    //滚动区域大小，无法设置滚动条居中
    this->widget->repaint();
    //设置滚动条居中
    int value=this->scrollArea->horizontalScrollBar()->maximum();
    this->scrollArea->horizontalScrollBar()->setValue(value/2);
}


/*
 * @brief 槽函数，添加新行
 */
void Widget::on_addButton_clicked(){
    //获取当前行数
    int nCount=ui->keyWordTable->rowCount();
    //在该位置插入
    ui->keyWordTable->insertRow(nCount);
    //插入一个和当前行有关的字符，频率为1
    QChar ch='A';
    ch=QChar('A'+nCount);
    this->num.append({ch,1});
    QTableWidgetItem *item[3];
    item[0]=new QTableWidgetItem(QString("%1").arg(nCount+1));
    //设置不可编辑
    item[0]->setFlags(item[0]->flags() & ~Qt::ItemIsEditable);
    item[0]->setTextAlignment(Qt::AlignCenter);
    ui->keyWordTable->setItem(nCount,0,item[0]);
    //关键字和频率可以修改
    item[1]=new QTableWidgetItem(this->num[nCount].first);
    item[1]->setFlags(item[1]->flags());
    item[1]->setTextAlignment(Qt::AlignCenter);
    ui->keyWordTable->setItem(nCount,1,item[1]);

    item[2]=new QTableWidgetItem(QString::number(this->num[nCount].second));
    item[2]->setFlags(item[2]->flags());
    item[2]->setTextAlignment(Qt::AlignCenter);
    ui->keyWordTable->setItem(nCount,2,item[2]);
    this->ui->textInput->setText(getStringFromNum());
    // //更新所有表格、图片
    // on_ensureButton_clicked();

}

/*
 * @brief 槽函数，删除选中行，同时删除该字符所有相关的表格、图像
 */
void Widget::on_deleteButton_clicked(){
    QList<QTableWidgetItem*> items=this->ui->keyWordTable->selectedItems();
    int row=0;
    //没有选中
    //删除尾部
    if(items.isEmpty()){
        row=this->ui->keyWordTable->rowCount()-1;
        qDebug()<<row;
        //少于两行，一次删除一行
        if(row>1){
            this->ui->keyWordTable->removeRow(row);
            this->num.remove(row);
        }
        //恰好为两行全部删除
        else{
            this->ui->keyWordTable->removeRow(row);
            this->num.remove(row);
            this->ui->keyWordTable->removeRow(row-1);
            this->num.remove(row-1);
        }
    }
    else{
        for(auto item:items){
            row=item->row();
            this->ui->keyWordTable->removeRow(row);
            this->num.remove(row);
        }
        if((row=this->ui->keyWordTable->currentRow())==0){
            this->ui->keyWordTable->removeRow(row);
            this->num.remove(row);
        }
    }

    this->ui->textInput->setText(getStringFromNum());
    //更新所有表格、图片
    on_ensureButton_clicked();
}
/*
 * @brief 从关键字频率列表中获取字符串
 */
QString Widget::getStringFromNum(){
    QString str;
    for(auto x:this->num){
        for(int j=0;j<x.second;j++){
            str+=x.first;
        }
    }
    return str;
}

//获取随机数字
/*
 * @brief  产生随机数字字符串
 * @param  length 长度
 * @return 随机数字字符串
 */
QString Widget::getRandomNumbers(int length){
    srand(QDateTime::currentMSecsSinceEpoch());
    QString str;
    for(int i=0;i<length;i++){
        str+=QString::number(rand()%9);
     }
    return str;
}
//获取随机汉字
/*
 * @brief  产生随机汉字字符串
 * @param  length 长度
 * @return 随机汉字字符串
 */
QString Widget::getRandomChinese(int length){
    srand(QDateTime::currentMSecsSinceEpoch());
    int rand1 = 0xf7 - 0xb0;
    int rand2 = 0xfe - 0xa1;
    QString str;
    QByteArray byte1, byte2;
    QByteArray text;
     for(int i=0;i<length;i++){
        byte1.clear();
        byte2.clear();
        text.clear();
        byte1.append(rand() % rand1 + 0xb0);
        byte2.append(rand() % rand2 + 0xa1);
        text = byte1;
        text+= byte2;
        str+= QString::fromLocal8Bit(text);
    }
    return str;

}
//获取随机字母
/*
 * @brief  产生随机字母字符串
 * @param  length 长度
 * @return 随机字母字符串
 */
QString Widget::getRandomLetters(int length){
    srand(QDateTime::currentMSecsSinceEpoch());
    QChar cha;
    QString str;
    for(int i=0;i<length;i++){
        int type=rand()%2;
        if(type==0){
            cha=QChar(rand()%('Z'-'A'+1)+'A');
            str+=cha;
        }
        else{
            cha=QChar(rand()%('z'-'a'+1)+'a');
            str+=cha;
        }
    }
    return str;
    // qDebug()<<"cha:"<<cha;

}

/*
 * @brief  产生随机字符串
 * @param  length 长度
 * @return 随机字符串
 */
QString Widget::getRandomStrings(int length){
    QString result;
    //随机数种子
    srand(QDateTime::currentMSecsSinceEpoch());
    //随机数类型
    int randomType=0;
    //汉字字符需要
    int rand1 = 0xf7 - 0xb0;
    int rand2 = 0xfe - 0xa1;
    QString text;
    QByteArray byte1, byte2;
    QByteArray str;
    //
    QChar cha;
    //产生随机字符
    // 40%-40%-10%-10%
    for(int i=0;i<length;i++){
        randomType=rand()%10;
        switch (randomType) {
        //数字，范围是0-9
        case 0:
        case 1:
        case 2:
        case 3:
            result+=QString::number(rand()%9);
            break;
        //字母
        case 4:
        case 5:
        case 6:
        case 7:
            cha=QChar(rand()%('z'-'A'+1)+'A');
            result+=cha;
            // qDebug()<<"cha:"<<cha;
            break;
        //汉字
        case 8:
            text.clear();
            byte1.clear();
            byte2.clear();
            str.clear();
            byte1.append(rand() % rand1 + 0xb0);
            byte2.append(rand() % rand2 + 0xa1);
            str = byte1;
            str+= byte2;
            text += QString::fromLocal8Bit(str);
            // qDebug()<<"str:"<<QString(str.toHex())<<text;
            result+=text;
            break;
        //其他可见字符
        default:
            //33~47
            cha=QChar(rand()%15+33);
            result+=cha;
            break;
        }
    }
    //设置字符
    return result;
}


/*
 * @brief 槽函数，根据选中项设置随机数
 * @param index 当前索引
 */
void Widget::on_randomComboBox_activated(int index){
    srand(QDateTime::currentMSecsSinceEpoch());
    this->ui->textInput->clear();
    //获取当前设置模式
    // qDebug()<<index;
    QString text;
    int length=rand()%20+5;
    switch (index) {
    case 0:
        text=getRandomStrings(length);
        break;
    case 1:
        text=getRandomNumbers(length);
        break;
    case 2:
        text=getRandomLetters(length);
        break;
    case 3:
        text=getRandomChinese(length);
        break;
    default:
        break;
    }
    this->ui->textInput->setText(text);
}

