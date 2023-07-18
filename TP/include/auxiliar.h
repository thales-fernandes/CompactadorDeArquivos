#ifndef AUXILIAR_
#define AUXILIAR_

#include <iostream>
#include "Dupla.h"
#include <string>

using namespace std;

// Função para verificar se uma palavra já existe no vetor de Duplas
template <typename T1, typename T2>
bool Palavra_Existe(const Dupla<T1, T2> *aux, size_t tamanho, const T1 &palavra_)
{
    for (size_t i = 0; i < tamanho; i++)
    {
        if (aux[i].primeiro_ == palavra_)
        {
            return true;
        }
    }
    return false;
}

// Atualiza a frequência de uma palavra no vetor de Duplas
template <typename T1, typename T2>
void Frequencia_Dupla(Dupla<T1, T2> *aux, size_t tamanho, const T1 &palavra_)
{
    for (size_t i = 0; i < tamanho; i++)
    {
        if (aux[i].primeiro_ == palavra_)
        {
            aux[i].segundo_ = T2(aux[i].segundo_ + 1);
            return;
        }
    }
    aux[tamanho] = Dupla<T1, T2>(palavra_, T2(1));
}

#endif