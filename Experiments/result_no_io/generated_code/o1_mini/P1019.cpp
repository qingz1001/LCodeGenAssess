#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 20

int max(int a, int b){
    return a > b ? a : b;
}

void dfs(char *suffix, int suffix_len, int current_len, int usage[], int n, char words[][MAX_LEN+1], int word_lens[], int *max_len){
    for(int i=0;i<n;i++){
        if(usage[i] <2){
            int min_k = suffix_len < word_lens[i] ? suffix_len : word_lens[i];
            int k =0;
            for(int m=min_k-1;m>=1;m--){
                if(strncmp(suffix + suffix_len -m, words[i], m) ==0){
                    if(m < suffix_len && m < word_lens[i]){
                        k =m;
                        break;
                    }
                }
            }
            if(k >0){
                int new_len = current_len + word_lens[i] -k;
                if(new_len > *max_len){
                    *max_len = new_len;
                }
                char new_suffix[MAX_LEN+1];
                int new_suffix_len = word_lens[i] -k;
                if(new_suffix_len > MAX_LEN){
                    new_suffix_len = MAX_LEN;
                }
                strncpy(new_suffix, words[i] +k, new_suffix_len);
                new_suffix[new_suffix_len] = '\0';
                usage[i]++;
                dfs(new_suffix, new_suffix_len, new_len, usage, n, words, word_lens, max_len);
                usage[i]--;
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    char words[MAX_N][MAX_LEN+1];
    int word_lens[MAX_N];
    for(int i=0;i<n;i++){
        scanf("%s", words[i]);
        word_lens[i] = strlen(words[i]);
    }
    char c;
    scanf(" %c", &c);
    int max_len =0;
    int usage[MAX_N];
    memset(usage, 0, sizeof(usage));
    for(int i=0;i<n;i++){
        if(words[i][0] == c){
            usage[i] =1;
            if(word_lens[i] > max_len){
                max_len = word_lens[i];
            }
            char suffix[MAX_LEN+1];
            int suffix_len = word_lens[i] < MAX_LEN ? word_lens[i] : MAX_LEN;
            strncpy(suffix, words[i] + word_lens[i] - suffix_len, suffix_len);
            suffix[suffix_len] = '\0';
            dfs(suffix, suffix_len, word_lens[i], usage, n, words, word_lens, &max_len);
            usage[i] =0;
        }
    }
    printf("%d\n", max_len);
    return 0;
}