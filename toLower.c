#include <stdio.h>
#include<ctype.h>

int main(void)

 {
     int letter;

     letter = getchar();
    
      while( letter != EOF )
{
      
      putchar(tolower(letter)) ;
       
        letter = getchar();
}
return 0;
}
