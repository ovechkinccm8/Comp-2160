/**
 * Power.c
 *
 * COMP 2160 SECTION A02
 * ASSIGNMENT    Assignment #1, question #1
 * @author       Ezra Hall, 7763713
 * @version     Oct.10,2018
 *
 * PURPOSE: Convert a java program called power from java to c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count;
float power2(float , int);
float power1(float , int);


  int main(void ) {
       float base[] = { 1.4, 1.3, 1.2, 1.1 };
        int   index []= { 5, 20, 63, 73 };
        float value;

         printf( "\nTest two algorithms for powering\n" );
          for( int i=0 ; i < 4 ; i++ ){
             count = 0;
             value = power1(base[i] , index[i] );
              printf("1:  %f^%d = %f, used %d multiplies\n", base[i],index[i],value,count);
               count = 0;
              value = power2( base[i], index[i] );
              printf("2:  %f^%d = %f, used %d multiplies\n", base[i],index[i],value,count);
              printf("\n");
    }

    printf( "\nEnd of processing\n" );
            }

            float power2( float base, int index ){
                float retValue;
                float temp;
                if( index == 0 ){
                  retValue = 1;
                } else if( index%2 == 1 ){
                  retValue = base * power2( base, index-1 );
                  count++;
                } else {
                  temp = power2( base, index/2 );
                  retValue = temp*temp;
                  count++;
                }
                return retValue;
            }
            float power1( float base, int index ) {
                float retValue;

                if( index == 0 ){
                  retValue = 1;
                } else {
                retValue = base * power1( base, index-1 );
                count++;
                }
                return retValue;
            }
