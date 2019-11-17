CXX = g++
FLAGS = -Werror
INC_PATH = ./includes/
OBJ_PATH = ./obj/
FILE_NAME = graph

SRC := $(wildcard ./sources/*.cpp)
OBJS := $(SRC:.cpp=.o)


.PHONY : all clean

all: build

build: $(OBJS)
	@$(CXX) $(FLAGS) -o $(FILE_NAME) $(OBJS) -lm
	@mkdir -p $(OBJ_PATH)
	@mv ./sources/*.o $(OBJ_PATH)
	@echo "BUILD DONE"

leak:
	@valgrind --leak-check=full ./$(FILE_NAME)

origins:
	@valgrind --track-origins=yes ./$(FILE_NAME)

%.o: %.c
	@$(CXX) $(FLAGS) -o $(FILE_NAME) -I$(INC_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@rm $(FILE_NAME)
	@echo "CLEAN DONE"