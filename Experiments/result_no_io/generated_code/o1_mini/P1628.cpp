#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 101

int cmp(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

int main(){
    int N;
    scanf("%d", &N);
    
    char **words = (char **)malloc(N * sizeof(char *));
    for(int i = 0; i < N; i++){
        words[i] = (char *)malloc(MAX_WORD_LEN * sizeof(char));
        scanf("%s", words[i]);
    }
    
    char T[MAX_WORD_LEN];
    scanf("%s", T);
    int T_len = strlen(T);
    
    char **matched = (char **)malloc(N * sizeof(char *));
    int count = 0;
    for(int i = 0; i < N; i++){
        if(strncmp(words[i], T, T_len) == 0){
            matched[count++] = words[i];
        }
    }
    
    qsort(matched, count, sizeof(char *), cmp);
    
    for(int i = 0; i < count; i++){
        printf("%s\n", matched[i]);
    }
    
    // Free allocated memory
    for(int i = 0; i < N; i++){
        free(words[i]);
    }
    free(words);
    free(matched);
    
    return 0;
}