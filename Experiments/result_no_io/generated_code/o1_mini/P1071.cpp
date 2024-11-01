#include<stdio.h>
#include<string.h>

int main(){
    char encrypted1[105], original1[105], encrypted2[105];
    scanf("%s %s %s", encrypted1, original1, encrypted2);
    
    int len1 = strlen(encrypted1);
    int len2 = strlen(encrypted2);
    
    char map[26];
    char reverse_map[26];
    for(int i=0;i<26;i++){
        map[i] = -1;
        reverse_map[i] = -1;
    }
    
    int failed = 0;
    for(int i=0;i<len1;i++){
        char x = original1[i];
        char y = encrypted1[i];
        int idx_x = x - 'A';
        int idx_y = y - 'A';
        
        if(map[idx_x] == -1){
            if(reverse_map[idx_y] != -1){
                failed = 1;
                break;
            }
            map[idx_x] = y;
            reverse_map[idx_y] = x;
        }
        else{
            if(map[idx_x] != y){
                failed = 1;
                break;
            }
        }
    }
    
    if(!failed){
        for(int i=0;i<26;i++){
            if(map[i] == -1){
                failed = 1;
                break;
            }
        }
    }
    
    if(failed){
        printf("Failed");
    }
    else{
        char translated[105];
        int len = strlen(encrypted2);
        for(int i=0;i<len;i++){
            char y = encrypted2[i];
            int idx_y = y - 'A';
            char x = reverse_map[idx_y];
            translated[i] = x;
        }
        translated[len] = '\0';
        printf("%s", translated);
    }
}