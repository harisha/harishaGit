#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* encrypt(char* str, unsigned int key)
{
    unsigned int start_val;
	unsigned int end_val;
	int i = 0;
	int len = strlen(str);
	
    if (key > 25)
	{
	    return str;
	}
	
	while(i < len)
	{
	    if(!isspace(str[i]))
		{
			if(str[i] >= 65 && str[i] <=90)
			{
				start_val = 65;
				end_val = 90;
			}
			else if(str[i] >= 97 && str[i] <= 122)
			{
				start_val = 97;
				end_val = 122;
			}
		
			/* if greater then end ascii */
			if(str[i] + key > end_val)
			{
				str[i] = ((str[i] + key) - end_val - 1) + start_val;
			}
			else
			{
				str[i] = str[i] + key;
			}
		}
		i++;
	}
	return str;
}

char* decrypt(char* str, unsigned int key)
{
    unsigned int start_val;
	unsigned int end_val;
	int i = 0;
	int len = strlen(str);

    if (key > 25)
	{
	    return str;
	}
	
	while(i < len)
	{
	    if(!isspace(str[i]))
		{
			if(str[i] >= 65 && str[i] <=90)
			{
				start_val = 65;
				end_val = 90;
			}
			else if(str[i] >= 97 && str[i] <= 122)
			{
				start_val = 97;
				end_val = 122;
			}
		
			/* if less then begin ascii */
			if(str[i] - key < start_val)
			{
				str[i] = end_val + ((str[i] - key) - start_val) + 1;
			}
			else
			{
				str[i] = str[i] - key;
			}
		}
		i++;
	}
	return str;
}


int main()
{
    char encrp[] = "going on";
	encrypt(encrp, 20);
	printf("%s\n", encrp);
	char decrp[] = "aicha ih";
	printf("%s\n", decrypt(decrp, 20));
}
