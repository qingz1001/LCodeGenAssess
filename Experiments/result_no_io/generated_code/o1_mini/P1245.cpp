#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_S 101
#define MAX_WORD_LEN 21

typedef struct {
    char word[MAX_WORD_LEN];
    char digits[21];
} Word;

int main(){
    int N;
    scanf("%d", &N);
    
    char S[MAX_S];
    scanf("%s", S);
    int S_len = strlen(S);
    
    Word words[MAX_N];
    
    // Mapping letters to digits
    char mapping[26];
    memset(mapping, '0', sizeof(mapping));
    // 1: a,b,c
    mapping['a'-'a'] = '1';
    mapping['b'-'a'] = '1';
    mapping['c'-'a'] = '1';
    //2: d,e,f
    mapping['d'-'a'] = '2';
    mapping['e'-'a'] = '2';
    mapping['f'-'a'] = '2';
    //3: g,h,i
    mapping['g'-'a'] = '3';
    mapping['h'-'a'] = '3';
    mapping['i'-'a'] = '3';
    //4: j,k,l
    mapping['j'-'a'] = '4';
    mapping['k'-'a'] = '4';
    mapping['l'-'a'] = '4';
    //5: m,n
    mapping['m'-'a'] = '5';
    mapping['n'-'a'] = '5';
    //6: o,p,q
    mapping['o'-'a'] = '6';
    mapping['p'-'a'] = '6';
    mapping['q'-'a'] = '6';
    //7: r,s,t
    mapping['r'-'a'] = '7';
    mapping['s'-'a'] = '7';
    mapping['t'-'a'] = '7';
    //8: u,v,w
    mapping['u'-'a'] = '8';
    mapping['v'-'a'] = '8';
    mapping['w'-'a'] = '8';
    //9: x,y,z
    mapping['x'-'a'] = '9';
    mapping['y'-'a'] = '9';
    mapping['z'-'a'] = '9';
    
    // Read words and convert to digit strings
    for(int i=0;i<N;i++){
        scanf("%s", words[i].word);
        int w_len = strlen(words[i].word);
        for(int j=0;j<w_len && j < 20;j++){
            char c = words[i].word[j];
            if(c >= 'a' && c <= 'z'){
                words[i].digits[j] = mapping[c - 'a'];
            }
            else{
                words[i].digits[j] = '0';
            }
        }
        words[i].digits[w_len] = '\0';
    }
    
    // DP array
    int dp[MAX_S];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    
    // To store which word was used to reach position i
    int prev[MAX_S];
    int word_idx[MAX_S];
    for(int i=1;i<=S_len;i++) {
        prev[i] = -1;
        word_idx[i] = -1;
    }
    
    for(int i=0;i<S_len;i++) {
        if(dp[i]){
            for(int w=0;w<N;w++){
                int w_len = strlen(words[w].digits);
                if(i + w_len <= S_len){
                    if(strncmp(&S[i], words[w].digits, w_len) == 0){
                        if(!dp[i + w_len]){
                            dp[i + w_len] = 1;
                            prev[i + w_len] = i;
                            word_idx[i + w_len] = w;
                        }
                    }
                }
            }
        }
    }
    
    if(!dp[S_len]){
        printf("No Solutions!");
        return 0;
    }
    
    // Reconstruct the path
    char result[MAX_S * 21];
    result[0] = '\0';
    int pos = S_len;
    char stack[MAX_S][21];
    int top = 0;
    while(pos > 0){
        int w = word_idx[pos];
        if(w == -1){
            break;
        }
        strcpy(stack[top++], words[w].word);
        pos = prev[pos];
    }
    // Combine words in reverse order
    result[0] = '\0';
    for(int i=top-1;i>=0;i--){
        strcat(result, stack[i]);
    }
    printf("%s", result);
    return 0;
}