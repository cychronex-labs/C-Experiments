#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void){
    // Opening a file
    FILE * file = fopen("test.hds", "r");
    // fopen returns NULL if any error happened
    if (file == NULL){
        printf("You fucked up, Try again.");
        // Exit with error
        return 1;
    }
    // Move the cursor 0 bytes *from* the END
    if (fseek(file, 0, SEEK_END) != 0){
        printf("OS even fucked up seek. Just shut down.");
        return 1;
    };
    // Tell me the size of everything until the cursor (Which is at the end)
    long size = ftell(file);
    // Unlike fopen, ftell returns -1 as Long on error
    if (size == -1L){
        printf("OS couldn't read bytes, Useless trash.");
        return 1;
    }
    // before reading the file again we shouldnt forget to put cursor back at starting point
    rewind(file);
    // Allocating a memory enough to hold the exact file contents with +1 extra
    // +1 bytes is for the '\0' character which is a terminator that tells C the string as ended
    // without the terminator the string never terminates causing C to read even after when the string is supposed to finish
    char * buffer = malloc(size+1);
    // Maybe memory is full? if OS failed to allocate required memory it returns NULL
    if (buffer == NULL){
        printf("OS is rude so be a good guy and leave the place.");
        return 1;
    }
    // Read everything in the file into buffer string
    fread(buffer, 1, size, file);
    // The terminator we talked about
    buffer[size] = '\0';
    // Close file, NO memory leaks!
    fclose(file);
    // Tokenize the buffer with newline [Now the line is pointer pointing to the first section before \n]
    char *line = strtok(buffer,"\n");
    char *variables[256] = {};
    char *values[256] = {};
    int i=0;
    // if the \n was end of the contents and no more line exists strtok returns NULL
    while (i<256 && line != NULL) {
        // Gives the pointer to ':' character in the line
        char * seperator_ptr = strchr(line, ':');
        // if it exists
        if(seperator_ptr != NULL){
            // like we terminated the buffer we do the same but this time we do it by replacing the colon
            // so C thinks they are different strings and so the first string before the \0 is variable

            *seperator_ptr = '\0';
            char * variable = line;
            // and when we do ptr+1 then it means its now pointing whats after \0 meaning the value
            char * value = seperator_ptr +1;
            variables[i] = variable;
            values[i] = value;
            printf("%s equals %s\n",variable,value);
        }
        // strtok when passed NULL it knows it is the buffer we are talking about and it returns the continuing line
        line = strtok(NULL,"\n");
        i++;
    };
    // free anything that uses malloc to prevent memory leaks!
    free(buffer);
    return 0;
}
