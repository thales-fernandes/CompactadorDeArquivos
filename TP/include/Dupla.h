#ifndef DUPLA_
#define DUPLA_

#include <iostream>

using namespace std;

template <typename T1, typename T2>
class Dupla
{
public:
    T1 primeiro_;
    T2 segundo_;

    Dupla() : primeiro_(), segundo_() {}

    Dupla(const T1 &f, const T2 &s) : primeiro_(f), segundo_(s) {}

    template <typename U1, typename U2>
    Dupla(const Dupla<U1, U2> &auxiliar) : primeiro_(auxiliar.primeiro_), segundo_(auxiliar.segundo_) {}

    Dupla &operator=(const Dupla &auxiliar)
    {
        if (this != &auxiliar)
        {
            primeiro_ = auxiliar.primeiro_;
            segundo_ = auxiliar.segundo_;
        }
        return *this;
    }

    template <typename U1, typename U2>
    Dupla &operator=(const Dupla<U1, U2> &auxiliar)
    {
        primeiro_ = auxiliar.primeiro_;
        segundo_ = auxiliar.segundo_;
        return *this;
    }
};

#endif