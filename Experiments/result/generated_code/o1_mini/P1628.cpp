#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b){
    return strcmp(*(char**)a, *(char**)b);
}

int main(){
    int N;
    scanf("%d", &N);
    char** words = malloc(N * sizeof(char*));
    for(int i=0; i<N; i++){
        words[i] = malloc(101 * sizeof(char));
        scanf("%s", words[i]);
    }
    char T[101];
    scanf("%s", T);
    int len_T = strlen(T);
    char** results = malloc(N * sizeof(char*));
    int count = 0;
    for(int i=0; i<N; i++){
        if(strncmp(words[i], T, len_T) == 0){
            results[count++] = words[i];
        }
    }
    qsort(results, count, sizeof(char*), cmp);
    for(int i=0; i<count; i++) printf("%s\n", results[i]);
    for(int i=0; i<N; i++) free(words[i]);
    free(words);
    free(results);
    return 0;
}