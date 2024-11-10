#ifndef SUPERIORDIALOG_H
#define SUPERIORDIALOG_H

#include <QInputDialog>
#include <QObject>
#include <QStringList>
#include <QMessageBox>
#include <QFormLayout>
#include <QRadioButton>
#include <QPushButton>
#include "Node.h"
/*
 * @brief 设置上下级对话框类
 */
class SuperiorDialog : public QDialog
{
    Q_OBJECT
public:
    //构造函数
    SuperiorDialog(QPair<Node*,Node*> nodes,QWidget *parent = nullptr);
    ~SuperiorDialog();
    //可以直接调用，返回输入字符
    static QStringList getStrings(QPair<Node*,Node*> nodes,QWidget *parent, bool *ok = nullptr);
private:
    //起始和终端部门名
    QLabel *startDepartmentLable;
    QLineEdit *startDepartmentLine;
    QLabel *terminalDepartmentLable;
    QLineEdit *terminalDepartmentLine;
    //设置子、父结点
    QLabel *setSuperiorLabel;
    QRadioButton *selectStartButton;
    QRadioButton *selectTerminalButton;
    //确认、取消按钮
    QPushButton*okButton;
    QPushButton*cancelButton;
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // SUPERIORDIALOG_H
