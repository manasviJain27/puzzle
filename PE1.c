/*
    @author Manasvi Jain
    My solution created for course EECS 2031 at York University. Problem designed by Professor Marzieh Ahmadzadeh.
    
    Like a word search, but with numbers. This code searches a 2D grid left to right, top to bottom, right to left, and bottom to top
    for instances of a given input. Return the number of times the input was found in the grid.
*/

#include <stdio.h>
#include <stdlib.h>

int SIZE; 
void setSize(int size){
    SIZE = size;
}

//Function for printing the 2-d array (the board)
void printBoard(int puzzle[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        printf("{");
        for(int j = 0; j < SIZE; j++){
            printf("[%d] ", puzzle[i][j]);
        }
        printf("}\n");
    }
    printf("\n");
}

/* Task 1: This function returns the number of time that input 'number' was 
found in the left to right direction */
int leftToRight(int puzzle[SIZE][SIZE], int number){
    //Initializing variables
    int count = 0; //variable to hold the number of occurences of the number
    int numDigits = 0; //variable to hold the number of digits in the number
    int k = 0; //counter variable like i and j
    int l = 0; //another counter variable like i and j
    int isPalindrome = 0; //this is a boolean variable that checks if the number passed to us is a palindrome
    int rem = 0; //variable that holds the remainder of the number when we are splitting the number into its individual digits
    int row, coloumn; //row and coloumn of 2-d array respectively

//Code Begins
    /* copying the value of the parameter number into a new variable called num so we can calculate number of digits in the number passed to us without affecting 
    the original value */
    int num = number; 

    //Finding number of digits in the number
    while(num != 0){
        num /= 10;
        numDigits++; //increasing the numDigits variable by 1 each time to find the total number of digits in the number
    }
    
    int revArray[numDigits]; //revArray will hold the reversed number because when we loop through the number and splitting into individual digits the number will be reversed
    int numArray[numDigits]; //numArray will hold the same number passed to us but in its individual digits
    
    //Now dividing the number into individual digits while storing each digit into numArray
    while(number != 0){
        rem = number % 10;
        number /= 10;
        revArray[k] = rem;
        k++;
    }
    
    //Checking if a number is a palindrome
    k = numDigits - 1;
    for(int i = 0; i < numDigits; i++){
        numArray[i] = revArray[k]; //Now we are reversing the number by looping backwards through revArray and storing each value into numArray 
        //while looping forwards through numArray
        k--;
        //This condition compares the digits backwards and forwards, if they are the same then this number is a palindrome and we set isPalindrome to true (1)
        if(numArray[i] == revArray[i]){
            isPalindrome = 1;
        }
        //if this condition is false then we set isPalindrome to false (0)
        else{
            isPalindrome = 0;
        }
    }

    //Counting the number of occurences of number appearing in the board by looping through the 2D array
    for(row = 0; row < SIZE; row++){
        l = 0; //setting index variable to 0
        for(coloumn = 0; coloumn < SIZE; coloumn++){
            //condition that checks if the current position in the array matches a number in numArray if it does the index is increased by 1
            if(puzzle[row][coloumn] == numArray[l]){
                l++;
            }

            //If the condition isn't true then reset the index back to 0
            else if(puzzle[row][coloumn] != numArray[l]){
                l = 0;
            }

            //if the index has reached the maximum then we have found a match and we can increase count by 1.
            if(l == numDigits){
                count++;
                l = 0;
            }
        } 
    }

    //if a number is a palindrome we increase the variable that holds the number of occurences of the number found by 1
    if(isPalindrome == 1){
        count++;
    }

    //returning the number of occurences
    return count;
}

/* Task 2: This function rotates the given puzzle 
90 degree to the left. 
a b      becomes     b   B
A B                  a   A
*/
void rotateLeft(int puzzle[SIZE][SIZE]){
    // add your code here
    int temp = 0;
    int i = 0;
    int j, k;
    //In order to rotate a matrix counter clockwise by 90 degrees we need to:
    //1) Make rows as coloumns and coloumns as rows. Coloumn 1 should be row 1 , coloumn 2 should be row 2, etc. 
    //2) Flip the rows of the matrix. The outermost rows should exchange with each other and the innermost rows should exchange with each other.
    //For example, suppose the SIZE = 4 then row 0 should become row 3 and vice versa, row 1 should become row 2 and vice versa, and etc. 
    
    //1) Make rows as coloumns and vice versa
    for(int i = 0; i < SIZE; i++){
        for(int j = i; j < SIZE; j++){
            temp = puzzle[i][j];
            puzzle[i][j] = puzzle[j][i];
            puzzle[j][i] = temp;
        }
    }

    //2) Flip the rows of the matrix i.e., flip top row with bottom row. 
    while(i < SIZE){
        j = 0;
        k = SIZE - 1;
        while(j < k){
            temp = puzzle[j][i];
            puzzle[j][i] = puzzle[k][i];
            puzzle[k][i] = temp;
            j++;
            k--;
        }
        i++;
    }
}

/* Task 3: This function finds the total occurences of 
the number in the puzzle */
int totalOccurrences(int puzzle[SIZE][SIZE], int number){
    // add your code here. you may want to change the return value.
    int count = 0;
    int value = 0;
    
    for(int i = 0; i < SIZE; i++){
        value = leftToRight(puzzle, number);
        count += value;
        rotateLeft(puzzle);
    }
    
    return count;
}
