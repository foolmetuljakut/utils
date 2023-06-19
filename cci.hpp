#include <cmath>
#include <map>
#include <functional>

#include <exception>
#include <sstream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

/* /home/sebastian/dev/mt-maffs/ */

class CCIException : public std::exception {
    std::string s;
public:
    CCIException(std::string descr) : s(descr) {}
    virtual const char* what() throw()
    {
        return s.c_str();
    }
};

template<typename T> class CCI {
    std::map<unsigned, vector<T>> ints;
    std::vector<T> conv;
    std::vector<unsigned> convn;

    T ai(T a, T b, unsigned N, double sN, std::function<T(T)> f) {
        conv.clear();
        convn.clear();

        T s = integrate(a, b, N, f);
        unsigned Np = N;
        for(unsigned i = 0; i < 1000; i++) {
            Np = (unsigned)(sN * (Np+1));
            T tmp = integrate(a, b, Np, f);

            conv.push_back(s > tmp ? s - tmp : tmp - s);
            convn.push_back(Np);

            if(conv.size() > 1) {
                T cs = *(--(--conv.end())),
                    ctmp = *((--conv.end()));
                if(ctmp > cs)
                    return s;
            }

            s = tmp;
        }
        return s;
    }
public:
    std::vector<T>& getconv() { return conv; }
    std::vector<unsigned>& getconvn() { return convn; }
    T integrate(T a, T b, unsigned N, std::function<T(T)> f) noexcept(false) {
        
        if(a == b || N == 0)
        {   
            std::stringstream s;
            s << "invalid parameters. (a=" << a << ",b=" << b << ",N=" << N << ")";
            throw CCIException(s.str());
        }

        vector<T> z;
        if(ints.find(N) == ints.end()) {
            z = vector<T>(N+1);
            for(unsigned j = 0; j <= N; j++){
                z[j] = 0;
                for(unsigned i = 0; i <= N; i++) {
                    T Dij = ((j == 0 || j == N) ? 1.0 : 2.0) / double(2*N) * cos(i * j * M_PI / N);
                    T Ii = (i == 0 || i == N ? 1.0 : 2.0) / (1.0 - double(i*i) * 4);
                    z[j] += Ii * Dij;
                }
            }
            ints[N] = z;
        }
        else {
            z = ints[N];
        }

        T c = (a + b) / 2, d = (b - a) / 2;
        T s = 0;
        for(unsigned i = 0; i <= N; i++) {
            s += z[i] * (f(c + d * cos(i * M_PI / (2*N))) + f(c - d * cos(i * M_PI / (2*N))));
        }
        if(std::isnan(s))
        {   
            std::stringstream s; 
            s << "calculation returned NAN. (a=" << a << ",b=" << b << ",N=" << N << ")";
            throw CCIException(s.str());
        }
        return s*d;
    }
    T simpleadi(T a, T b, unsigned N, std::function<T(T)> f) { // N' += 0.1 * N
        return ai(a, b, N, 1.1, f);
    }
};