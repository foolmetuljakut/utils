#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <boost/timer.hpp>
#include <boost/filesystem.hpp>

// neat little program that tries to find as many primes as possible
// in as little time as possible
// convention: return 0 if n's a prime

bool check0(unsigned long long n) {
    bool divided = false;
    double s = std::sqrt(n);
    for(unsigned long long i = 2; (double)i <= s; i++)
        if(n % i == 0) {
            divided = true; 
            break;
        }
    return divided;
}

bool check1(std::vector<unsigned long long>& primes, unsigned long long n) {
    bool divided = false;
    double s = std::sqrt(n);
    for(auto& p : primes) {
        if(p > s)
            break;
        if(n % p == 0) {
            divided = true; 
            break;
        }
    }
    return divided;
}

int main0(int argc, char **argv) {
    std::vector<unsigned long long> primes;
    primes.push_back(2);

    boost::timer t;
    for(unsigned long long n = 3; n < 1e6; n += 2) {
        if(!check1(primes, n))
            primes.push_back(n);
    }
    double dt = t.elapsed();
    std::cout << "dt = " << dt << "s\n" 
            << " (#" << (primes.size()-1) << ": " << primes.back() << ")\n";

    return 0;
}

int main(int argc, char **argv) {

    std::vector<unsigned long long> primesinpi;
    std::vector<unsigned long long> primes;
    primes.push_back(2);

    unsigned long long checkeduntil = 3;

    std::string digits;
    boost::filesystem::ifstream fsh("etc/pi.txt");
    fsh >> digits;

    boost::timer t;
    for(unsigned i = 2; i < digits.size()-8; i++) {
        unsigned long long n = std::stoull(digits.substr(i, 8));

        if(n > checkeduntil) {
            std::cout << "[" << i << "] enlarging prime buffer to check...";
            double s = std::sqrt(n);
            for(unsigned long long l = checkeduntil; l < s; l += 2) {
                if(!check1(primes, l))
                    primes.push_back(l);
                if(l % (int)(0.1*s-1) == 0)
                    std::cout << ".";
            }
            checkeduntil = ( n % 2 == 1) ? n : (n+1); 
            std::cout << " increased to " << checkeduntil << "\n";
        }

        if(!check1(primes, n)) {
            std::cout << n << "\n";
            primes.insert(std::upper_bound(primes.begin(), primes.end(), n), n);
            primesinpi.push_back(n);
        }       
    }
    double dt = t.elapsed();
    std::cout << "dt = " << dt << "s in total, " << primes.size() << " numbers in total\n";

    boost::filesystem::ofstream pfs("etc/primes.txt");
    for(auto& p : primesinpi)
        pfs << p << std::endl;

    return 0;
}