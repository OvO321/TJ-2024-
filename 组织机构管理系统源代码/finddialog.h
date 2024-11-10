#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QStandardItemModel>
#include <QComboBox>
#include "Node.h"
#include "propertiesdialog.h"
#include "myView.h"


/*
 * @brief 搜索对话框类
 */
class FindDialog :public QDialog{
    Q_OBJECT
public:
    //构造函数
    FindDialog(QWidget*parent=nullptr);
private slots:
    //相应寻找按钮
    void findClicked();
    //按钮的使能信号
    void enableFindButton(QString text);
    //接受主窗口的信息
    void receiveSignal(QSet<Node*>nodeTree,MyView*currentView);
    //响应鼠标点击
    void on_resultComboBox_activated(int index);
private:
    //标签和输出框
    QLabel *findDepartmentLabel;
    QLineEdit*findDepartmentLine;
    QLabel *findPersonLabel;
    QLineEdit*findPersonLine;
    QLabel *resultLabel;
    QComboBox *resultComboBox;
    //选择大小写框
    QCheckBox*caseCheckBox;
    //寻找、关闭按钮
    QPushButton*findButton;
    QPushButton*closeButton;
    //网格布局
    QGridLayout*mainLayout;
    //父控件副本
    QSet<Node*>subNodeTree;
    MyView*subCurrentView;

};

#endif // FINDDIALOG_H
