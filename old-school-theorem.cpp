#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Trial Division Method - Basic primality test
bool isPrimeTrialDivision(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Greatest Common Divisor using Euclidean Algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Extended Euclidean Algorithm
// Returns gcd(a, b) and finds x, y such that ax + by = gcd(a, b)
int extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd_val = extendedGCD(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd_val;
}

// Modular Inverse using Extended Euclidean Algorithm
int modularInverse(int a, int m) {
    int x, y;
    int gcd_val = extendedGCD(a, m, x, y);
    
    if (gcd_val != 1) {
        cout << "Modular inverse doesn't exist" << endl;
        return -1;
    }
    
    return (x % m + m) % m;
}

// Fast Exponentiation (Power with modulo)
long long fastPower(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}

// Prime Factorization
vector<pair<int, int>> primeFactorization(int n) {
    vector<pair<int, int>> factors;
    
    // Count factors of 2
    int count = 0;
    while (n % 2 == 0) {
        count++;
        n /= 2;
    }
    if (count > 0) {
        factors.push_back({2, count});
    }
    
    // Count odd factors
    for (int i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count > 0) {
            factors.push_back({i, count});
        }
    }
    
    // If n is still > 1, then it's a prime
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}

// Euler's Totient Function (φ(n))
int eulerTotient(int n) {
    int result = n;
    
    // Consider all prime factors of n
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            // Remove all factors of i from n
            while (n % i == 0) {
                n /= i;
            }
            // Multiply result with (1 - 1/i)
            result -= result / i;
        }
    }
    
    // If n has a prime factor greater than sqrt(n)
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}

// Wilson's Theorem: (p-1)! ≡ -1 (mod p) if and only if p is prime
bool wilsonTheorem(int p) {
    if (p <= 1) return false;
    
    long long factorial = 1;
    for (int i = 1; i < p; i++) {
        factorial = (factorial * i) % p;
    }
    
    return factorial == p - 1; // -1 ≡ p-1 (mod p)
}

int main() {
    cout << "=== Old School Number Theory Algorithms ===" << endl << endl;
    
    int choice, n, a, b, m;
    
    while (true) {
        cout << "\nChoose an algorithm:" << endl;
        cout << "1. Prime Check (Trial Division)" << endl;
        cout << "2. GCD (Euclidean Algorithm)" << endl;
        cout << "3. Extended GCD" << endl;
        cout << "4. Modular Inverse" << endl;
        cout << "5. Fast Exponentiation" << endl;
        cout << "6. Prime Factorization" << endl;
        cout << "7. Euler's Totient Function" << endl;
        cout << "8. Wilson's Theorem" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter number: ";
                cin >> n;
                if (isPrimeTrialDivision(n)) {
                    cout << n << " is prime" << endl;
                } else {
                    cout << n << " is not prime" << endl;
                }
                break;
                
            case 2:
                cout << "Enter two numbers: ";
                cin >> a >> b;
                cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << endl;
                break;
                
            case 3:
                cout << "Enter two numbers: ";
                cin >> a >> b;
                int x, y;
                int gcd_val = extendedGCD(a, b, x, y);
                cout << "GCD(" << a << ", " << b << ") = " << gcd_val << endl;
                cout << "Coefficients: " << a << "*(" << x << ") + " << b << "*(" << y << ") = " << gcd_val << endl;
                break;
                
            case 4:
                cout << "Enter number and modulus: ";
                cin >> a >> m;
                int inv = modularInverse(a, m);
                if (inv != -1) {
                    cout << "Modular inverse of " << a << " mod " << m << " = " << inv << endl;
                    cout << "Verification: " << a << " * " << inv << " mod " << m << " = " << (a * inv) % m << endl;
                }
                break;
                
            case 5:
                long long base, exp, mod;
                cout << "Enter base, exponent, and modulus: ";
                cin >> base >> exp >> mod;
                cout << base << "^" << exp << " mod " << mod << " = " << fastPower(base, exp, mod) << endl;
                break;
                
            case 6:
                cout << "Enter number: ";
                cin >> n;
                cout << "Prime factorization of " << n << ": ";
                vector<pair<int, int>> factors = primeFactorization(n);
                for (auto factor : factors) {
                    cout << factor.first << "^" << factor.second << " ";
                }
                cout << endl;
                break;
                
            case 7:
                cout << "Enter number: ";
                cin >> n;
                cout << "Euler's Totient φ(" << n << ") = " << eulerTotient(n) << endl;
                break;
                
            case 8:
                cout << "Enter number to test Wilson's theorem: ";
                cin >> n;
                if (wilsonTheorem(n)) {
                    cout << n << " satisfies Wilson's theorem (is prime)" << endl;
                } else {
                    cout << n << " doesn't satisfy Wilson's theorem (not prime)" << endl;
                }
                break;
                
            case 0:
                cout << "Exiting..." << endl;
                return 0;
                
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
