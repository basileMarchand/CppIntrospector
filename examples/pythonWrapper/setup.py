from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize


import os


extensions = [
    Extension("*", ["src/*.pyx"],
              include_dirs=[os.path.join(os.path.dirname(os.path.abspath(__file__)), "..","..","include"), 
                            os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "cpp"),
                            os.path.join(os.path.dirname(os.path.abspath(__file__)), "src") ],
              libraries=['test'],
              library_dirs=[os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "cpp")],
              language="c++",
              extra_compile_args=['-std=c++11']

          ),
]

setup(
    name="wrapper",
    ext_modules=cythonize(extensions),
)
