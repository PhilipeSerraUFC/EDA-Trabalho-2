#include <bits/stdc++.h>
#include "van_emde_boas.hpp"

/*Funções para leitura do arquivo de texto de entrada e escrita do arquivo de saída*/

using namespace std;

const string out_path = "out.txt";

enum Command {
    /*Enumeração das possíveis operações na BST*/
    INC, REM, SUC, PRE, IMP
};

//Alias para facilitar a leitura do codigo
using Operation = tuple<Command,int>;

/*Funções auxiliares*/

vector<string> SplitString(string& str, char delimiter){
    
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;

}

/*Funções principais*/

vector<Operation> ParserText(string data_path){
    /*Função que lê o arquivo de entrada e retorna um vetor de triplas (Comando, Chave, Versão)
    
    No caso de Inclusao e remocao, onde não há versão, o campo de versão será igual a -1
    
    No caso da imprimir, onde não há chave, o campo de chave será igual a -1 */

    ifstream text(data_path);
    vector<Operation> result;

    if(!text.is_open()){
        cerr << "Erro ao abrir o arquivo.\n";
        exit(1);
        return result;
    }

    string line;

    int line_index = 0;

    while (getline(text, line)){

        Command command;
        int key;

        line_index ++;
        vector<string> operation_string = SplitString(line, ' ');

        if (operation_string[0] == "INC"){
            command = INC;
            key = stoi(operation_string[1]);
        }

        else if (operation_string[0] == "REM"){
            command = REM;
            key = stoi(operation_string[1]);
        }
        
        else if (operation_string[0] == "SUC"){
            command = SUC;
            key = stoi(operation_string[1]); 
        }

        else if (operation_string[0] == "PRE"){
            command = PRE;
            key = stoi(operation_string[1]); 
        }

        else if (operation_string[0] == "IMP"){
            command = IMP;
            key = -1; 
        }

        else {
            cerr << "Operacao Invalida na linha " << line_index << endl;
            exit(1);
        }

        Operation op = Operation(command, key);
        result.push_back(op);
    }

    text.close();

    return result;
}

void WriteText(string text){
    std::ofstream file(out_path); 

    if (file.is_open()) {
        file << text << "\n"; 
        
        file.close();

    } else {
        std::cerr << "Não foi possivel abrir o arquivo.\n";
    }

}

string VanEmdeBoasPrintToText(VanEmdeBoas* tree){

    vector<vector<int>> veb_print = tree->Print();

    if(veb_print.size() == 0) return "\n";

    string result;

    result.append("Min: ");
    result.append(to_string(veb_print[0][0]));

    if(veb_print.size() == 1){
        result.append("\n");
        return result;
    }
    
    result.append(", ");

    for(int vec_index = 1; vec_index < veb_print.size(); vec_index++){
 

        result.append("C[ ");
        result.append(to_string((veb_print[vec_index][0]) >> (tree->number_of_bits/2)));
        result.append("]:");

        for(int index = 0; index < veb_print[vec_index].size(); index++){
            result.append(" ");
            result.append(to_string(veb_print[vec_index][index]));
            result.append(", ");
        }

    }

    result.pop_back(); //Apaga o ultimo espaço desnecessário
    result.pop_back(); //e depois apaga a ultima virgula desnecessária

    result.append("\n");
    return result;
}

void OperateTree(VanEmdeBoas* tree, vector<Operation> operations){
    
    string text = "";

    for(Operation operation : operations){

        if(get<Command>(operation) == INC){
            tree->Insert(get<int>(operation));
            text.append("INC ");
            text.append(to_string(get<int>(operation)));
            text.append("\n");
        }

        if(get<Command>(operation) == REM){
            tree->Remove(get<int>(operation));
            text.append("REM ");
            text.append(to_string(get<int>(operation)));
            text.append("\n");
        }

        if(get<Command>(operation) == IMP){
            string dfs_str = VanEmdeBoasPrintToText(tree);
            text.append("IMP ");
            text.append("\n");
            text.append(dfs_str);
        } 

        if(get<Command>(operation) == SUC) {
            string succ_str = to_string(tree->Sucessor(get<int>(operation)));  
            text.append("SUC ");
            text.append(to_string(get<int>(operation)));
            text.append("\n");
            text.append(succ_str);
            text.append("\n");
        };

        if(get<Command>(operation) == PRE) {
            string pred_str = to_string(tree->Predecessor(get<int>(operation)));  
            text.append("SUC ");
            text.append(to_string(get<int>(operation)));
            text.append("\n");
            text.append(pred_str);
            text.append("\n");
        };

    }

    WriteText(text);

};










