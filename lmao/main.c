#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

int count_row(char *filename) {
  FILE *fp = fopen(filename, "r");
  int count = 0;
  for (char i = getc(fp); i != EOF; i = getc(fp))
    if (i == '\n')
      count = count + 1;
  fclose(fp);
  return count;
}
bool number_check(char *str) {

  bool result = true;
  int sta = 0;
  int b = (int)str[5];
  for (int i = 0; str[i] != '\0'; i++) {
    if ((int)str[i] > 39) {
      if (str[i] == '.') {
        if (sta == 0) {
          sta = 1;
        } else {

          result = false;
        }
      } else if (!isdigit(str[i])) {
        result = false;
      }
    }
  }
  return result;
}

int main(int argc, char *argv[]) {

  char f[] = "-f\0";
  char r[] = "-r\0";
  char h[] = "-h\0";
  char ma[] = "-max\0";
  char mi[] = "-min\0";
  char mea[] = "-mean\0";
  char rec[] = "-records\0";

  for (int i = 0; i < argc; i++) {
    FILE *fp = fopen(argv[argc - 1], "r");

    // Error in file opening
    if (!fp) {
      printf("Can't open file\n");
      return 1;
    }
    // printf("argv[%d] is %s\n", i, argv[i]);

    //-f
    if (!strcmp(argv[i], f)) {
      char row[MAXCHAR];
      char *firstrow = fgets(row, MAXCHAR, fp);
      char *token = strtok(firstrow, ",");
      int iterator = 0;
      while (token != NULL) {
        // printf("%s\n", token );
        iterator++;
        token = strtok(NULL, ",");
      }

      printf("%d\n", iterator);

    } //-r
    else if (!strcmp(argv[i], r)) {
      int count = 0;
      int c;
      for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
          count = count + 1;
      printf("%d\n", count);
    } //-h
    else if (!strcmp(argv[i], h)) {

    } // max
    else if (!strcmp(argv[i], ma)) {
      char row[MAXCHAR];
      int input = atoi(argv[i + 1]); // user input field
      char *firstrow = fgets(row, MAXCHAR, fp);
      char *token2 = strtok(firstrow, ",");

      int max = 0;
      int file_row_num = count_row(argv[argc - 1]);
      char first_letter;
      char last_letter;

      // state to see if loop should be executed for find quotation mark
      int sw = 0;

      for (int z = 0; z < file_row_num; z++) {
        firstrow = fgets(firstrow, MAXCHAR, fp);
        for (int n = 0; n < input + 1; n++) {
          if (n == 0) {
            token2 = strtok(firstrow, ",");

            first_letter = token2[0];
            last_letter = token2[strlen(token2) - 1];
            // see if end and begin quotation mark exist
            if ((first_letter == '"') && last_letter != '"') {
              sw = 1;
            }
          } else {
            if (sw == 0) {
              token2 = strtok(NULL, ",");
              first_letter = token2[0];
              last_letter = token2[strlen(token2) - 1];
              // see if end and begin quotation mark exist
              if ((first_letter == '"') && last_letter != '"') {
                sw = 1;
              }
            }
            // case of end quotation mark doesn't exit
            if (sw == 1) {
              // loop strtok() until find the end quotation mark
              while (sw == 1) {
                token2 = strtok(NULL, ",");
                last_letter = token2[strlen(token2) - 1];
                // if end quotaion mark found, set sw=0 for exiting the loop
                if (last_letter == '"') {
                  sw = 0;
                }
              }
            }
          }
        }

        if (!number_check(token2)) {
          printf("No numeric data\n");
          exit(EXIT_FAILURE);
        }

        if (atoi(token2) > max) {
          max = atoi(token2);
        }
      }
      printf("The Max value of %d is %d\n", input, max);
    } // min
    else if (!strcmp(argv[i], mi)) {
      char row[MAXCHAR];
      int input = atoi(argv[i + 1]); // user input field
      char *firstrow = fgets(row, MAXCHAR, fp);
      char *token2 = strtok(firstrow, ",");
      int min = 999999999;
      int file_row_num = count_row(argv[argc - 1]);
      char first_letter;
      char last_letter;

      // state to see if loop should be executed for find quotation mark
      int sw = 0;

      for (int z = 0; z < file_row_num; z++) {
        firstrow = fgets(firstrow, MAXCHAR, fp);
        for (int n = 0; n < input + 1; n++) {
          if (n == 0) {
            token2 = strtok(firstrow, ",");

            first_letter = token2[0];
            last_letter = token2[strlen(token2) - 1];
            // see if end and begin quotation mark exist
            if ((first_letter == '"') && last_letter != '"') {
              sw = 1;
            }
          } else {
            if (sw == 0) {
              token2 = strtok(NULL, ",");
              first_letter = token2[0];
              last_letter = token2[strlen(token2) - 1];
              // see if end and begin quotation mark exist
              if ((first_letter == '"') && last_letter != '"') {
                sw = 1;
              }
            }
            // case of end quotation mark doesn't exit
            if (sw == 1) {
              // loop strtok() until find the end quotation mark
              while (sw == 1) {
                token2 = strtok(NULL, ",");
                last_letter = token2[strlen(token2) - 1];
                // if end quotaion mark found, set sw=0 for exiting the loop
                if (last_letter == '"') {
                  sw = 0;
                }
              }
            }
          }
        }
        if (!number_check(token2)) {
          printf("No numeric data\n");
          exit(EXIT_FAILURE);
        }

        if (atoi(token2) < min) {
          min = atoi(token2);
        }
      }
      printf("The Min value of %d is %d\n", input, min);
    } // mean
    else if (!strcmp(argv[i], mea)) {
      char row[MAXCHAR];
      int input = atoi(argv[i + 1]); // user input field
      char *firstrow = fgets(row, MAXCHAR, fp);
      char *token2 = strtok(firstrow, ",");
      float sum = 0.0;
      int file_row_num = count_row(argv[argc - 1]);
      char first_letter;
      char last_letter;
      float totoal_nu = 0.0;

      // state to see if loop should be executed for find quotation mark
      int sw = 0;

      for (int z = 0; z < file_row_num; z++) {
        firstrow = fgets(firstrow, MAXCHAR, fp);
        for (int n = 0; n < input + 1; n++) {
          if (n == 0) {
            token2 = strtok(firstrow, ",");

            first_letter = token2[0];
            last_letter = token2[strlen(token2) - 1];
            // see if end and begin quotation mark exist
            if ((first_letter == '"') && last_letter != '"') {
              sw = 1;
            }
          } else {
            if (sw == 0) {
              token2 = strtok(NULL, ",");
              first_letter = token2[0];
              last_letter = token2[strlen(token2) - 1];
              // see if end and begin quotation mark exist
              if ((first_letter == '"') && last_letter != '"') {
                sw = 1;
              }
            }
            // case of end quotation mark doesn't exit
            if (sw == 1) {
              // loop strtok() until find the end quotation mark
              while (sw == 1) {
                token2 = strtok(NULL, ",");
                last_letter = token2[strlen(token2) - 1];
                // if end quotaion mark found, set sw=0 for exiting the loop
                if (last_letter == '"') {
                  sw = 0;
                }
              }
            }
          }
        }
        if (!number_check(token2)) {
          printf("No numeric data\n");
          exit(EXIT_FAILURE);
        }
        totoal_nu = totoal_nu + 1.0;
        sum = sum + atof(token2);
      }
      float result = sum / totoal_nu;
      printf("The Mean value of %d is %f\n", input, result);
    }
    // record
    else if (!strcmp(argv[i], rec)) {
      char row[MAXCHAR];
      int input = atoi(argv[i + 1]); // user input field
      char *firstrow = fgets(row, MAXCHAR, fp);

      char *token2 = strtok(firstrow, ",");
      int file_row_num = count_row(argv[argc - 1]);
      char first_letter;
      char last_letter;

      // state to see if loop should be executed for find quotation mark
      int sw = 0;

      for (int z = 0; z < file_row_num; z++) {

        firstrow = fgets(firstrow, MAXCHAR, fp);
        char *cpy_row;
        cpy_row = (char *)malloc(MAXCHAR);
        strcpy(cpy_row, firstrow);

        for (int n = 0; n < input + 1; n++) {
          if (n == 0) {
            token2 = strtok(firstrow, ",");

            first_letter = token2[0];
            last_letter = token2[strlen(token2) - 1];
            // see if end and begin quotation mark exist
            if ((first_letter == '"') && last_letter != '"') {
              sw = 1;
            }
          } else {
            if (sw == 0) {
              token2 = strtok(NULL, ",");
              first_letter = token2[0];
              last_letter = token2[strlen(token2) - 1];
              // see if end and begin quotation mark exist
              if ((first_letter == '"') && last_letter != '"') {
                sw = 1;
              }
            }
            // case of end quotation mark doesn't exit
            if (sw == 1) {
              // loop strtok() until find the end quotation mark
              while (sw == 1) {
                token2 = strtok(NULL, ",");
                last_letter = token2[strlen(token2) - 1];
                // if end quotaion mark found, set sw=0 for exiting the loop
                if (last_letter == '"') {
                  sw = 0;
                }
              }
            }
          }
        }

        if (atof(token2) == atof(argv[i + 2])) {
          printf("%s\n", cpy_row);
        }

        //////
      }
    }
    fclose(fp);
  }

  return 0;
}
