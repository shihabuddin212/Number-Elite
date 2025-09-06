#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate (base^exp) % mod using fast exponentiation
long long fastPower(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1; // exp = exp / 2
        base = (base * base) % mod;
    }
    
    return result;
}

// Function to calculate modular inverse using Fermat's Little Theorem
// Works only when mod is prime and a is not divisible by mod
long long modularInverse(long long a, long long mod) {
    // According to Fermat's Little Theorem: a^(p-1) ≡ 1 (mod p)
    // Therefore: a^(p-2) ≡ a^(-1) (mod p)
    return fastPower(a, mod - 2, mod);
}

// Function to check if a number is prime (simple check)
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to verify Fermat's Little Theorem
bool verifyFermatsLittleTheorem(long long a, long long p) {
    if (!isPrime(p)) {
        cout << p << " is not a prime number!" << endl;
        return false;
    }
    
    if (a % p == 0) {
        cout << a << " is divisible by " << p << endl;
        return false;
    }
    
    long long result = fastPower(a, p - 1, p);
    return result == 1;
}

int main() {
    long long a, p;
    
    cout << "=== Fermat's Little Theorem Implementation ===" << endl;
    cout << "Theorem: If p is prime and a is not divisible by p," << endl;
    cout << "then a^(p-1) ≡ 1 (mod p)" << endl << endl;
    
    cout << "Enter base (a): ";
    cin >> a;
    cout << "Enter prime (p): ";
    cin >> p;
    
    cout << endl << "Results:" << endl;
    
    // Verify Fermat's Little Theorem
    if (verifyFermatsLittleTheorem(a, p)) {
        cout << "✓ Fermat's Little Theorem verified: " << a << "^" << (p-1) << " ≡ 1 (mod " << p << ")" << endl;
        
        // Calculate a^(p-1) mod p
        long long result = fastPower(a, p - 1, p);
        cout << a << "^" << (p-1) << " mod " << p << " = " << result << endl;
        
        // Calculate modular inverse
        long long inverse = modularInverse(a, p);
        cout << "Modular inverse of " << a << " mod " << p << " = " << inverse << endl;
        
        // Verify inverse
        long long verification = (a * inverse) % p;
        cout << "Verification: " << a << " * " << inverse << " mod " << p << " = " << verification << endl;
        
    } else {
        cout << "✗ Fermat's Little Theorem conditions not met or failed!" << endl;
    }
    
    // Additional examples
    cout << endl << "=== Additional Examples ===" << endl;
    
    // Example 1: 2^6 mod 7
    cout << "Example 1: 2^6 mod 7 = " << fastPower(2, 6, 7) << " (should be 1)" << endl;
    
    // Example 2: 3^10 mod 11
    cout << "Example 2: 3^10 mod 11 = " << fastPower(3, 10, 11) << " (should be 1)" << endl;
    
    // Example 3: Modular inverse of 3 mod 7
    cout << "Example 3: Inverse of 3 mod 7 = " << modularInverse(3, 7) << endl;
    cout << "Verification: 3 * " << modularInverse(3, 7) << " mod 7 = " << (3 * modularInverse(3, 7)) % 7 << endl;
    
    return 0;
}
