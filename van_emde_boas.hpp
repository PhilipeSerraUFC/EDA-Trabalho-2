#include <bits/stdc++.h>
#include "hashing_table.hpp"



VanEmdeBoas::VanEmdeBoas(int number_of_bits){
        this->number_of_bits = number_of_bits;
        clusters = new VeBExtensibleHash(number_of_bits/2); //Começa vazio
        summary = nullptr; //É criado quando inserimos o primeiro elemento
                            // Caso esteja vazio novamente, ele será apagado e trocado por um nullptr
    }

void VanEmdeBoas::Delete(){};

void VanEmdeBoas::Insert(int value){
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

void VanEmdeBoas::Remove(int value){
        if (veb_min == veb_max && veb_max == value){
            is_empty = true;
            return;
        }

        if(value == veb_min){
            int summary_high = (summary->veb_min << number_of_bits/2);
            int next_cluster = summary->veb_min;
            veb_min = summary_high + clusters->Search(next_cluster)->veb_min;
            value = veb_min;
        }

        //Pegando os bits da metade direita
        int high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        int low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Search(high);

        child->Remove(low);

        if(child->is_empty){
            summary->Remove(high);
            if(summary->is_empty){
                summary->Delete();
                summary = nullptr;
            }
        }

        if(value == veb_max){
            if(summary == nullptr) veb_max = veb_min;
            else{
                int summary_high = (summary->veb_max << number_of_bits/2);
                int next_cluster = summary->veb_max;
                veb_max = summary_high + clusters->Search(next_cluster)->veb_max;
            }
        }
    }

int VanEmdeBoas::Sucessor(int value){
        if(value < veb_min) return veb_min;

        if(value >= veb_max) return INFINITY;

        //Pegando os bits da metade direita
        int high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        int low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Search(high);

        if(child != nullptr and low < child->veb_max)
            return (high << (number_of_bits / 2)) + child->Sucessor(low);

        int new_cluster_index = summary->Sucessor(high);

        VanEmdeBoas* new_child = clusters->Search(new_cluster_index); //Certamente retorna um valor não nulo por causa do summary
        
        return (new_cluster_index << (number_of_bits / 2)) + new_child->veb_min;

    }

int VanEmdeBoas::Predecessor(int value){

        if(value < veb_min) return -INFINITY;

        if(value >= veb_max) return veb_max;

        //Pegando os bits da metade direita
        int high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        int low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Search(high);

        if(child != nullptr and low > child->veb_min){
            int pred = child->Predecessor(low);
            if(pred == -INFINITY) return (high << (number_of_bits / 2)) + child->veb_min;
            else return (high << (number_of_bits / 2)) + pred;
        }

        int new_cluster_index = summary->Predecessor(high);

        VanEmdeBoas* new_child = clusters->Search(new_cluster_index); //Certamente retorna um valor não nulo por causa do summary
        
        return (new_cluster_index << (number_of_bits / 2)) + new_child->veb_max;

    }

    //Retorna um vetor com o primeiro elemento sendo o elemento minimo
    //e o restante dos elementos são vetores que contém os valores dentro de cada clusters 

vector<vector<int>> VanEmdeBoas::Print(){
        vector<vector<int>> result;

        result.push_back({veb_min});

        if(veb_min == veb_max) return result;

        for(vector<pair<int, VanEmdeBoas*>> bucket : clusters->buckets){
            for(pair<int, VanEmdeBoas*> element : bucket){
                result.push_back({});
                vector<vector<int>> low_values = get<VanEmdeBoas*>(element)->Print();
                int high = get<int>(element) << (number_of_bits / 2);
                
                for(vector<int> vec_values: low_values) for(int value : vec_values){
                    result[result.size()-1].push_back(value + high);
                }

            }
        }

        return result;
    }

