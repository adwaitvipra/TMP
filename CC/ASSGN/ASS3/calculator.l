%{
    #include <math.h>
    #include "y.tab.h"
%}

%% 

[0-9]+|[0-9]*\.[0-9]+ { 
                            yylval.p = atof (yytext);
                            return num;
}

sin {
    return SIN;
}

cos {
    return COS;
}

tan {
    return TAN;
}

ln {
    return LN;
}

sqrt {
    return SQRT;
}

[ \t];
\n  return 0;
.   return yytext[0];

%% 

