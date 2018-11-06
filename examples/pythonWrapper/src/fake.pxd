# -*- Mode: python -*-                                                          

from libcpp.string cimport string 
from libcpp.vector cimport vector

cdef extern from "FakeObject.hpp":
     cdef cppclass FakeObject:

         vector[string] getAttrNames();
         string getAttrTypes(string);
         vector[string] getMethodNames();
         void set[T](string name, T x);
         T get[T](string name);
         void call(string name);

