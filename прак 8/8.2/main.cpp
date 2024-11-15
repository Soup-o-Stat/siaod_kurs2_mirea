#include <iostream>
#include <vector>
#include <string>

using namespace std;

int countSequencesDP(int n) {
    if (n == 1)
        return 2;

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    dp[1][0] = 1;
    dp[1][1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
    }

    return dp[n][0] + dp[n][1];
}

bool isValidSequence(const string& seq) {
    for (size_t i = 1; i < seq.size(); ++i)
        if (seq[i] == '1' && seq[i - 1] == '1')
            return false;
    return true;
}

int countSequencesBruteForce(int n) {
    int count = 0;
    int limit = 1 << n;

    for (int i = 0; i < limit; i++) {
        string seq;
        for (int j = 0; j < n; j++)
            seq = ((i >> j) & 1 ? '1' : '0') + seq;
        if (isValidSequence(seq))
            ++count;
    }
    return count;
}

int main() {
    int n;
    cout << "Enter the length of the sequence n: ";
    cin >> n;
    if (n <= 0) {
        cout << "Error" << endl;
        return -1;
    }

    int resultDP = countSequencesDP(n);
    cout << "The number of sequences of length " << n << " without two consecutive units (dynamic programming): " << resultDP << endl;
    int resultBruteForce = countSequencesBruteForce(n);
    cout << "The number of sequences of length " << n << " without two consecutive units (bruteforce): " << resultBruteForce << endl;
    return 0;
}
