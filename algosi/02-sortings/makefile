# Папки
BIN_DIR := bin
OBJ_DIR := obj
HEADER_DIR := include
SRC_DIR := src

# Компилятор и его флаги
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -I$(HEADER_DIR) -I$(SRC_DIR) -MMD -MP

# Целевой бинарник
TARGET := $(BIN_DIR)/sortings

# Автоматический поиск исходных файлов и составление списка объектных
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

# Цель по умолчанию
all: $(TARGET)

# Link target
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Компиляция исходных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создать папки, если их не существует
$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

# Чистка артефактов сборки
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Подсос автоматически сгенерированных зависимостей
-include $(DEP_FILES)

.PHONY: all clean
