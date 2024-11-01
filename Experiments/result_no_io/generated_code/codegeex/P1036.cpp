#include <stdio.h>
#include <stdbool.h>

// 函数声明
bool isPrime(int num);
void combinationSum(int arr[], int n, int k, int index, int sum, int count, bool visited[], int *primeCount);

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    
    int primeCount = 0;
    combinationSum(arr, n, k, 0, 0, 0, visited, &primeCount);
    
    printf("%d\n", primeCount);
    return 0;
}

// 判断一个数是否为素数
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// 计算组合数的和
void combinationSum(int arr[], int n, int k, int index, int sum, int count, bool visited[], int *primeCount) {
    if (count == k) {
        if (isPrime(sum)) {
            (*primeCount)++;
        }
        return;
    }
    
    for (int i = index; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            combinationSum(arr, n, k, i + 1, sum + arr[i], count + 1, visited, primeCount);
            visited[i] = false;
        }
    }
}