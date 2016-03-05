#include "binNode.h"

template <typename T> int BinNode<T>::size() 

{ //统计当前节点后代总数，即以其为根的子树规模
  int s = 1; //计入本身
  if (lChild_) s += lChild->size(); //递归计入左子树规模
  if (rChild_) s += rChild->size(); //递归计入右子树规模
  return s;
}

template <typename T> //将e作为当前节点的左孩子插入二叉树
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e) 
{
  return lChild_ = new BinNode(e, this);  
}

template <typename T> //将e作为当前节点的右孩子插入二叉树
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
 { 
  return rChild_ = new BinNode(e, this); 
 }
