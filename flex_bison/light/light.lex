%{
#include <stdlib.h>
void yyerror(char *);
#include "light.tab.h"
char token_str[100]={0};
%}
%%
LIGHT	{strncpy(token_str,yytext,99);return(TOK_LIGHT);}
CALL	{strncpy(token_str,yytext,99);return(TOK_CALL);}
"\n"	{strncpy(token_str,yytext,99);return(END);}
%%
int yywrap(void) {
    return 1;
}
