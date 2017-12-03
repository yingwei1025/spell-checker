//==============================================================================
//=  Author: CHUA YING WEI                                                     =
//=          B150085B                                                          =
//=          yingwei1025@gmail.com                                             =
//=          Operating System Project Spell Checker                            =
//==============================================================================
//----- Include files ----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //for tolower function
#include <stdbool.h>//bool type library
#include <time.h>
#include "trie.h"

//----- Global variables -------------------------------------------------------
FILE *filename;
char line[20];
char word_search[20], loop_answer;
struct TrieNode *root;
struct TrieNode *usedRoot;

//----- Function prototypes ----------------------------------------------------
void searchWord ();
char *toLowerCase (char *str);

//==============================================================================
//=  Main program                                                              =
//==============================================================================
int main (int argc, char **argv)
{ 
  //start counting time
  clock_t begin = clock();
  root = getNode ();
  usedRoot = getNode ();
  //open dictionary
  filename = fopen ("dictionary/dictionary-268000.txt", "r");
  if (filename)
    {
     //reads a line from the stream and stores it into the string pointed
      while (fgets (line, sizeof (line), filename))
    {
      //remove '\n' in line
      strtok (line, "\n");  
      //load dictionary to memory
      insert (root, line);
      
    }
      //close the file
      fclose (filename);
      printf("\n------------------------------------------------------------------------------\n");
      printf ("\nWelcome to the Spell Checker!\n");
      printf ("The Dictionary-268000 has been loaded.\n\n");
      //stop counting time
      clock_t end = clock();
      //calculating time spent
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Dictionary load in: %f seconds\n\n", time_spent);
    }
  else
    {
      printf ("Dictionary file Not Found! \n");
      printf ("Please make sure put \"dictionary txt file\" in the same folder! \n");
      printf ("Press enter to exit...\n");
      //pause 
      getchar ();
      return (1);

    }

//------------------------------------------------------------------------------
//-   do-while loop prompt user algorithm                                           -
//------------------------------------------------------------------------------
  do
    {
      /* Prompt to instruct use to enter the string to be searched */
      printf ("Please enter the word would you like to check:");  
      /* Capture of the search string by the system */  
      scanf ("%s", word_search);   
      clock_t begin2 = clock();
      searchWord (word_search);
      clock_t end2 = clock();
      double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
      printf("\nSearch done in: %f seconds\n", time_spent2);
      printf("\n------------------------------------------------------------------------------\n");
      printf("Would you like to enter another word? \nPress Y to continue or N \nto exit : ");
      //capture for user answer to continue or not
      scanf (" %c", &loop_answer);
      printf("\n------------------------------------------------------------------------------\n");
    }
  while (loop_answer == 'y' || loop_answer == 'Y');
  // print the message if user press n
  if (loop_answer == 'n' || loop_answer == 'N')
      {
        printf ("\nGood Bye, Program Exit\n");
      }

  return (0);
} //end main


//------------------------------------------------------------------------------
//-  Converts a string to lower case                                           -
//------------------------------------------------------------------------------
char *toLowerCase (char *str)
{
  unsigned char *chgstr = (unsigned char *) str;
  while (*chgstr)
    { 
    //change to lower case
      *chgstr = tolower (*chgstr);
      chgstr++;
    }
  return str;
}

//------------------------------------------------------------------------------
//-   Trie search algorithm                                                    -
//------------------------------------------------------------------------------
void searchWord(char *word) {
	//change word to lower case
    word = toLowerCase(word);
    //compare the word
    if (strcmp("\n", word) != 0) {
    	//initialize 
        int check = 0;

        if (check == 0) {
        	//return true if success find the word in dictionary
            if(search(root, word) == true) { 
                printf("Great, \"%s\" is in the dictionary!\n", word);
                //change check to 1 to stop the searching
                check = 1; 
            }
        }
        if (check == 0) {
            printf("\"%s\" is NOT in the dictionary!\n", word);
        }
    }
}