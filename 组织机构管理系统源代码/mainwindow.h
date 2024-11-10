#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QIcon>
#include <QToolBar>
#include <QLabel>
#include <QSplashScreen>
#include <QClipboard>
#include <QColorDialog>
#include <QDockWidget>
#include <QTreeWidget>
#include <QFileDialog>
#include <ActiveQt/QAxObject>

#include "propertiesdialog.h"
#include "superiordialog.h"
#include "myGraphicsScene.h"
#include "myView.h"
#include "Node.h"
#include "Link.h"
#include "finddialog.h"
#include "person.h"
#include "department.h"

#include <QDialog>
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

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
/*
 * @brief 主窗口类
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //创建项
    void createActions();
    //创建菜单
    void createMenus();
    //创建工具栏
    void createToolBar();
    //创建工具栏
    void createStatusBar();
    //创建按钮连接
    void createButtonConnect();
    //调整场景大小
    void resizeScene(QRectF rect);
    //设置Z轴值
    void setZValue(int value);
    //选择两个结点
    QPair<Node *,Node*> selectNodePair();
    //选择一个结点
    Node* selectNode();
    //选择一个连线
    Link* selectLink();
    //设置选项窗口
    void setTabWidget();
    //设置停靠窗口
    void setDockWidget();
    //显示警告信息
    void showWarningMsg();
    //删除两个结点之间的连线
    void deleteLink(Node* startNode,Node*terminalNode);
    void insertRow(int row,QString id,QString name,QString position,QTableWidget*infoTable);
    //根据输入列数映射到excel列
    QString mapToExecleCol(int col);
    //获取当前视图
    MyView* getCurrentView();
    //随机产生人员id
    int getRandomPersonId();
private slots:
    //工具相应槽函数
    void newFile();
    void savePhoto();
    void saveTable();
    void exitAppication();
    void deleteNode();
    void cutNode();
    void copyNode();
    void pasteNode();
    //设置手型工具
    void setHandTool(bool value);
    //设置选择工具
    void setSelectionTool(bool value);
    //在指定位置创建结点，并返回该结点
    Node * setupNode(QPointF point,QString name,
                    QVector<QPair<QString,QPair<QString,QString>>> info,
                    int type);
    //添加结点
    void addNode(QPointF point=QPointF(300,300),QString name="",
                 QVector<QPair<QString,QPair<QString,QString>>> info= QVector<QPair<QString,QPair<QString,QString>>>(),
                 int type=1,bool isShowDialog=true);
    //添加连线
    void addLink();
    //插入结点
    void insertNode();
    //设置结点在最上层
    void bringToFront();
    //设置结点为最底部
    void sendToBack();
    //更新所有项的使能信号
    void updateAllActions();
    //放大视图
    void zoomIn();
    //缩小视图
    void zoomOut();
    //弹出选择框
    void findDialog();
    //设置画布高度
    void setSceneHeight(int);
     //设置画布宽度
    void setSceneWidth(int);

signals:
    //向查找框发出消息
    void sendFindSignal(QSet<Node*>nodes,MyView*currentView);

private:
    Ui::MainWindow *ui;
    //menuBar 在ui界面中
    // QMenuBar* menuBar;
    //菜单
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* toolsMenu;
    //菜单项
    //文件
    QAction *newAction;
    QAction* savePhotoAction;
    QAction* saveTableAction;
    QAction* exitAction;
    QAction* separator;
    //编辑
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *findAction;
    QAction *goToNodeAction;
    //工具
    QAction *selectionMode;
    QAction *handToolAction;
    QAction *selectionToolAction;
    QAction *addNodeAction;
    QAction *addLinkAction;
    QAction *insertNodeAction;
    QAction *sendToBackAction;
    QAction *bringToFrontAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    //工具栏
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *viewToolBar;
    //
    //状态栏
    QLabel *locationLabel;
    QLabel *tipLabel;
    //当前视图
    MyView *currentView;
    //当前指向的类型
    int itemType;
    //Z轴坐标设置，用于管理图形的纵向位置
    int minZ;
    int maxZ;
    //
    //鼠标位置
    QPointF mousePos;

protected:
    //处理退出界面事件
   void closeEvent(QCloseEvent *event);
    //右键菜单
   void contextMenuEvent(QContextMenuEvent *event);

};
#endif // MAINWINDOW_H
