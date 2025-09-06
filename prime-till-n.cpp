#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Method 1: Simple Trial Division
vector<int> primeTillNSimple(int n) {
    vector<int> primes;
    
    for (int i = 2; i <= n; i++) {
        bool isPrime = true;
        
        for (int j = 2; j <= sqrt(i); j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        
        if (isPrime) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// Method 2: Optimized Trial Division
vector<int> primeTillNOptimized(int n) {
    if (n < 2) return {};
    
    vector<int> primes;
    primes.push_back(2); // First prime
    
    for (int i = 3; i <= n; i += 2) { // Check only odd numbers
        bool isPrime = true;
        
        // Check divisibility only by primes found so far
        for (int prime : primes) {
            if (prime * prime > i) break; // Only check up to sqrt(i)
            
            if (i % prime == 0) {
                isPrime = false;
                break;
            }
        }
        
        if (isPrime) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// Method 3: Simple Sieve (not the standard Sieve of Eratosthenes)
vector<int> primeTillNSieve(int n) {
    if (n < 2) return {};
    
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;
    
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            
            // Mark multiples as composite
            for (int j = i * 2; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return primes;
}

// Method 4: Using 6k±1 optimization
vector<int> primeTillN6kOptimization(int n) {
    if (n < 2) return {};
    
    vector<int> primes;
    
    if (n >= 2) primes.push_back(2);
    if (n >= 3) primes.push_back(3);
    
    // All primes > 3 are of the form 6k±1
    for (int i = 5; i <= n; i += 6) {
        // Check 6k-1
        if (i <= n) {
            bool isPrime = true;
            for (int j = 5; j * j <= i; j += 6) {
                if (i % j == 0 || i % (j + 2) == 0) {
                    isPrime = false;
                    break;
                }
            }
            // Also check divisibility by 2 and 3
            if (isPrime && i % 2 != 0 && i % 3 != 0) {
                primes.push_back(i);
            }
        }
        
        // Check 6k+1
        if (i + 2 <= n) {
            bool isPrime = true;
            int candidate = i + 2;
            for (int j = 5; j * j <= candidate; j += 6) {
                if (candidate % j == 0 || candidate % (j + 2) == 0) {
                    isPrime = false;
                    break;
                }
            }
            // Also check divisibility by 2 and 3
            if (isPrime && candidate % 2 != 0 && candidate % 3 != 0) {
                primes.push_back(candidate);
            }
        }
    }
    
    return primes;
}

// Function to display primes
void displayPrimes(const vector<int>& primes, const string& method) {
    cout << "\n=== " << method << " ===" << endl;
    cout << "Found " << primes.size() << " primes:" << endl;
    
    for (int i = 0; i < primes.size(); i++) {
        cout << primes[i];
        if (i < primes.size() - 1) cout << ", ";
        if ((i + 1) % 10 == 0) cout << endl; // New line every 10 primes
    }
    if (primes.size() % 10 != 0) cout << endl;
}

// Function to count primes in different ranges
void primeStatistics(int n) {
    vector<int> primes = primeTillNOptimized(n);
    
    cout << "\n=== Prime Statistics up to " << n << " ===" << endl;
    cout << "Total primes: " << primes.size() << endl;
    
    if (!primes.empty()) {
        cout << "Largest prime: " << primes.back() << endl;
        cout << "Smallest prime: " << primes.front() << endl;
        
        // Count primes in different ranges
        int count_1_10 = 0, count_11_50 = 0, count_51_100 = 0, count_above_100 = 0;
        
        for (int prime : primes) {
            if (prime <= 10) count_1_10++;
            else if (prime <= 50) count_11_50++;
            else if (prime <= 100) count_51_100++;
            else count_above_100++;
        }
        
        cout << "Primes 1-10: " << count_1_10 << endl;
        cout << "Primes 11-50: " << count_11_50 << endl;
        cout << "Primes 51-100: " << count_51_100 << endl;
        cout << "Primes above 100: " << count_above_100 << endl;
    }
}

int main() {
    int n;
    cout << "=== Prime Numbers up to N ===" << endl;
    cout << "Enter the limit (n): ";
    cin >> n;
    
    if (n < 2) {
        cout << "No primes exist below 2." << endl;
        return 0;
    }
    
    cout << "\nChoose method:" << endl;
    cout << "1. Simple Trial Division" << endl;
    cout << "2. Optimized Trial Division" << endl;
    cout << "3. Simple Sieve" << endl;
    cout << "4. 6k±1 Optimization" << endl;
    cout << "5. Compare all methods" << endl;
    cout << "6. Prime statistics only" << endl;
    
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            vector<int> primes = primeTillNSimple(n);
            displayPrimes(primes, "Simple Trial Division");
            break;
        }
        case 2: {
            vector<int> primes = primeTillNOptimized(n);
            displayPrimes(primes, "Optimized Trial Division");
            break;
        }
        case 3: {
            vector<int> primes = primeTillNSieve(n);
            displayPrimes(primes, "Simple Sieve");
            break;
        }
        case 4: {
            vector<int> primes = primeTillN6kOptimization(n);
            displayPrimes(primes, "6k±1 Optimization");
            break;
        }
        case 5: {
            cout << "\n=== Comparing All Methods ===" << endl;
            
            vector<int> primes1 = primeTillNSimple(n);
            displayPrimes(primes1, "Simple Trial Division");
            
            vector<int> primes2 = primeTillNOptimized(n);
            displayPrimes(primes2, "Optimized Trial Division");
            
            vector<int> primes3 = primeTillNSieve(n);
            displayPrimes(primes3, "Simple Sieve");
            
            vector<int> primes4 = primeTillN6kOptimization(n);
            displayPrimes(primes4, "6k±1 Optimization");
            
            // Verify all methods give same result
            if (primes1 == primes2 && primes2 == primes3) {
                cout << "\n✓ All methods produced the same result!" << endl;
            } else {
                cout << "\n✗ Methods produced different results!" << endl;
            }
            break;
        }
        case 6: {
            primeStatistics(n);
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
