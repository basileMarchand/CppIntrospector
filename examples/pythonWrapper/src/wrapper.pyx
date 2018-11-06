cimport fake

cdef class pyFake:
     def __cinit__(self):
         self._thisptr = new fake.FakeObject()

     def __dealloc__(self):
         if self._thisptr != NULL:
             del self._thisptr

     cpdef void set(self, object name, object value):
         cdef string _type = self._thisptr.getAttrTypes(name);
         if _type == b"double":
            self._thisptr.set[double](name, value)
         elif _type == b"int":
            self._thisptr.set[int](name, value)

     cpdef object get(self, object name):
         cdef string _type = self._thisptr.getAttrTypes(name);

         if _type == b"double":
             return self._thisptr.get[double](name);
         elif type == b"int":
             return self._thisptr.get[int](name);
         elif type == b"string":
             return self._thisptr.get[string](name);


     cpdef void call(self, object name):
         self._thisptr.call(name)