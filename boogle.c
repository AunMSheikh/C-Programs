#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "word_checker.h"
#include "dictionary.h"

#define MAX_LINE 100
#define file_name "EnglishWords.txt"


// 2D array of the dice
char dice[16][7] = {
	{'R','I','F','O','B','X'},
	{'I','E','F','H','E','Y'},
	{'D','E','N','O','W','S'},
	{'U','T','O','K','N','D'},
	{'H','M','S','R','A','O'},
	{'L','U','P','E','T','S'},
	{'A','C','I','T','O','A'},
	{'Y','L','G','K','U','E'},
	{'Q','B','M','J','O','A'},
	{'E','H','I','S','P','N'},
	{'V','E','T','I','G','N'},
	{'B','A','L','I','Y','T'},
	{'E','Z','A','V','N','D'},
	{'R','A','L','E','S','C'},
	{'U','W','I','L','R','G'},
	{'P','A','C','E','M','D'}
};


int main(int argc, char ** argv ) {

	int i,n,j, k;
	char word[30] = "1";
	extern int check_input(char *word);
    int word_length;
	
	//randomly generating number between 0 and 5 to mimic a roll of a dice for all 16 dice	
    srand( time(NULL));
    char roll[4][4];
    
    k = 0;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            n = rand() % 6;
            roll[i][j] = dice[k][n];
            k++;
        }
    }

	
	while(strcmp(word,"q") != 0 && strcmp(word,"n") != 0){
		/* printing the 4 by 4 grid */
        
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                printf("%c\t", roll[i][j]);
            }
            printf("\n");
        }
        word_length = strlen(word);
        
        if(word_check(roll, word, word_length) != 0){
            if(check_input(word) != 0){
                printf("valid\n");
            }
        }
		
		printf("next word:\n");
		scanf("%s", word);
		system("clear");
	}
        //return_score_card();	
	return 0;
}

