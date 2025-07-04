#include <bits/stdc++.h>

using namespace std; 

//forward declaration
class VanEmdeBoas { public: VanEmdeBoas(int number_of_bits);};


/* Hashing table com Doubling/Having

Ideia: A Hash table terá um tamanho igual a uma potência de 2, suponha 2^k
O resultado então da função hash de n será (n mod 2^n).
Talvez não seja a melhor função Hash, porém estatisticamente os elementos estarão bem distribuidos

*/


class VeBExtensibleHash{

    public:

    vector<vector<pair<int, VanEmdeBoas*>>> buckets = {};
    int values_quantity = 0;
    int hash_size = 0;
    int number_of_bits;

    const float MAX_OCCUPANCY_RATE = 0.75;
    const float MIN_OCCUPANCY_RATE = 0.25;

    int HashFunction(int value){
        return value % hash_size;
    }

    void Doubling(){

        this->hash_size = 2*this->hash_size;
        this->buckets.resize(this->hash_size);

        for(int bucket_index = 0; bucket_index < hash_size/2; bucket_index++){
            for(int vec_index = 0; vec_index < this->buckets[bucket_index].size(); vec_index++){
                
                pair<int, VanEmdeBoas*> element = this->buckets[bucket_index][vec_index];
                if(HashFunction(get<int>(element)) != bucket_index){
                    this->buckets[bucket_index].erase(this->buckets[bucket_index].begin() + vec_index);
                    vec_index -= 1; //Volta uma casas
                    this->buckets[HashFunction(get<int>(element))].push_back(element);
                }

            }


        }


    };

    void Halfing(){

        this->hash_size = this->hash_size/2;

        for(int bucket_index = 0; bucket_index < 2*hash_size; bucket_index++){
            for(int vec_index = 0; vec_index < this->buckets[bucket_index].size(); vec_index++){
                
                pair<int, VanEmdeBoas*> element = this->buckets[bucket_index][vec_index];
                if(HashFunction(get<int>(element)) != bucket_index){
                    this->buckets[bucket_index].erase(this->buckets[bucket_index].begin() + vec_index);
                    vec_index -= 1; //Volta uma casas
                    this->buckets[HashFunction(get<int>(element))].push_back(element);
                }

            }
        }

        this->buckets.resize(this->hash_size);

    };

    void Rehash(){
        if((float)this->values_quantity > MAX_OCCUPANCY_RATE*(float)hash_size) Doubling();
        if((float)this->values_quantity < MIN_OCCUPANCY_RATE*(float)hash_size) Halfing();
    };



    VeBExtensibleHash(int number_of_bits){
        this->number_of_bits = number_of_bits;
    }

    //Retorna VanEmdeBoas associada ao valor value
    VanEmdeBoas* Search(int value){
        for(pair<int, VanEmdeBoas*> element : this->buckets[HashFunction(value)]){
            if(get<int>(element) == value) return get<VanEmdeBoas*>(element);
        }

        return nullptr; //Não encontrou o valor dentro da tabela
    }

    //Insere uma VanEmdeBoas na tabela e retorna seu endereço
    VanEmdeBoas* Insert(int value){

        if(hash_size == 0){
            hash_size = 1;
            Rehash();
        }

        VanEmdeBoas* result = Search(value);

        if(result != nullptr) return result;

        result = new VanEmdeBoas(number_of_bits);
        this->buckets[HashFunction(value)].push_back(pair<int, VanEmdeBoas*>(value, result));

        this->values_quantity++;

        Rehash();

        return result;

    }

    void Delete(int value){

        if(hash_size == 0) return;

        int index;
        int element_index = HashFunction(value);
        bool value_is_in_bucket = false;

        //inicializando o indice fora do for, assim o valor do indice é mantido após o termino do loop
        for(index = 0; index < this->buckets[element_index].size(); index++){
            pair<int, VanEmdeBoas*> element = this->buckets[element_index][index];
            if(get<int>(element) == value){ 
                break;
                value_is_in_bucket = true;
            }
        }

        if(!value_is_in_bucket) return;

        this->buckets[element_index].erase(this->buckets[element_index].begin() + index);

        this->values_quantity -= 1;

        Rehash();

    }

};