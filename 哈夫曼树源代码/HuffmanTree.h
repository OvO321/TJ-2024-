#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <QVector>
#include <QString>

class HuffmanTree{
public:
    bool isLeaf;    //是否为叶子结点
    bool isSelected;  //是否被选择过
    int weight;     //权值
    QString keyWord;    //关键字
    int parent;      //双亲结点位置
    int leftChild;   //左孩子位置
    int rightChild;  //右孩子位置
    int pos;         //实际数值位置
public:
    //构造函数
    HuffmanTree(bool isLeaf,bool isSelect,int weight,QString keyWord,int parent,int leftChild,int rightChild,int pos);
    ~HuffmanTree();
};























#endif // HUFFMANTREE_H
