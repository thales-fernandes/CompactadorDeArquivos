#ifndef NOHUFFMAN_
#define NOHUFFMAN_

#include <iostream>
#include <string>

using namespace std;

class No_Huffman
{
    public:
    string palavra_;
    int frequencia_;
    No_Huffman *esquerdo_;
    No_Huffman *direito_;

    No_Huffman(string valor_, int freq)
    {
        palavra_ = valor_;
        frequencia_ = freq;
        esquerdo_ = direito_ = nullptr;
    }
};

// Função de comparação para a fila de prioridade
struct Compara_No
{
    bool operator()(No_Huffman *a, No_Huffman *b)
    {
        return a->frequencia_ > b->frequencia_;
    }
};

#endif