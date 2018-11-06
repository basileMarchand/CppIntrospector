#ifndef _FAKE_OBJECT_HPP_
#define _FAKE_OBJECT_HPP_

#include "Introspector.hpp"


//
// A fake object
//
class FakeObject: public Introspector<FakeObject>{
protected:
  double _value;
  string _name;
  vector<string> _variables;

public:
  FakeObject();
  void  print();
  double test();
  double test2(double);
  double test3(double, int);
  void test4(double, int);
};



#endif
