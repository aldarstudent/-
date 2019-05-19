#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>


template <typename T>
class Polynomial {
private:
    std::vector<T> pol;

    void zerodel(std::vector<T> &coef) {
        for (auto iter = coef.rbegin(); iter != coef.rend(); ++iter) {
            if (*iter == T(0)) {
                coef.pop_back();
            }
            else {
                break;
            }
        }
    }

public:
    Polynomial(const std::vector<T> &v) :pol(v) {
        zerodel(pol);
    }

    template <typename Iterator>
    Polynomial<T>(Iterator start, Iterator finish) {
        while (start != finish) {
            pol.push_back(*start++);
        }
        zerodel(pol);
    }

    Polynomial<T>(const T &num = T()) {
        pol.push_back(num);
        zerodel(pol);
    }

    T operator[] (size_t i) const {
        if (i >= pol.size()) {
            return T(0);
        }
        else {
            return pol[i];
        }
    }

    int Degree() const {
        if (pol.empty()) {
            return -1;
        }
        else {
            return static_cast<int>(pol.size()) - 1;
        }
    }

    bool operator == (const Polynomial<T> &other) const {
        if (pol.size() != other.pol.size()) {
            return false;
        }
        for (size_t i = 0; i != pol.size(); ++i) {
            if (pol[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator != (const Polynomial<T> &other) const {
        return !(*this == other);
    }

    bool operator ==(const T &num) {
        return *this == Polynomial<T>(num);
    }

    bool operator !=(const T &num) {
        return *this != Polynomial<T>(num);
    }

    Polynomial<T>& operator += (const Polynomial<T> &other) {
        pol.resize(std::max(other.pol.size(), pol.size()), T(0));
        for (size_t i = 0; i != std::min(pol.size(), other.pol.size()); ++i) {
            pol[i] += other.pol[i];
        }
        zerodel(pol);
        return *this;
    }

    Polynomial<T>& operator -= (const Polynomial<T> &other) {
        pol.resize(std::max(other.pol.size(), pol.size()), T(0));
        for (size_t i = 0; i != std::min(pol.size(), other.pol.size()); ++i) {
            pol[i] -= other.pol[i];
        }
        zerodel(pol);
        return *this;
    }

    Polynomial<T>& operator +=(const T &num) {
        *this += Polynomial<T>(num);
        zerodel(pol);
        return *this;
    }

    Polynomial<T>& operator -=(const T &num) {
        *this -= Polynomial<T>(num);
        zerodel(pol);
        return *this;
    }

    Polynomial<T>& operator *=(const Polynomial<T> &other) {
        std::vector<T> temp(pol.size() + other.pol.size(), T(0));
        for (size_t i = 0; i != pol.size(); ++i) {
            for (size_t j = 0; j != other.pol.size(); ++j) {
                temp[i + j] += pol[i] * other.pol[j];
            }
        }
        zerodel(temp);
        *this = Polynomial(temp);
        return *this;
    }

    Polynomial<T>& operator *=(const T &num) {
        for (size_t i = 0; i != pol.size(); ++i) {
            pol[i] *= num;
        }
        zerodel(pol);
        return *this;
    }

    T operator () (const T &point) const {
        T ans = T(0);
        for (auto iter = pol.rbegin(); iter != pol.rend(); ++iter) {
            ans += *iter;
            if ((iter + 1) != pol.rend()) {
                ans *= point;
            }
        }
        return ans;
    }

    friend std::ostream& operator << (std::ostream& out, const Polynomial<T> &Pol) {
        bool flag = false;
        unsigned long long degree = Pol.pol.size() - 1;
        for (auto iter = Pol.pol.rbegin(); iter != Pol.pol.rend(); ++iter, --degree) {
            T coef = *iter;
            if (coef != T(0)) {
                if (coef > T(0) && flag) {
                    out << '+';
                }
                flag = true;
                if (degree == 0) {
                    out << coef;
                }
                else if (coef == T(1)) {
                    out << 'x';
                }
                else if (coef == T(-1)) {
                    out << "-x";
                }
                else {
                    out << coef << "*x";
                }
                if (degree > 1) {
                    out << '^' << degree;
                }
            }
        }
        if (Pol.pol.size() == 0) {
            out << 0;
        }
        return out;
    }

    friend Polynomial<T> operator&(const Polynomial<T> &first, const Polynomial<T> &second) {
        Polynomial<T> comp(first.pol.at(0));
        Polynomial<T> copy(second.pol);
        size_t iter = 1;
        for (size_t degree = 1; degree != first.pol.size(); ++degree) {
            for (; iter != degree; ++iter) {
                copy *= second;
            }
            comp += copy * first.pol[degree];
        }
        return comp;
    }

    Polynomial<T> &operator /= (const Polynomial<T> &other) {
        Polynomial<T> priv(T(0));
        while (pol.size() >= other.pol.size()) {
            T coef = pol.back() / other.pol.back();
            size_t degree = pol.size() - other.pol.size();
            std::vector<T> div(degree + 1);
            div.back() = coef;
            Polynomial<T> temp(div);
            *this -= other * temp;
            priv += temp;
        }
        pol = priv.pol;
        return *this;
    }

    Polynomial<T> &operator %= (const Polynomial<T> &other) {
        Polynomial<T> quotient = *this / other;
        *this -= other * quotient;
        return *this;
    }

    friend Polynomial<T> operator,(const Polynomial<T> &first, const Polynomial<T> &second) {
        Polynomial<T> gcd = first;
        Polynomial<T> copy = second;
        while (copy.pol.size() != 0) {
            gcd %= copy;
            std::swap(gcd, copy);
        }
        if (gcd.pol.size() != 0) {
            Polynomial<T> temp(gcd[gcd.pol.size() - 1]);
            gcd /= temp;
        }
        return gcd;
    }

    auto begin() const {
        return pol.begin();
    }

    auto end() const {
        return pol.end();
    }
};

template <typename T>
Polynomial<T> operator *(Polynomial<T> first, const Polynomial<T> &second) {
    return first *= second;
}

template <typename T>
Polynomial<T> operator +(Polynomial<T> first, const Polynomial<T> &second) {
    return first += second;
}

template <typename T>
Polynomial<T> operator -(Polynomial<T> first, const Polynomial<T> &second) {
    return first -= second;
}

template<typename T>
Polynomial<T> operator /(const Polynomial<T> &first, const Polynomial<T> &second) {
    auto copy = first;
    copy /= second;
    return copy;
}

template<typename T>
Polynomial<T> operator %(const Polynomial<T> &first, const Polynomial<T> &second) {
    auto copy = first;
    copy %= second;
    return copy;
}

template <typename T>
Polynomial<T> operator +(Polynomial<T> Poly, const T &num) {
    return Poly += Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator +(const T &num, Polynomial<T> Poly) {
    return Poly += Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator -(Polynomial<T> Poly, const T &num) {
    return Poly -= Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator -(const T &num, Polynomial<T> Poly) {
    return Polynomial<T>(num) -= Poly;
}

template <typename T>
Polynomial<T> operator *(Polynomial<T> Poly, const T &num) {
    return  Poly *= Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator *(const T &num, Polynomial<T> Poly) {
    return  Poly *= Polynomial<T>(num);
}
