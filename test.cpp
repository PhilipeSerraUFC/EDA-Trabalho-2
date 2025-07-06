#include <bits/stdc++.h>
#include "parser.hpp"
#include "int32.hpp"
using namespace std;

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

    cout << "---------" << endl;
    cout << Int32(32) + Int32(42) << endl;
    cout << INF + Int32(42) << endl;
    cout << (INF == -INF) << endl;
    cout << (Int32(32) == Int32(42)) << endl;
    cout << (Int32(42) == Int32(42)) << endl;
    cout << (Int32(42) == 42) << endl;
    cout << (Int32(42) == 32) << endl;
    cout << (42 == Int32(42)) << endl;
    cout << (Int32(42) + 32) << endl;
    cout << (32 + Int32(42)) << endl;
    cout << 14 + INF << endl;
    cout << -INF + 14 << endl;


}