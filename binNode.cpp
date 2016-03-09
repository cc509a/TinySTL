#include "binNode.h"
#include <stack>
#include <queue>
template <typename T> int BinNode<T>::size() 

{ //统计当前节点后代总数，即以其为根的子树规模
  int s = 1; //计入本身
  if (lChild) s += lChild->size(); //递归计入左子树规模
  if (rChild) s += rChild->size(); //递归计入右子树规模
  return s;
}

template <typename T> //将e作为当前节点的左孩子插入二叉树
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e) 
{
  return lChild = new BinNode(e, this);  
}

template <typename T> //将e作为当前节点的右孩子插入二叉树
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
 { 
  return rChild = new BinNode(e, this); 
 }

template <typename T> template <typename VST> 
void BinNode<T>::travPre(VST& visit) { 
  BinNode<T*> x = this;
  std::stack<BinNodePosi(T)> s;
  if (x) 
    s.push(x);
  while(!s.empty())
  {
    vist(s.top());
    x = s.top();
    s.pop();
    if(x->rChild)
      s.push(x->rChild);
    if(x->lChild)
      s.push(x->lChild);
  }
}


template <typename T> template <typename VST> 
void BinNode<T>::travIn(VST& visit) 
{
  BinNode<T*> x = this;
  std::stack<BinNodePosi(T)> s;
  while(x && !s.empty)
  {
    while(x)
   {
     if(x->lChild) 
     {
       s.push(x->lChild);
       x = x->lChild;
     }
   }
   x = s.top();
   vist(x);
   s.pop();
   x = x->rChild; 
  }
}

template <typename T> template <typename VST> 
void BinNode<T>::travLevel(VST& visit) { 
   std::queue<BinNodePosi(T)> Q; 
   Q.enqueue(this); 
   while (!Q.empty()) { 
      BinNodePosi(T) x = Q.dequeue(); visit(x->data);
      if (HasLChild(*x)) Q.enqueue(x->lChild); 
      if (HasRChild(*x)) Q.enqueue(x->rChild); 
   }
}




