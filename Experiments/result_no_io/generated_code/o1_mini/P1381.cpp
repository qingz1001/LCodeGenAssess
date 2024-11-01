#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_string(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

int main(){
    int n;
    scanf("%d", &n);
    char (*mem_words)[11] = malloc(n * sizeof(*mem_words));
    for(int i=0;i<n;i++) {
        scanf("%s", mem_words[i]);
    }
    qsort(mem_words, n, sizeof(*mem_words), cmp_string);
    int m;
    scanf("%d", &m);
    int *word_indices = malloc(m * sizeof(int));
    char buffer[11];
    for(int i=0;i<m;i++) {
        scanf("%s", buffer);
        char *found = bsearch(buffer, mem_words, n, sizeof(*mem_words), cmp_string);
        if(found) {
            word_indices[i] = found - mem_words;
        }
        else {
            word_indices[i] = -1;
        }
    }
    int *count = calloc(n, sizeof(int));
    int max_unique = 0;
    int min_length = m +1;
    int current_unique = 0;
    int start =0;
    for(int end=0; end<m; end++) {
        if(word_indices[end] != -1){
            if(count[word_indices[end]] ==0){
                current_unique++;
            }
            count[word_indices[end]]++;
        }
        while(start <= end){
            if(word_indices[start] == -1){
                start++;
            }
            else if(word_indices[start] != -1 && count[word_indices[start]] >1){
                count[word_indices[start]]--;
                start++;
            }
            else {
                break;
            }
        }
        int window_length = end - start +1;
        if(current_unique > max_unique){
            max_unique = current_unique;
            min_length = window_length;
        }
        else if(current_unique == max_unique && window_length < min_length){
            min_length = window_length;
        }
    }
    printf("%d\n%d\n", max_unique, min_length);
    free(mem_words);
    free(word_indices);
    free(count);
    return 0;
}