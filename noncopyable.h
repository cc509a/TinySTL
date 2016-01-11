#ifndef AYU_NONCOPYABLE_H
#define AYU_NONCOPYABLE_H

namespace ayu
{
class noncopyable
{
 protected:
  noncopyable(){}
  ~noncopyable(){}
 private:
  noncopyable(const& temp); 
  const noncopyable& operator= (const noncopyable&);
}
}

#endif
