#include "finddialog.h"





/*
 * @brief 构造函数
 * @param parent 父节点指针
 */
FindDialog::FindDialog(QWidget*parent):QDialog(parent) {
    //部门查找
    findDepartmentLabel=new QLabel(tr("Find &Department:"));
    findDepartmentLine=new QLineEdit;
    findDepartmentLabel->setBuddy(findDepartmentLine);
    //人员查找
    findPersonLabel=new QLabel(tr("Find &person        :"));
    findPersonLine=new QLineEdit;
    findPersonLabel->setBuddy(findPersonLine);
    //存储结果
    resultLabel=new QLabel(tr("Find &Result         :"));
    resultComboBox=new QComboBox(this);
    resultLabel->setBuddy(resultComboBox);
    connect(resultComboBox,SIGNAL(activated(int)),this,SLOT(on_resultComboBox_activated(int)));
    //区分大小写
    caseCheckBox=new QCheckBox(tr("Match &case"));
    findButton=new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);
    closeButton=new QPushButton(tr("Close"));
    //网格布局
    mainLayout=new QGridLayout;
    mainLayout->addWidget(findDepartmentLabel,0,0);
    mainLayout->addWidget(findDepartmentLine,0,1,1,2);
    mainLayout->addWidget(findPersonLabel,1,0);
    mainLayout->addWidget(findPersonLine,1,1,1,2);

    mainLayout->addWidget(resultLabel,2,0);
    mainLayout->addWidget(resultComboBox,2,1,1,2);

    mainLayout->addWidget(caseCheckBox,3,0);
    mainLayout->addWidget(findButton,3,1);
    mainLayout->addWidget(closeButton,3,2);

    setLayout(mainLayout);
    //信号连接
    connect(findDepartmentLine,SIGNAL(textChanged(QString)),this,SLOT(enableFindButton(QString)));
    connect(findPersonLine,SIGNAL(textChanged(QString)),this,SLOT(enableFindButton(QString)));
    connect(findButton,SIGNAL(clicked()),this,SLOT(findClicked()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());

}


/*
 * @brief 槽函数，响应点击搜索按钮
 */
void FindDialog::findClicked(){
    QStringList list;
    list<<this->findDepartmentLine->text();
    list<<this->findPersonLine->text();
    Qt::CaseSensitivity cs=caseCheckBox->isChecked()?Qt::CaseInsensitive:Qt::CaseSensitive;
    this->resultComboBox->clear();
    bool notFound=true;
     //只有部门
    if(list[1]==""){
        foreach (auto iter, this->subNodeTree) {
            if(iter->getDepartmentName().indexOf(list[0],0,cs)!=-1){
                this->resultComboBox->addItem(iter->getDepartmentName());
                notFound=false;
                // return;
            }
        }
    }
    //只有人员
    else if(list[0]==""){
        foreach (auto iter, this->subNodeTree) {
            QVector<QPair<QString,QPair<QString,QString>>> info=iter->getPersonInfo();
            for(int i=0;i<info.size();i++){
                if(info[i].second.first.indexOf(list[1],0,cs)!=-1){
                    this->resultComboBox->addItem("The person is found in department \""+iter->getDepartmentName()
                                              +"\" "+QString::number(i+1)+" row");
                     notFound=false;
                    // return;
                }
            }
        }
    }
    //同时有部门和人员
    else{
        foreach (auto iter, this->subNodeTree) {
            if(iter->getDepartmentName().indexOf(list[0],0,cs)!=-1){
                  QVector<QPair<QString,QPair<QString,QString>>> info=iter->getPersonInfo();
                for(int i=0;i<info.size();i++){
                    if(info[i].second.first.indexOf(list[1],0,cs)!=-1){
                        this->resultComboBox->addItem("The person is found in department \""+iter->getDepartmentName()
                                                  +"\" "+QString::number(i+1)+" row");
                         notFound=false;
                        // return;
                    }
                }
            }


        }
    }
    //没有找到，输出错误信息
    if(notFound){
         this->resultComboBox->addItem("Not Found");
    }


}


/*
 * @brief 槽函数，响应点击搜索按钮
 * @param nodeTree 当前视图所有结点
 * @param currentView 当前视图指针
 */
void FindDialog::receiveSignal(QSet<Node*>nodeTree,MyView*currentView){
    this->subNodeTree=nodeTree;
    this->subCurrentView=currentView;
}


/*
 * @brief 设置按钮使能信号
 * @param text 文本框内容
 */
void FindDialog::enableFindButton(QString text){

    findButton->setEnabled((!this->findDepartmentLine->text().isEmpty())
                           ||(!this->findPersonLine->text().isEmpty()));
}
void FindDialog::on_resultComboBox_activated(int index){
    QString text=this->resultComboBox->currentText();
    qDebug()<<text;
    if(text=="Not Found"){
        return;
    }
    else{
        foreach(auto iter, this->subNodeTree){
            qDebug()<<iter->getDepartmentName();
            if(text.indexOf(iter->getDepartmentName())!=-1){
                //先放大视图
                subCurrentView->getTransform().scale(1.5,1.5);
                //
                QPointF posOffset = iter->pos();
                QPoint newCenter=subCurrentView->mapFromScene(posOffset);
                subCurrentView->centerOn((newCenter));

                iter->setSelected(true);
                qDebug()<<"Sure";
                break;
            }
        }
    }
}


