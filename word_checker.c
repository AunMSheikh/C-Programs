#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "word_checker.h"
#include "dictionary.h"


int check_input(char *word){
    
    //opening and populating the dictionary
    FILE *input_FP;
    char line[MAX_LINE];
    DNode* result;
    static DNode* big_dictionary [BIG_HASH_SIZE];
    static DNode* small_dictionary [SMALL_HASH_SIZE];
    int i;
    
    //converting the word into lower case to avoid case sensitivity
    
    for (i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
    
    if(!(input_FP = fopen(file_name, "r"))) {
        fprintf(stderr, "Could not open file \"%s\" for reading dictionary words\n", file_name);
        return 1;
    }
    
    // the word is checked against a hash table to see if the word is even a real word
    
    while( fgets (line, MAX_LINE, input_FP) != NULL){
        line[strcspn(line, "\r\n")] = '\0';
        insert (big_dictionary, BIG_HASH_SIZE, line);
    }
    fclose (input_FP);
    
    result = lookup (big_dictionary, BIG_HASH_SIZE, word);
    if (result != NULL){
        
        fprintf(stderr,"%s is in the dictionary\n", word);
        // Now we check to see if this word has been previously submitted during this session
        
        result = lookup (small_dictionary, SMALL_HASH_SIZE, word);
        
        if (result == NULL)
            insert(small_dictionary,SMALL_HASH_SIZE, word);
        else
            fprintf(stderr,"%s has already been using in this session", word);
        
    }
    else {
        fprintf(stderr,"%s is not in the dictionary\n", word);
        
    }
    
    free_dictionary(small_dictionary, SMALL_HASH_SIZE);
    
    free_dictionary(big_dictionary, BIG_HASH_SIZE);
    
    
    
    return 0;
    
    
}

int check_direction(char ** roll, char * sec_word, int row, int col){
    
    int check = 0;
    
    if (row  == 0){
        // coordinates  are 00 has 3 options right, down and diagonal
        if (col == 0){
            if (strcmp(roll[row][col +1], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0 || strcmp(roll[row + 1][col + 1], sec_word) == 0){
                check = 1;
            }
            
        }
        else if (col == 1 || col == 2){
            //right or the left
            if (strcmp(roll[row][col + 1],sec_word) == 0 || strcmp(roll[row][col - 1], sec_word) == 0){
                check = 1;
            }
            //2 diagonals and down
            else if(strcmp(roll[row + 1][col - 1], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0 || strcmp(roll[row + 1][col + 1], sec_word) == 0){
                check = 1;
            }
            
        }
        
        else {
            // col = 3 and it has left, diagonal and down option
            if (strcmp(roll[row][col - 1], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0 || strcmp(roll[row + 1][col - 1], sec_word) == 0){
                check = 1;
            }
            
        }
    }
    
    
    else if (row == 1){
        // up, down and right and 2 diagonals
        if (col = 0){
            // up, down and right
            if (strcmp(roll[row -1][col], sec_word) == 0 || strcmp(roll[row][col + 1], sec_word) == 0 || strcmp(roll[row+1][col], sec_word) == 0){
                check == 1;
            }
            //diagonal
            else if (strcmp(roll[row - 1][col + 1], sec_word) == 0 || strcmp(roll[row + 1][col + 1], sec_word) == 0){
                check == 1;
            }
            
            
        }
        // up, down, right, left and 4 diagonals
        else if (col == 1 || col == 2){
            //up, down, right and left
            if (strcmp(roll[row][col - 1], sec_word) == 0 || strcmp(roll[row][col + 1], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0 || strcmp(roll[row -1][col], sec_word) == 0){
                check = 1;
            }
            //splitting diagonals below to keep code clean
            // up diagonals
            else if (strcmp(roll[row - 1][col - 1], sec_word) == 0 || strcmp(roll[row - 1][col + 1], sec_word) == 0) {
                check = 1;
            }
            //down diagonals
            else if (strcmp(roll[row + 1][col - 1], sec_word) == 0 || strcmp(roll[row + 1][col +1], sec_word) == 0){
                check = 1;
            }
            
        }
        //col 3 has up, down, left and 2 diagonals
        else {
            //up, down and left
            if (strcmp(roll[row][col - 1], sec_word) == 0 || strcmp(roll[row - 1][col], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0){
                check = 1;
            }
            // 2 diagonals
            else if (strcmp(roll[row - 1][col - 1], sec_word) == 0 || strcmp(roll[row + 1][col - 1], sec_word) == 0){
                check = 1;
            }
        }
    }
    
    
    else if (row  == 2){
        // up, down, right and 2 diagonals
        if (col == 0){
            if (strcmp(roll[row - 1][col], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0 || strcmp(roll[row][col + 1], sec_word) == 0){
                check = 1;
            }
            //2 diagonals
            else if (strcmp(roll[row - 1][col + 1], sec_word) == 0 || strcmp(roll[row + 1][col + 1], sec_word) == 0){
                check = 1;
            }
        }
        // up, down, left, right and 4 diagonals
        else if (col == 1 || col == 2){
            //up, down, right and left
            if (strcmp(roll[row][col - 1], sec_word) == 0 || strcmp(roll[row][col + 1], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0 || strcmp(roll[row -1][col], sec_word) == 0){
                check = 1;
            }
            //splitting diagonals below to keep code clean
            // up diagonals
            else if (strcmp(roll[row - 1][col - 1], sec_word) == 0 || strcmp(roll[row - 1][col + 1], sec_word) == 0) {
                check = 1;
            }
            //down diagonals
            else if (strcmp(roll[row + 1][col - 1], sec_word) == 0 || strcmp(roll[row + 1][col +1], sec_word) == 0){
                check = 1;
            }
        }
        
        else {
            //up, down and left
            if (strcmp(roll[row][col - 1], sec_word) == 0 || strcmp(roll[row - 1][col], sec_word) == 0 || strcmp(roll[row + 1][col], sec_word) == 0){
                check = 1;
            }
            //2 diagonals
            else if (strcmp(roll[row - 1][col - 1], sec_word) == 0 || strcmp(roll[row + 1][col - 1], sec_word) == 0){
                check = 1;
            }
        }
    }
    
    // row 3
    else {
        // up, right and diagonal
        if (col == 0){
            if (strcmp(roll[row - 1][col], sec_word) == 0 || strcmp(roll[row][col + 1], sec_word) == 0 || strcmp(roll[row - 1][col + 1], sec_word) == 0){
                check = 1;
            }
            
        }
        // up, right, left, and 2 diagonals
        else if (col == 1 || col == 2){
            //up, right and left
            if (strcmp(roll[row - 1][col], sec_word) == 0 || strcmp(roll[row][col - 1], sec_word) == 0 || strcmp(roll[row][col + 1], sec_word) == 0){
                check = 1;
            }
            //2 diagonals
            else if (strcmp(roll[row - 1][col - 1], sec_word) == 0 || strcmp(roll[row + 1][col + 1], sec_word) == 0){
                check = 1;
            }
        }
        // col 3 has up, left and diagonal
        else {
            if (strcmp(roll[row][col - 1], sec_word) == 0 || strcmp(roll[row - 1][col], sec_word) == 0 || strcmp(roll[row - 1][col - 1], sec_word) == 0){
                check = 1;
            }
            
        }
    }
    
    return check;
    
}



int word_check(char ** roll, char * word, int length_word) {
    
    int row, col;
    int check = 0;
    int i, j;
    int valid = 0;
    char *char2 = word + 1;
    
    
    //setting up recursion cases
    //Case 1:
    
    if (length_word == 1){
        
        //check to see if that word is on the board
        
        for (i = 0; i < 4; i++){
            for (j = 0; j < 4; j++){
                if (strcmp(roll[i][j], *word)){
                    valid = 1;
                }
            }
        }
        
    }
    else {
        for (row = 0; row < 4; row++){
            for (col = 0; col < 4; col++){
                if (strcmp(&(roll[row][col]), &(word[0])) == 0){
                    check = check_direction(roll, &char2, row, col);
                    if (check != 0)
                        break;
                    else
                        continue;
                }
                
            }
        }
    }
    
    if (check != 0) {
        char *new_word;
        int new_length = length_word - 1;
        new_word = &(word[1]);
        
        valid = word_check(&roll, &new_word, new_length);
    }
    
    
    
    return valid;

}