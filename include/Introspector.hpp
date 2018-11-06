#ifndef _INTROSPECTOR_HPP_
#define _INTROSPECTOR_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;
// 
// The struct used to convert a c++ type to a string 
// 
template<typename T>
struct TypeOf{ static string str(){return "void";} };
template<>
struct TypeOf<double>{ static string str(){return "double";} };
template<>
struct TypeOf<int>{ static string str(){return "int";} };
template<>
struct TypeOf<string>{ static string str(){return "string";} };

template<typename T>
struct TypeOf< vector< T > >{ static string str(){return "vector[" + TypeOf<T>::str() + "]";} };

// The BaseAttr class --- the value of the attribut is not stored here but in the daughter templated class
// This class is only here to have a common type between all attributs to store all of them in a vector<BaseAttr*>
class BaseAttr{
protected:
  string _name; 
  string _type;

public:
  BaseAttr(string name): _name(name){
  }
  string name(){
    return this->_name ;
  }
  string type(){
    return this->_type;
  }
};


// The true Attribut class --- the value is stored here and the set and get method are defined here
// This implies than a static_cast<T> is needed later to used Attribut
template<typename T>
class Attribut: public BaseAttr{  
protected:
  T& _value;

public:
  Attribut(string name, T& val ): BaseAttr(name), _value(val){
    this->_type = TypeOf<T>::str();
  }

  void set(T val ){
    this->_value = val;
  }

  T get(){
    return this->_value;
  }

};


// The BaseMethod class --- the base class used to handle public methods 
// The goal of this BaseMethod is to have a common type between all methods to store them in a vector<BaseMethod*>
class BaseMethod{
protected:
  string _name;
  
public:
  BaseMethod(string name): _name(name){}
  string name(){
    return this->_name;
  }

  
};



// The true Method class --- the pointer to the method is stored here
// A variadic template parameter is used to handle all types of method arguments
// The method return type is also templated (a specialization is needed for a return type void because a void& is not allowed)
template<typename O, typename R=void, typename... Args>
class Method: public BaseMethod{
protected:
  O* _owner;
  typedef R (O::*Member)(Args...) ;

  Member _method;
public:
  Method(string name, O* instance, Member method): BaseMethod(name), _owner( instance ){
    this->_method =method;
  }
  
  void call(R& ret, Args ... args){
    ret = (this->_owner->*(this->_method))(args...);
  }
};



// Template specialization needed for void& return 
template<typename O, typename ... Args>
class Method<O,void, Args...>: public BaseMethod{
protected:
  O* _owner;
  typedef void (O::*Member)(Args...) ;
  
  Member _method;

public:
  Method(string name, O* instance, Member method): BaseMethod(name), _owner( instance ){
    this->_method =method;
  }
  
  void call(Args... args){
    (this->_owner->*(this->_method))(args...);
  }
};


//
// The introspector class --- It is the Base Object from which all other objects should inherite
// to implement utilities for introspection
//

template<typename O>
class Introspector{
protected:
  vector<BaseAttr*> _attributs;
  vector<BaseMethod*> _methods;

public:
  Introspector(){
  }

  vector<BaseAttr*>& getAttributList(){
    return this->_attributs;
  }

  vector<string> getAttrNames(){
    vector<string> _names( this->_attributs.size() );
    for( int i=0; i<_names.size(); i++){
      _names[i] = this->_attributs[i]->name();
    }
    return _names;
  }

  vector<string> getMethodNames(){
    vector<string> _names( this->_methods.size() );
    for( int i=0; i<_names.size(); i++){
      _names[i] = this->_methods[i]->name();
    }
    return _names;
  }


  vector<string> getAttrTypes(){
    vector<string> _types( this->_attributs.size() );
    for( int i=0; i<_types.size(); i++){
      _types[i] = this->_attributs[i]->type();
    }
    return _types;
  }

  string getAttrTypes(string name){
    string _type;
    bool ok=false;
    for( int i=0; i<this->_attributs.size(); i++){
      if( this->_attributs[i]->name() == name ){
	_type = this->_attributs[i]->type();
	ok = true;
	break;
      }
    }
    if( !ok ){
      throw invalid_argument("There is no attribut " + name + " defined");
    }

    return _type;
  }



  template<typename T>
  void set(string name, T x){
    for( int i=0; i<this->_attributs.size(); i++){
      if( this->_attributs[i]->name() == name ){
	static_cast<Attribut<T>*>(this->_attributs[i])->set( x );
	return ;
      }
    }
    throw invalid_argument("There is no attribut " + name + " defined");
  }

  template<typename T>
  void get(string name, T& x){
    for( int i=0; i<this->_attributs.size(); i++){
      if( this->_attributs[i]->name() == name ){
	x = static_cast<Attribut<T>*>(this->_attributs[i])->get();
	return;
      }
    }
    throw invalid_argument("There is no attribut " + name + " defined");
  }

  template<typename T>
  T get(string name){
    T x;
    bool ok=false;
    for( int i=0; i<this->_attributs.size(); i++){
      if( this->_attributs[i]->name() == name ){
	x = static_cast<Attribut<T>*>(this->_attributs[i])->get();
	ok = true;
	break;
      }
    }

    if( !ok ){
      throw invalid_argument("There is no attribut " + name + " defined");
    }
    return x;
  }



  void call(string mname ){
    for( int i=0; i<this->_methods.size(); i++){
      if( this->_methods[i]->name() == mname ){
	static_cast<Method<O>*>(this->_methods[i])->call();
	return;
      }
    }
    throw invalid_argument("There is no method " + mname + " defined");
  }

  template<typename R, typename... I>
  void call(string mname, R& ret, I...args ){
    for( int i=0; i<this->_methods.size(); i++){
      if( this->_methods[i]->name() == mname ){
	static_cast<Method<O,R,I...>*>(this->_methods[i])->call(ret, args...);
	return;
      }
    }
    throw invalid_argument("There is no method " + mname + " defined");
  }

  template<typename... I>
  void call(string mname, I...args ){
    for( int i=0; i<this->_methods.size(); i++){
      if( this->_methods[i]->name() == mname ){
	static_cast<Method<O,void,I...>*>(this->_methods[i])->call(args...);
	return;
      }
    }
    throw invalid_argument("There is no method " + mname + " defined");
  }
};


#endif
