#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_S1 7000
#define MAX_S2 70000

typedef struct TrieNode {
    struct TrieNode *children[128];
    int is_end;
} TrieNode;

// Function to create a new Trie node
TrieNode* create_node() {
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    node->is_end = 0;
    for(int i=0;i<128;i++) node->children[i] = NULL;
    return node;
}

// Function to insert a word into the Trie
void insert(TrieNode *root, char *word) {
    TrieNode *node = root;
    for(int i=0; word[i] != '\0'; i++) {
        char c = word[i];
        if(node->children[c] == NULL) {
            node->children[c] = create_node();
        }
        node = node->children[c];
    }
    node->is_end = 1;
}

int main(){
    char S1[MAX_S1+2];
    char S2[MAX_S2+2];
    char S2_lower[MAX_S2+2];
    char S1_lower[MAX_S1+2];
    // Read S1
    if(!fgets(S1, sizeof(S1), stdin)) return 0;
    // Remove newline
    int len1 = strlen(S1);
    if(S1[len1-1] == '\n') { S1[len1-1] = '\0'; len1--; }
    // Read S2
    if(!fgets(S2, sizeof(S2), stdin)) return 0;
    // Remove newline
    int len2 = strlen(S2);
    if(S2[len2-1] == '\n') { S2[len2-1] = '\0'; len2--; }
    // Create lowercase copies
    for(int i=0;i<len1;i++) S1_lower[i] = tolower(S1[i]);
    S1_lower[len1] = '\0';
    for(int i=0;i<len2;i++) S2_lower[i] = tolower(S2[i]);
    S2_lower[len2] = '\0';
    // Extract words from S1_lower
    char *words[1000];
    int word_count = 0;
    char current_word[100];
    int cw = 0;
    for(int i=0;i<=len1;i++){
        if(isalpha(S1_lower[i])){
            current_word[cw++] = S1_lower[i];
        }
        else{
            if(cw > 0){
                current_word[cw] = '\0';
                words[word_count++] = strdup(current_word);
                cw = 0;
            }
        }
    }
    // Generate all possible two or more word phrases
    TrieNode *root = create_node();
    for(int i=0;i<word_count;i++){
        char phrase[MAX_S1];
        phrase[0] = '\0';
        for(int j=i; j<word_count; j++){
            if(j == i){
                strcpy(phrase, words[j]);
            }
            else{
                strcat(phrase, " ");
                strcat(phrase, words[j]);
            }
            if(j - i +1 >=2){
                insert(root, phrase);
            }
        }
    }
    // Initialize bold array
    int bold_flag[MAX_S2];
    for(int i=0;i<len2;i++) bold_flag[i] = 0;
    // Traverse S2_lower and mark bold positions
    for(int i=0;i<len2;i++){
        TrieNode *node = root;
        int j = i;
        while(j < len2 && node->children[(int)S2_lower[j]] != NULL){
            node = node->children[(int)S2_lower[j]];
            if(node->is_end){
                for(int k=i; k<=j; k++) bold_flag[k] = 1;
            }
            j++;
        }
    }
    // Output with <b> and </b>
    int in_bold = 0;
    for(int i=0;i<len2;i++){
        if(bold_flag[i] && !in_bold){
            printf("<b>");
            in_bold = 1;
        }
        if(!bold_flag[i] && in_bold){
            printf("</b>");
            in_bold = 0;
        }
        printf("%c", S2[i]);
    }
    if(in_bold){
        printf("</b>");
    }
    printf("\n");
    // Free allocated memory
    for(int i=0;i<word_count;i++) free(words[i]);
    // Function to free Trie
    // Implemented recursively
    // Define a stack-based free to avoid stack overflow for large tries
    typedef struct StackNode {
        TrieNode *node;
        struct StackNode *next;
    } StackNode;
    StackNode *stack = NULL;
    if(root) {
        stack = (StackNode*)malloc(sizeof(StackNode));
        stack->node = root;
        stack->next = NULL;
    }
    while(stack){
        StackNode *current = stack;
        stack = stack->next;
        TrieNode *n = current->node;
        for(int i=0;i<128;i++) {
            if(n->children[i]){
                StackNode *new_node = (StackNode*)malloc(sizeof(StackNode));
                new_node->node = n->children[i];
                new_node->next = stack;
                stack = new_node;
            }
        }
        free(n);
        free(current);
    }
    return 0;
}