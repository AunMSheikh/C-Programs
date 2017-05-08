//
//  word_checker.h
//  
//
//  Created by Muhammad Aun on 2016-06-30.
//
//

#ifndef word_checker_h
#define word_checker_h
#define MAX_LINE 100
#define file_name "EnglishWords.txt"


int check_input(char *word);

int check_direction(char ** roll,char * sec_word, int row, int col);

int word_check(char ** roll, char * word, int length_word);



#endif /* word_checker_h */
