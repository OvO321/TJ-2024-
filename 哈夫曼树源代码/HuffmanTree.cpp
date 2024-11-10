#include "HuffmanTree.h"




/*
 * @brief 构造函数
 * @param isLeaf    是否为叶子结点
 * @param isSelected  是否已经被选择
 * @param weight    //权值
 * @param keyWord   //关键字
 * @param parent    //父亲结点位置
 * @param leftChild  //左孩子结点位置
 * @param rightChild //右孩子结点位置
 * @param pos      //当前位置
 */
HuffmanTree::HuffmanTree(bool isLeaf,bool isSelected,int weight,QString keyWord,int parent,int leftChild,int rightChild,int pos){
    //设置对应的值
    this->isLeaf=isLeaf;
    this->isSelected=isSelected;
    this->weight=weight;
    this->keyWord=keyWord;
    this->parent=parent;
    this->leftChild=leftChild;
    this->rightChild=rightChild;
    this->pos=pos;
}
HuffmanTree::~HuffmanTree(){
}
