#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 11
#define MAX_TEXT_LEN 1000005

int main(){
    char word[MAX_WORD_LEN];
    char text[MAX_TEXT_LEN];
    if(scanf("%s", word)!=1) return 0;
    getchar(); // consume newline
    fgets(text, MAX_TEXT_LEN, stdin);
    int word_len = strlen(word);
    for(int i=0;i<word_len;i++) word[i] = tolower(word[i]);
    int count =0, first = -1;
    int pos =0;
    int len = strlen(text);
    int i=0;
    while(i < len){
        while(i < len && text[i] == ' ') i++;
        if(i >= len) break;
        int start = i;
        int j=0;
        while(i < len && text[i] != ' ') {
            if(j < word_len){
                // do nothing
            }
            i++;
            j++;
        }
        int current_len = j;
        if(current_len == word_len){
            int match =1;
            for(int k=0;k<word_len;k++) {
                if(tolower(text[start +k]) != word[k]){
                    match =0;
                    break;
                }
            }
            if(match){
                count++;
                if(first == -1) first = start;
            }
        }
    }
    if(count>0) printf("%d %d", count, first);
    else printf("-1");
    return 0;
}