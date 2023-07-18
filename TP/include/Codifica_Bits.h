#ifndef CODIFICABITS_
#define CODIFICABITS_

#include <iostream>
#include <string>
#include "No_Huffman.h"
#include "Dupla.h"

using namespace std;
// Cria um mapeamento das palavras para bits 0 ou 1
void Codifica_Bits(No_Huffman *raiz, string bits_, Dupla<string, string> *tabela_bits, size_t &tabelabits_tam)
{   // se for nó folha, adiciona o par de valores dentro do vetor de Dupla
    if (raiz->esquerdo_ == nullptr && raiz->direito_ == nullptr)
    {
        tabela_bits[tabelabits_tam++] = Dupla<string, string>(raiz->palavra_, bits_);
        return;
    }
    // se for chamada recursivamente para um nó esquerdo, adiciona um bit 0 à string da palavra em questão
    Codifica_Bits(raiz->esquerdo_, bits_ + "0", tabela_bits, tabelabits_tam);
    // se for chamada recursivamente para um nó direito, adiciona um bit 1 à string da palavra em questão
    Codifica_Bits(raiz->direito_, bits_ + "1", tabela_bits, tabelabits_tam);
}

#endif