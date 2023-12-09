%{
        #include <stdio.h>
        #include <stdlib.h>
        #include <math.h>

        int yylex ();
        int yyerror ();
%}

%union
{ double p;}

%token <p> num
%token SIN COS TAN LN SQRT

%left '+' '-'
%left '*' '/'

%type <p> expr

%%
ss: expr {printf ("%g\n", $1);}

expr:	expr'+'expr  { $$ = $1 + $3;}
    |	expr'-'expr  { $$ = $1 - $3;}
    |	expr'*'expr  { $$ = $1 * $3;}
    |	expr'/'expr  {
			if ($3 == 0){
        			printf ("division by zero...\n");
				exit (EXIT_FAILURE);
    			}
		    	else{
				$$ = $1 / $3;
			}
		}
    |	'-'expr		{ $$ = -$2;}
    |	'('expr')'	{ $$ = $2;}
    |	SIN'('expr')'	{ $$ = sin ($3);}
    |	COS'('expr')'	{ $$ = cos ($3);}
    |	TAN'('expr')'	{ $$ = tan ($3);}
    |	LN'('expr')'	{ $$ = log ($3);}
    |	SQRT'('expr')'	{ $$ = sqrt ($3);}
    |	num;
%%

int main (const int argc, const char *argv[])
{
        do
        {
                printf("\n> ");
                yyparse();
        }while (1);

	return EXIT_SUCCESS;
}

int yyerror (char *str)
{
        printf ("invalid expression...\n");
	return EXIT_FAILURE;
}
