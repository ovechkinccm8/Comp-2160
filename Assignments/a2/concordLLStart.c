/**
 * CocncordLLStart.c
 *
 * COMP 2160 SECTION A02
 * ASSIGNMENT    Assignment #2, question #1
 * @author       Ezra Hall, 7763713
 * @version     Oct.25,2018
 *
 * PURPOSE: take standard input of some text an make a concordance while using the
 * propeties of design by contract. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
// used for user interaction can be commneted out along with the sleep function
//used later
#include <unistd.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

typedef enum BOOL { false, true } Boolean;

typedef struct NODE Node;
struct NODE{
  char *item;
  Node *next;
};



//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
Node *head = NULL;
Node *current = NULL;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// add an element to the beginning of the linked list
Boolean insert( char *new_string );
// empty the list so that we clear all memory and can start a fresh list
void clearList();
// tells us whether or not the given string is in the list
Boolean search( char *target );
// starts a list traversal by getting the data at top
char * firstItem();
// increment the traversal and gets the data at the current traversal node
char * nextItem();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
void validate_string(char *my_string)
{
  //assert the string isnt NULL its length is greater than 0
  //and it has a null terminator as its last charecter
	assert( my_string != NULL );
	assert( strlen(my_string) >= 0 );
	assert( my_string[strlen(my_string)] == '\0' );
}
// read from standard input, tokenize and insert words into a linked list
// note that we must ensure that there are no duplicates in our list
void loadFile()
{
#define LINE_SIZE 256
  char input[LINE_SIZE];
  char *token = NULL;
  //make sure file isnt empty
  assert(!feof(stdin));
  while ( fgets( input, LINE_SIZE, stdin ) )
  //check the file isnt empty
  {
    // parse the data into separate elements
    token = strtok( input, " \t\n" );

    while ( token )
    {
      validate_string(token);
      if ( !search( token ) )
        insert( token );

      token = strtok( NULL, " \t\n" );
    }
  }
}

// print the contents of the linked list to standard output
void printConcordance()
{
  //if the head is NULL there will be no firstItem to print
  assert(head != NULL);
  if (head != NULL){
    //make sure current is set to head so all values are printed
    assert(current == head);
    current = head;
    char *theWord = firstItem();

    while ( theWord )
    {
      validate_string(theWord);
      printf( "%s\n", theWord );
      theWord = nextItem();
    }
  } else {
    printf("%s\n", "Concordance is empty");
  }

}
Boolean search(char *key) {

   //start from the first link
   validate_string(key);
   current = head;
   assert(current == head);

   //if list is empty
   if(head == NULL) {
      return false;
   }

   //navigate through list
   while(strcmp(current->item, key) != 0) {
      validate_string(current->item);
      //if it is last node
      if(current->next == NULL) {
         return false;
      } else {
         //go to next link
         current = current->next;

      }
   }
   //if data found, return the current Link
   //make sure that the value is in the list before returning true
   assert(strcmp(current->item, key)==0);
   return true;
}
char * firstItem(){
  assert(head != NULL);
  if (head != NULL){
    validate_string(head->item);
    return head->item;
  } else {
    printf("%s\n", "Error No Items In Linked List");
    return NULL;
  }
}
char * nextItem(){
  assert(current!=NULL);
  if(current->next !=NULL){
    current = current->next;
    validate_string(current->item);
    return current->item;
  } else {
    return NULL;
  }
}
Boolean insert (char *new_string){
  //make assertions its a valid string
  validate_string(new_string);
  Node *new_Node;
  new_Node = malloc(sizeof(Node));
  //assert malloc works
  assert(new_Node != NULL);
  // insert fails if malloc doesnt work
  if (new_Node == NULL) {
    printf("Error inserting  %s failed in insert\n" , new_string);
    return false;
  }
  new_Node->item = malloc(sizeof(char)* strlen(new_string)+1);
  //assert malloc works
  assert(new_Node->item != NULL);
  strcpy(new_Node->item, new_string);
  //assert that the strcpy works
  assert(strcmp(new_Node->item, new_string) == 0);
  new_Node->next = head;
  head = new_Node;
  current = new_Node;
  // assert that the head contains the string to be added
  validate_string(head->item);
  assert(strcmp(head->item, new_string)==0);
  return true;
}
void clearList(){
  Node *previous;
  //cant clear an empty list
  assert(head != NULL);
  while(head != NULL){
    previous = head;
    head = head->next;
    free(previous->item);
    free(previous);
  }
  assert(head == NULL);
}
int main( int argc, char *argv[] )
{
  // the following lines are just for user friendliness and crete user insructions
  // this mostly is to deal witht the case there is no redirection and is for
  //stdin
  //if thse lines are ran the output will be slightly longer than the output.txt file
  //given in the assignment because of the instructions.
  //{
  //printf("If a file is redirected to be used as standard input \nconcordance will be printed. Otherwise Type words to concord \nand then press (Enter followed by cntrl+d) to end\n");
  //  sleep(4);
  //}
  loadFile();
  printConcordance();
  clearList();

  return EXIT_SUCCESS;
}
