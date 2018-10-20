/**
 * Levenshtein.c
 *
 * COMP 2160 SECTION A02
 * ASSIGNMENT    Assignment #1, question #2
 * @author       Ezra Hall, 7763713
 * @version     Oct.10,2018
 *
 * PURPOSE: Convert a java program called levenshtein from java to c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

    int testsFailed = 0;
    int testsExecuted = 0;

    int minimum(int,int,int);
    int endsWith(char*, char*);
    int levenshtein(char*, char*);
    void testDistance(char*, char*, int);

    int main( )
    {
        printf( "Testing typical cases.\n" );
        testDistance( "kitten", "kitten", 0 );
        testDistance( "kitten", "sitting", 3 );
        testDistance( "kitten", "mittens", 2 );
        testDistance( "balloon", "saloon", 2 );
        testDistance( "hello", "doggo", 4 );
        testDistance( "\t\thi", "\t\t\t\thi", 2 );

        printf( "\nTesting empty/edge cases.\n" );
        testDistance( "", "", 0 );
        testDistance( "hello", "", 5 );
        testDistance( "", "doggo", 5 );
        testDistance( "a", "b", 1 );
        testDistance( "b", "b", 0 );
        testDistance( " ", " ", 0 );

        printf( "\nThis might take a while...\n" );
        testDistance( "12345678901", "123456789012", 1 );

        printf( "\nThese tests will not succeed in the C version\n" );
        testDistance( "kitten", "mitten\0s", 3 );           // fail because of the null terminator in the strings
        testDistance( "\0totally", "\0different", 9 );

        printf( "\nTotal number of tests executed: %d", testsExecuted );
        printf( "\nNumber of tests passed: %d", (testsExecuted - testsFailed) );
        printf( "\nNumber of tests failed: %d\n", testsFailed );
    }
    /*int intLength(int* minimum){
      int i = 0;
      while (i != '\0'){
        i++;
      }
      return i;
    }*/
    int minimum( int a, int b, int c )
    {
        int minimum[] = {a,b,c};
        int minimumLength = (int) (sizeof(minimum)/sizeof(minimum[0]));
        int min = 0;
        assert( minimumLength > 0 );

        if ( minimumLength > 0 )
        {
          min = minimum[0];

          for ( int i = 1; i < minimumLength; i++ )
          {
              if ( minimum[i] < min )
              {
                  min = minimum[i];
              }
          }
        }

        return min;
    }
    //finds if a string end with the same value as another
        int endsWith(char* s, char* t){
          int sLength = strlen(s)-1;
          int tLength = strlen(t)-1;
          int i;
          for (i = 0 ; i <= tLength ; i++){
            if (s[sLength-i] != t[tLength-i]) {
              return 0;
            }

          }
          return 1;
        }

        int levenshtein( char* s, char* t )
        {
            int cost;
            int distance;
            char* deleteS = NULL;
            char* deleteT = NULL;

            assert( s != NULL );
            assert( t != NULL );

            if (strlen(s) == 0)
            {
                distance = strlen(t);
            }
            else if (strlen(t) == 0)
            {
                distance = strlen(s);
            }
            else
            {
                if (s[0] == t[0])
                {
                    cost = 0;
                }
                else
                {
                    cost = 1;
                }
                int numberOfChars = 50; // can be any number needed
                deleteT = (char*)calloc(numberOfChars + 1, sizeof(char));
                deleteS = (char*)calloc(numberOfChars + 1, sizeof(char));
                strncpy(deleteS,&s[1],strlen(s)-1);
                strncpy(deleteT,&t[1], strlen(t)-1);

                assert(strlen(deleteS) == strlen(s) - 1);
                assert(strlen(deleteT) == strlen(t) - 1);

                assert(endsWith(s,deleteS));
                assert(endsWith(t,deleteT));

                distance = minimum(levenshtein(deleteS, t) + 1,
                                   levenshtein(s, deleteT) + 1,
                                   levenshtein(deleteS, deleteT) + cost);
            }
            free(deleteS);
            free(deleteT);
            return distance;
        }

    void testDistance( char* s, char* t, int expected )
    {
        int distance = levenshtein( s, t );

        if ( distance == expected )
        {
            printf( "\nPassed! You can get from '%s' to '%s' in %d moves.",s,t,expected );
        }
        else
        {
            printf( "\nFAILED: I thought it would take %d moves, but apparently it takes %d moves to get from '%s' to '%s'.", expected, distance,s,t);
            testsFailed++;
        }

        testsExecuted++;
    }
