#include <stdio.h>
#include <stdlib.h>

//function declarations
int valid_chars_count (char *input, int size);
int valid_char (char c);
int expected (int c, int g);

int main (int argc, char *argv[]) {
	char * inputfile_name=argv[1]; 
	FILE * input_fp;
	char *input_buffer; //stores all bytes in the input file
	char *sequence; //char array holding the final cleaned DNA sequence
		
	int *valid_cpg_positions; //array of all positions in sequence
	int input_len, seq_len;
		
	int i, j;
	int r;

	//open the file
	if ( !(input_fp= fopen ( inputfile_name , "rb" )) ) {

		return (-1);
	}

	//compute total number of characters in the input file
	fseek (input_fp, 0, SEEK_END);
	input_len=ftell (input_fp);
	rewind (input_fp); 
		
	//allocate an array to hold these characters
	input_buffer = (char*) malloc (input_len+1);
		
	//read file content into the input buffer
	r = fread (input_buffer, 1, input_len,  input_fp);

	if (r != input_len) {
		printf("Reading error \n");
		return (-1);
	}
	//add terminating character
	input_buffer [input_len] ='\0';

	//determine total number of valid DNA characters
	//and allocate array of chars to hold them
	seq_len = valid_chars_count (input_buffer, input_len);

	sequence = (char*) malloc (seq_len+1); 
		
	//transfer valid characters from raw buffer
	for (i=0, j=0; i < input_len; i++) {
		if (valid_char (input_buffer [i])) {
			sequence [j++] = input_buffer [i];
		}
	}
	sequence [seq_len] = '\0';
		
	//allocate int array for all the positions
	valid_cpg_positions = (int*) malloc (seq_len*sizeof(int));
	for (i=0; i<seq_len; i++)
		valid_cpg_positions[i] = 0;
			
	/* YOUR CpG ISLANDS DISCOVERY CODE HERE */
	// While and for loops to loop through the array for the window of 200 characters
	// the sequence is the array that holds the DNA sequence and seq_line is the total number of nucleotides
	int start = 0;
	int window = 200; 
	int index;
	int ind;
 
	while (start + window <= seq_len){
		int count_c = 0;
		int count_g = 0;
		int count_cg = 0;
		for(index = start; index <= window; index++){
			if (sequence[index] == 'c') {
				count_c += 1;
			}
			else if (sequence[index] == 'g') {
				count_g += 1;
			}
			else if (sequence[index] == 'c' && sequence[index] == 'g'){
				count_cg += 1;
			}

		}
		if ((count_c + count_g) / 200 >= 0.5) {
			int e_value = expected (count_c, count_g);
			if ((e_value / count_cg) >= 0.6){
				for (ind = start; ind <= window; ind++){
					if(sequence[ind] == 'c' || sequence[ind] == 'g'){
						valid_cpg_positions[ind] = 1;
					}
				}
			}	
			
		}
		start += 1;
		window += 1;

	}
	
	int s = 0;
	int original = s;
	while(s != seq_len){
		int size = 0;
		if (valid_cpg_positions[s] == 1){
			size += 1;
			s++;
		}
		else{
			size = 0;
			s++;
			original = s;

		}	
		if ( size >= 200){
			printf("CpG island\t %d..%d\t size=%d", original, s, size);
		}
	}
		
	return 0;
}

int valid_chars_count (char *input, int size) {
	int i, count = 0;
	for (i=0; i<size; i++) {
		if (valid_char (input [i]) )
			count++;
	}
	return count;
}

int valid_char (char c) {
	if (c == 'a' || c == 'c' || c == 'g' || c == 't' ) 
		return 1;
	return 0;
}


int expected (int c, int g) {

	int ev = (c * g) / 200;
	
	return ev;
}



