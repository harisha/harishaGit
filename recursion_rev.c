#include <stdio.h>


void recurString(char *src_ptr,char *dest_ptr)
{
    static int i = 0;
    if(src_ptr[strlen(src_ptr) -1 -i] != '\0') 
    {
        dest_ptr[i] = src_ptr[strlen(src_ptr) -1 -i];
        i++;
	recurString(src_ptr,dest_ptr);
    }
    else
    {
    	dest_ptr[i] = '\0'; 
    }
}

int main()
{
    char* src = "Harisha B Manjunath"; 
    char dest[100];
    recurString(src,dest);
    printf("%s\n",dest);
}
