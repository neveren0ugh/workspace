#include <iostream>
#include <new>

using namespace std;

int main() {

   double **p = 0;
   p = new double*;
   *p = new double;
   **p = 2;
   cout << **p << endl;
   delete *p;
   delete p;


    return 0;
}
