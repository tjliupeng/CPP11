#include <utility>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class String
{
 public:
  String()
    : data_(new char[1])
  {
    *data_ = '\0';
  }
 
  String(const char* str)
    : data_(new char[strlen(str) + 1])
  {
    strcpy(data_, str);
  }
 
  String(const String& rhs)
    : data_(new char[rhs.size() + 1])
  {
    cout<<"copy constructor, data address is "<<hex<<int(&data_)<<endl;
    strcpy(data_, rhs.c_str());
  }
  /* Delegate constructor in C++11
  String(const String& rhs)
    : String(rhs.data_)
  {
  }
  */
 
  ~String()
  {
    delete[] data_;
  }
 
  /* Traditional:
  String& operator=(const String& rhs)
  {
    String tmp(rhs);
    swap(tmp);
    return *this;
  }
  */
  String& operator=(String rhs)
  {
    swap(rhs);
    return *this;
  }
 
  // C++ 11
  String(String&& rhs)
    : data_(rhs.data_)
  {
    cout<<"move constructor, data address is "<<hex<<int(&data_)<<endl;  
    rhs.data_ = nullptr;
  }
 
  String& operator=(String&& rhs)
  {
    swap(rhs);
    cout<<"move assignment, data address is "<<hex<<int(&data_)<<endl;
    return *this;
  }
 
  // Accessors
 
  size_t size() const
  {
    return strlen(data_);
  }
 
  const char* c_str() const
  {
    return data_;
  }
 
  void swap(String& rhs)
  {
    std::swap(data_, rhs.data_);
  }
 
  friend ostream& operator<< (ostream& os, const String& str)
  {
    os<<"data_ address is "<<hex<<int(&(str.data_))<<", string is "<<str.data_<<endl;
    return os;
  }
 private:
  char* data_;
};
void foo(String x)
{
}
 
void bar(const String& x)
{
}
 
String baz()
{
  String ret("world");
  cout<<"calling baz()"<<endl;
  return ret;
}
 
int main()
{
  String s0;
  cout << "s0" << s0 <<endl;
  String s1("hello");
  cout << "s1" << s1 <<endl;
  String s2(s0);
  cout << "s2" << s2 <<endl;
  String s3 = s1;
  cout << "s3" << s3 <<endl;
  s2 = s1;
  cout<<"after s2 = s1" << " s2 " << s2 <<endl;
 
  foo(s1);
  bar(s1);
  foo("temporary");
  bar("temporary");
  String s4 = baz();
  cout<<"s4 " <<s4<<endl;
 
  vector<String> svec;
  cout<<"push 1"<<endl;
  svec.push_back(s0);
  cout<<"push 2"<<endl;
  svec.push_back(s1);
  cout<<"push 3"<<endl;
  svec.push_back(baz());
  cout<<"push 4"<<endl;
  svec.push_back("good job");
}

