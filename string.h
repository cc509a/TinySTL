#ifndef AYU_STRING_H
#define AYU_STRING_H
#include "head.h"
#include "assert.h"
using namespace ayu;
namespace ayu
{
extern size_t strlen(const char *str);
extern char* strcpy(char* des, char* source);
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
    str_[len_] = '\0'; 
   }
  
   string (const string &str)
     :len_(str.size())
   {
     strcpy(str_, str.str_);
   }
   
   string& operator=(const string& str)
   {
     string temp = str;
     swap(*this,temp);
     return *this;
   }

   string(string&& str)
     :len_(str.size()),
     str_(str.str_)
   {
     str.str_ = nullptr;
   }
   
   string& operator=(string&& str)
   {
     swap(*this,str);
     return *this;
   }

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

   size_t strlen(const char* str)
   {
     assert(str != nullptr);
     size_t len = 0;
     while((*str++) != '\0')
     {
       ++len;
     }
     return len;
   }

   char* strcpy(char* des, char* source)
   {
     assert((des != nullptr) && (source != nullptr));
     char *ret = des;
     while((*des++ = *source++) != '\0');
     return ret;
   }

}

