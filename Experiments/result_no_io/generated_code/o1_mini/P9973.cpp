#include <stdio.h>
#include <string.h>

#define MAX_LEN 201
#define PREFIX_LEN 19

int main() {
    char s[MAX_LEN];
    // Define the AI prefix here. Replace "AI_Prefix_String" with the actual 19-character prefix.
    char ai_prefix[PREFIX_LEN + 1] = "AI_Prefix_String"; // Example: "ThisIs19CharPrefix"
    
    if (fgets(s, MAX_LEN, stdin) == NULL) {
        return 0;
    }
    
    // Remove newline character if present
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
    }
    
    // Compare the first 19 characters
    if (strncmp(s, ai_prefix, PREFIX_LEN) == 0) {
        printf("AI\n");
    } else {
        printf("Human\n");
    }
    
    return 0;
}