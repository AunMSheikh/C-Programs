#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define largest_word_length 47


void word_count(){
    
}




//function to create subarrays and send them to individual children of a pipe based on the arguement -n

void create_subarray(char *filename[], int processes, int num_of_files){
    //creating a master array to keep track of different word lengths and their frequencies
    int* word_list;
    int i, j;
    FILE *fp;
    char buf[1024];
    int length;
    
    word_list = malloc(largest_word_length * sizeof(int));
    
    for (i = 0; i < largest_word_length; i++){
        word_list[i] = 0;
    }
    
    
    // if the number of processes is 0 or 1 we get the parent do the entire word count
    if (processes < 2) {
        
        for (j = 0; j < num_of_files; j++){
            
            fp = fopen(filename[j], "r");
            
            //error checking for file opening
            
            if (fp == NULL){
                perror("Error");
                exit(1);
            }
            
            //reading word at a time, assuming the word is not longer than 1023
            
            while (fgets(buf, 1023, fp)){
                
                //tokenizing the word and then taking its length to update the list
                char * pch;
                char delimiter[] = " ,.-!?\"|':;+";
                
                pch = strtok (buf,delimiter);
                while (pch != NULL) {
                     //now updating the list
                    length = strlen(pch);
                    word_list[length] = word_list[length] + length;
                    pch = strtok (NULL,delimiter);
                    
                    
                }
                
            }
            
        }
        
    }
    
    else {
        //creating sub arrays
        
        
        //creating child processes
        int     fd[2], nbytes;
        pid_t   childpid;
        char    readbuffer[1024];
        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }
        
        if(childpid == 0)
        {
            close(fd[0]);
            
            write(fd[1], *filename, (strlen(*filename)+1));
            exit(0);
        }
        else
        {
            close(fd[1]);
            
           
            nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
            
        }
    }
    
    //printing the array
    
    for (i = 0; i < largest_word_length; i++){
        printf("%d, %d\n", i, word_list[i]);
    }
    
    //freeing memory space allocated due to malloc
    free(word_list);

    
}




int main(int argc, char **argv){
       //setting up get-opt to take up user input
    
    extern char *optarg;
    extern int optind;
    int ch;
    //FILE *infp; //*outfp;
    
    char *infile = NULL;
    char *outfile = NULL;
    int num_of_process = 0;
    int d = 0;
 
    //reading in the arguements
    //Three arguements: -d<input file dir>, -n<number of processes>, and -o<output file name>
    // -d is required and -n and -o are optional
    
    while((ch = getopt(argc, argv, "d:n:o:")) != -1){
        
        switch(ch){
            case 'd':
                infile = optarg;
                d = 1;
                break;
                
            case 'n':
                num_of_process = atoi(optarg);
                break;
                
            case 'o':
                outfile = optarg;
                break;
                
            default:
                fprintf(stderr, "Usage: phist -d <inputfile>, [-n <number of process>], [-o <outputfile>]\n");
                exit(1);
        }
    }

   // Code to check if -d arguement was provided since its required
    
    
    
    if (d == 0){
        fprintf(stderr,"Usage: phist -d inputfile, [-n number of process], [-o outputfile]\n" );
        exit(1);
    }

    
    DIR *di;
    struct dirent *dir;
    int count = 0;
    int index = 0;
    int i = 0;
    char *filenames[310];
    
    //opening the directory
    di = opendir (infile);
   
    //error checking
    
    if (di == NULL) {
        perror ("Cannot open ");
        exit (1);
    }
    
    while ((dir = readdir(di)) != NULL) {
        //making sure only the files with .txt extensions are read
        const size_t len = strlen(dir->d_name);
        if (len > 4 && dir->d_name[len - 4] == '.' && dir->d_name[len - 3] == 't' && dir->d_name[len - 2] == 'x' && dir->d_name[len - 1] == 't'){
            
            filenames[i] = malloc(strlen(dir->d_name) + 1);
            strcpy(filenames[i], dir->d_name);
            count++;
            i++;
        }
        
    }
    create_subarray(filenames, num_of_process, count);
    
    closedir (di);
    
    
   
    
    
    // cleaning up the memory allocated by malloc
    while(index > 0) {
        free(filenames[i]);
        i++;
        index--;
    }


	return 0;	

}
