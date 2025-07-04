#include "parser.hpp"

using namespace std;

int main(){

    string data_path;

    cout << "Insira o caminho do arquivo de entrada: ";
    cin >> data_path;

    vector<Operation> operations = ParserText(data_path);
    VanEmdeBoas* tree = new VanEmdeBoas();

    OperateTree(tree, operations);

    cout<<"Operacoes na arvore realizada, veja o arquivo out.txt";
    return 0;

}