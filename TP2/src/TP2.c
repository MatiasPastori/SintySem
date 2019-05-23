/*
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//123 + 15 * 2
//009 + 0 + (9 * 1)
//15*2+110
//15    +    1    *   (2   )
struct Node
{
   char c;
   struct Node *sig;
};

struct Node *Pila = NULL;
//Posiblemente para ser usada en la evaluacion o podria usarse la pila
struct Node *Calculo = NULL;

void push(char c)
{
   struct Node * nuevo = (struct Node*)malloc(sizeof(struct Node));
   nuevo->sig = NULL;
   nuevo->c = c;
   if( Pila==NULL )
   {
      Pila = nuevo;
   }
   else
   {
      struct Node* aux = Pila;
      Pila = nuevo;
      Pila->sig = aux;
   }

}
char pop()
{
   char x = Pila->c;
   struct Node* aux = Pila->sig;
   free(Pila);
   Pila = aux;
   return x;

}
//descarta todas la expresiones que no tengan parentesis completos
//ejemplo ()() (()) )()(  ))((  true no descarta expresion
//()) ())) ((((  )))) false si descarta la expresion
bool parentesisPar(char s[])
{
   int i = 0;
   int cont1 = 0;
   int cont2 = 0;
   while( s[i]!='\0' )
   {
      if( s[i]=='(' )
      {
         cont1++;
      }
      if( s[i]==')' )
      {
         cont2++;
      }
      i++;
   }
   return cont1==cont2;
}
//elimina los espacios de la expresion
void eliminarEspacios(char s[])
{
//4 37  8
   int i = 0;
   while( s[i]!='\0' )
   {
      if( s[i]==' ' )
      {
         while( s[i]!='\0' )
         {
            s[i] = s[i+1];
            i++;
         }
         i = 0;

      }
      i++;
   }
}

//derivacion
//Exp -> Ter | Exp + Ter
//Ter -> Fac | Ter * Fac
//Fac -> Num | (Exp)
//Num -> Dig Num | Dig
//Dig -> 0|1|2|3|4|5|6|7|8|9

//E1 -> T1 E2
//E2 -> + T1 E2 | &
//T1 -> F1 T2
//T2 -> * F1 T2 | &
//F1 -> (E1) | NUM
//NUM -> DIG NUM | DIG
//DIG -> 0|1|2|3|4|5|6|7|8|9

//Reemplazo
//E -> T e
//e -> + T e | &
//T -> F t
//t -> * F t | &
//F -> (E) | N
//N -> D N | N
//D -> 0|1|2|3|4|5|6|7|8|9

bool esExpresion(char s[])
{
   bool esExp = true;
   int i = 0;
   int cont1 = 0;
   push('E');
   pop();
   push('e');
   push('T');
   pop();
   push('t');
   push('F');
   char x;
   if( !parentesisPar(s) )
   {
      esExp = false;
      return esExp;
   }

   do
   {
      x = pop();
      switch(x)
      {
      case 'E':
         push('e');
         push('T');
         break;

      case 'e':
         if( s[i]=='+' )
         {
            push('e');
            push('T');
            i++;
         }
         break;

      case 'T':
         push('t');
         push('F');
         break;

      case 't':
         if( s[i]=='*' )
         {
            push('t');
            push('F');
            i++;
         }
         break;
      case 'F':
         if( s[i]=='(' )
         {
            push('E');
            i++;
            cont1++;
         }
         else
         {
            if( s[i]>='0'&&s[i]<='9' )
            {
               push('N');
            }
            else
            {
               esExp = false;
               return esExp;
            }
         }
         break;
      case 'N':
         if( s[i]>='0'&&s[i]<='9'&&s[i+1]>='0'&&s[i+1]<='9' )
         {
            push('N');
            push('D');
         }
         else
         {
            push('D');
         }
         break;
      case 'D':
         i++;
         while( s[i]==')' )
         {
            if( cont1>0 )
            {
               cont1--;
               i++;
            }
            else
            {
               esExp = false;
               return esExp;
            }

         }
         if( s[i]=='(' )
         {
            esExp = false;
            return esExp;
         }

         break;
      default:
         break;
      }

   }
   while( Pila!=NULL );

   return esExp;
}

//Evaluacion no esta hecha

//int length(char c[])
//{
//   int i = 0;
//   while( c[i]!='\0' )
//   {
//      i++;
//   }
//   return i;
//}
//
//int charToInt(char ch)
//{
//   return ch-'0';
//}

//(2)  (2+4)*3 23+24 12*3 ((3)) (3)+() evaluacion
//void calcularExpresion(char s[])
//{
//   int i = length(s)-1;
//   int cont = 0;
//   char x;
//
//   //2*4+(3+23)
//   while( s[i]!='\0' )
//   {
//
//      if( s[i]==')' )
//      {
//         cont++;
//         push(s[i]);
//         i--;
//      }
//      else
//      {
//         if( s[i]=='(' )
//         {
//            push(s[i]);
//            cont--;
//
//         }
//         else
//         {
//            if( s[i]=='+'||s[i]=='*' )
//            {
//               push(s[i]);
//            }
//            else
//            {
//               push(s[i]);
//               push('D');
//
//            }
//         }
//
//      }
//   }
//}

int main(void)
{
   printf("Escribe la expresion: \n");
   char cadena[100];

   gets(cadena);
   eliminarEspacios(cadena);
   bool x = esExpresion(cadena);
   if( x )
   {
      printf("La expresion %s es correcta",cadena);
   }
   else
   {
      printf("La expresion %s es incorrecta",cadena);
   }

   return 0;
}
