#include "FakeObject.hpp"


int main(){
 FakeObject fake;
 double v;
 vector<string> names = fake.getAttrNames();
 vector<string>  types = fake.getAttrTypes();

 cout << "The list of available attributs :" << endl;
 for(unsigned int i=0; i<names.size();i++){
   cout << "   " << names[i] << " of type :" << types[i] << endl;
 }

 
 fake.set( names[0], 1.5 );
 fake.get( names[0], v );
 cout << "fake.get  : " << v << endl;

 vector<string> mnames = fake.getMethodNames();
 
 for( unsigned int i=0; i<mnames.size(); i++){
   cout << "Available fake."<< mnames[i] << endl;
 }

 fake.call("print");
 double tmp=0;
 fake.call("test",tmp );
 double in=1.;

 fake.call("test2", tmp, in);
 int in2=10;
 fake.call("test3", tmp, 20., in2);

 fake.call("test4", 20., in2);
 return 0;
}
