#include <bits/stdc++.h>
#include "parser.hpp"
using namespace std;

int inf(){ return INFINITY; }

int main(){
    VeBExtensibleHash* hash = new VeBExtensibleHash(32);

    hash->Insert(0);
    hash->Insert(1);
    hash->Insert(2);
    hash->Insert(3);
    hash->Insert(8);
    hash->Print();

    hash->Remove(1);

    hash->Remove(3);

    hash->Print();

    hash->Remove(0);

    hash->Remove(8);

    hash->Print();


}