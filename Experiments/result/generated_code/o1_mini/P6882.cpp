#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int N;
    scanf("%d", &N);
    getchar(); // consume the newline after N
    char line[1005];
    fgets(line, sizeof(line), stdin);
    int names_count[5] = {0};
    int current_sentence = 0;
    char *token = strtok(line, " \n");
    while(token != NULL && current_sentence < N){
        int len = strlen(token);
        char last_char = token[len-1];
        int has_punct = 0;
        if(last_char == '.' || last_char == '?' || last_char == '!'){
            has_punct = 1;
            token[len-1] = '\0';
            len--;
        }
        if(len > 0){
            int is_name = 1;
            if(!isupper(token[0])){
                is_name = 0;
            }
            for(int i=1;i<len;i++){
                if(!islower(token[i])){
                    is_name = 0;
                    break;
                }
            }
            for(int i=0;i<len;i++){
                if(!isalpha(token[i])){
                    is_name = 0;
                    break;
                }
            }
            if(is_name){
                names_count[current_sentence]++;
            }
        }
        if(has_punct){
            current_sentence++;
        }
        token = strtok(NULL, " \n");
    }
    for(int i=0;i<N;i++){
        printf("%d\n", names_count[i]);
    }
    return 0;
}