#include "propertiesdialog.h"

#include <QHeaderView>



/*
 * @brief 存储副本
 */
struct Table{
    QString number;
    QString id;
    QString name;
    QString position;
};



/*
 * @brief 构造函数
 * @param node  结点指针
 * @param parent  父组件指针
 * @param isShow  是否选择显示有关位置的信息
 *                如果是addNode需要设置且父节点信息不可更改。
 */
PropertiesDialog::PropertiesDialog(Node*node,bool isShow,QWidget *parent)
    : QDialog(parent){
    // 382*595A
    this->setMaximumSize(330,330);
    this->setMinimumSize(330,330);
    mainLayOut=new QGridLayout(this);
    createDepartment(node,isShow);
    createTable(node,isShow);
    okButton=new QPushButton(tr("OK"),this);
    cancelButton=new QPushButton(tr("Cancel"),this);
    //连接信号
    connect(okButton,SIGNAL(clicked()),this,SLOT(on_okButton_clicked()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(on_cancelButton_clicked()));

    //布局
    mainLayOut->addWidget(okButton,8,0);
    mainLayOut->addWidget(cancelButton,8,1);

    setLayout(mainLayOut);
    // qDebug()<<this->width()<<this->height();
    // setWindowFlag(Qt::WindowCloseButtonHint, false); // 不显示右上角关闭


    setWindowTitle("Properties");
}
//
/*
 * @brief 创建部门相关标签、输入框
 * @param node：处理结点
 * @param isShow 是否显示上级部门
 */
void PropertiesDialog::createDepartment(Node*node,bool isShow){
    //部门名设置
    departmentNameLabel=new QLabel(tr("Department Name:"),this);
    departmentNameLine=new QLineEdit(node->getDepartmentName(),this);
    departmentNameLabel->setBuddy(departmentNameLine);
    mainLayOut->addWidget(departmentNameLabel,0,0);
    mainLayOut->addWidget(departmentNameLine,0,1);

    //上级部门设置
    superiorNameLabel=new QLabel(tr("Superior:"),this);
    superiorNameLabel->setHidden(isShow);
    //考虑无上级部门的情况
    if(node->getParentNode()==nullptr){
        subSuperiorName="Not Set";
    }
    else{
        subSuperiorName=node->getParentNode()->getDepartmentName();
    }
    superiorNameLine=new QLineEdit(subSuperiorName,this);
    superiorNameLine->setHidden(isShow);
    superiorNameLine->setReadOnly(true);
    mainLayOut->addWidget(superiorNameLabel,1,0);
    mainLayOut->addWidget(superiorNameLine,1,1);
    //位置设置
    positionLabel=new QLabel(tr("Set Position:"),this);
    positionLabel->setHidden(!isShow);
    mainLayOut->addWidget(positionLabel,2,0);
    mousePositionButton=new QRadioButton(tr("Mouse Position"),this);

    mousePositionButton->setHidden(!isShow);
    mousePositionButton->setChecked(true);
    viewCenterButton=new QRadioButton(tr("Center Position"),this);
    viewCenterButton->setHidden(!isShow);

    mainLayOut->addWidget(mousePositionButton,3,0);
    mainLayOut->addWidget(viewCenterButton,3,1);
}
/*
 * @brief 创建人员表相关标签、输入框、按钮
 * @param node：处理结点
 * @param isShow 是否显示上级部门
 */
void PropertiesDialog::createTable(Node*node,bool isShow){
    //部门人员表格标签
    personalInfoLabel=new QLabel(tr("Person Information:"),this);
    mainLayOut->addWidget(personalInfoLabel,4,0);
    //添加删除按钮
    addRowButton=new QPushButton(tr("+"),this);
    removeRowButton=new QPushButton(tr("-"),this);
    //连接信号
    connect(addRowButton,SIGNAL(clicked()),this,SLOT(on_addRowButton_clicked()));
    connect(removeRowButton,SIGNAL(clicked()),this,SLOT(on_removeRowButton_clicked()));
    QHBoxLayout *horizon=new QHBoxLayout;
    horizon->addWidget(addRowButton);
    horizon->addWidget(removeRowButton);
    mainLayOut->addLayout(horizon,4,1);
    //部门人员表格
    infoTable=new QTableWidget(this);
    infoTable->setColumnCount(4);
    //隐藏默认显示的序号
    infoTable->verticalHeader()->setVisible(false);
    QStringList header;
    header<<"Number"<<"id"<<"Name"<<"Position";
    infoTable->setHorizontalHeaderLabels(header);
    infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    infoTable->setColumnWidth(0,75);
    infoTable->setColumnWidth(1,75);
    infoTable->setColumnWidth(2,75);
    infoTable->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    //导入数据表格信息
    QVector<QPair<QString,QPair<QString,QString>>>info=node->getPersonInfo();
    for(int i=0;i<(int)info.size();i++){
        insertRow(i,info[i].first,info[i].second.first,info[i].second.second);
    }
    //导入数据表格
    mainLayOut->addWidget(infoTable,5,0,1,2);
    //跳转到指定行
    gotoRowLabel=new QLabel(tr("Go to Row:"),this);
    mainLayOut->addWidget(gotoRowLabel,6,0);
    gotoRowLine=new QLineEdit("",this);
    mainLayOut->addWidget(gotoRowLine,6,1);
    connect(gotoRowLine,&QLineEdit::textChanged,[=](){
        int row=this->gotoRowLine->text().toInt();
        QTableWidgetItem *item = this->infoTable->item(row-1, 0);
        this->infoTable->scrollToItem(item, QAbstractItemView::PositionAtCenter);
    });
    importButton=new QPushButton(tr("Import Data"),this);
    mainLayOut->addWidget(importButton,7,0,1,2);
    connect(importButton,SIGNAL(clicked()),this,SLOT(on_importButton_clicked()));

}
/*
 * @brief 析构函数
 */
PropertiesDialog::~PropertiesDialog(){

}
/*
 * @brief 在人员表的指定位置插入数据
 * @param row   行号
 * @param id    工号
 * @param name  人员名
 * @param position  职位
 */
void PropertiesDialog::insertRow(int row,QString id,QString name,QString position){
    this->infoTable->insertRow(row);
    QTableWidgetItem *item[4];
    //填入序号
    item[0]=new QTableWidgetItem(QString("%1").arg(row+1));
    item[0]->setTextAlignment(Qt::AlignCenter);
    //设置不可编辑
    item[0]->setFlags(item[0]->flags() & ~Qt::ItemIsEditable);
    this->infoTable->setItem(row,0,item[0]);
    //填入工号
    item[1]=new QTableWidgetItem(id);
    item[1]->setTextAlignment(Qt::AlignCenter);
    this->infoTable->setItem(row,1,item[1]);
    //填入姓名
    item[2]=new QTableWidgetItem(name);
    item[2]->setTextAlignment(Qt::AlignCenter);
    this->infoTable->setItem(row,2,item[2]);
    //填入职位
    item[3]=new QTableWidgetItem(position);
    item[3]->setFlags(item[3]->flags());
    item[3]->setTextAlignment(Qt::AlignCenter);
    this->infoTable->setItem(row,3,item[3]);
}

/*
 * @brief 构造属性对话框
 * @param node    被选中的结点
 * @param parent  父组件指针
 * @param personTable 当前的人员表，避免新建人员时有人员-工号不匹配的情况
 * @param isShow  是否显示位置信息，创建结点时显示
 * @param ok
 * @return 返回的字符串数组格式如下:
 *  success :{"部门名","-1/0/1":未显示位置框/初始鼠标位置/屏幕中央,"人员表格行数","人员 职位"...}
 *  fail: ""，空字符串
 */
QStringList PropertiesDialog::getStrings(Node* node,QWidget *parent,QVector<Person> personTable, bool isShow,bool *ok){
    PropertiesDialog *dialog = new PropertiesDialog(node,isShow,parent);
    QStringList list;
    while(true){
        list.clear();
        //执行操作，进入模态对话框，阻塞其他进程
        const int ret = dialog->exec();
        //存储错误信息
        QString wrongMessage="";
        if (ok){
            *ok = !!ret;
        }
        //有异常情况，返回对话框
        if(ret==3){
            continue;
        }
        //读取属性框信息
        //部门名
        list<<dialog->departmentNameLine->text();
        //位置信息
        if(!isShow){
            list<<"-1";
        }
        else{
            if(dialog->mousePositionButton->isChecked()){
                list<<"0";
            }
            else{
                list<<"1";
            }
        }
        QVector<QPair<QString,QPair<QString,QString>>> sub;
        //表格信息
        int rowCount=dialog->infoTable->rowCount();
        list<<QString::number(rowCount);
        for(int i=0;i<rowCount;i++){
            QString id=dialog->infoTable->item(i,1)->text();
            //职员工号
            list<<id;
            //职员姓名
            QString name=dialog->infoTable->item(i,2)->text();
            list<<name;
            //职员职务
            QString position=dialog->infoTable->item(i,3)->text();
            list<<position;
            QVector<Table> subTable;
            //如果有工号和姓名不匹配的情况
            foreach (auto iter, personTable) {
                if(iter.id==id&&iter.personName!=name){
                    wrongMessage+=QString("\"%1\"row  \"id\":%2 and \"name\":%3 don't match!\n")
                                        .arg(QString::number(i+1))
                                        .arg(id)
                                        .arg(name);
                    wrongMessage+=QString("This id should match name:\"%1\"\n\n").arg(iter.personName);
                }
            }

        }
        //有错误信息弹出信息框
        if(wrongMessage!=""){
            QMessageBox::warning(dialog,"Warning",wrongMessage,
                                 QMessageBox::Yes,QMessageBox::Yes);
            //恢复原数据

            continue;
        }
        else if(ret==QDialog::Accepted){
            break;
        }
        else if(ret==QDialog::Rejected){
            list.clear();
            break;
        }

    }
    //删除对象
    dialog->deleteLater();

    return list;
}





/*
 * @brief 槽函数，响应OK按钮按下时发出的信号
 */
void PropertiesDialog::on_okButton_clicked(){
    //部门名不能为空
    if(this->departmentNameLine->text().isEmpty()){
        QMessageBox::warning(this,tr("Warning"),tr("The department name can't be empty!"),
                             QMessageBox::Yes,QMessageBox::Yes);
        //自定义返回值
        done(3);
    }
    else{
        accept();
    }

}
/*
 * @brief 槽函数，响应Cancel按钮按下时发出的信号
 */
void PropertiesDialog::on_cancelButton_clicked(){
    reject();
}
/*
 * @brief 槽函数，添加人员表新行
 */
void PropertiesDialog::on_addRowButton_clicked(){
    //获取当前行数
    int nCount=this->infoTable->rowCount();
    qDebug()<<"nCount="<<nCount;
    insertRow(nCount,QString::number(nCount+1),"Unnamed","科员");

}
/*
 * @brief 槽函数，删除选择的行
 */
void PropertiesDialog::on_removeRowButton_clicked(){
    QList<QTableWidgetItem*> items=this->infoTable->selectedItems();

    int row=0;
    //没有选中，则删除尾部
    if(items.isEmpty()){
        row=this->infoTable->rowCount()-1;
        qDebug()<<row;
        if(row>1){
            this->infoTable->removeRow(row);
        }
        // else{
        //     this->removeRowButton->setCheckable(false);
        // }
    }
    //否则删除选中项
    else{
        for(auto item:items){
            row=item->row();
            if(row==0||row==1){
                QMessageBox::warning(this,tr("Warning"),tr("The department needs at least two people,"
                                                             " both managers!"),
                                     QMessageBox::Yes,QMessageBox::Yes);
                break;
            }
            this->infoTable->removeRow(row);
        }
    }

    //重新调整行号
    refresh();
}



/*
 * @brief 槽函数，从excel导入人员信息表格
 */
void PropertiesDialog::on_importButton_clicked(){
    //存储每行数据
    QVector<QString> arr;
    //存储所有数据
    QVector<QVector<QString>> array;
   //获取当前路径
    QString curPash =QDir::currentPath();
    QString dlgTitle="选择表格文件";
    //过滤文件格式
    QString filter="表格文件(*.xls *.xlsx);;xls文件(*.xls);;xlsx文件(*.xlsx);;所有文件(*.*)";
    //创建文件选择对话框
    QStringList strFile = QFileDialog::getOpenFileNames(this,dlgTitle,curPash,filter);
    //判断非法情况
    if(strFile.isEmpty()){
        return;
    }
    //加载Excel驱动
    QAxObject excel("Excel.Application");
    //不显示Excel界面
    excel.setProperty("Visible", false);
    QAxObject *workBooks = excel.querySubObject("WorkBooks");
    //打开指定文件
    workBooks->dynamicCall("Open (const QString&)", strFile);
    QAxObject *workBook = excel.querySubObject("ActiveWorkBook");
    //获取工作表
    QAxObject *workSheets = workBook->querySubObject("Sheets");
    QString ExcelName;
    int row_count = 0;
    int column_count = 0;
    //获取工作表数目
    int sheet_count = workSheets->property("Count").toInt();
    if(sheet_count > 0){
        //设置为获取第一页数据
        QAxObject *workSheet = workBook->querySubObject("Sheets(int)", 1);
        QAxObject *usedRange = workSheet->querySubObject("UsedRange");
        QAxObject *rows = usedRange->querySubObject("Rows");
        //获取行数
        row_count = rows->property("Count").toInt();
        QAxObject *column = usedRange->querySubObject("Columns");
         //获取列数
        column_count = column->property("Count").toInt();
        //获取第一行第一列数据
        ExcelName = workSheet->querySubObject("Cells(int,int)", 1,1)->property("Value").toString();
        //获取表格中需要的数据，此处从第2行第2列获取数据
        for (int i =2; i <= row_count; i++) {
            for (int j = 2; j <= column_count;j++) {
                //获取cell的内容
                QAxObject *range = workSheet->querySubObject("Cells(int,int)",i,j);
                QString text = range->dynamicCall("Value2()").toString();
                arr.append(text);
            }
            array.append(arr);
            arr.clear();
        }
        workBook->dynamicCall("Close(Boolean)", false);  //关闭文件
        excel.dynamicCall("Quit(void)");  //退出
    }
    // this->infoTable->clear();
    //删除原先数据
    int row=this->infoTable->rowCount()-1;
    qDebug()<<row;
    while(row>=0){
        this->infoTable->removeRow(row);
        row=this->infoTable->rowCount()-1;
    }
    //导入数据至表格
    for(int i=0;i<array.size();i++){
        insertRow(i,array[i][0],array[i][1],array[i][2]);
    }
}


/*
 * @brief 重新调整序号
 */
void PropertiesDialog::refresh(){
    //获取行数
    int rowCount=this->infoTable->rowCount();
    //只重新设置序号
    for(int i=0;i<rowCount;i++){
        QTableWidgetItem* item=this->infoTable->item(i,0);
        item[0].setText(QString::number(i+1));
    }
}
