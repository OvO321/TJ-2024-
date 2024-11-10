#include "superiordialog.h"



/*
 * @brief 构造函数，当添加连线时显示，可以设置上下级结点
 * @param nodes  结点对指针
 * @param parent  父组件指针
 */
SuperiorDialog::SuperiorDialog(QPair<Node*,Node*> nodes,QWidget *parent)
    : QDialog(parent) {
    QGridLayout *mainLayout=new QGridLayout(this);
    //显示部门名
    startDepartmentLable=new QLabel(QString(tr("Start department name     : ")));
    startDepartmentLine=new QLineEdit(nodes.first->getDepartmentName());
    terminalDepartmentLable=new QLabel(QString(tr("Terminal department name: ")));
    terminalDepartmentLine=new QLineEdit(nodes.second->getDepartmentName());
    mainLayout->addWidget(startDepartmentLable,0,0);
    mainLayout->addWidget(startDepartmentLine,0,1);
    mainLayout->addWidget(terminalDepartmentLable,1,0);
    mainLayout->addWidget(terminalDepartmentLine,1,1);
    //显示选项框
    setSuperiorLabel=new QLabel(tr("Set superior:"));
    mainLayout->addWidget(setSuperiorLabel,2,0);
    //显示按钮
    selectStartButton=new QRadioButton((("Select"+startDepartmentLine->text())),this);
    selectTerminalButton=new QRadioButton((("Select"+terminalDepartmentLine->text())),this);
    //默认末尾按钮为上级
    selectTerminalButton->setChecked(true);
    mainLayout->addWidget(selectStartButton,3,0);
    mainLayout->addWidget(selectTerminalButton,3,1);
    //显示确认和取消
    okButton=new QPushButton((tr("OK")),this);
    cancelButton=new QPushButton(tr("Cancel"),this);
    mainLayout->addWidget(okButton,4,0);
    mainLayout->addWidget(cancelButton,4,1);
    //连接信号
    connect(okButton,SIGNAL(clicked()),this,SLOT(on_okButton_clicked()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(on_cancelButton_clicked()));
    //设置布局
    setLayout(mainLayout);
    //设置标题
    this->setWindowTitle("Set Superior");
}
/*
 * @brief 析构函数
 */
SuperiorDialog::~SuperiorDialog(){

}


/*
 * @brief 构造属性对话框
 * @param nodes    被选中的结点对
 * @param parent  父组件指针
 * @param ok
 * @return 返回的字符串数组格式如下:
 *   success:{"起始部门名",{终端部门名},"0/1"(0：设置起始部门为上级 1：设置终端部门为上级)}
 *   fail: ""，空字符串
 */
QStringList SuperiorDialog::getStrings(QPair<Node*,Node*> nodes,QWidget *parent, bool *ok){
    SuperiorDialog *dialog = new SuperiorDialog(nodes,parent);
    QStringList list;
    while(true){
        //执行操作，进入模态对话框，阻塞其他进程
        const int ret = dialog->exec();
        if (ok){
            *ok = !!ret;
        }
        //有异常情况，返回对话框
        if(ret==3){
            continue;
        }
        //正确返回
        else if(ret==QDialog::Accepted){
            list<<dialog->startDepartmentLine->text();
            list<<dialog->terminalDepartmentLine->text();
            if(dialog->selectStartButton->isChecked()){
                list<<"0";
            }
            else{
                list<<"1";
            }
            break;
        }
        //返回空字符串
        else if(ret==QDialog::Rejected){
            break;
        }
        else{
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
void SuperiorDialog::on_okButton_clicked(){
    //部门名称必须非空
    if(this->startDepartmentLine->text().isEmpty()||
        this->terminalDepartmentLine->text().isEmpty()){
        QMessageBox::warning(this,tr("Warning"),tr("The department name can't be empty!"),
                    QMessageBox::Yes,QMessageBox::Yes);
        //自定义返回值
        done(3);
    }
    else{
        //返回正确值1
        accept();
    }

}
/*
 * @brief 槽函数，响应Cancel按钮按下时发出的信号
 */
void SuperiorDialog::on_cancelButton_clicked(){
    //返回取消值0
    reject();
}
