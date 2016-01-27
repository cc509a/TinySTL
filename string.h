#ifndef AYU_STRING_H
#define AYU_STRING_H
#include "head.h"
#include "assert.h"
using namespace ayu;
namespace ayu
{
 class string
 {
   public:

   string()
     :len_(0),
      str_(new char[1])
   {
     str_[0] = '\0';
   }

   string(const char* str)
     :len_(strlen(str)),
      str_(new char[len_+1])
   {
    strcpy(str_,str); 
   }
  
   string (const string &str)
     :len_(str.size())
   {
     strcpy(str_, str.str_);
   }
   
   string& operator=(const string& str)
   {
     string temp = str;
     sw(temp);
     return *this;
   }

   string(string&& str)
     :len_(str.size()),
     str_(str.str_)
   {
     str.str_ = nullptr;
   }
   virtual ~string ()
   {
     delete []str_;
   }

//operator   
   string& operator=(string&& str)
   {
     sw(str);
     return *this;
   }

  friend std::ostream& operator<<(std::ostream& os, const string& str)
   {
     os<<str.str_;
     return os;
   }
   
   char & operator[](size_t i)
   {
    assert(i<0 || i >len_);
    return str_[i];
   }
//swap
   void sw(string& v)
   {
     swap (str_, v.str_);
     swap (len_, v.len_);
   }
//return
   const char *c_str() const
   {
     return str_;
   }

   size_t size() const 
   {
    return len_;
   }

   private:
     size_t len_;
     char * str_;
 };


}
#endif
