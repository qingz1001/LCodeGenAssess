#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100000
#define MAX_NAME_LENGTH 20

typedef struct {
    char input[MAX_NAME_LENGTH];
    char output[MAX_NAME_LENGTH];
    int number;
} FileInfo;

int compare(const void *a, const void *b) {
    return ((FileInfo*)a)->number - ((FileInfo*)b)->number;
}

int extractNumber(char *filename) {
    int len = strlen(filename);
    int i = len - 1;
    while (i >= 0 && (filename[i] < '0' || filename[i] > '9')) i--;
    int end = i;
    while (i >= 0 && filename[i] >= '0' && filename[i] <= '9') i--;
    return atoi(filename + i + 1);
}

int main() {
    char input_format[MAX_NAME_LENGTH], output_format[MAX_NAME_LENGTH];
    int start_number = -1;
    FileInfo files[MAX_FILES];
    int file_count = 0;

    if (scanf("%s", input_format) == 1) {
        if (input_format[0] >= '0' && input_format[0] <= '9') {
            start_number = atoi(input_format);
        } else {
            scanf("%s", output_format);
        }
    }

    while (scanf("%s %s", files[file_count].input, files[file_count].output) == 2) {
        files[file_count].number = extractNumber(files[file_count].input);
        file_count++;
    }

    qsort(files, file_count, sizeof(FileInfo), compare);

    for (int i = 0; i < file_count; i++) {
        char new_input[MAX_NAME_LENGTH], new_output[MAX_NAME_LENGTH];
        
        if (start_number != -1) {
            sprintf(new_input, "%.*s%d.%s", 
                    (int)(strchr(files[i].input, '.') - files[i].input),
                    files[i].input, start_number + i,
                    strchr(files[i].input, '.') + 1);
            sprintf(new_output, "%.*s%d.%s", 
                    (int)(strchr(files[i].output, '.') - files[i].output),
                    files[i].output, start_number + i,
                    strchr(files[i].output, '.') + 1);
        } else {
            sprintf(new_input, input_format, i);
            sprintf(new_output, output_format, i);
        }
        
        printf("%s %s\n", new_input, new_output);
    }

    return 0;
}