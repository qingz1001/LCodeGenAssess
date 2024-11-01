#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_S1_LEN 7000
#define MAX_S2_LEN 7000
#define MAX_WORDS 10000
#define MAX_TOKEN_LEN 20

typedef struct {
    char word[140]; // Up to 20 tokens, each up to 7 chars, plus spaces
} Word;

Word wordList[MAX_WORDS];
int wordCount = 0;

// Function to check if a token is pinyin (all lowercase letters)
int is_pinyin(char *token) {
    for(int i = 0; token[i]; i++) {
        if (!islower(token[i]))
            return 0;
    }
    return 1;
}

// Function to add a word to the wordList
void add_word(char *tokens[], int start, int end) {
    if (end - start +1 < 2) return; // Only words with two or more tokens
    // Check all tokens are pinyin
    for(int i = start; i <= end; i++) {
        if (!is_pinyin(tokens[i])) return;
    }
    // Concatenate tokens with space
    char buffer[140] = "";
    for(int i = start; i <= end; i++) {
        strcat(buffer, tokens[i]);
        if(i != end) strcat(buffer, " ");
    }
    // Add to wordList
    strcpy(wordList[wordCount].word, buffer);
    wordCount++;
}

// Function to check if a word exists in wordList
int word_exists(char *word) {
    for(int i = 0; i < wordCount; i++) {
        if(strcmp(wordList[i].word, word) == 0)
            return 1;
    }
    return 0;
}

int main(){
    char S1[MAX_S1_LEN];
    char S2[MAX_S2_LEN];
    // Read S1
    if(!fgets(S1, sizeof(S1), stdin)) return 0;
    S1[strcspn(S1, "\n")] = 0;
    // Read S2
    if(!fgets(S2, sizeof(S2), stdin)) return 0;
    S2[strcspn(S2, "\n")] = 0;

    // Tokenize S1
    char *tokens1[1000];
    int n1 = 0;
    char *token = strtok(S1, " ");
    while(token){
        tokens1[n1++] = token;
        token = strtok(NULL, " ");
    }
    // Generate all possible words from S1
    for(int i = 0; i < n1; i++){
        for(int j = i+1; j < n1; j++){
            add_word(tokens1, i, j);
        }
    }

    // Tokenize S2 and keep track of original string positions
    char *tokens2[2000];
    int n2 = 0;
    char copyS2[MAX_S2_LEN];
    strcpy(copyS2, S2);
    token = strtok(copyS2, " ");
    while(token){
        tokens2[n2++] = token;
        token = strtok(NULL, " ");
    }

    // Reconstruct S2 into char array with spaces
    char S2_reconstructed[MAX_S2_LEN * 8];
    S2_reconstructed[0] = '\0';
    for(int i = 0; i < n2; i++){
        strcat(S2_reconstructed, tokens2[i]);
        if(i != n2-1) strcat(S2_reconstructed, " ");
    }
    int len_S2 = strlen(S2_reconstructed);
    // Initialize bold array
    int bold[len_S2];
    for(int i = 0; i < len_S2; i++) bold[i] = 0;

    // Create an array of token positions
    int token_start[2000];
    int pos = 0;
    for(int i = 0; i < n2; i++){
        token_start[i] = pos;
        pos += strlen(tokens2[i]);
        if(i != n2-1) { bold[pos] = -1; pos +=1; } // space as -1
    }

    // Iterate over all possible words and mark bold positions
    for(int i = 0; i < n2; i++){
        for(int j = i+1; j < n2; j++){
            // Extract word from i to j
            int total_len = 0;
            for(int k = i; k <= j; k++) total_len += strlen(tokens2[k]) + (k != j ? 1 : 0);
            if(total_len >= 2){
                char current_word[140] = "";
                for(int k = i; k <= j; k++){
                    strcat(current_word, tokens2[k]);
                    if(k != j) strcat(current_word, " ");
                }
                if(word_exists(current_word)){
                    // Mark bold
                    int start = token_start[i];
                    int end = token_start[j] + strlen(tokens2[j]);
                    for(int p = start; p < end; p++) bold[p] = 1;
                }
            }
        }
    }

    // Build the final string with <b> tags
    char result[MAX_S2_LEN * 2];
    int idx = 0;
    int in_bold = 0;
    for(int i = 0; i < len_S2; i++){
        if(bold[i] == 1 && !in_bold){
            strcat(result, "<b>");
            in_bold = 1;
        }
        if(bold[i] != 1 && in_bold){
            strcat(result, "</b>");
            in_bold = 0;
        }
        // Append current character if it's not a space marked as -1
        if(bold[i] != -1){
            strncat(result, &S2_reconstructed[i], 1);
        }
    }
    if(in_bold){
        strcat(result, "</b>");
    }
    printf("%s\n", result);
    return 0;
}