CppIntrospector 
===============


Interest
--------

CppIntrospector is a single C++ header file enabling class introspection, i.e. an object using this introspector : 

* can return the list of its attributs and the associated type (under string format)

* has the get and set method to push pull attribut value
* can return the list of its exposed methods 
* has a call command to execute the given method considering any number of input argument


Installation
------------

Since the CppIntrospector is a single c++ header file, no installation step is needed. 

Usage
-----

To used CppIntrospector you only have to include the header file in your code. 

```c
#include "Introspector.hpp"
```

Then your object should inherit from the Introspector class as follow: 

```c++
class FakeObject: Introspector<FakeObject>{
	int _int_attr;
	double _double_attr;
	vector<double> _vector_attr;
	
};
```

To expose some of your attributs using the CppIntrospector API, you only have to set (in the class constructor for example)


```c++
FakeObject::FakeObject(): Introspector(){
    this->_attributs.resize(3) ;
    this->_attributs[0] = new Attribut<int>("int_attr", this->_int_attr );
    this->_attributs[1] = new Attribut<double>("double_attr", this->_double_attr );
    this->_attributs[2] = new Attribut< vector<double> >("doubles", this->_vector_attr );

...
}
```

In the same way, if you want to expose some methods using the CppIntrospector API, you only have to add the following lines : 

```c++
FakeObject::FakeObject(): Introspector(){
	...
	
    this->_methods.resize(5);
    this->_methods[0] = new Method<FakeObject>( "print", this, &FakeObject::print );
    this->_methods[1] = new Method<FakeObject, double>( "test", this, &FakeObject::test );
    this->_methods[2] = new Method<FakeObject, double, double>( "test2", this, &FakeObject::test2 );
    this->_methods[3] = new Method<FakeObject, double, double, int>( "test3", this, &FakeObject::test3 );
    this->_methods[4] = new Method<FakeObject, void, double, int>( "test4", this, &FakeObject::test4 );

}
```

For a full example you can check in the directory *examples/cpp*.



Another usage 
-------------

A possible usage of this kind of tools is to develop "automatic" wrapper between languages. For example it is really simple to develop a Python wrapper around c++ class if there is some introspection features. For example in the directory *examples/pythonWrapper* you have a minimal prototype of a Python wrapper around the c++ FakeObject using very few lines of Cython. 

** Limitations ** : the wrapping cannot handle the call method when there is input parameter due to the fact that actually Cython doesn't support c++11 variadic template arguments. 









