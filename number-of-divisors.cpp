#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Function to count number of divisors of a number
int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (n / i == i) {
                count++; // Perfect square case
            } else {
                count += 2; // Both i and n/i are divisors
            }
        }
    }
    return count;
}

// Optimized version using prime factorization
int countDivisorsOptimized(int n) {
    int count = 1;
    
    // Count factors of 2
    int power = 0;
    while (n % 2 == 0) {
        power++;
        n /= 2;
    }
    count *= (power + 1);
    
    // Count odd factors
    for (int i = 3; i <= sqrt(n); i += 2) {
        power = 0;
        while (n % i == 0) {
            power++;
            n /= i;
        }
        count *= (power + 1);
    }
    
    // If n is still > 1, then it's a prime
    if (n > 1) {
        count *= 2;
    }
    
    return count;
}

// Function to find all divisors
vector<int> findAllDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (n / i != i) {
                divisors.push_back(n / i);
            }
        }
    }
    return divisors;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    
    cout << "Number of divisors of " << n << " is: " << countDivisors(n) << endl;
    cout << "Number of divisors (optimized): " << countDivisorsOptimized(n) << endl;
    
    vector<int> divisors = findAllDivisors(n);
    cout << "All divisors: ";
    for (int div : divisors) {
        cout << div << " ";
    }
    cout << endl;
    
    return 0;
}
