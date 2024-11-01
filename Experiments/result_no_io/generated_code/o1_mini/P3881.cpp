#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_S 20
#define MAX_LEN 400
#define INITIAL_CAPACITY 100000

// Comparator for qsort
int cmpstr(const void *a, const void *b){
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(){
    int n;
    char S[MAX_S][21];
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%s", S[i]);

    // Initialize current level with empty string
    char **current = malloc(sizeof(char*) * 1);
    current[0] = strdup("");
    int current_size = 1;

    while(1){
        // Prepare next level
        // Maximum possible next strings: current_size * n
        int next_capacity = current_size * n;
        char **next = malloc(sizeof(char*) * next_capacity);
        int next_count = 0;

        for(int i=0;i<current_size;i++){
            for(int j=0;j<n;j++){
                int len1 = strlen(current[i]);
                int len2 = strlen(S[j]);
                if(len1 + len2 > MAX_LEN) continue;
                char temp[MAX_LEN+1];
                strcpy(temp, current[i]);
                strcat(temp, S[j]);
                next[next_count++] = strdup(temp);
            }
        }

        // Free current level
        for(int i=0;i<current_size;i++) free(current[i]);
        free(current);

        // Sort next level
        qsort(next, next_count, sizeof(char*), cmpstr);

        // Traverse sorted next and find duplicates
        int found = 0;
        char result[MAX_LEN+1];
        for(int i=0;i<next_count;){
            int j = i + 1;
            while(j < next_count && strcmp(next[i], next[j]) == 0) j++;
            if(j - i >=2){
                if(!found || strcmp(next[i], result) < 0){
                    strcpy(result, next[i]);
                    found = 1;
                }
            }
            i = j;
        }

        if(found){
            printf("%lu\n%s\n", strlen(result), result);
            // Free all allocated memory before exiting
            for(int i=0;i<next_count;i++) free(next[i]);
            free(next);
            return 0;
        }

        // Remove duplicates for next level
        char **unique = malloc(sizeof(char*) * next_count);
        int unique_size = 0;
        for(int i=0;i<next_count;){
            int j = i + 1;
            while(j < next_count && strcmp(next[i], next[j]) == 0) j++;
            unique[unique_size++] = strdup(next[i]);
            i = j;
        }

        // Free all next strings
        for(int i=0;i<next_count;i++) free(next[i]);
        free(next);

        // Set current to unique
        current = unique;
        current_size = unique_size;
    }

    return 0;
}