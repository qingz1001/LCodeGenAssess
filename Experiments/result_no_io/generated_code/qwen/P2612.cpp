pp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double calculateProbability(int N, int M, int K) {
    vector<int> indices(N);
    for (int i = 0; i < N; ++i) {
        indices[i] = i + 1;
    }

    long long totalPermutations = factorial(N);
    long long validPermutations = 0;

    do {
        int currentSum = 0;
        for (int i = 1; i < N; ++i) {
            currentSum += abs(indices[i] - indices[i - 1]);
        }
        if (currentSum >= M) {
            ++validPermutations;
        }
    } while (next_permutation(indices.begin(), indices.end()));

    double probability = static_cast<double>(validPermutations) / totalPermutations;
    return round(probability * pow(10, K)) / pow(10, K);
}

long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    cout << fixed << setprecision(K) << calculateProbability(N, M, K) << endl;
    return 0;
}