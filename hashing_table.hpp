#include <bits/stdc++.h>

using namespace std; 

//forward declaration
class VanEmdeBoas { public: VanEmdeBoas()};


/* Hashing table com Doubling/Having

Ideia: A Hash table terá um tamanho igual a uma potência de 2, suponha 2^k
O resultado então da função hash de n será (n mod 2^n).
Talvez não seja a melhor função Hash, porém estatisticamente os elementos estarão bem distribuidos

*/

using Bucket = vector<pair<int, VanEmdeBoas*>>;

class ExtensibleHash{

    vector<Bucket> buckets = {};
    int values_quantity = 0;
    int hash_size = 0;

    int HashFunction(int value){
        return value % this->hash_size;
    }

    void Doubling();

    void Halfing();

    void Rehash(){
        if((float)this->values_quantity > 0.75*(float)hash_size) Doubling();
        if((float)this->values_quantity < 0.75*(float)hash_size) Halfing();
    };

    public:

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

        result = new VanEmdeBoas();
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

    }

};