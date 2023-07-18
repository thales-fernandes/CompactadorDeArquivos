#ifndef ARVOREHUFFMAN_
#define ARVOREHUFFMAN_

#include <iostream>
#include <string>
#include "MeuVector.h"
#include "Dupla.h"

using namespace std;
//Cria a árvore de huffman
No_Huffman *Arvore_Huffman(Dupla<string, int> *tabela_frequencia, size_t tamanho)
{
    MeuVector arvore_vec;

    for (size_t i = 0; i < tamanho; i++)
    {   // insere os nós de huffman dentro do MeuVectir
        arvore_vec.Insere(new No_Huffman(tabela_frequencia[i].primeiro_, tabela_frequencia[i].segundo_));
    }

    while (arvore_vec.tamanho() > 1)
    {   // Combina os nós de menor frequência até sobrar apenas o nó raiz
        No_Huffman *esquerdo_ = arvore_vec.Frente_();
        arvore_vec.Remove();
        No_Huffman *direito_ = arvore_vec.Frente_();
        arvore_vec.Remove();

        No_Huffman *newNode = new No_Huffman("$", esquerdo_->frequencia_ + direito_->frequencia_);
        newNode->esquerdo_ = esquerdo_;
        newNode->direito_ = direito_;

        arvore_vec.Insere(newNode);
    }

    return arvore_vec.Frente_();
}

#endif