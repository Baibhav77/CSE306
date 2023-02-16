#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include<stdbool.h>
#define MAXCHAR 500

char f[] = "-f\0";
char r[] = "-r\0";
char h[] = "-h\0";
char min[] = "-min\0";
char max[] = "-max\0";
char me[] = "-mean\0";
char re[] = "-records\0";

// Display the number of fields in the first record of the file
int dashF(char *filename) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    char row[MAXCHAR];
    char *firstrow = fgets(row, MAXCHAR, fp);
    char *token = strtok(firstrow, ",");
    int iterator = 0;
    while( token != NULL ) {
        iterator ++;
        token = strtok(NULL, ",");
    }
    fclose(fp);
    return iterator;
}

// Display the number of data records in file.
int dashR(char *filename) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    char row[MAXCHAR];
    int count = 1;
    int c;
    fgets(row, MAXCHAR, fp);
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    fclose(fp);
    return count;
}


char *content(char* token, int input) {
    char first_letter;
    char last_letter;

    // state to see if loop should be executed for find quotation mark
    bool sw = false;
    char temp[MAXCHAR] = "\0";
    char *add = &temp;
    // Get first token
    char *token2 = strtok(token, ",");
    first_letter = token2[0]; // checks to see if first letter in the first token has a quotation
    last_letter = token2[strlen(token2) - 1]; // checks to see if the last character in the first token has quotation
    // see if end and begin quotation mark exist
    if ((first_letter == '"') && last_letter != '"') { // checks to see if first and last letter is a quotation
        sw = true; // if first letter does and last doesn't we will look for the last quotation
    }
    strcat(temp, token2);
    for (int n = 1; n < input + 1; n++) {
        temp[0] = '\0';
        token2 = strtok(NULL, ",");
        first_letter = token2[0]; // checks to see if first letter in the first token has a quotation
        last_letter = token2[strlen(token2) - 1]; // checks to see if the last character in the first token has quotation
        // see if end and begin quotation mark exist
        if ((first_letter == '"') && last_letter != '"') { // checks to see if first and last letter is a quotation
            sw = true; // if first letter does and last doesn't we will look for the last quotation
        }
            if (!sw) { // if first and last letter is not a quotation then we can safely traverse with another token using , as a delimiter
                // printf("%s\n", token2);
                first_letter = token2[0];
                last_letter = token2[strlen(token2) - 1];
                // see if end and begin quotation mark exist
                if ((first_letter == '"') && last_letter != '"') { // checks to see if new token has quotation marks
                    sw = true;
                }
                else {
                    strcat(temp, token2);
                }
            }
            // case of end quotation mark doesn't exist
            else {
                // printf("%s\n", temp);
                // loop strtok() until find the end quotation mark
                while (sw == 1) {
                    strcat(temp, token2);
                    token2 = strtok(NULL, ",");
                    strcat(temp, ",");
                    strcat(temp, token2);
                    last_letter = token2[strlen(token2) - 1];
                    // if end quotation mark found, set sw=0 for exiting the loop
                    if (last_letter == '"') {
                    sw = false;
                    }
                }

                // strcpy(token2, temp);
            }
            // printf("Token: %s\n", temp);
    }
    // printf("Token: %s\n", temp);
    // printf("AFTER:%s\n", temp);
    temp[strlen(temp)] = '\0'; 
    return add;
}

// checks if 
bool isNumber(char s[]) {
    for (int i = 0; s[i]!= '\0'; i++) {
        if (isdigit(s[i]) == 0)
              return false;
    }
    return true;
}

// Display the minimum value in the indicated field of the data records. The first field is numbered 0. 
// This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records 
// the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used. 
double dashMin(char *filename, int column, bool isthereH) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    char *row[MAXCHAR];
    int numRow = dashR(filename);
    fgets(row, MAXCHAR, fp);
    if (isthereH) {
        fgets(row, MAXCHAR, fp);
        numRow--;
    }
    else if (!isNumber(content(row, column))) {
        fgets(row, MAXCHAR, fp);
        numRow--;
    }
    float smallest = atof(content(row, column));
    for (int i = 1; i < numRow; i++) {
        fgets(row, MAXCHAR, fp);
        float temp = atof(content(row, column));
        if (temp < smallest) {
            smallest = temp;
        }
    }
    return smallest;
}

// Display the maximum value in the indicated field of the data records. The first field is numbered 0. 
// This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in 
// any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used. 
double dashMax(char *filename, int column, bool isthereH) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    char *row[MAXCHAR];
    int numRow = dashR(filename);
    fgets(row, MAXCHAR, fp);
    if (isthereH) {
        fgets(row, MAXCHAR, fp);
        numRow--;
    }
    else if (!isNumber(content(row, column))) {
        fgets(row, MAXCHAR, fp);
        numRow--;
    }
    double largest = atof(content(row, column));
    for (int i = 1; i < numRow; i++) {
        fgets(row, MAXCHAR, fp);
        double temp = atof(content(row, column));
        if (temp > largest) {
            largest = temp;
        }
    }
    return largest;
}

// Display the arithmetic mean (average) value in the indicated field of the data records. 
// The first field is numbered 0. This option ignores non-numeric data in the indicated field. 
// If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. 
// See how fields are identified when the -h option is used. 
double dashMean(char *filename, int column, bool isthereH) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    char *row[MAXCHAR];
    int numRow = dashR(filename);
    fgets(row, MAXCHAR, fp);
    if (isthereH) {
        fgets(row, MAXCHAR, fp);
        numRow--;
    }
    else if (!isNumber(content(row, column))) {
        fgets(row, MAXCHAR, fp);
        numRow--;
    }
    double first = atof(content(row, column));
    int n = 1;
    for (int i = 1; i < numRow; i++) {;
        fgets(row, MAXCHAR, fp);
        double temp = atof(content(row, column));
        first = first + temp;
        n = n + 1;
    }
    // printf("Total Numbers: %d\n", n);
    double mean = first / n;
    return mean;
}

int printallTokens(char* filename, char* token, int column) {
    int numColumn = dashF(filename);
    for (int i = 0; i < numColumn; i++) {
        if (i != column) {
            printf("%s", content(strdup(token), i)); 
            if (i < numColumn - 2) {
                printf(",");
            }
        }
    }
    printf("\n");

}

// Display the records from file containing value in the the indicated field. The first field is numbered 0. 
// Value is formatted according to the same rules as data in fields. 
// See how fields are identified when the -h option is used. 
int dashRecords(char *filename, int column, double value, bool isthereH) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    char *row[MAXCHAR];
    int numColumn = dashF(filename);
    int numRow = dashR(filename);
    int current = 0;
    fgets(row, MAXCHAR, fp);
    if (isthereH) {
        fgets(row, MAXCHAR, fp);
        current = current + 1;
    }
    else if (!isNumber(content(row, column))) {
        fgets(row, MAXCHAR, fp);
        current = current + 1;
    }
    double first = atof(content(row, column));
    if (first == value) {
        printallTokens(filename, strdup(row), column);
    }
    for ( ; current < numRow; current++) {
        fgets(row, MAXCHAR, fp);
        double temp = atof(content(strdup(row), column));
        if (temp == value) {
            // printf("WE REACHED HERE\n");
            printallTokens(filename, strdup(row), column);
        }
    }
    // printf("Total Numbers: %d\n", n);

    return 0;
}

// Treat the first record of file as a header record rather than a data record. 
// If this option is used then field in the following options must be specified with the title of the corresponding 
// field from the header row (the numeric positional option is not available). If this option is not used then field in 
//the following options must be specified with the the numeric positional option (the title of the corresponding field 
//from the header row is not available). If an incorrect field identifier is used the program exits with error code EXIT_FAILURE. 
int dashH(char *filename, int argc, char* input[]) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No file found\n");
        return 1;
    }
    int column_count = dashF(filename); // Gets number of columns

    char row[MAXCHAR];

    char *column[column_count]; // Stores the labels of each column
    for (int i = 0; i < column_count; i++) {
        column[i] = malloc(MAXCHAR*sizeof(char));
    }
    fgets(row, MAXCHAR, fp);
    char *token = strtok(row, ",");
    int c = 0;

    while (token != NULL) {
        column[c] = token;
        if (c == (column_count - 1)) {
            column[c][strlen(column[c]) - 2] = '\0';
        }
        token = strtok(NULL, ",");
        c++;
    }
    for (int i = 0; i < argc; i++) {

        if (!strcmp(input[i], f)) {
            printf("%d\n", dashF(filename));
        }
        else if (!strcmp(input[i], r)){
            printf("%d\n", dashR(filename));;
        }
        else if (!strcmp(input[i], min)){
            int index;
            for (int j = 0; j < column_count; j++) {
                if (!strcmp(column[j], input[i+1])) {
                    index = j;
                    break;
                }
            }
            printf("%f\n", dashMin(filename, index, true));
        }
        else if (!strcmp(input[i], max)){
            int index;
            for (int j = 0; j < column_count; j++) {
                if (!strcmp(column[j], input[i+1])) {
                    index = j;
                    break;
                }
            }
            printf("%f\n", dashMax(filename, index, true));
        }
        else if (!strcmp(input[i], me)){
            int index;
            for (int j = 0; j < column_count; j++) {
                if (!strcmp(column[j], input[i+1])) {
                    index = j;
                    break;
                }
            }
            printf("%f\n", dashMean(filename, index, true));
        }

        else if (!strcmp(input[i], re)){;
            int index;
            double value = atof(input[i+2]);
            for (int j = 0; j < column_count; j++) {
                if (!strcmp(column[j], input[i+1])) {
                    index = j;
                    break;
                }
            }
            dashRecords(filename, index, value, true);
        }

    }
    return 0;
}


int main(int argc, char* argv[])
{
    char *filename = argv[argc - 1];
    // Parsing command line inputs

    char input[sizeof(argv)] = {"\0"};
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], f)) {
            printf("%d\n", dashF(filename));
            input[0] = '\0';
        }
        else if (!strcmp(argv[i], r)){
            printf("%d\n", dashR(filename));
            input[0] = '\0';
        }
        else if (!strcmp(argv[i], h)) {
            dashH(filename, argc - 2, &argv[i+1]);
            break;
        }
        else if (!strcmp(argv[i], min)) {
            int column = atoi(argv[i+1]);
            printf("%f\n", dashMin(filename, column, false));
        }
        else if (!strcmp(argv[i], max)) {
            int column = atoi(argv[i+1]);
            printf("%f\n", dashMax(filename, column, false));
        }
        else if (!strcmp(argv[i], me)){
            int column = atoi(argv[i+1]);
            printf("%f\n", dashMean(filename, column, false));
        }
        else if (!strcmp(argv[i], re)){
            int column = atoi(argv[i+1]);
            double value = atof(argv[i+2]);
            dashRecords(filename, column, value, false);
        }
        
    }
}
