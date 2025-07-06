#include <bits/stdc++.h>
#include "hashing_table.hpp"

VanEmdeBoas::VanEmdeBoas(uint8_t number_of_bits){
        this->number_of_bits = number_of_bits;
        clusters = new VeBExtensibleHash(number_of_bits/2); //Começa vazio
        summary = nullptr; //É criado quando inserimos o primeiro elemento
                            // Caso esteja vazio novamente, ele será apagado e trocado por um nullptr
    }

void VanEmdeBoas::Delete(){


    for(vector<pair<Int32, VanEmdeBoas*>> bucket : clusters->buckets){
        for(pair<Int32, VanEmdeBoas*> element : bucket){
                get<VanEmdeBoas*>(element)->Delete();
        }
    }
    
    delete clusters;

    if(summary != nullptr){
        summary->Delete();
        delete summary;
    }
    
    delete this;
};

void VanEmdeBoas::Insert(Int32 value){
        if(is_empty){
            veb_min = value;
            veb_max = value;
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
        Int32 high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        Int32 low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Insert(high); //Se já estiver inserido, não insere um novo elemento

        child->Insert(low);

        if(child->veb_min == child->veb_max)
            summary->Insert(high);
    }

void VanEmdeBoas::Remove(Int32 value){
        if (veb_min == veb_max && veb_max == value){
            is_empty = true;
            return;
        }

        if(clusters->buckets.size() == 0){
            //Arvore só tem um elemento, o veb_min
            if(veb_min != value) return; //Elemento não está na arvore
        }
        

        if(value == veb_min){
            Int32 summary_high = (summary->veb_min << number_of_bits/2);
            Int32 next_cluster = summary->veb_min;
            veb_min = summary_high + clusters->Search(next_cluster)->veb_min;
            value = veb_min;
        }

        //Pegando os bits da metade direita
        Int32 high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        Int32 low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Search(high);

        if(child == nullptr) return;

        child->Remove(low);

        if(child->is_empty){
            summary->Remove(high);
            if(summary->is_empty){
                summary->Delete(); //Leva O(1), uma vez que summary não tem elementos 
                summary = nullptr;
            }

            clusters->Remove(high);
            child->Delete(); //Leva O(1), uma vez que child não tem elementos 

        }

        if(value == veb_max){
            if(summary == nullptr) veb_max = veb_min;
            else{
                Int32 summary_high = (summary->veb_max << number_of_bits/2);
                Int32 next_cluster = summary->veb_max;
                veb_max = summary_high + clusters->Search(next_cluster)->veb_max;
            }
        }
    }

Int32 VanEmdeBoas::Sucessor(Int32 value){
        

        if(value < veb_min) return veb_min;

        if(value >= veb_max) return INF;

        //Pegando os bits da metade direita
        Int32 high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        Int32 low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Search(high);

        if(child != nullptr and low < child->veb_max)
            return (high << (number_of_bits / 2)) + child->Sucessor(low);


        
        Int32 new_cluster_index = summary->Sucessor(high);

        VanEmdeBoas* new_child = clusters->Search(new_cluster_index); //Certamente retorna um valor não nulo por causa do summary
        
        return (new_cluster_index << (number_of_bits / 2)) + new_child->veb_min;

    }

Int32 VanEmdeBoas::Predecessor(Int32 value){

        if(value <= veb_min) return -INF;

        if(value > veb_max) return veb_max;

        //Pegando os bits da metade direita
        Int32 high = value >> (number_of_bits / 2);

        //Pegando os bits da metade esquerda
        Int32 low = value - (high << (number_of_bits / 2));

        VanEmdeBoas* child = clusters->Search(high);

        if(child != nullptr && high == 0 && low <= child->veb_min){
            return veb_min;
        }

        if(child != nullptr && low > child->veb_min){
            Int32 pred = child->Predecessor(low);
            
            if(pred == -INF) return (high << (number_of_bits / 2)) + child->veb_min;
            else return (high << (number_of_bits / 2)) + pred;
        }
        
        Int32 new_cluster_index = summary->Predecessor(high);
        cout<<new_cluster_index<<endl;
        VanEmdeBoas* new_child = clusters->Search(new_cluster_index); //Certamente retorna um valor não nulo por causa do summary
        cout<<new_child->veb_max<<endl;
        return (new_cluster_index << (number_of_bits / 2)) + new_child->veb_max;

    }

    //Retorna um vetor com o primeiro elemento sendo o elemento minimo
    //e o restante dos elementos são vetores que contém os valores dentro de cada clusters 

vector<vector<Int32>> VanEmdeBoas::Print(){
        vector<vector<Int32>> result;

        result.push_back({veb_min});

        if(veb_min == veb_max) return result;

        for(vector<pair<Int32, VanEmdeBoas*>> bucket : clusters->buckets){
            for(pair<Int32, VanEmdeBoas*> element : bucket){
                result.push_back({});
                vector<vector<Int32>> low_values = get<VanEmdeBoas*>(element)->Print();
                Int32 high = get<Int32>(element) << (number_of_bits / 2);
                
                for(vector<Int32> vec_values: low_values) for(Int32 value : vec_values){
                    result[result.size()-1].push_back(value + high);
                }

            }
        }

        return result;
    }

