#include <stdio.h>
#include <string.h>

int main(){
    char encrypted1[101], original1[101], encrypted2[101];
    if(!fgets(encrypted1, sizeof(encrypted1), stdin)) return 0;
    if(!fgets(original1, sizeof(original1), stdin)) return 0;
    if(!fgets(encrypted2, sizeof(encrypted2), stdin)) return 0;
    
    // Remove newline characters
    int len1 = strlen(encrypted1);
    if(encrypted1[len1-1]=='\n') encrypted1[len1-1]=0;
    len1 = strlen(original1);
    if(original1[len1-1]=='\n') original1[len1-1]=0;
    len1 = strlen(encrypted2);
    if(encrypted2[len1-1]=='\n') encrypted2[len1-1]=0;
    
    int mapping[26];
    int reverse_map[26];
    for(int i=0;i<26;i++) { mapping[i]=-1; reverse_map[i]=-1; }
    int len = strlen(encrypted1);
    int failed = 0;
    for(int i=0;i<len;i++){
        char o = original1[i];
        char e = encrypted1[i];
        int o_idx = o - 'A';
        int e_idx = e - 'A';
        if(mapping[o_idx]==-1){
            mapping[o_idx] = e_idx;
        }
        else{
            if(mapping[o_idx] != e_idx){
                failed = 1;
                break;
            }
        }
        if(reverse_map[e_idx]==-1){
            reverse_map[e_idx] = o_idx;
        }
        else{
            if(reverse_map[e_idx] != o_idx){
                failed = 1;
                break;
            }
        }
    }
    if(!failed){
        for(int i=0;i<26;i++) {
            if(mapping[i]==-1){
                failed =1;
                break;
            }
        }
    }
    if(failed){
        printf("Failed");
        return 0;
    }
    // Now translate encrypted2
    int len2 = strlen(encrypted2);
    char result[101];
    for(int i=0;i<len2;i++){
        char e = encrypted2[i];
        int e_idx = e - 'A';
        if(reverse_map[e_idx]==-1){
            failed =1;
            break;
        }
        result[i] = reverse_map[e_idx] + 'A';
    }
    result[len2] = '\0';
    if(failed){
        printf("Failed");
    }
    else{
        printf("%s", result);
    }
}