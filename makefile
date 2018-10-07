CC = c++
CFLAGS = -std=c++11 -g
CFLAGS = -c -Wall -O2
SRC_DIR = src
EXEC_DIR = ~/temp
SOURCES = $(wildcard $(SRC_DIR)/*.cxx)
INCLUDES = -I include/
OBJECTS := $(patsubst %.cxx,%.o,$(SOURCES))

EXEC_NAME = run.me

$(EXEC_NAME): $(OBJECTS)
	$(CC) -o $(EXEC_DIR)/$(EXEC_NAME) $(OBJECTS)

.cxx.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) src/*.o include/*.o $(EXEC_DIR)/$(EXEC_NAME) 
