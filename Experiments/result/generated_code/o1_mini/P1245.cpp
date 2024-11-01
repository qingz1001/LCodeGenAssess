#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_N 100
#define MAX_WORD_LEN 20
#define MAX_DIGIT_LEN 100
#define MAX_DIGIT_MAP_LEN (MAX_WORD_LEN + 1)
#define MAX_SOLUTION_WORDS 100

char digit_map[26];
char S[MAX_DIGIT_LEN + 1];
int N;
char words[MAX_N][MAX_WORD_LEN + 1];
char word_digits[MAX_N][MAX_DIGIT_MAP_LEN];
int found = 0;
char solution[MAX_SOLUTION_WORDS][MAX_WORD_LEN + 1];
int sol_count = 0;

void initialize_digit_map(){
    // Initialize the mapping as per the problem statement
    // 1: a, b, c
    // 2: d, e, f
    // 3: g, h, i
    // 4: j, k, l
    // 5: m, n
    // 6: o, p, q
    // 7: r, s, t
    // 8: u, v, w
    // 9: x, y, z
    memset(digit_map, '0', sizeof(digit_map));
    char *groups[] = {"abc","def","ghi","jkl","mn","opq","rst","uvw","xyz"};
    for(int i=0;i<9;i++){
        for(int j=0; groups[i][j] != '\0'; j++){
            digit_map[groups[i][j]-'a'] = '1' + i;
        }
    }
}

int compute_word_digits(int idx){
    int len = strlen(words[idx]);
    for(int i=0;i<len;i++){
        if(!islower(words[idx][i])){
            return 0;
        }
        word_digits[idx][i] = digit_map[words[idx][i]-'a'];
        if(word_digits[idx][i] == '0') return 0;
    }
    word_digits[idx][len] = '\0';
    return 1;
}

int match(int pos, int word_idx){
    int len = strlen(word_digits[word_idx]);
    if(pos + len > strlen(S)) return 0;
    return strncmp(&S[pos], word_digits[word_idx], len) == 0;
}

int dfs(int pos){
    if(found) return 0;
    if(S[pos] == '\0'){
        found = 1;
        return 1;
    }
    for(int i=0;i<N;i++){
        int wd_len = strlen(word_digits[i]);
        if(match(pos, i)){
            strcpy(solution[sol_count], words[i]);
            sol_count++;
            if(dfs(pos + wd_len)){
                return 1;
            }
            sol_count--;
        }
    }
    return 0;
}

int main(){
    initialize_digit_map();
    if(scanf("%d", &N)!=1) return 0;
    if(N <1 || N > MAX_N) return 0;
    if(scanf("%s", S)!=1) return 0;
    for(int i=0;i<N;i++){
        if(scanf("%s", words[i])!=1) return 0;
        compute_word_digits(i);
    }
    dfs(0);
    if(found){
        for(int i=0;i<sol_count;i++){
            if(i>0) printf(" ");
            printf("%s", solution[i]);
        }
        printf("\n");
    }
    else{
        printf("No Solutions!\n");
    }
    return 0;
}