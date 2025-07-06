#include "include/parser.hpp"
#include "include/van_emde_boas.hpp"
#include "include/veb_extensible_hash.hpp"

using namespace std;

void SillyTests(){
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

void ExecuteProgram(string data_path){

    int number_of_bits = 32;
    vector<Operation> operations = ParserText(data_path);
    VanEmdeBoas* tree = new VanEmdeBoas(number_of_bits);



    OperateTree(tree, operations);
 
}

int main(int argc, char* argv[]){

    if(argc != 2){
        cerr << "parametro invalido para o programa" << endl;
        exit(1);
    }

    string data_path = argv[1];

    ExecuteProgram(data_path);

    return 0;
}