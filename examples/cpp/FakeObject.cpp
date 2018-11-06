#include "FakeObject.hpp"


FakeObject::FakeObject(): Introspector() {
    this->_attributs.resize(3) ;
    this->_attributs[0] = new Attribut<double>("value", this->_value );
    this->_attributs[1] = new Attribut<string>("name", this->_name );
    this->_attributs[2] = new Attribut< vector<string> >("variables", this->_variables );

    this->_methods.resize(5);
    this->_methods[0] = new Method<FakeObject>( "print", this, &FakeObject::print );
    this->_methods[1] = new Method<FakeObject, double>( "test", this, &FakeObject::test );
    this->_methods[2] = new Method<FakeObject, double, double>( "test2", this, &FakeObject::test2 );
    this->_methods[3] = new Method<FakeObject, double, double, int>( "test3", this, &FakeObject::test3 );
    this->_methods[4] = new Method<FakeObject, void, double, int>( "test4", this, &FakeObject::test4 );  
}



void FakeObject::print(){
    cout << "In Action::print" << endl;
  }

double FakeObject::test(){
    cout << "In Action::test" << endl;
    return this->_value;
  }

double FakeObject::test2(double x){
    cout << "In Action::test2" << endl;
    cout << " input : " << x << endl;
    return this->_value + x;
  }

double FakeObject::test3(double x, int n){
    cout << "In Action::test3" << endl;
    cout << " input : " << x << endl;
    return n*this->_value + x/n;
  }

void FakeObject::test4(double x, int n){
    cout << "In Action::test4" << endl;
    cout << " input : " << x << endl;
    cout <<  n*this->_value + x/n << endl;
  }



