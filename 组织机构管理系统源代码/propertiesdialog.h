#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableView>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringList>
#include <QVBoxLayout>


#include "person.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableView>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringList>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QDockWidget>
#include <QTreeWidget>
#include <QFileDialog>
#include <ActiveQt/QAxObject>
#include "Node.h"

class Node;
/*
 * @brief 属性对话框类
 */
class PropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    PropertiesDialog(Node*node,bool isShow,QWidget *parent);
    ~PropertiesDialog();
    //重新设置行号
    void refresh();
    //创建部门相关标签、输入框
    void createDepartment(Node*node,bool isShow);
    //创建表格相关标签、输入框
    void createTable(Node*node,bool isShow);
    //插入新行
    void insertRow(int row,QString id,QString name,QString position);
    //获取属性框
    static QStringList getStrings(Node* node,QWidget *parent,QVector<Person> personTable,bool isShow,bool *ok = nullptr);

private:
    //显示控件
    //部门名
    QLabel*departmentNameLabel;
    QLineEdit*departmentNameLine;
    //上级部门名
    QLabel*superiorNameLabel;
    QLineEdit*superiorNameLine;
    //初始设置位置
    QLabel*positionLabel;
    QRadioButton *mousePositionButton;
    QRadioButton *viewCenterButton;
    //表格
    QLabel*personalInfoLabel;
    QPushButton *addRowButton;
    QPushButton *removeRowButton;
    QTableWidget *infoTable;
    QPushButton *importButton;
    //跳转到某一行
    QLabel*gotoRowLabel;
    QLineEdit*gotoRowLine;
    //确认、退出按钮
    QPushButton*okButton;
    QPushButton*cancelButton;
    //布局控件
    QGridLayout*mainLayOut;
    //属性信息
    QString subDepartmentName;
    QString subSuperiorName;
    QVector<QPair<QString,QPair<QString,QString>>> subPositionPersonInfo;
private slots:
    //完成设置按钮
    void on_okButton_clicked();
    //取消按钮
    void on_cancelButton_clicked();
    //添加新行按钮
    void on_addRowButton_clicked();
    //移除行按钮
    void on_removeRowButton_clicked();
    //导入表格按钮
    void on_importButton_clicked();
};

#endif // PROPERTIESDIALOG_H
