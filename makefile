# Variabili del compilatore
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Iinclude -g

# Cartelle
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# File sorgenti e oggetti
# Includiamo main.cpp e tutti i .cpp dentro src/
SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
# Trasformiamo i nomi dei .cpp in .o dentro la cartella obj/
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# Nome dell'eseguibile
TARGET = MyCompressor

# Regola principale
all: $(OBJ_DIR) $(TARGET)

# Creazione dell'eseguibile
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilazione dei file .o da main.cpp
$(OBJ_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilazione dei file .o dalla cartella src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creazione della cartella degli oggetti se non esiste
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Pulizia dei file generati
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Pulizia completata."

.PHONY: all clean