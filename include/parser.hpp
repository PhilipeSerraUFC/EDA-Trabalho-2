#ifndef PARSER_HPP
#define PARSER_HPP

#include "van_emde_boas.hpp"
#include <string>

extern const string out_path;


enum Command {
    /*Enumeração das possíveis operações na BST*/
    INC, REM, SUC, PRE, IMP
};

//Alias para facilitar a leitura do codigo
using Operation = tuple<Command,uint32_t>;

vector<string> SplitString(string&, char);

vector<Operation> ParserText(string);

void WriteText(string, string);

string VanEmdeBoasPrintToText(VanEmdeBoas*);

void OperateTree(VanEmdeBoas*, vector<Operation>, string);

#endif