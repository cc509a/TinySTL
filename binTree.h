#pragma once
#include "binNode.h" 
template <typename T> 
class BinTree 
{ //二叉树模板类
protected:
   int size_; //规模
   BinNodePosi(T) root_; //根节点
   virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
   void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
   BinTree() : size_(0), root__(NULL) { } //构造函数
   ~BinTree() { if (0 < size_) remove(root_); } //析构函数
   int size() const { return size_; } //规模
   bool empty() const { return !root_; } //判空
   BinNodePosi(T) root() const { return root_; } //树根
   BinNodePosi(T) insertAsRoot(T const & e); //插入根节点
   BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const & e); //e作为x的左孩子（原无）插入
   BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const & e); //e作为x的右孩子（原无）插入
   BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x左子树接入
   BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x右子树接入
   int remove(BinNodePosi(T) x); //删除以位置x处节点为根的子树，返回该子树原先的规模
   BinTree<T>* secede(BinNodePosi(T) x); //将子树x从当前树中摘除，并将其转换为一棵独立子树
   template <typename VST> //操作器
   void travLevel(VST& visit) { if (root_) root_->travLevel(visit); } //层次遍历
   template <typename VST> //操作器
   void travPre(VST& visit) { if (root_) root_->travPre(visit); } //先序遍历
   template <typename VST> //操作器
   void travIn(VST& visit) { if (root_) root_->travIn(visit); } //中序遍历
   template <typename VST> //操作器
   void travPost(VST& visit) { if (root_) root_->travPost(visit); } //后序遍历
// 比较器、判等器（各列其一，其余自行补充）
   bool operator<(BinTree<T> const& t) { return root_ && t.root_ && lt(root_, t.root_); }
   bool operator==(BinTree<T> const& t) { return root_ && t.root_ && (root_ == t.root_); }
/*DSA*/
/*DSA*/void stretchToLPath() { stretchByZag(root_); } //借助zag旋转，转化为左向单链
/*DSA*/void stretchToRPath() { stretchByZig(root_, size_); } //借助zig旋转，转化为右向单链
}; //BinTree

