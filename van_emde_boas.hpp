#include <bits/stdc++.h>
#include "hashing_table.hpp"
#define INF 4294967296
class VanEmdeBoas{

    bool is_empty = true;


    public:
    
    int number_of_bits;
    int veb_min;
    int veb_max;


    VeBExtensibleHash* clusters;
    VanEmdeBoas* summary;

    VanEmdeBoas(int number_of_bits){
        this->number_of_bits = number_of_bits;
        clusters = new VeBExtensibleHash(number_of_bits); //Começa vazio
        summary = nullptr; //É criado quando inserimos o primeiro elemento
    }

    void Insert(int value){
        if(is_empty){
            veb_min = value;
            veb_min = value;
            is_empty = false;
            return;
        }

        if(veb_min == value || veb_max == value) return; //Já está inserido

        //O primeiro elemento sera inserido
        if(summary == nullptr) summary = new VanEmdeBoas(number_of_bits / 2);

        if(value < veb_min){
            //Swap de Value e veb_min usando Xor
            value = value ^ veb_min;
            veb_min = value ^ veb_min;
            value = value ^ veb_min;
        }

        if(value > veb_max) veb_max = value;

        //Pegando os bits da metade direita
        int high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        int low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Insert(high); //Se já estiver inserido, não insere um novo elemento
        child->Insert(low);

        if(child->veb_min == child->veb_max)
            summary->Insert(high);

    }

    void Remove(int value){

    }

    int Sucessor(int value){
        if(value < veb_min) return veb_min;

        if(value >= veb_max) return;
    }

    int Predecessor(int value){

    }

    //Retorna um vetor com o primeiro elemento sendo o elemento minimo
    //e o restante dos elementos são vetores de modo que o primeiro elemento
    //de cada vetor é o valor da chave do cluster e depois os valores dentro dos clusters 
    vector<vector<int>> Print();

};