#pragma once

#define BinNodePosi(T) BinNode<T>* 
#define stature(p) ((p) ? (p)->height : -1) 
template <typename T> 
struct BinNode 
{
   T data_; 
   BinNodePosi(T) parent_; 
   BinNodePosi(T) lChild_;
   BinNodePosi(T) rChild_; 
   int height_; 
   int npl_; //Null Path Length（左式堆，也可直接用height代替）
   RBColor color_; //颜色（红黑树）
// 构造函数
   BinNode() : parent_(NULL), lChild_(NULL), rChild_(NULL), height_(0), npl_(1), color_(RB_RED) { }
   BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
           int h = 0, int l = 1, RBColor c = RB_RED)
      : data_(e), parent_(p), lChild_(lc), rChild_(rc), height_(h), npl_(l), color_(c) { }
// 操作接口
   int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
   BinNodePosi(T) insertAsLC(T const &); //作为当前节点的左孩子插入新节点
   BinNodePosi(T) insertAsRC(T const &); //作为当前节点的右孩子插入新节点
   BinNodePosi(T) succ(); //取当前节点的直接后继
   template <typename VST> void travLevel(VST&); //子树层次遍历
   template <typename VST> void travPre(VST&); //子树先序遍历
   template <typename VST> void travIn(VST&); //子树中序遍历
   template <typename VST> void travPost(VST&); //子树后序遍历
// 比较器、判等器（各列其一，其余自行补充）
   bool operator<(BinNode const& bn) { return data_ < bn.data_; } //小于
   bool operator==(BinNode const& bn) { return data_ == bn.data_; } //等于
/*DSA*/
/*DSA*/BinNodePosi(T) zig(); //顺时针旋转
/*DSA*/BinNodePosi(T) zag(); //逆时针旋转
};
