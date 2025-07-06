# Nome do executável
TARGET = main

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCLUDE_DIR)
LDFLAGS = 

# Detectar sistema operacional
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = del /Q
    MKDIR = if not exist "$(1)" mkdir "$(1)"
    RMDIR = rmdir /S /Q $(OBJ_DIR) 2>nul || true
else
    RM = rm -f
    MKDIR = mkdir -p $(1)
    RMDIR = rm -rf $(OBJ_DIR)
endif

# Arquivos fonte
SOURCES = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.hpp)  # Para dependências
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIRS = $(sort $(dir $(OBJECTS)))

# Regra principal
all: $(TARGET)

# Criar executável
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilar com dependência dos headers
$(OBJ_DIR)/%.o: %.cpp $(HEADERS) | $(OBJ_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar diretórios
$(OBJ_DIRS):
	$(call MKDIR,$@)

# Limpeza
clean:
	$(RM) $(TARGET)
	$(RMDIR)

# Executar
args = $(filter-out $@,$(MAKECMDGOALS))

run: $(TARGET)
	./$(TARGET) $(args)

%:
    @:

.PHONY: all clean run
