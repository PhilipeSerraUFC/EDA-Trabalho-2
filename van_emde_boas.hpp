#include <bits/stdc++.h>
#include "hashing_table.hpp"
class VanEmdeBoas{

    public:
    
    int veb_min;
    int veb_max;

    VeBExtensibleHash* clusters;
    VanEmdeBoas* summary;

    VanEmdeBoas();

    void Insert(int value);

    void Remove(int value);

    int Sucessor(int value);

    int Predecessor(int value);

    //Retorna um vetor com o primeiro elemento sendo o elemento minimo
    //e o restante dos elementos são vetores de modo que o primeiro elemento
    //de cada vetor é o valor da chave do cluster e depois os valores dentro dos clusters 
    vector<vector<int>> Print();

}