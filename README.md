# Estruturas de Dados Avançadas - Árvore Van Emde Boas

Alunos:
Philipe Serra - 547874
Theo Araujo - 555910
Guilherme Galvão - 520402

# Documentação

Este programa implementa uma estrutura de dados Van Emde Boas Tree em C++ com suporte a operações de inserção, remoção, busca de sucessor e predecessor, além de impressão da estrutura.

## Estrutura do Projeto

```
projeto/
├── makefile
├── main.cpp
├── src/
│   ├── int32.cpp
│   ├── parser.cpp
│   ├── van_emde_boas.cpp
│   └── veb_extensible_hash.cpp
├── include/
│   ├── int32.hpp
│   ├── parser.hpp
│   ├── van_emde_boas.hpp
│   └── veb_extensible_hash.hpp
└── data/
    └── out.txt (gerado após execução)
```


## Como Executar o Programa

### Pré-requisitos

- Compilador C++ compatível com C++17 ou superior
- Sistema operacional Windows ou Unix/Linux
- Make instalado no sistema


### Passos para Execução

1. **Prepare o arquivo de entrada**: Crie um arquivo de texto contendo as operações que deseja executar. O arquivo pode ser colocado em qualquer diretório do sistema.
2. **Compile o programa**: Execute o comando no diretório raiz do projeto:

```bash
make
```

3. **Execute o programa**: Forneça o caminho do arquivo de entrada como parâmetro:

```bash
./main caminho/para/arquivo_entrada.txt
```

4. **Verifique o resultado**: Após a execução, os resultados das operações estarão disponíveis no arquivo `data/out.txt`.

### Comandos do Makefile

- `make` ou `make all`: Compila o projeto
- `make clean`: Remove arquivos compilados
- `make run`: Compila e executa o programa


### Formato do Arquivo de Entrada

O arquivo de entrada deve conter uma operação por linha, seguindo o formato:

- `INC <número>` - Inserir um número na estrutura
- `REM <número>` - Remover um número da estrutura
- `SUC <número>` - Encontrar o sucessor de um número
- `PRE <número>` - Encontrar o predecessor de um número
- `IMP` - Imprimir a estrutura atual


### Exemplo de Arquivo de Entrada

```
INC 5
INC 10
INC 3
SUC 5
PRE 10
IMP
REM 5
IMP
```


## Documentação dos Códigos

### **Int32 - Classe de Inteiros Estendidos**

A classe `Int32` é uma implementação customizada de inteiros de 32 bits que suporta valores infinitos positivos e negativos.

#### Características Principais:

- **Armazenamento**: Utiliza `uint32_t` para o valor numérico e flags booleanas para infinitos
- **Suporte a Infinitos**: Implementa `+INF` e `-INF` através das flags `is_pos_inf` e `is_neg_inf`
- **Operadores Sobrecarregados**: Implementa todos os operadores aritméticos, de comparação e bitwise


#### Funcionalidades Especiais:

- **Operações com Infinito**: Trata adequadamente operações matemáticas envolvendo infinitos
- **Validação de Operações**: Previne operações inválidas como módulo com infinito ou shifts infinitos
- **Conversões**: Suporte a conversão explícita para `int` e função `to_string` customizada


#### Implementação dos Operadores:

A classe implementa operadores aritméticos (`+`, `-`, `*`), bitwise (`<<`, `>>`, `^`), comparação (`==`, `!=`, `<`, `<=`, `>`, `>=`) e módulo (`%`). Cada operador trata casos especiais envolvendo infinitos, garantindo comportamento matemático correto.

### **Parser - Sistema de Entrada e Saída**

O módulo `parser` é responsável por processar arquivos de entrada e gerar arquivos de saída formatados.

#### Componentes Principais:

**Enumeração Command**: Define os tipos de operações suportadas:

- `INC` - Inserção
- `REM` - Remoção
- `SUC` - Sucessor
- `PRE` - Predecessor
- `IMP` - Impressão

**Função `ParserText`**:

- Lê o arquivo de entrada linha por linha usando `ifstream`
- Converte cada linha em uma tupla `Operation` contendo comando e chave
- Valida a sintaxe das operações e reporta erros com número da linha
- Retorna um vetor de operações para processamento

**Função `OperateTree`**:

- Executa sequencialmente todas as operações na árvore Van Emde Boas
- Gera log detalhado de cada operação executada
- Formata adequadamente os resultados de sucessor e predecessor
- Salva todos os resultados no arquivo `data/out.txt`

**Função `VanEmdeBoasPrintToText`**:

- Converte a estrutura hierárquica da árvore em formato texto legível
- Exibe o mínimo e os clusters organizados por índice 


### **Van Emde Boas Tree - Estrutura Principal**

A classe `VanEmdeBoas` implementa a estrutura de dados Van Emde Boas Tree, uma estrutura eficiente para operações em conjuntos de inteiros .

#### Atributos Fundamentais:

- **`number_of_bits`**: Define o universo de valores (2^number_of_bits)
- **`veb_min` e `veb_max`**: Armazenam os valores mínimo e máximo
- **`clusters`**: Hash table extensível contendo sub-árvores
- **`summary`**: Árvore auxiliar para navegação entre clusters
- **`is_empty`**: Flag indicando se a árvore está vazia


#### Operações Principais:

**Inserção (`Insert`)**:

- Complexidade: O(log log U) onde U é o universo
- Trata casos especiais de árvore vazia

**Remoção (`Remove`)**:

- Complexidade: O(log log U)
- Atualiza estruturas auxiliares quando clusters ficam vazios 
- Realiza limpeza automática de memória através do método `Delete`

**Sucessor (`Sucessor`)**:

- Complexidade: O(log log U)
- Retorna `INF` quando não há sucessor

**Predecessor (`Predecessor`)**:

- Complexidade: O(log log U)
- Retorna `-INF` quando não há predecessor 

#### Complexidade Espacial:

Utilizando a tabela de dispersão, usamos memória proporcional à quantidade de elementos na estrutura, ou seja, `O(n)` 


### **VeB Extensible Hash - Tabela Hash Dinâmica**

A classe `VeBExtensibleHash` implementa uma tabela hash que cresce e diminui dinamicamente conforme necessário .

#### Características Técnicas:

- **Função Hash**: Utiliza módulo com potências de 2 para distribuição uniforme
- **Redimensionamento Automático**: Dobra ou reduz pela metade baseado na taxa de ocupação
- **Taxas de Ocupação**: Mantém entre 25% e 75% de ocupação


#### Operações de Redimensionamento:

**Doubling**: Quando ocupação > 75%

- Dobra o tamanho da tabela (`hash_size = 2 * hash_size`)
- Redistribui todos os elementos conforme nova função hash 

**Halfing**: Quando ocupação < 25%

- Reduz o tamanho pela metade (`hash_size = hash_size / 2`)
- Reorganiza elementos para manter consistência 


#### Integração com Van Emde Boas:

- Armazena pares `(chave, ponteiro_para_VanEmdeBoas)` usando `vector<pair<Int32, VanEmdeBoas*>>`
- Permite acesso rápido a sub-árvores através do método `Search` 
- Gerencia automaticamente a memória das sub-estruturas


### **Makefile - Sistema de Compilação**

O Makefile fornece um sistema de compilação multiplataforma que:

#### Funcionalidades:

- **Detecção Automática de SO**: Adapta comandos para Windows e Unix/Linux
- **Compilação Incremental**: Recompila apenas arquivos modificados
- **Gestão de Dependências**: Monitora mudanças nos headers
- **Organização**: Separa arquivos objeto em diretório dedicado (`obj/`)


#### Flags de Compilação:

- `-std=c++17`: Utiliza padrão C++17
- `-Wall -Wextra`: Ativa warnings abrangentes
- `-I$(INCLUDE_DIR)`: Especifica diretório de headers

## Exemplo de Uso Completo

1. Crie um arquivo `entrada.txt`:
```
INC 16
INC 8
INC 24
SUC 8
PRE 24
IMP
```

2. Execute:
```bash
make
./main entrada.txt
```

3. Verifique o resultado em `data/out.txt`:
```
INC 16
INC 8
INC 24
SUC 8
16
PRE 24
16
IMP
Min: 8, C[^0]: 16, 24
```