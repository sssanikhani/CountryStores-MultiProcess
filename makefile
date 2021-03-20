CC = g++

UTILS = utils.cpp
UTILS_OBJ = utils.o


MAIN = StoreCalculator.cpp \
		command.cpp \
		province.cpp \
		city.cpp \
		store.cpp

CALCULATOR_EXE = StoreCalculator.out
CALCULATOR_OBJS = StoreCalculator.o $(UTILS_OBJ)


COMMAND_EXE = command
COMMAND_OBJS = command.o $(UTILS_OBJ)

PROVINCE_EXE = province
PROVINCE_OBJS = province.o $(UTILS_OBJ)

CITY_EXE = city
CITY_OBJS = city.o $(UTILS_OBJ)

STORE_EXE = store
STORE_OBJS = store.o $(UTILS_OBJ)

EXEC_FILES = $(CALCULATOR_EXE) \
			 $(COMMAND_EXE) \
			 $(PROVINCE_EXE) \
			 $(CITY_EXE) \
			 $(STORE_EXE)

OBJ_FILES = utils.o \
			StoreCalculator.o \
			command.o \
			province.o \
			city.o \
			store.o


DEFAULT_COMMANDS_PATH = commands.txt
DEFAULT_ASSETS_DIR = assets
PIPES_TEMPLATE = c_*


target:
	$(CC) -c $(UTILS)

	$(CC) -c $(MAIN)

	$(CC) -o $(CALCULATOR_EXE) $(CALCULATOR_OBJS)

	$(CC) -o $(COMMAND_EXE) $(COMMAND_OBJS)

	$(CC) -o $(PROVINCE_EXE) $(PROVINCE_OBJS)

	$(CC) -o $(CITY_EXE) $(CITY_OBJS)

	$(CC) -o $(STORE_EXE) $(STORE_OBJS)


run:
	$(CC) -c $(UTILS)

	$(CC) -c $(MAIN)

	$(CC) -o $(CALCULATOR_EXE) $(CALCULATOR_OBJS)

	$(CC) -o $(COMMAND_EXE) $(COMMAND_OBJS)

	$(CC) -o $(PROVINCE_EXE) $(PROVINCE_OBJS)

	$(CC) -o $(CITY_EXE) $(CITY_OBJS)

	$(CC) -o $(STORE_EXE) $(STORE_OBJS)

	./$(CALCULATOR_EXE) $(DEFAULT_COMMANDS_PATH) $(DEFAULT_ASSETS_DIR)


clean:
	rm -f $(OBJ_FILES)
	rm -f $(EXEC_FILES)
	rm -f $(PIPES_TEMPLATE)
