#include <bits/stdc++.h>

using namespace std; 

//forward declaration
class VeBExtensibleHash;

//forward declaration
class VanEmdeBoas { 
    private:
        bool is_empty = true;

    public: 

        int number_of_bits;
        int veb_min;
        int veb_max;

        VeBExtensibleHash* clusters;
        VanEmdeBoas* summary;

        VanEmdeBoas(int);

        void Delete();

        void Insert(int);

        void Remove(int);

        int Sucessor(int);

        int Predecessor(int);

        vector<vector<int>> Print();
};


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
        buckets = {};
        
    }

    //Retorna VanEmdeBoas associada ao valor value
    VanEmdeBoas* Search(int value){
    
        if(buckets.size() == 0) return nullptr;
 
        for(pair<int, VanEmdeBoas*> element : this->buckets[HashFunction(value)]){

            if(get<int>(element) == value) return get<VanEmdeBoas*>(element);
        }

        return nullptr; //Não encontrou o valor dentro da tabela
    }

    //Insere uma VanEmdeBoas na tabela e retorna seu endereço
    VanEmdeBoas* Insert(int value){
        
        if(hash_size == 0){
            hash_size = 1;
            buckets.resize(1);
        }

        VanEmdeBoas* result = Search(value);
  
        if(result != nullptr) return result;

        result = new VanEmdeBoas(number_of_bits);

        this->buckets[HashFunction(value)].push_back(pair<int, VanEmdeBoas*>(value, result));

        this->values_quantity++;

        Rehash();


        return result;

    }

    void Remove(int value){

        if(hash_size == 0) return;

        int index;
        int element_index = HashFunction(value);
        bool value_is_in_bucket = false;

        //cout<<element_index<<endl;
        //cout<<value<<endl;

        //inicializando o indice fora do for, assim o valor do indice é mantido após o termino do loop
        for(index = 0; index < this->buckets[element_index].size(); index++){
            pair<int, VanEmdeBoas*> element = this->buckets[element_index][index];
            if(get<int>(element) == value){ 
                value_is_in_bucket = true;
                break;
            }
        }

        //cout<<value_is_in_bucket<<endl;
        //cout<<"-----"<<endl;

        if(!value_is_in_bucket) return;

        this->buckets[element_index].erase(this->buckets[element_index].begin() + index);

        this->values_quantity -= 1;

        Rehash();

    }

    void Print(){

        cout<<"----"<<endl;
        for(vector<pair<int, VanEmdeBoas*>> bucket : buckets){
            for(pair<int, VanEmdeBoas*> element : bucket){
                cout<<get<int>(element)<<" ";
            }

            cout<<"\n----"<<endl;
        }
    }

};