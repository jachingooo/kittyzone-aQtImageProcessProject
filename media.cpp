#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
 srand((unsigned int)time(0));

unsigned int a[5];

for(int i = 0; i < 5; i++) {

 	a[i] = rand();
 	cout<<a[i]<<endl;}
        return 0;
}
