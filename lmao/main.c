#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include<stdbool.h>
#define MAXCHAR 1000

int dashF(FILE *fp) {
    // Display the number of fields in the first record of the file
    char row[MAXCHAR];
    char *firstrow = fgets(row, MAXCHAR, fp);
    char *token = strtok(firstrow, ",");
    int iterator = 0;
    while( token != NULL ) {
        iterator ++;
        token = strtok(NULL, ",");
    }
    return iterator;
}

int dashR(FILE *fp) {
    // Display the number of data records in file.
    char row[MAXCHAR];
    int count = 1;
    int c;
    fgets(row, MAXCHAR, fp);
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    return count;
}

int dashH(FILE* fp, int argc, char* input[]) {
    // Treat the first record of file as a header record rather than a data record. 
    // If this option is used then field in the following options must be specified with the title of the corresponding 
    // field from the header row (the numeric positional option is not available). If this option is not used then field in 
    //the following options must be specified with the the numeric positional option (the title of the corresponding field 
    //from the header row is not available). If an incorrect field identifier is used the program exits with error code EXIT_FAILURE. 
        for (int i = 1; i < argc; i++) {


    return 0;
}


int main(int argc, char* argv[])
{
    char f[] = "-f\0";
    char r[] = "-r\0";
    char h[] = "-h\0";
    // Opening file
    char *filename = argv[argc - 1];

    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    // Parsing command line inputs

    char input[sizeof(argv)] = {"\0"};

    for (int i = 1; i < argc; i++) {
        if (!strcmp(input, f)) {
            printf("%d\n", dashF(fp));
            input[0] = '\0';
        }
        else if (!strcmp(input, r)){
            printf("%d\n", dashR(fp));
            input[0] = '\0';
        }
        else if (!strcmp(input, h)) {
            dashH(fp, argc, argv);
        }
    }







//     //-h
//     // read and discard the header line
//     printf("%s\n", row);
//     fgets((char *) MAXCHAR, MAXCHAR, fp);
//     printf("%s\n", row);

//     // if not used then dont discard




//     const char delimiter[] = ",";

//     //char *token = my_strtok(row, delimiter);
//     char *words[]={};
//     words[0]="haha";
//     words[1]="lol";
//     words[0]="adibro";
//     char *newwords[]={};
//     newwords[0]=words[0];
//     //printf(newwords[0]);
//     //token = my_strtok(NULL, delimiter);
//     //token = my_strtok(NULL, delimiter);
//     //printf("%s\n", token);


// //    while (feof(fp) != true)
// //    {
// //
// //        printf("Row: %s", row);
// //    }


//     fclose(fp);
//     return 0;
}
