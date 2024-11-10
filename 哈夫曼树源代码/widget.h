#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScrollBar>
#include <QScrollArea>
#include <QPainter>
#include <QHash>
#include <QFont>
#include <QLabel>
#include <QQueue>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDateTime>
#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QTableWidget>
#include <ActiveQt/QAxObject>
#include <QTimer>
#include <QPalette>
#include "HuffmanTree.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    //根据输入的数据得到关键字和频率
    void recordFrequency(const QString &s);
    //在当前的哈夫曼树中找出权值最小和此小的两个结点的位置
    void select(int &leftChild,int &rightChild);
    //构造哈夫曼树
    void construct();
    //绘制结点
    void drawNode(QPainter &painter,int posX, int posY, int i,int diameter,int height,int n,int deepth);
    //绘制哈夫曼树
    void drawPicture();
    ~Widget();
    //事件过滤器函数
    bool eventFilter(QObject *obj, QEvent *event);
    //实际调用的绘制函数
    void paint();
    //对关键字进行编码
    void encoder();
    //插入编码列表数据
    void insertEncoderTable();
    //插入关键字频率列表数据
    void insertKeyWordTable();
    //字符串倒序
    void reverseString(QString &str);
    //获取哈夫曼树的最大深度
    int getMaxDeepth();
    //设置根结点
    void setRoot();
    //从关键字频率列表中获取字符串
    QString getStringFromNum();
    //获取随机数字
    QString getRandomNumbers(int length);
    //获取随机汉字
    QString getRandomChinese(int length);
    //获取随机字母
    QString getRandomLetters(int length);
    //获取随机字符串
    QString getRandomStrings(int length);
private:
    //绘图对象
    Ui::Widget *ui;
    //根节点
    HuffmanTree* root = nullptr;
    //哈夫曼树
    QVector<HuffmanTree*>huffmanTree;
    //存储关键字和频率
    QVector<QPair<QString,int>> num;
    //存储编码
    QVector<QString> encoderList;
    //显示视图区域
    QScrollArea * scrollArea;
    //实际绘图区域
    QWidget * widget;
protected:
           // void paintEvent(QPaintEvent*);

private slots:
    void on_ensureButton_clicked();
    void on_textInput_textChanged(const QString &arg1);
    void on_clearButton_clicked();
    void on_importTextButton_clicked();
    void on_exportTableButton_clicked();
    void on_exportPhotoButton_clicked();
    void on_keyWordTable_itemActivated(QTableWidgetItem *item);
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_randomComboBox_activated(int index);
};
#endif // WIDGET_H
