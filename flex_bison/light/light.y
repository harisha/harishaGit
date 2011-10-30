%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(char *);
    extern char token_str[100];
%}
%token TOK_LIGHT TOK_CALL END
%start Input 
%%
Input:
          /* Empty */
        | Input Line
        ;
Line:
          END                                   {printf("end\n"); }
          | CABIN_LC_type END                   {printf("cabin command \n"); }
         ;
CABIN_LC_type:  
                TOK_LIGHT			 {printf("TOK_LIGHT");}
                | TOK_CALL			{printf("TOK_CALL");}
                ;
%%
void yyerror(char *s) {
    //fprintf(stderr, "%s\n", s);
    fprintf(stderr,"err:%s",token_str);
}
int main(void) {
    yyparse();
    return 0;
}
