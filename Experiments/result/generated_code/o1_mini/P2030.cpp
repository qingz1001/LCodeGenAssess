#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie Node Definition
typedef struct TrieNode {
    struct TrieNode* children[256];
    int isEnd;
} TrieNode;

// Initialize a Trie Node
TrieNode* createTrieNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEnd = 0;
    for(int i=0;i<256;i++) node->children[i] = NULL;
    return node;
}

// Insert a string into the trie
void insertTrie(TrieNode* root, char* s) {
    TrieNode* current = root;
    for(int i=0; s[i]; i++) {
        unsigned char c = s[i];
        if(!current->children[c]) {
            current->children[c] = createTrieNode();
        }
        current = current->children[c];
    }
    current->isEnd = 1;
}

// Search for a prefix in the trie
int searchTrie(TrieNode* root, char* s) {
    TrieNode* current = root;
    for(int i=0; s[i]; i++) {
        unsigned char c = s[i];
        if(!current->children[c]) return 0;
        current = current->children[c];
    }
    return 1;
}

// Add two numeric strings. a and b are strings with digits in reverse order.
char* addStrings(char* a, char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;
    char* res = (char*)malloc(max_len + 2); // +1 for possible carry, +1 for '\0'
    int carry = 0, i;
    for(i=0;i<max_len;i++) {
        int digit_a = i < len_a ? a[i] - '0' : 0;
        int digit_b = i < len_b ? b[i] - '0' : 0;
        int total = digit_a + digit_b + carry;
        res[i] = (total % 10) + '0';
        carry = total / 10;
    }
    if(carry) {
        res[i++] = carry + '0';
    }
    res[i] = '\0';
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Part 1: Trie for prefixes
    TrieNode* root = createTrieNode();
    char buffer[256];
    for(int i=0;i<n;i++) {
        scanf("%s", buffer);
        // Insert all prefixes of buffer into trie
        for(int j=1; buffer[j-1]; j++) {
            buffer[j] = buffer[j-1];
            buffer[j] = '\0';
            // But data guarantees unique prefixes, so we can just insert the whole string
        }
        insertTrie(root, buffer);
    }
    
    // Read all names and insert into trie
    rewind(stdin);
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) {
        scanf("%s", buffer);
        insertTrie(root, buffer);
    }
    
    int count =0;
    for(int i=0;i<m;i++) {
        scanf("%s", buffer);
        if(searchTrie(root, buffer)) count++;
    }
    printf("%d\n", count);
    
    // Part 2: DP for arrangements
    // We store numbers in reverse order
    char** dp = (char**)malloc((n+2) * sizeof(char*));
    dp[0] = NULL; // not used
    dp[1] = (char*)malloc(2);
    dp[1][0] = '1';
    dp[1][1] = '\0';
    if(n >=2){
        dp[2] = (char*)malloc(3);
        dp[2][0] = '2';
        dp[2][1] = '\0';
    }
    for(int i=3;i<=n;i++) {
        dp[i] = addStrings(dp[i-1], dp[i-2]);
    }
    // Print dp[n] in reverse to get the correct order
    int len = strlen(dp[n]);
    for(int i=len-1;i>=0;i--) putchar(dp[n][i]);
    putchar('\n');
    
    // Free memory
    for(int i=1;i<=n;i++) if(dp[i]) free(dp[i]);
    free(dp);
    
    // Free trie
    // Skipping trie deallocation for brevity
    
    return 0;
}