CXX = g++
CXXFLAGS = -std=c++23 -Wall -Iinclude -MMD -MP
MAIN = test.cxx
SRC_DIR = src
OBJ_DIR = objs
SRCS = $(wildcard $(SRC_DIR)/*.cxx)
OBJS = $(patsubst $(SRC_DIR)/%.cxx,$(OBJ_DIR)/%.o,$(SRCS))
MAIN_OBJ := $(OBJ_DIR)/$(MAIN:.cxx=.o)
BIN = test.exe

all: $(BIN)

$(BIN): $(MAIN_OBJ) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS)  -c $< -o $@
clean:
	rm -f $(BIN)

build:
	cmake -S . -B build
build_exe:
	cmake -S . -B exe -DCMAKE_BUILD_TYPE=Release
app:
	cmake --build build -j8
appexe:
	cmake --build exe -j8
	sh ./install.sh
clean_build:
	rm -rf ./build
	rm -rf ./cputemp_monitor
clean_app:
	rm -rf ./exe
	rm -rf ./cputemp_monitor
	sh ./uninstall.sh
