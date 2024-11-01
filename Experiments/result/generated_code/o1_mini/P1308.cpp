#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD 11
#define MAX_ARTICLE 1000005

int main(){
    char search[MAX_WORD];
    char article[MAX_ARTICLE];
    
    // Read the search word
    scanf("%s", search);
    
    // Convert search word to lowercase
    int search_len = strlen(search);
    for(int i=0;i<search_len;i++) {
        if('A' <= search[i] && search[i] <= 'Z') {
            search[i] = search[i] + ('a' - 'A');
        }
    }
    
    // Read the remaining line as article
    int c = getchar(); // consume the newline after the first word
    int idx = 0;
    while((c = getchar()) != EOF && c != '\n') {
        article[idx++] = c;
    }
    article[idx] = '\0';
    
    int count = 0;
    int first_pos = -1;
    int pos = 0;
    int i = 0;
    while(i < idx){
        // Skip any leading spaces
        while(i < idx && article[i] == ' ') i++;
        if(i >= idx) break;
        int start = i;
        // Find the end of the word
        while(i < idx && article[i] != ' ') i++;
        int end = i;
        int word_len = end - start;
        if(word_len == search_len){
            // Compare case-insensitively
            int match = 1;
            for(int j=0; j<word_len; j++){
                char a = article[start + j];
                char b = search[j];
                if('A' <= a && a <= 'Z') a = a + ('a' - 'A');
                if(a != b){
                    match = 0;
                    break;
                }
            }
            if(match){
                count++;
                if(count == 1){
                    first_pos = start;
                }
            }
        }
    }
    
    if(count > 0){
        printf("%d %d\n", count, first_pos);
    }
    else{
        printf("-1\n");
    }
    
    return 0;
}