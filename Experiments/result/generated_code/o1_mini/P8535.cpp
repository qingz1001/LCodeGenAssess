#include <stdio.h>
#include <string.h>

int main(){
    long long n;
    scanf("%lld", &n);
    // Define digits and their star counts
    char digits_char[10] = {'1','2','3','4','5','6','7','8','9','0'};
    int star_counts[10] = {5,8,15,30,23,11,16,10,18,24};
    // Define the order to choose digits from '9' to '0'
    int order[10] = {8,7,6,5,4,3,2,1,0,9};
    // Find minimum star count
    int m = 5; // minimum star count is for '1'
    // Calculate maximum number of digits
    long long k = n / m;
    if(k ==0){
        // Not possible, but as n>=5, not needed
    }
    // Prepare the output buffer
    char output[200001];
    long long pos;
    for(pos=0; pos<k; pos++){
        // Iterate through digits from '9' to '0'
        for(int j=0; j<10; j++){
            int digit_idx = order[j];
            int cost = star_counts[digit_idx];
            if(n >= cost + (k - pos -1)*m){
                output[pos] = digits_char[digit_idx];
                n -= cost;
                break;
            }
        }
    }
    output[k] = '\0';
    printf("%s\n", output);
}