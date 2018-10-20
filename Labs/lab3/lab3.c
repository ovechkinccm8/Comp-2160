#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct STRING
{
	unsigned int length;
	char *content;
} string;
string make_string(char *);
void destroy_string(string);
void split(string, string arr[]);

int main(){
  FILE *f = fopen("template.txt", "r");
  FILE *g = fopen("data.txt", "r");
  #define LINE_WIDTH 80
  char line[LINE_WIDTH];
  char line2[LINE_WIDTH];
  string arr[9];
  //int k = 0;
  //string data[30];
  if (g != NULL){


     while (fgets(line2, LINE_WIDTH, g) != NULL) {


    // printf("%s\n",line2 );
     string dataNow = make_string(line2);
     split(dataNow, arr);

  //fgets(line2, LINE_WIDTH, g);
  //printf("%s\n", line2);
  //string string2 = make_string("Public|Jane|Q|Ms.|600|Maple Street|Your Town|Iowa|12345");
  //string arr[9];
//  split(string2, arr);
  //string data[] = {make_string("the"),make_string("dog"),make_string("is"),make_string("is"),make_string("is"),make_string("is"),make_string("is")};
  if (f != NULL)
  {
  //  printf("The file is: %p\n", f);
    while( fgets(line, LINE_WIDTH, f) != NULL )
    {
      printf("\n" );
      int i = 0;
      char c = line[i];
      while(c != '\n'){
      if (c == '$') {
        c = line[i+1];
        //printf("%c\n", c);
        int data_value = c - '0';
      //  printf("%d\n",data_value );
        printf("%s",arr[data_value].content );
        i+=2;
        c = line[i];
      }else{
      printf("%c", line[i]);
        i++;
        c = line[i];
      }
    }
    }

  }
  else
  {
    printf("That file doesn't exist.\n");
    return 1;
  }

  printf("\n" );
  rewind(f);
}
fclose(f);
}
  return 0;
}
string make_string(char *orig)
{
	string new_string;
	new_string.content = malloc(sizeof(char) * strlen(orig));
	strcpy(new_string.content, orig);
	new_string.length = strlen(orig);
	return new_string;
}

void destroy_string(string my_string)
{
	free(my_string.content);
}
void split(string my_string, string arr[])
{
	char *orig = my_string.content;
	int count = 0;
	char *word = strtok(orig, "|");

	while ( word != NULL )
	{
		arr[count] = make_string( word );
		count++;
		word = strtok( NULL, "|" );

	}
}
