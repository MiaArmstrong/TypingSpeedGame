//Homework 1 - Typing Speed Game
//By: Mia Armstrong for CS201
//Filename: typing_word_game.c
/*This program is a typing speed game. The user is prompted to type a random word out of nine words in a sentence. The user is timed. If the user fails to type the word correctly, the user is prompted to try again. Once the user has typed all the words in the sentence correctly the timer stops and the time the user took to complete the task is displayed. */


#include <stdio.h>
#include <stdlib.h> //required to use 'rand()' and 'srand()'
#include <sys/time.h>
#include <time.h> //required to use 'gettimeofday()'
#include <string.h>


//function declarations
void play(void); //manages the game
int rand_num(int total); //generates a random number
double time_diff(struct timeval time_start, struct timeval time_end); //gets the time it took to play the game
int again(); //asks user if they want to play again

int main()
{

   struct timeval tv;
   do
   { 
      gettimeofday(&tv, NULL); //get the time is usecs to use as the seed for srand.
      srand(tv.tv_usec); // for randomization      

      play();
   }while(again()==1); //play the game again till the user wants to quit.

   return 0;
}

//This function manages the game. 
void play(void)
{

   int total = 8;
   int index = 0;
   int i = 0;
   int max = 0;
   char str[10];
   //create an array of strings
   char words[9][6] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
   //create an array of numbers
   int nums[9] = {0,1,2,3,4,5,6,7,8};

   printf("\n\nWelcome to the Typing Speed Game!!\nType these words as fast as you can!");

   printf("\nReady??\nPress ENTER to start.");
   getchar();
 
   struct timeval before, after; 
   gettimeofday(&before, NULL);  //get the time at the start of the game
 
   while (total > 0)  //randomize the array of integers by swapping the last for a random number within the array, this is repeated for all the numbers.
   {
      index = rand_num(total);
    
      max = nums[total];
      nums[total] = nums[index];  //shuffle the two numbers
      nums[index] = max;
      --total; //decriment the total to leave the numbers that have been shuffled alone.
   }
   
   for (i = 0; i < 9; ++i) //Print the word that corresponds to the number in the array. User must match the word exactly to proceed to the next.
   {
     do
      {
         printf("\nWord #%d is %s: ",i+1, words[nums[i]]); //print the word 
         scanf("%9s", str);  //input a word from the user
         if (strcmp(str,words[nums[i]]) !=0)  
            printf("Incorrect. Try again.\n");  //if not a match, try again
      }while(strcmp(str, words[nums[i]]) != 0); 
    
   }
   gettimeofday(&after, NULL);  //get the time at the end of the game

   //Calculate the difference between the start and end time, then print it along with the time calculated in seconds.
   printf("\n\nCorrect!  Your time is: %.0lf sec, %.0lf usec\n" ,(time_diff(before, after) * 1.0e-6), time_diff(before, after));

   
}   

//This function takes in a number, total.
//Returns a random number between 0 and total.
int rand_num(int total)
{

   int num;
   num = rand()%total; //generate a number between 0 and the total 
   return num;
}

//Takes two times in microseconds as arguments and returns the difference in microseconds.
double time_diff(struct timeval time_start, struct timeval time_end)
{
   double time_start_ms, time_end_ms, time_diff;

   time_start_ms = (double)time_start.tv_sec*1000000 + (double)time_start.tv_usec;
   time_end_ms = (double)time_end.tv_sec*1000000 + (double)time_end.tv_usec;

   time_diff = (double)time_end_ms - (double)time_start_ms;

   return time_diff;
}

//Promps the user to play again. Returns true for yes and falser for no.
int again()
{
   char reply;
   printf("Would you like to play again (y/n)?");
   scanf(" %c%*c", &reply);
   if (reply == 'y' || reply == 'Y')
      return 1;
   else
      return 0;
}
