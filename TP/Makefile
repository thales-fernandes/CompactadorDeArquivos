# Variáveis de diretórios
BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Compilador e opções
CXX = g++

# Arquivos de código fonte
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Nome do executável
EXECUTABLE = $(BIN_DIR)/tp

# Argumentos digitados pelo usuário
ARG1 = $(word 1, $(ARGS))
ARG2 = $(word 2, $(ARGS))
FLAG = $(word 3, $(ARGS))

# Regras de compilação
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Regra de execução
run: all
	@./$(EXECUTABLE) $(ARG1) $(ARG2) $(FLAG)
