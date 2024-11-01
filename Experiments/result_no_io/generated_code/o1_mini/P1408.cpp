#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

// Define maximum A[i]
#define MAX_A 20000000

// Structure for dynamic list of integers
typedef struct {
    int *data;
    int size;
    int capacity;
} IntList;

// Initialize IntList
void initList(IntList *list) {
    list->size = 0;
    list->capacity = 4;
    list->data = (int*)malloc(list->capacity * sizeof(int));
}

// Append to IntList
void appendList(IntList *list, int value) {
    if(list->size == list->capacity){
        list->capacity *=2;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
    }
    list->data[list->size++] = value;
}

// Free IntList
void freeList(IntList *list){
    free(list->data);
}

// Dynamic array of IntList for primes
typedef struct {
    int prime;
    IntList positions;
} PrimeList;

// Compare function for qsort
int cmp_int(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

int main(){
    int n;
    scanf("%d", &n);
    int *A = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &A[i]);

    // Sieve to get small primes up to sqrt(2e7)
    int limit = (int)sqrt(MAX_A) +1;
    int sieve_size = limit +1;
    char *sieve = (char*)calloc(sieve_size, sizeof(char));
    IntList primes;
    initList(&primes);
    for(int p=2;p<=limit;p++) {
        if(!sieve[p]){
            appendList(&primes, p);
            for(int multiple = p*p; multiple <= limit; multiple +=p){
                sieve[multiple] = 1;
            }
        }
    }
    free(sieve);
    // Initialize prime lists
    int prime_capacity = primes.size;
    PrimeList *primeLists = (PrimeList*)malloc(prime_capacity * sizeof(PrimeList));
    for(int i=0;i<primes.size;i++){
        primeLists[i].prime = primes.data[i];
        initList(&primeLists[i].positions);
    }

    // To store additional large primes
    PrimeList *extraPrimes = NULL;
    int extra_size =0, extra_capacity=0;

    // Factorize each A[i}
    for(int i=0;i<n;i++){
        int num = A[i];
        // Factorize using small primes
        for(int j=0; j < primes.size && primes.data[j]*primes.data[j] <= num; j++){
            if(num % primes.data[j] ==0){
                appendList(&primeLists[j].positions, i);
                while(num % primes.data[j] ==0) num /= primes.data[j];
            }
        }
        if(num >1){
            // Check if num is already in primeLists
            int found = 0;
            for(int j=0; j < primes.size; j++){
                if(primeLists[j].prime == num){
                    appendList(&primeLists[j].positions, i);
                    found =1;
                    break;
                }
            }
            if(!found){
                // Check in extraPrimes
                int k;
                for(k=0; k < extra_size; k++) {
                    if(extraPrimes[k].prime == num){
                        appendList(&extraPrimes[k].positions, i);
                        found =1;
                        break;
                    }
                }
                if(!found){
                    // Add a new prime
                    if(extra_size == extra_capacity){
                        extra_capacity = extra_capacity ==0 ? 16 : extra_capacity *2;
                        extraPrimes = (PrimeList*)realloc(extraPrimes, extra_capacity * sizeof(PrimeList));
                    }
                    extraPrimes[extra_size].prime = num;
                    initList(&extraPrimes[extra_size].positions);
                    appendList(&extraPrimes[extra_size].positions, i);
                    extra_size++;
                }
            }
        }
    }

    // Now process all primes
    long long total_cost =0;
    // Process small primes
    for(int i=0;i<primes.size;i++){
        IntList *plist = &primeLists[i].positions;
        if(plist->size ==0) continue;
        // Sort positions
        qsort(plist->data, plist->size, sizeof(int), cmp_int);
        // Count operations
        int count =0;
        int idx=0;
        while(idx < plist->size -1){
            if(plist->data[idx+1] == plist->data[idx]+1){
                count++;
                idx +=2;
            }
            else{
                idx++;
            }
        }
        total_cost += (long long)count * primeLists[i].prime;
    }
    // Process extra primes
    for(int i=0;i<extra_size;i++){
        IntList *plist = &extraPrimes[i].positions;
        if(plist->size ==0) continue;
        qsort(plist->data, plist->size, sizeof(int), cmp_int);
        int count =0;
        int idx=0;
        while(idx < plist->size -1){
            if(plist->data[idx+1] == plist->data[idx]+1){
                count++;
                idx +=2;
            }
            else{
                idx++;
            }
        }
        total_cost += (long long)count * extraPrimes[i].prime;
    }

    printf("%lld", total_cost);

    // Free memory
    free(A);
    for(int i=0;i<primes.size;i++) freeList(&primeLists[i].positions);
    free(primeLists);
    for(int i=0;i<extra_size;i++) freeList(&extraPrimes[i].positions);
    free(extraPrimes);
    freeList(&primes);
    return 0;
}