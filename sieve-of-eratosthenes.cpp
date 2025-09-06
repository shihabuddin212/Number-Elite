#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Basic Sieve of Eratosthenes
vector<bool> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            // Mark all multiples of i as composite
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

// Optimized Sieve of Eratosthenes (only odd numbers)
vector<bool> optimizedSieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    // Handle 2 separately
    if (n >= 2) {
        // Mark all even numbers > 2 as composite
        for (int i = 4; i <= n; i += 2) {
            isPrime[i] = false;
        }
    }
    
    // Process odd numbers starting from 3
    for (int i = 3; i * i <= n; i += 2) {
        if (isPrime[i]) {
            // Mark odd multiples of i starting from i^2
            for (int j = i * i; j <= n; j += 2 * i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

// Segmented Sieve for large numbers
vector<int> segmentedSieve(int n) {
    int limit = sqrt(n) + 1;
    vector<bool> primesUpToLimit = sieveOfEratosthenes(limit);
    
    // Get all primes up to sqrt(n)
    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (primesUpToLimit[i]) {
            primes.push_back(i);
        }
    }
    
    vector<int> result;
    
    // Add small primes to result
    for (int prime : primes) {
        if (prime <= n) {
            result.push_back(prime);
        }
    }
    
    // Process segments
    int segmentSize = max(limit, 1);
    
    for (int low = limit + 1; low <= n; low += segmentSize) {
        int high = min(low + segmentSize - 1, n);
        vector<bool> segment(high - low + 1, true);
        
        // Mark multiples in current segment
        for (int prime : primes) {
            // Find first multiple of prime in segment
            int start = max(prime * prime, (low + prime - 1) / prime * prime);
            
            for (int j = start; j <= high; j += prime) {
                segment[j - low] = false;
            }
        }
        
        // Add primes from current segment
        for (int i = 0; i < segment.size(); i++) {
            if (segment[i]) {
                result.push_back(low + i);
            }
        }
    }
    
    return result;
}

// Linear Sieve (Sieve of Euler)
vector<int> linearSieve(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;
    
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
        
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break; // Key optimization: avoid marking same number multiple times
            }
        }
    }
    
    return primes;
}

// Function to extract primes from boolean array
vector<int> extractPrimes(const vector<bool>& isPrime) {
    vector<int> primes;
    for (int i = 0; i < isPrime.size(); i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to display primes
void displayPrimes(const vector<int>& primes, const string& method, int displayLimit = 100) {
    cout << "\n=== " << method << " ===" << endl;
    cout << "Found " << primes.size() << " primes" << endl;
    
    if (primes.size() <= displayLimit) {
        cout << "Primes: ";
        for (int i = 0; i < primes.size(); i++) {
            cout << primes[i];
            if (i < primes.size() - 1) cout << ", ";
            if ((i + 1) % 10 == 0) cout << endl << "        "; // Indent continuation
        }
        cout << endl;
    } else {
        cout << "First 50 primes: ";
        for (int i = 0; i < 50; i++) {
            cout << primes[i];
            if (i < 49) cout << ", ";
            if ((i + 1) % 10 == 0) cout << endl << "                 "; // Indent continuation
        }
        cout << endl;
        cout << "Last 10 primes: ";
        for (int i = primes.size() - 10; i < primes.size(); i++) {
            cout << primes[i];
            if (i < primes.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Performance comparison function
void performanceTest(int n) {
    cout << "\n=== Performance Test for n = " << n << " ===" << endl;
    
    // Test basic sieve
    vector<bool> result1 = sieveOfEratosthenes(n);
    vector<int> primes1 = extractPrimes(result1);
    cout << "Basic Sieve: " << primes1.size() << " primes found" << endl;
    
    // Test optimized sieve
    vector<bool> result2 = optimizedSieve(n);
    vector<int> primes2 = extractPrimes(result2);
    cout << "Optimized Sieve: " << primes2.size() << " primes found" << endl;
    
    // Test linear sieve
    vector<int> primes3 = linearSieve(n);
    cout << "Linear Sieve: " << primes3.size() << " primes found" << endl;
    
    // Test segmented sieve
    vector<int> primes4 = segmentedSieve(n);
    cout << "Segmented Sieve: " << primes4.size() << " primes found" << endl;
    
    // Verify results match
    if (primes1.size() == primes2.size() && primes2.size() == primes3.size() && primes3.size() == primes4.size()) {
        cout << "✓ All methods found the same number of primes" << endl;
    } else {
        cout << "✗ Methods found different numbers of primes!" << endl;
    }
}

int main() {
    int n, choice;
    
    cout << "=== Sieve of Eratosthenes Implementation ===" << endl;
    cout << "Enter the limit (n): ";
    cin >> n;
    
    if (n < 2) {
        cout << "No primes exist below 2." << endl;
        return 0;
    }
    
    cout << "\nChoose implementation:" << endl;
    cout << "1. Basic Sieve of Eratosthenes" << endl;
    cout << "2. Optimized Sieve (odd numbers only)" << endl;
    cout << "3. Linear Sieve (Sieve of Euler)" << endl;
    cout << "4. Segmented Sieve" << endl;
    cout << "5. Compare all methods" << endl;
    cout << "6. Performance test" << endl;
    
    cout << "Enter choice: ";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            vector<bool> isPrime = sieveOfEratosthenes(n);
            vector<int> primes = extractPrimes(isPrime);
            displayPrimes(primes, "Basic Sieve of Eratosthenes");
            break;
        }
        case 2: {
            vector<bool> isPrime = optimizedSieve(n);
            vector<int> primes = extractPrimes(isPrime);
            displayPrimes(primes, "Optimized Sieve");
            break;
        }
        case 3: {
            vector<int> primes = linearSieve(n);
            displayPrimes(primes, "Linear Sieve (Sieve of Euler)");
            break;
        }
        case 4: {
            vector<int> primes = segmentedSieve(n);
            displayPrimes(primes, "Segmented Sieve");
            break;
        }
        case 5: {
            cout << "\n=== Comparing All Methods ===" << endl;
            
            vector<bool> isPrime1 = sieveOfEratosthenes(n);
            vector<int> primes1 = extractPrimes(isPrime1);
            displayPrimes(primes1, "Basic Sieve", 50);
            
            vector<bool> isPrime2 = optimizedSieve(n);
            vector<int> primes2 = extractPrimes(isPrime2);
            displayPrimes(primes2, "Optimized Sieve", 50);
            
            vector<int> primes3 = linearSieve(n);
            displayPrimes(primes3, "Linear Sieve", 50);
            
            vector<int> primes4 = segmentedSieve(n);
            displayPrimes(primes4, "Segmented Sieve", 50);
            
            // Verify results
            if (primes1 == primes2 && primes2 == primes3 && primes3 == primes4) {
                cout << "\n✓ All methods produced identical results!" << endl;
            } else {
                cout << "\n✗ Methods produced different results!" << endl;
            }
            break;
        }
        case 6: {
            performanceTest(n);
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
