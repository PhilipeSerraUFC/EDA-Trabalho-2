#include "include/parser.hpp"
#include "include/van_emde_boas.hpp"
#include "include/veb_extensible_hash.hpp"
#include <fstream>

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

void ExecuteProgram(string data_path, string out_path = out_path){

    int number_of_bits = 32;
    vector<Operation> operations = ParserText(data_path);
    VanEmdeBoas* tree = new VanEmdeBoas(number_of_bits);



    OperateTree(tree, operations, out_path);
 
}

/*
void Tests(){

    int ok = 0;
    for(int i = 0; i< 320; i++){
        string data_path = "tests/in-" + to_string(i) + ".txt";
        string out_path = "tests/out-"+ to_string(i) + ".txt";
        string out_in_path = "tests/out-in-"+ to_string(i) + ".txt";
        ExecuteProgram(data_path, out_path);


        ifstream out_text(out_path);
        ifstream out_in_text(out_in_path);
        string out_line;
        string out_in_line;
        int index = 0;
        bool not_ok = false;
        while(getline(out_text, out_line) && !not_ok){
            index++;
            getline(out_in_text, out_in_line);

            if(out_line == "-INF" || out_line == "INF" || out_line == ""){
                out_line = "None";
            }

            if(out_line != out_in_line){
                if(out_in_line != ""){
                    cerr <<"Erro no teste "<<i<<"Na linha "<<index<<"\n";
                    not_ok = true;
                    break;
                }
            }
        }

        if(!not_ok) ok++;

    }

    cout<<"Tudo ok!"<<ok<<" / "<<320<<endl;

}
*/

int main(int argc, char* argv[]){

    if(argc != 2){
        cerr << "parametro invalido para o programa" << endl;
        exit(1);
    }

    string data_path = argv[1];

    ExecuteProgram(data_path);

    //Tests();

    return 0;
}