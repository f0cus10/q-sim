CXX ?= g++

#paths
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = ~/temp

# exec #
BIN_NAME = run.me

# extensions #
SRC_EXT = cxx 

# code list #
# use all source files
SOURCES = $(wildcard *.cxx)
# make source files into object files
OBJECTS := $(pathsubst %.cxx,%.o,$(SOURCES))

DEPS = $(OBJECTS:.o=.d)

# flags #
CFLAGS = -std=c++11 -Wall -Wextra -g -O2 
INCLUDES = -I include/ -I /usr/local/include

.PHONY: default_target release dirs clean all

release: export CXXFLAGS := $(CXXFLAGS) $(CFLAGS)
release: dirs
	@$(MAKE) all

dirs:
	@echo "Creating directories"
	@mkdir -p $(BIN_PATH)

clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) $(BIN_PATH)/$(BIN_NAME)

all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Creating the actual exec
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	@(CC) $(OBJECTS) -o $@

-include $(DEPS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
