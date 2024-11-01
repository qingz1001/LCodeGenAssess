#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOTAL 1001
#define MAX_SENTENCES 5
#define MAX_SENTENCE_LENGTH 1001
#define MAX_WORDS 200
#define MAX_WORD_LENGTH 1001

int is_name(char *word) {
    int len = strlen(word);
    if(len == 0) return 0;
    // Check for ending punctuation
    char last = word[len-1];
    int has_punct = 0;
    if(last == '.' || last == '?' || last == '!') {
        has_punct = 1;
        word[len-1] = '\0';
        len--;
        if(len == 0) return 0;
    }
    // First character must be uppercase
    if(!isupper(word[0])) return 0;
    // Remaining characters must be lowercase letters
    for(int i=1;i<len;i++) {
        if(!islower(word[i])) return 0;
    }
    return 1;
}

int main(){
    int N;
    scanf("%d", &N);
    getchar(); // consume newline after number
    char buffer[MAX_TOTAL];
    fgets(buffer, sizeof(buffer), stdin);
    int len = strlen(buffer);
    if(buffer[len-1] == '\n') buffer[len-1] = '\0';
    
    int counts[MAX_SENTENCES];
    for(int i=0;i<N;i++) counts[i]=0;
    
    int current_sentence =0;
    int start =0;
    for(int i=0;i<=strlen(buffer);i++){
        if(buffer[i]=='.' || buffer[i]=='?' || buffer[i]=='!' || buffer[i]=='\0'){
            // Extract sentence from start to i
            char sentence[MAX_SENTENCE_LENGTH];
            int s_len = i - start;
            strncpy(sentence, buffer + start, s_len);
            sentence[s_len] = '\0';
            // Process words in sentence
            char *token = strtok(sentence, " ");
            while(token != NULL){
                if(is_name(token)){
                    counts[current_sentence]++;
                }
                token = strtok(NULL, " ");
            }
            current_sentence++;
            start = i+1;
            if(current_sentence >= N) break;
        }
    }
    for(int i=0;i<N;i++) printf("%d\n", counts[i]);
    return 0;
}