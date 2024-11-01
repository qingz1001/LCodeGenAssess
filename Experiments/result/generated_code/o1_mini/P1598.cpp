#include <stdio.h>
#include <string.h>

#define MAX_LINE 105
#define LETTERS 26

int main(){
    int counts[LETTERS] = {0};
    char line[MAX_LINE];
    
    for(int i=0;i<4;i++){
        if(fgets(line, sizeof(line), stdin)){
            for(int j=0; line[j] != '\0' && line[j] != '\n'; j++){
                if(line[j] >= 'A' && line[j] <= 'Z'){
                    counts[line[j]-'A']++;
                }
            }
        }
    }
    
    int max = 0;
    for(int i=0;i<LETTERS;i++) if(counts[i] > max) max = counts[i];
    
    for(int level = max; level >=1; level--){
        char buffer[LETTERS * 2];
        int pos = 0;
        for(int i=0;i<LETTERS;i++){
            if(counts[i] >= level){
                buffer[pos++] = '*';
            }
            else{
                buffer[pos++] = ' ';
            }
            if(i != LETTERS-1){
                buffer[pos++] = ' ';
            }
        }
        buffer[pos] = '\0';
        
        // Trim trailing spaces
        int end = pos-1;
        while(end >=0 && buffer[end] == ' ') end--;
        buffer[end+1] = '\0';
        
        printf("%s\n", buffer);
    }
    
    // Print letters
    char letters_line[LETTERS * 2];
    int pos = 0;
    for(int i=0;i<LETTERS;i++){
        letters_line[pos++] = 'A' + i;
        if(i != LETTERS-1){
            letters_line[pos++] = ' ';
        }
    }
    letters_line[pos] = '\0';
    printf("%s\n", letters_line);
    
    return 0;
}