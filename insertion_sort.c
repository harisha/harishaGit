#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int a[] = {10, 15, 1, 9, 99 , 100, 7};
    int num_elems = 7;
    int i, j;
    int temp;
    
    for(i=1;i<num_elems;i++)
    {
        j=i;
        while(j>0 && a[j]<a[j-1])
        {
            temp = a[j-1];
            a[j-1] = a[j];
            a[j] = temp;
            j--;
        }
    }
    
    for(i=0;i<num_elems;i++)
    {
        printf("%d\n", a[i]);
    }
    
}
