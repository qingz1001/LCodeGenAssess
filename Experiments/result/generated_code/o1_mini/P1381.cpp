#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 100000
#define MAX_WORD 11

int cmp(const void *a, const void *b){
    return strcmp((const char*)a, (const char*)b);
}

int main(){
    int n;
    scanf("%d", &n);
    char target_words[MAX_N][MAX_WORD];
    for(int i=0;i<n;i++) scanf("%s", target_words[i]);
    qsort(target_words, n, MAX_WORD, cmp);
    int m;
    scanf("%d", &m);
    char article[MAX_M][MAX_WORD];
    for(int i=0;i<m;i++) scanf("%s", article[i]);
    int counts[MAX_N];
    for(int i=0;i<n;i++) counts[i]=0;
    int current_count=0;
    int max_count=0;
    int min_length=0;
    int left=0;
    for(int right=0; right<m; right++){
        char *word = article[right];
        char *found = bsearch(word, target_words, n, MAX_WORD, cmp);
        int idx = -1;
        if(found){
            idx = found - target_words;
            if(counts[idx]==0) current_count++;
            counts[idx]++;
        }
        while(left <= right){
            char *left_word = article[left];
            char *left_found = bsearch(left_word, target_words, n, MAX_WORD, cmp);
            if(left_found){
                int left_idx = left_found - target_words;
                if(counts[left_idx] > 1){
                    counts[left_idx]--;
                    left++;
                }
                else{
                    break;
                }
            }
            else{
                left++;
            }
        }
        if(current_count > max_count){
            max_count = current_count;
            min_length = right - left +1;
        }
        else if(current_count == max_count){
            if(right - left +1 < min_length){
                min_length = right - left +1;
            }
        }
    }
    printf("%d\n%d\n", max_count, min_length);
    return 0;
}