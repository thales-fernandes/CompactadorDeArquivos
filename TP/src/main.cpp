#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <cstring>
#include "MeuVector.h"
#include "No_Huffman.h"
#include "Dupla.h"
#include "Codifica_Bits.h"
#include "Arvore_Huffman.h"
#include "auxiliar.h"

using namespace std;

// Compacta o arquivo de entrada usando a tabela de códigos de Huffman
void Compactar(const string &arq_entrada, const string &arq_saida)
{
    ifstream stream_entrada(arq_entrada);
    if (!stream_entrada.is_open())
    {   // Erro de leitura de arquivo
        cout << "O arquivo especificado para leitura não existe." << endl;
        exit(1);
    }
    ofstream stream_saida(arq_saida, ios::binary);

    // Contagem das frequências das palavras
    const size_t max_tam = 50000; // Tamanho máximo da tabela de frequência
    Dupla<string, int> tabela_frequencia[max_tam];
    memset(tabela_frequencia, 0, sizeof(tabela_frequencia));
    size_t tabelafreq_tam = 0;

    string palavra_;
    while (stream_entrada >> palavra_)
    {
        if (Palavra_Existe(tabela_frequencia, tabelafreq_tam, palavra_))
        {
            Frequencia_Dupla(tabela_frequencia, tabelafreq_tam, palavra_);
        }
        else
        {
            tabela_frequencia[tabelafreq_tam] = Dupla<string, int>(palavra_, 1);
            tabelafreq_tam++;
        }
    }

    // Constrói a árvore de Huffman
    No_Huffman *raiz = Arvore_Huffman(tabela_frequencia, tabelafreq_tam);

    // Gera a tabela de códigos de Huffman
    const size_t MaxCodes = 50000; // Tamanho máximo da tabela de códigos
    Dupla<string, string> tabela_bits[MaxCodes];
    size_t tabelabits_tam = 0;
    Codifica_Bits(raiz, "", tabela_bits, tabelabits_tam);

    // Escreve a tabela de códigos no arquivo de saída
    for (size_t i = 0; i < tabelabits_tam; i++)
    {
        stream_saida << tabela_bits[i].primeiro_ << " " << tabela_bits[i].segundo_ << endl;
    }
    stream_saida << "+=-=fim" << endl; // Marca o fim da tabela de códigos

    // Volta para o início do arquivo de entrada
    stream_entrada.clear();
    stream_entrada.seekg(0);

    // Compacta as palavras e escreve no arquivo de saída
    string Buffer_;
    Buffer_.reserve(8); // Tamanho máximo de um byte

    while (stream_entrada >> palavra_)
    {
        string bits_;
        for (size_t i = 0; i < tabelabits_tam; i++)
        {
            if (tabela_bits[i].primeiro_ == palavra_)
            {
                bits_ = tabela_bits[i].segundo_;
                break;
            }
        }

        // Concatena os bits no buffer comprimido
        Buffer_ += bits_;

        // Enquanto o buffer contiver 8 bits (1 byte), escreve no arquivo
        while (Buffer_.length() >= 8)
        {
            // Obtém os primeiros 8 bits do buffer
            string byte = Buffer_.substr(0, 8);

            // Converte a sequência de bits em um caractere novamente
            char char_comprimido = static_cast<char>(stoi(byte, nullptr, 2));

            // Escreve o caractere comprimido no arquivo binário
            stream_saida.put(char_comprimido);

            // Remove os 8 primeiros bits do buffer
            Buffer_ = Buffer_.substr(8);
        }
    }

    // Se ainda houver bits remanescentes no buffer, escreve-os no arquivo
    if (!Buffer_.empty())
    {
        // Completa o último byte com zeros à direita
        Buffer_.append(8 - Buffer_.length(), '0');

        // Converte a sequência de bits em um caractere novamente
        char char_comprimido = static_cast<char>(stoi(Buffer_, nullptr, 2));

        // Escreve o último caractere comprimido no arquivo
        stream_saida.put(char_comprimido);
    }

    stream_entrada.close();
    stream_saida.close();
}

// Descompacta o arquivo de entrada usando a tabela de códigos de Huffman
void Descompactar(const string &arq_entrada, const string &arq_saida)
{
    ifstream stream_entrada(arq_entrada, ios::binary);
    if (!stream_entrada.is_open())
    {   // Erro de leitura de arquivo
        cout << "O arquivo especificado para leitura não existe." << endl;
        exit(1);
    }
    ofstream stream_saida(arq_saida);

    // Lê a tabela de códigos do arquivo de entrada
    const size_t MaxCodes = 50000; // Tamanho máximo da tabela de códigos
    Dupla<string, string> tabela_bits[MaxCodes];
    size_t tabelabits_tam = 0;

    string linha_;

    while (getline(stream_entrada, linha_) && linha_ != "+=-=fim")
    {
        if (!linha_.empty())
        {
            size_t spacePos = linha_.find(' ');
            string palavra_ = linha_.substr(0, spacePos);
            string bits_ = linha_.substr(spacePos + 1);
            tabela_bits[tabelabits_tam++] = Dupla<string, string>(bits_, palavra_);
        }
    }

    // Lê o conteúdo comprimido do arquivo
    string Buffer_;
    char char_comprim;

    while (stream_entrada.get(char_comprim))
    {
        Buffer_ += bitset<8>(char_comprim).to_string();
    }

    // Remove os bits extras adicionados na compressão
    size_t tam_resto = Buffer_.back() - '0';
    Buffer_ = Buffer_.substr(0, Buffer_.length() - tam_resto);

    // Escreve o texto descompactado no arquivo de saída
    string texto_descompactado;

    for (char bit : Buffer_)
    {
        texto_descompactado += bit;

        for (size_t i = 0; i < tabelabits_tam; i++)
        {
            if (tabela_bits[i].primeiro_ == texto_descompactado)
            {
                string palavra_descompactada = tabela_bits[i].segundo_;
                stream_saida << palavra_descompactada << " ";
                texto_descompactado = "";
                break;
            }
        }
    }

    stream_entrada.close();
    stream_saida.close();
}

int main(int argc, char *argv[])
{
    if (argc > 4 || argc < 4)
    {
        cout << "Comando incorreto no terminal!" << endl;
        return 0;
    }

    string arq_entrada = argv[1];
    string arq_saida = argv[2];
    string operacao_ = argv[3];

    if (operacao_ == "-c")
    {
        Compactar(arq_entrada, arq_saida);
        cout << "Arquivo de entrada compactado!" << endl;
    }
    else if (operacao_ == "-d")
    {
        Descompactar(arq_entrada, arq_saida);
        cout << "Arquivo de entrada descompactado!" << endl;
    }
    else
    {
        cout << "Operação inválida! Use -c para compactar ou -d para descompactar." << endl;
        return 0;
    }

    return 0;
}