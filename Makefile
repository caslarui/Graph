CXX = g++
FLAGS = -Werror
INC_PATH = ./includes/
OBJ_PATH = ./obj/
FILE_NAME = tetripic

SRC := $(wildcard ./sources/*.cpp)
OBJS := $(SRC:.cpp=.o)


.PHONY : all clean

all: build

build: $(OBJS)
	@$(CXX) $(FLAGS) -o $@ $(OBJS) -lm
	@mkdir -p $(OBJ_PATH)
	@mv ./sources/*.o $(OBJ_PATH)
	@echo "BUILD DONE"

%.o: %.c
	@$(CXX) $(FLAGS) -o $(FILE_NAME) -I$(INC_PATH)

clean:
	@rm -rf $(OBJ_PATH) $(FILE_NAME)
	@rm build
	@echo "CLEAN DONE"

re: clean
	build