#include "mainwindow.h"
#include "ui_mainwindow.h"








//      2.处理人员表   (×)

//      4.处理人员表格的导入和导出 (×)
//      3.查找时信息不全




/*
 * @brief 构造函数
 * @param parent  父组件指针
 * @param ui      Qt designer指针，指向图形设计界面
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    //设置类型
    this->itemType = 1;
    this->minZ=0;
    this->maxZ=0;
    ui->setupUi(this);
    // this->currentView->viewport()->installEventFilter()
    //创建项
    createActions();
    //创建菜单
    createMenus();
    //创建工具栏
    createToolBar();
    //创建状态栏
    createStatusBar();
    //创建按钮连接
    createButtonConnect();
    setContextMenuPolicy(Qt::DefaultContextMenu);
    //设置标题
    setWindowTitle("组织管理系统");
    setTabWidget();
    setDockWidget();
    //设置使能关系
    updateAllActions();
}
/*
 * @brief 析构函数，删除ui
 *
 */
MainWindow::~MainWindow(){
    delete ui;
}

/*
 * @brief 创建项
 *
 */
void MainWindow::createActions(){
    //新建
    newAction=new QAction(tr("&New"),this);
    newAction->setIcon(QIcon(":/images/File-icons/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    // menuFile->addAction(newAction);
    //保存图片
    savePhotoAction=new QAction(tr("&Save Photo"),this);
    savePhotoAction->setIcon(QIcon(":/images/File-icons/save.png"));
    savePhotoAction->setShortcut(QKeySequence::Save);
    savePhotoAction->setStatusTip(tr("Save as Photo"));
    connect(savePhotoAction,SIGNAL(triggered()),this,SLOT(savePhoto()));
    //保存表格
    saveTableAction=new QAction(tr("&Save Table"),this);
    saveTableAction->setShortcut(QKeySequence::SaveAs);
    saveTableAction->setStatusTip(tr("Save as Table"));
    connect(saveTableAction,SIGNAL(triggered()),this,SLOT(saveTable()));
    //退出
    exitAction=new QAction(tr("&Exit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the programe"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exitAppication()));
    //编辑
    //剪切
    cutAction=new QAction(tr("&Cut"),this);
    cutAction->setIcon(QIcon(":/images/Edit-icons/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut a node"));
    connect(cutAction,SIGNAL(triggered()),this,SLOT(cutNode()));
    //复制
    copyAction=new QAction(tr("&Copy"),this);
    copyAction->setIcon(QIcon(":/images/Edit-icons/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy a node"));
    connect(copyAction,SIGNAL(triggered()),this,SLOT(copyNode()));
    //粘贴
    pasteAction=new QAction(tr("&Paste"),this);
    pasteAction->setIcon(QIcon(":/images/Edit-icons/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste a node"));
    connect(pasteAction,SIGNAL(triggered()),this,SLOT(pasteNode()));
    //删除
    deleteAction=new QAction(tr("&Delete"),this);
    deleteAction->setIcon(QIcon(":/images/Edit-icons/delete.png"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("delete a node"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteNode()));
    //寻找
    findAction=new QAction(tr("&Find"),this);
    findAction->setIcon(QIcon(":/images/Edit-icons/search.png"));
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("find a node"));
    connect(findAction,SIGNAL(triggered()),this,SLOT(findDialog()));
    //工具栏
    //手型拖拽
    handToolAction=new QAction(tr("&Hand Tool"));
    handToolAction->setIcon(QIcon(":/images/Tools-icons/hand-tool.png"));
    handToolAction->setCheckable(true);
    handToolAction->setShortcut(tr("H"));
    handToolAction->setStatusTip(tr("Use hand tool"));
    connect(handToolAction,SIGNAL(toggled(bool)),this,SLOT(setHandTool(bool)));
    //矩形选择
    //初始设置为选择矩形
    selectionToolAction=new QAction(tr("&Selection Tool"));
    selectionToolAction->setIcon(QIcon(":/images/Tools-icons/selection-tool.png"));
    selectionToolAction->setCheckable(true);
    selectionToolAction->setChecked(true);
    selectionToolAction->setShortcut(tr("V"));
    selectionToolAction->setStatusTip(tr("Use selection tool"));
    connect(selectionToolAction,SIGNAL(toggled(bool)),this,SLOT(setSelectionTool(bool)));
    //添加结点
    addNodeAction=new QAction(tr("&Add Department"));
    addNodeAction->setIcon(QIcon(":/images/Tools-icons/add-node.png"));
    addNodeAction->setShortcut(tr("Alt+N"));
    addNodeAction->setStatusTip(tr("Add a node"));
    connect(addNodeAction,SIGNAL(triggered()),this,SLOT(addNode()));
    //添加连接
    addLinkAction=new QAction(tr("&Add Link"));
    addLinkAction->setIcon(QIcon(":/images/Tools-icons/add-link.png"));
    addLinkAction->setShortcut(tr("Alt+L"));
    addLinkAction->setStatusTip(tr("Add a link between two nodes"));
    connect(addLinkAction,SIGNAL(triggered()),this,SLOT(addLink()));
    //插入结点
    insertNodeAction=new QAction(tr("&Insert Department"));
    insertNodeAction->setIcon(QIcon(":/images/Tools-icons/insert-node.png"));
    insertNodeAction->setShortcut(tr("Alt+I"));
    insertNodeAction->setStatusTip(tr("Add a node between two nodes"));
    connect(insertNodeAction,SIGNAL(triggered()),this,SLOT(insertNode()));
    //设置结点为最底部
    sendToBackAction=new QAction(tr("&Send to back"));
    sendToBackAction->setStatusTip(tr("Set the node to bottom"));
    connect(sendToBackAction,SIGNAL(triggered()),this,SLOT(sendToBack()));
    //设置结点为最顶层
    bringToFrontAction=new QAction(tr("&Bring to front"));
    bringToFrontAction->setStatusTip(tr("Set the node to top"));
    connect(bringToFrontAction,SIGNAL(triggered()),this,SLOT(bringToFront()));
    //放大视图
    zoomInAction=new QAction(tr("Zoom in"));
    zoomInAction->setIcon(QIcon(":/images/Tools-icons/zoom-in.png"));
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));
    //缩小视图
    zoomOutAction=new QAction(tr("Zoom out"));
    zoomOutAction->setIcon(QIcon(":/images/Tools-icons/zoom-out.png"));
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));
    //创建场景
    this->itemType = 1;

    //设置鼠标跟踪
    setMouseTracking(true);
}
/*
 * @brief 创建菜单
 *
 */
void MainWindow::createMenus(){
    //文件菜单
    fileMenu=this->ui->menubar->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(savePhotoAction);
    fileMenu->addAction(saveTableAction);
    separator=fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    //编辑菜单
    editMenu=this->ui->menubar->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);
    //工具菜单
    toolsMenu=this->ui->menubar->addMenu(tr("Tools"));
    QMenu *selectionMenu=toolsMenu->addMenu(tr("Selection Mode"));
    selectionMenu->addAction(selectionToolAction);
    selectionMenu->addAction(handToolAction);
    toolsMenu->addSeparator();
    toolsMenu->addAction(addNodeAction);
    toolsMenu->addAction(addLinkAction);
    toolsMenu->addAction(insertNodeAction);
    toolsMenu->addSeparator();
    toolsMenu->addAction(bringToFrontAction);
    toolsMenu->addAction(sendToBackAction);
    toolsMenu->addSeparator();
    toolsMenu->addAction(zoomInAction);
    toolsMenu->addAction(zoomOutAction);
}
/*
 * @brief 创建工具栏
 *
 */
void MainWindow::createToolBar(){
    //添加文件工具栏
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(savePhotoAction);
    //添加编辑工具栏
    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addAction(deleteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    //添加视图缩放工具栏
    viewToolBar=addToolBar(tr("&View"));
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
}
/*
 * @brief 创建状态栏
 *
 */
void MainWindow::createStatusBar(){
    /* W999 作用：1.显示的内容。2.决定locationLabel的尺寸大小*/
    locationLabel = new QLabel(" Status ");
    /*对齐方式：居中对齐*/
    locationLabel->setAlignment(Qt::AlignHCenter);
    /*最小大小为窗口部件的理想大小*/
    locationLabel->setMinimumSize(locationLabel->sizeHint());
    tipLabel = new QLabel;
    /*缩进，文本与左侧边的偏移量*/
    tipLabel->setIndent(3);
    /*单元格定位指示器，伸展因子默认为0*/
    statusBar()->addWidget(locationLabel);
    /*单元格公式指示器，伸展因子为1*/
    statusBar()->addWidget(tipLabel, 1);
}



/*
 * @brief 槽函数，添加新文件
 *
 */
void MainWindow::newFile(){
    //设置初始名称
    QString text = "Graph_" + QString::number(this->ui->tabWidget->count()+1);
    //创建视图和场景
    MyGraphicsScene *myScene = new MyGraphicsScene(QSizeF(1000,1000),this);

    MyView *view = new MyView();
    view->setScene(myScene);
    currentView = view;
    //添加至标签
    ui->tabWidget->addTab(currentView, text);
    //转到新建的视图
    ui->tabWidget->setCurrentWidget(currentView);
    //设置当前视图
    this->currentView->setDragMode(QGraphicsView::RubberBandDrag);
    this->currentView->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    setAcceptDrops(true);
    connect(this->currentView->scene(),SIGNAL(selectionChanged()),this,SLOT(updateAllActions()));
}



/*
 * @brief 创建按钮连接
 */
void MainWindow::createButtonConnect(){
    //导入按钮样式
    QFile file(":/images/qss/style.qss");
    if(!file.open(QFile::ReadOnly))
        return;
    QTextStream textStream(&file);
    QString stylesheet = textStream.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
   //为每个按钮添加信号
    for(int i=1;i<=10;i++){
        QString buttonName="depButton_"+QString::number(i);
        QPushButton *btn=this->findChild<QPushButton *>(buttonName);
        connect(btn,&QPushButton::clicked,[=](){
            itemType=i;
        });

    }
}

/*
 * @brief 槽函数，保存图片
 *
 */
void MainWindow::savePhoto(){
    if(ui->tabWidget->count() == 0)
        return;
    // int index = ui->tabWidget->currentIndex();
    //获取保存路径
    QString filepath=QFileDialog::getSaveFileName(this,tr("保存图片"),".",tr(" (*.png)"));
    if(!filepath.isEmpty()){
        int width=this->currentView->scene()->width();
            int height=this->currentView->scene()->height();
        QImage image(width,height, QImage::Format_RGB888);
        QPainter painter(&image);
        this->currentView->scene()->render(&painter);   //关键函数
        image.save(filepath);
    }
}





/*
 * @brief 槽函数，保存表格
 *
 */
void MainWindow::saveTable(){
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
        //起始列
        int startColumn=1;
        foreach (auto item, this->currentView->getNodeTree()) {
            //部门人员表格
            QTableWidget*infoTable=new QTableWidget(this);
            infoTable->setColumnCount(4);
            //隐藏默认显示的序号
            infoTable->verticalHeader()->setVisible(false);
            QStringList header;
            header<<"Number"<<"id"<<"Name"<<"Position";
            infoTable->setHorizontalHeaderLabels(header);
            infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            infoTable->setColumnWidth(0,60);
            infoTable->setColumnWidth(1,60);
            infoTable->setColumnWidth(2,60);
            infoTable->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
            //导入数据表格信息
            QVector<QPair<QString,QPair<QString,QString>>>info=item->getPersonInfo();
            for(int i=0;i<(int)info.size();i++){
                insertRow(i,info[i].first,info[i].second.first,info[i].second.second,infoTable);
            }
            //设置部门值，合并单元格
            QString start=mapToExecleCol(startColumn);
            QString end=mapToExecleCol(startColumn+3);
            QAxObject *range = workSheet->querySubObject("Range(const Qvariant&)", QVariant("=(" +start+ ": " +end+ ")"));
            if(range == NULL)
                return ;
            //合并单元格
            range->setProperty("MergeCells", true);
            //设置内容
            range->setProperty("Value2", item->getDepartmentName());
            //设置表头值
            for(int i=startColumn;i<infoTable->columnCount()+startColumn;i++){
                //设置某行某列
                QAxObject *Range = workSheet->querySubObject("Cells(int,int)", 2, i);
                Range->dynamicCall("SetValue(const QString &)",infoTable->horizontalHeaderItem(i-startColumn)->text());
            }
            //设置表格数据
            for(int i = 1;i<infoTable->rowCount()+1;i++){
                for(int j = startColumn;j<infoTable->columnCount()+startColumn;j++){
                    QAxObject *Range = workSheet->querySubObject("Cells(int,int)", i+2, j);
                    Range->dynamicCall("SetValue(const QString &)",infoTable->item(i-1,j-startColumn)->data(Qt::DisplayRole).toString());
                }
            }
            startColumn+=(infoTable->columnCount()+1);
            //保存至filepath
            workBook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));
        }
        workBook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        qDebug() << "\n导出成功！！！";

    }
}


/*
 * @brief 根据输入列数映射到excel列
 * @param  col:输入列数
 * @return 对应的excel列的字符（A1...）
 */
QString MainWindow::mapToExecleCol(int col){
    QString result;
    while(col-'A'>0){
        result+="A";
    }
    result+=(QChar('A'+col-1));
    result+="1";
    qDebug()<<result;
    return result;
}

/*
 * @brief  插入表格
 * @param row  行数
 * @param id   工号
 * @param name  部门名
 * @param position 职位
 * @param infoTable 需要插入的表格
 */
void MainWindow::insertRow(int row,QString id,QString name,QString position,QTableWidget*infoTable){
    infoTable->insertRow(row);
    QTableWidgetItem *item[4];
    //填入序号
    item[0]=new QTableWidgetItem(QString("%1").arg(row+1));
    item[0]->setTextAlignment(Qt::AlignCenter);
    //设置不可编辑
    item[0]->setFlags(item[0]->flags() & ~Qt::ItemIsEditable);
    infoTable->setItem(row,0,item[0]);
    //填入工号
    item[1]=new QTableWidgetItem(id);
    item[1]->setTextAlignment(Qt::AlignCenter);
    infoTable->setItem(row,1,item[1]);
    //填入姓名
    item[2]=new QTableWidgetItem(name);
    item[2]->setTextAlignment(Qt::AlignCenter);
    infoTable->setItem(row,2,item[2]);
    //填入职位
    item[3]=new QTableWidgetItem(position);
    item[3]->setFlags(item[3]->flags());
    item[3]->setTextAlignment(Qt::AlignCenter);
    infoTable->setItem(row,3,item[3]);
}



/*
 * @brief 退出事件
 * @param event 事件指针
 */
void MainWindow::closeEvent(QCloseEvent *event){
    if(ui->tabWidget->count() == 0){
        qApp->quit();
        return;
    }
    QMessageBox messageBox;
    QPushButton *closeButton = messageBox.addButton("Close",QMessageBox::ActionRole);
    QPushButton *cancelButton = messageBox.addButton("Cancel",QMessageBox::ActionRole);
    messageBox.setText("Whether you want to close the application?");
    messageBox.exec();
    if(messageBox.clickedButton() == closeButton){
        qApp->quit();
    }
    else {
        event->ignore();
    }
}
/*
 * @brief 槽函数，响应退出
 */
void MainWindow::exitAppication(){
    qApp->quit();
}
/*
 * @brief 槽函数，响应搜索按钮
 */
void MainWindow::findDialog(){
    if(this->ui->tabWidget->count()==0){
        return;
    }
    FindDialog*findDialog=new FindDialog;
    connect(this,SIGNAL(sendFindSignal(QSet<Node*>,MyView*)),findDialog,SLOT(receiveSignal(QSet<Node*>,MyView*)));
    //发送信号
    emit sendFindSignal(this->currentView->getNodeTree(),this->currentView);
    findDialog->show();
}
/*
 * @brief 更新所有项的使能信号
 *
 */
void MainWindow::updateAllActions(){
    //如果还未创建视图,除了文件菜单不设置使能信号
    if(this->ui->tabWidget->count()==0){
        return;
    }
    //是否有选中项
    bool isSelected=!this->currentView->scene()->selectedItems().isEmpty();
    //是否选中结点
    bool isSelectNode=(selectNode()!=0);
    //是否选中结点对
    bool isSelectNodePair=((selectNodePair())!=QPair<Node *,Node*>());
    cutAction->setEnabled(isSelectNode);
    copyAction->setEnabled(isSelectNode);
    deleteAction->setEnabled(isSelected);
    addLinkAction->setEnabled(isSelectNodePair);

}


/*
 * @brief 设置选项窗口
 */
void MainWindow::setTabWidget(){
    ui->tabWidget->setTabsClosable(true);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=](int index){
                Q_UNUSED(index);

            currentView = dynamic_cast<MyView *>(ui->tabWidget->currentWidget());
            if(currentView!=nullptr){
                        this->ui->widthSpinBox->setValue(currentView->scene()->width());
                        this->ui->heightSpinBox->setValue(currentView->scene()->height());
                    }
            });
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index){
        QMessageBox messageBox;
        messageBox.setText("The document has changed. Whether to save?");
        QPushButton *saveButton = messageBox.addButton("Save", QMessageBox::ActionRole);
        QPushButton *unsaveButton = messageBox.addButton("Unsave", QMessageBox::ActionRole);
        QPushButton *cancelButton = messageBox.addButton("Cancel", QMessageBox::ActionRole);
        Q_UNUSED(cancelButton);
        messageBox.exec();
        if(messageBox.clickedButton() == saveButton) {
            savePhoto();
            ui->tabWidget->removeTab(index);
        }
        else if (messageBox.clickedButton() == unsaveButton) {
            ui->tabWidget->removeTab(index);
        }
    });

}
/*
 * @brief 设置停靠窗口
 */
void MainWindow::setDockWidget(){

    this->ui->widthSpinBox->setRange(500,3000);
    this->ui->widthSpinBox->setValue(500);
    this->ui->heightSpinBox->setRange(500,3000);
    this->ui->heightSpinBox->setValue(500);
    this->ui->dockWidget_4->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    connect(this->ui->widthSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSceneWidth(int)));
    connect(this->ui->heightSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSceneHeight(int)));

}
/*
 * @brief 设置屏幕宽度
 * @param value 设置值
 */
void MainWindow::setSceneWidth(int value){
    if(this->ui->tabWidget->count()==0){
        return;
    }
    int height=this->currentView->scene()->height();
    this->currentView->scene()->setSceneRect(0,0,value,height);
}
/*
 * @brief 设置屏幕高度
 * @param value 设置值
 */
void MainWindow::setSceneHeight(int value){
    if(this->ui->tabWidget->count()==0){
        return;
    }
    int width=this->currentView->scene()->height();
    this->currentView->scene()->setSceneRect(0,0,width,value);
}


/*
 * @brief 重新设置场景大小
 * @param rect 新的场景矩形
 */
void MainWindow::resizeScene(QRectF rect){
    this->currentView->scene()->setSceneRect(rect);
}


/*
 * @brief 添加结点
 * @param point 添加位置
 * @param name 初始设置的部门名
 * @param info 人员-职位信息
 * @param type 决定部门图片
 * @param isShowDialog 是否显示属性对话框(粘贴时不需要)
 */
void MainWindow::addNode(QPointF point,QString name,QVector<QPair<QString,QPair<QString,QString>>> info,int type,bool isShowDialog){

    //如果没有打开任何界面不处理
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        return;
    }
    //粘贴时处理，不显示对话框，不设置人员表的初始值，用参数进行赋值,且使用原来的名称和图片
    if(!isShowDialog){
        setupNode(point,name,info,type);
        this->currentView->scene()->update();
    }
    //第一次创建时产生，设置一些初始值
    else{
        QSize size(50,50);
        int count=this->currentView->getID();
        this->currentView->atuoIncrement();
        //设置初始名称
        QString initialName="New_"+QString::number(count);
        Node *item = new Node(this->currentView,count,QRectF(point, size),initialName,this->itemType);
        QString personId=QString::number(this->getRandomPersonId());
        //设置初始值
        QPair<QString,QPair<QString,QString>> pair(personId,{"unnamed","主管"});
        info.append(pair);
        pair.first=QString::number(this->getRandomPersonId()+1);
        pair.second.first.push_back("_2");
        pair.second.second.push_front("副");
        info.append(pair);
        item->setPersonInfo(info);
        // this->currentView->resetPersonTable(info);
        //对属性进行编辑
        //返回序列，格式为:
        //{"部门名","-1/0/1":未显示位置框/初始鼠标位置/屏幕中央,"人员表格行数","工号 人员 职位"...}
        // qDebug()<<(this->currentView);
        QStringList list=PropertiesDialog::getStrings(item,this,this->currentView->getPersonTable(),true);
        QPointF setPoint;
        if(!list.isEmpty()){
            item->setDepartmentName(list[0]);
            //鼠标位置
            if(list[1]=="0"){
                setPoint=this->currentView->getMousePos();
                qDebug()<<"now Pos"<<setPoint;
                // setPoint=this->currentView->mapToScene(setPoint);
                item->setPos(setPoint);
            }
            else if(list[1]=="1"){
                // setPoint=this->currentView->scene()->;
                setPoint.setX(this->currentView->scene()->width()/2);
                setPoint.setY(this->currentView->scene()->height()/2);
                item->setPos(setPoint);
            }
            else{
            }
            info.clear();
            int rowCount=list[2].toInt();
            for(int i=0;i<rowCount;i++){
                pair.first=list[(3*i+3)];
                pair.second.first=list[i*3+4];
                pair.second.second=list[3*i+5];
                info.append(pair);
            }
            item->setPersonInfo(info);
            this->currentView->resetPersonTable(info);
            //
            //添加结点
            // item->setPos(point);
            this->currentView->scene()->addItem(item);
            //增加计数
            this->currentView->getNodeTree().insert(item);
            //清除选择
            this->currentView->scene()->clearSelection();
            //设置选择当前项
            item->setSelected(true);
            bringToFront();
            this->currentView->scene()->update();
        }

    }


}

/*
 * @brief 在指定位置创建结点，并返回该结点
 * @param point 添加位置
 * @param name 初始设置的部门名
 * @param info 人员-职位信息
 * @param type 决定部门图片
 * @return 创建的结点
 */
Node* MainWindow::setupNode(QPointF point,QString name,QVector<QPair<QString,QPair<QString,QString>>> info,int type){
    //实际图片大小
    QSize size(50,50);
    //为结点分配id
    int count=this->currentView->getID();
    this->currentView->atuoIncrement();
    Node *item = new Node(this->currentView,count,QRectF(point, size),name,type);
    item->setPersonInfo(info);
    this->currentView->resetPersonTable(info);
    //添加结点
    qDebug()<<"itemPos="<<item->scenePos();
    // item->setPos(point);
    this->currentView->scene()->addItem(item);
    //树结点增加
    this->currentView->getNodeTree().insert(item);
    //清除选择
    this->currentView->scene()->clearSelection();
    //设置选择当前项
    item->setSelected(true);
    bringToFront();
    return item;
}



int MainWindow::getRandomPersonId(){
    srand(QDateTime::currentMSecsSinceEpoch());
    return (rand()%80000+10000);
}

/*
  * @brief 设置选择结点为最上层
 *
 */
void MainWindow::bringToFront(){
    ++maxZ;
    setZValue(maxZ);
}
/*
 * @brief 设置选择结点为最底部
 */
void MainWindow::sendToBack(){
    --minZ;
    setZValue(minZ);
}

/*
 * @brief 设置当前选择结点的z值
 * @param value: 需要设置的z值
 */
void MainWindow::setZValue(int value){
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        return;
    }
    Node *node=selectNode();
    if(node){
        node->setZValue(value);
    }
}

/*
 * @brief 选择一个结点
 * @return:
 *         0 :未选择一个结点
 *         其他值：选择的结点指针
 *
 */
Node* MainWindow::selectNode(){
    QList<QGraphicsItem*> items=this->currentView->scene()->selectedItems();

    if(items.count()==1&&items.first()->type()==65536){
        //返回的是指针的引用
        return (Node*)items.first();
    }
    else{
        return 0;
    }
}


/*
 * @brief 选择一个连线
 * @return:
 *         0 :未选择一个连线
 *         其他值：选择的连线指针
 */
Link* MainWindow::selectLink(){
    QList<QGraphicsItem*> items=this->currentView->scene()->selectedItems();
    if(items.count()==1&&items.first()->type()==6){
        //返回的是指针的引用
        return (Link*)items.first();
    }
    else{
        return 0;
    }
}
/*
 * @brief 选择一对结点
 * @return:
 *         QPair<Node *,Node*>():未选择一对结点
 *         其他值：选择的结点对
 */
QPair<Node *,Node*> MainWindow::selectNodePair(){
    QList<QGraphicsItem*> items=this->currentView->scene()->selectedItems();
    if(items.count()==2&&items.first()->type()==65536&&items.last()->type()==65536){
        Node *start= (Node*)items.first();
        Node *end=(Node*)items.last();
        if(start&&end){
            return QPair<Node*,Node*>(start,end);
        }
        else{
            return QPair<Node*,Node*>();
        }
    }
    else{
        return QPair<Node*,Node*>();
    }
}


/*
 * @brief 添加连线
 */
void MainWindow::addLink(){
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        return;
    }
    QPair<Node*,Node*> nodes=selectNodePair();
    QStringList list;
    if(nodes!=QPair<Node*,Node*>()){

        list=SuperiorDialog::getStrings(nodes,this);
        //如果返回在字符串链表非空
        if(!list.isEmpty()){
            //解析字符串链表
            nodes.first->setDepartmentName(list[0]);
            nodes.second->setDepartmentName(list[1]);
            // qDebug()<<list[2];
            //first作为上级
            if(list[2]=="0"){
                //取消second和原先parent的连线
                if(nodes.second->getParentNode()!=nullptr){
                    deleteLink(nodes.second,nodes.second->getParentNode());
                }
                //防止互为父结点
                if(nodes.first->getParentNode()==nodes.second){
                    nodes.first->setParentNode(nullptr);
                }
                //两个结点增加逻辑关系
                nodes.second->setParentNode(nodes.first);
                nodes.first->addChild(nodes.second);
                //设置箭头方向
                Link *link=new Link(nodes.second,nodes.first);
                this->currentView->scene()->addItem(link);
            }
            //second作为上级
            else{
                //取消first和原先parent的连线
                if(nodes.first->getParentNode()!=nullptr){
                    deleteLink(nodes.first,nodes.first->getParentNode());
                }
                 //防止互为父结点
                if(nodes.second->getParentNode()==nodes.first){
                    nodes.second->setParentNode(nullptr);
                }
                //两个结点增加逻辑关系
                nodes.first->setParentNode(nodes.second);
                nodes.second->addChild(nodes.first);
                //指向：起点至终点->
                Link *link=new Link(nodes.first,nodes.second);
                this->currentView->scene()->addItem(link);
            }

        }
    }
}



/*
 * @brief 删除选中的结点和连线
 */
void MainWindow::deleteNode(){
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        return;
    }
    QList<QGraphicsItem*> items=this->currentView->scene()->selectedItems();

    //迭代器起始指向第一个元素之前
    QMutableListIterator<QGraphicsItem*> iter(items);
    while (iter.hasNext()) {
        //.next()自动移动迭代器一次
        Link * link=dynamic_cast<Link*>(iter.next());
        if(iter.value()->type()==65536){
            this->currentView->getNodeTree().remove(dynamic_cast<Node*>(iter.value()));
        };
        if(link){
            delete link;
            iter.remove();
        }
        //
        int c=(this->currentView->getNodeTree().size());
        qDebug()<<c;
    }
    qDeleteAll(items);
}


/*
 * @brief 删除两个结点之间的连线以及结点的关系
 * @param startNode  起始结点指针
 * @param endNode    结束结点指针
 */
void MainWindow::deleteLink(Node* startNode,Node*terminalNode){
    Link *link=startNode->isConnect(terminalNode);
    if(link!=nullptr){
        startNode->deleteLink(link);
        terminalNode->deleteLink(link);
        this->currentView->scene()->removeItem(link);
        //删除逻辑关系
        if(startNode->getParentNode()==terminalNode){
            startNode->setParentNode(nullptr);
            terminalNode->removeChild(startNode);
        }
        else{
            terminalNode->setParentNode(nullptr);
            startNode->removeChild(terminalNode);
        }
        return;
    }
}

/*
 * @brief 插入两个结点之间，两个结点必须先连线
 */
void MainWindow::insertNode(){
    if(this->ui->tabWidget->count()==0){
        showWarningMsg();
        return;
    }
    QPair<Node*,Node*>nodes=selectNodePair();
    //结点之间没有连线
    Link *link;
    if((link=nodes.first->isConnect(nodes.second))==nullptr){
        QMessageBox::warning(this,"Warning","The selected nodes must be connected first!",
                             QMessageBox::Yes,QMessageBox::Yes);

    }
    else{
        //生成结点
        //设置初始值
        QVector<QPair<QString,QPair<QString,QString>>>info;
        QString personId=QString::number(this->getRandomPersonId());
        QPair<QString,QPair<QString,QString>> pair(personId,{"unnamed","主管"});
        info.append(pair);
        pair.first=QString::number(this->getRandomPersonId()+1);
        pair.second.first.push_back("_2");
        pair.second.second.push_front("副");
        info.append(pair);
        Node *node=setupNode(this->currentView->getMousePos(),"Untitled",info,this->itemType);
        //second作为上级
        if(nodes.first->getParentNode()==nodes.second){
            //删除连线，改变逻辑关系
            deleteLink(nodes.first,nodes.second);
            //两个结点增加逻辑关系
            nodes.first->setParentNode(node);
            node->addChild(nodes.first);
            //设置箭头方向
            Link *link=new Link(nodes.first,node);
            this->currentView->scene()->addItem(link);
            //
            node->setParentNode(nodes.second);
            nodes.second->addChild(node);
            //设置箭头方向
            link=new Link(node,nodes.second);
            this->currentView->scene()->addItem(link);

        }
        //first作为上级
        else{
            //删除连线，改变逻辑关系
            deleteLink(nodes.first,nodes.second);
            //两个结点增加逻辑关系
            nodes.second->setParentNode(node);
            node->addChild(nodes.second);
            //设置箭头方向
            Link *link=new Link(nodes.second,node);
            this->currentView->scene()->addItem(link);
            //
            node->setParentNode(nodes.first);
            nodes.first->addChild(node);
            //设置箭头方向
            link=new Link(node,nodes.first);
            this->currentView->scene()->addItem(link);
        }
    }

}
/*
 * @brief 剪切选中的结点
 */
void MainWindow::cutNode(){
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        return;
    }
    Node*node=this->selectNode();
    if(node){
        copyNode();
        this->currentView->getNodeTree().remove(node);
        delete node;
    }
    else{
        return;
    }
}
/*
 * @brief 复制选中的结点
 * 复制格式，以空格分开 "Node"+"部门名"+"图片类型"
 * +"表格行数"+"工号"+"人员名"+"职位"...
 */
void MainWindow::copyNode(){
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        return;
    }
    Node*node=this->selectNode();
    if(node){
        QStringList list;
        list<<"Node";
        list<<node->getDepartmentName();
        list<<QString::number(node->getType());
        QVector<QPair<QString,QPair<QString,QString>>>info=node->getPersonInfo();
        list<<QString::number(info.size());
        for(int i=0;i<int(info.size());i++){
            list<<info[i].first;
            list<<info[i].second.first;
            list<<info[i].second.second;
        }
        //以'|'分割，防止部门中含空格被分割
        QString str=list.join("|");
        QApplication::clipboard()->setText(str);
    }
    else{
        return;
    }
}
/*
 * @brief 粘贴选中的结点
 */
void MainWindow::pasteNode(){
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        return;
    }
    QString str=  QApplication::clipboard()->text();
    QStringList strList=str.split("|");
    if(strList[0]=="Node"){
        QPointF point=this->currentView->getMousePos();
        //信息表
        QVector<QPair<QString,QPair<QString,QString>>>info;
        QPair<QString,QPair<QString,QString>>pair;
        //信息表长度
        int len=strList[3].toInt();
        //获取信息
        for(int i=0;i<len;i++){
            pair.first=strList[3*i+4];
            pair.second.first=strList[3*i+5];
            pair.second.second=strList[3*i+6];
            info.append(pair);
        }
        //不显示属性框
        addNode(point,strList[1],info,(strList[2]).toInt(),false);
    }
}

/*
 * @brief 设置手型工具
 * @param value 是否设置
 */
void MainWindow::setHandTool(bool value){
    if(this->ui->tabWidget->count()==0){
          showWarningMsg();
        this->selectionToolAction->setChecked(false);
        return;
    }
    if(value){
        this->selectionToolAction->setChecked(false);
        this->currentView->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}
/*
 * @brief 设置选择工具
 * @param value 是否设置
 */
void MainWindow::setSelectionTool(bool value){
    if(this->ui->tabWidget->count()==0){
        showWarningMsg();
        //取消选中
        this->handToolAction->setChecked(false);
        return;
    }
    if(value){
        //取消选中
        this->handToolAction->setChecked(false);
        //设置模式
        this->currentView->setDragMode(QGraphicsView::RubberBandDrag);
    }
}


/*
 * @brief 放大视图
 */
void MainWindow::zoomIn(){
    if(this->ui->tabWidget->count()==0){
        showWarningMsg();
        return;
    }
    this->currentView->viewZoomIn();
}

/*
 * @brief 缩小视图
 */
void MainWindow::zoomOut(){
    if(this->ui->tabWidget->count()==0){
        showWarningMsg();
        return;
    }
    this->currentView->viewZoomOut();
}

/*
 * @brief 右键菜单
 * @param event 事件指针
 */
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    if(this->ui->tabWidget->count()==0){
        showWarningMsg();
        return;
    }
    qDebug()<<"event Pos"<<event->pos();
    QMenu menu;
    menu.addAction(addNodeAction);
    menu.addAction(addLinkAction);
    menu.addAction(insertNodeAction);
    // 右键菜单在鼠标处被阻塞
    menu.exec(QCursor::pos());
}

/*
 * @brief 显示警告信息
 */
void MainWindow::showWarningMsg(){
    QMessageBox::warning(this,"Warning","You need to create a new File First",
                         QMessageBox::Yes,QMessageBox::Yes);
}

/*
 * @brief 获取当前视图
 */
MyView* MainWindow::getCurrentView(){
    return this->currentView;
}
