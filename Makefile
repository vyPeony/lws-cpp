CXX = g++
# CXX_FLAGS = -Wall -Wextra -g -O0 -MMD -DDEBUG -std=c++11
CXX_FLAGS = -Wall -Wextra -O2 -MMD -std=c++11
BIN_DIR = bin
SRC_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(foreach i, $(SOURCES), $(BIN_DIR)/$(basename $(i)).o)
PROGRAM = ./lws


.PHONY: test clean rebuild


all: test


test: build
	@echo ----- run -----
	@date +"%H:%M:%S"
	-@$(RM) -f tmp.rb
	@$(PROGRAM) > tmp.rb
	@ruby tmp.rb
	@date +"%H:%M:%S"


build: $(PROGRAM)


$(PROGRAM): $(OBJECTS)
	$(CXX) $^ -o $@


$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@


clean:
	-@$(RM) -f $(PROGRAM)
	-@$(RM) -f $(BIN_DIR)/*.d $(BIN_DIR)/*.o


rebuild: clean build


-include $(BIN_DIR)/*.d
