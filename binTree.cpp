#include "binTree.h"
#include <stack>
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) 
{
   return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template <typename T> 
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) 
{ 
  while (x) 
  { 
    updateHeight(x); x = x->parent;
  } 
} 

template <typename VST> 
void travPre(VST& e)
{
  stack<VST> s;
  s.push(e);
  while (!s.empty())
	
}
