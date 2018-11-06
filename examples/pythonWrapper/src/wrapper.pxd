from libcpp.vector cimport vector
from libcpp.string cimport string

cimport fake

cdef class pyFake:
     cpdef fake.FakeObject* _thisptr;
     cpdef object get(self, object);
     cpdef void set(self, object, object);
     cpdef void call(self, object);