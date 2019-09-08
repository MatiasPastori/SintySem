%{

#include <math.h>
#include <stdio.h>
int acum = 0;

%}

CEDECIMAL 	[1-9][0-9]*
CEOCTAL		0[0-7]*
CEHEXA		0[xX][A-Fa-f0-9]+
CREAL	    [0-9]*"."[0-9]+([eE]([\+\-]?)[0-9]+)?[FfLlDd]?|[0-9]+"."([eE][\+\-]?[0-9]+)?[FfLlDd]?|[0-9]+([eE][\+\-]?[0-9]+)[FfLlDd]?
ID       	[a-zA-Z_][a-zA-Z0-9_]*
PRESERVADA	while|do|if|else|for|int|char|return|case|switch
COMENTARIOS "//".*\n|"/*"(.|\n)*"*/"
LITERALCADENA \"([^\"]|"\"")*\"

%%

{CEDECIMAL}   {acum = acum + atoi(yytext); printf("El valor acumulado es %d\n", acum);}
{CEOCTAL}     {printf("La cadena %s representa una constante entera octal\n", yytext);}
{CEHEXA}      {printf("La cadena %s representa una constante entera hexadecimal\n", yytext);}
{CREAL}       {printf("La cadena %s representa una constante real\n", yytext);
               int dec = octToDec(yytext);
               printf("Y su forma decimal entera es : %d \n",dec);}
{PRESERVADA}  {printf("La cadena %s representa una palabra reservada\n", yytext);}
{ID}          {printf("La cadena %s representa un identificador\n", yytext);}
{COMENTARIOS} {printf("La cadena %s representa un comentario\n", yytext);} 
{LITERALCADENA} {printf("La cadena %s representa un literal cadena\n", yytext);} 
[ \t\n]+          /* se come los espacios en blanco */

%%

int octToDec(char oct[]){
    int i=0,dec=0;
    for(i,oct[i]!='\0',i++);
    for(j=0,oct[j]!='\0',j++){
        dec += oct[j] * pow(10,i);
        i--;
    }
    return dec;
}

int main(){
    yyout = fopen("salida.txt","w");
    yyin = fopen("entrada.txt","r");
    yylex();
    return 0;
    }
