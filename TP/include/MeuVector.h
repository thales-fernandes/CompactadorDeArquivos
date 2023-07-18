#ifndef MEUVECTOR_
#define MEUVECTOR_

#include <iostream>
#include <algorithm>
#include "No_Huffman.h"

using namespace std;

class MeuVector
{
public:
    MeuVector() : vetor_(nullptr), tam_vetor(0), cap_vetor(0)
    {
        vetor_ = new No_Huffman *[cap_vetor];
    }

    ~MeuVector()
    {
        delete[] vetor_;
    }

    void Insere(No_Huffman *node)
    {
        if (tam_vetor == cap_vetor)
        {
            Aumentar_cap();
        }

        vetor_[tam_vetor++] = node;
        push_heap(vetor_, vetor_ + tam_vetor, compara_);
    }

    No_Huffman *Frente_()
    {
        return vetor_[0];
    }

    void Remove()
    {
        pop_heap(vetor_, vetor_ + tam_vetor, compara_);
        tam_vetor--;
    }

    bool Vazio() const
    {
        return tam_vetor == 0;
    }

    size_t tamanho() const
    {
        return tam_vetor;
    }

private:
    No_Huffman **vetor_;
    size_t tam_vetor;
    size_t cap_vetor;
    Compara_No compara_;

    void Aumentar_cap()
    {
        size_t cap_novovetor = (cap_vetor == 0) ? 1 : cap_vetor * 2;
        No_Huffman **novovetor_ = new No_Huffman *[cap_novovetor];

        for (size_t i = 0; i < tam_vetor; i++)
        {
            novovetor_[i] = vetor_[i];
        }

        delete[] vetor_;
        vetor_ = novovetor_;
        cap_vetor = cap_novovetor;
    }
};

#endif
