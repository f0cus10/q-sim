TARGET_EXEC ?= run.me

BUILD_DIR ?= ./build
SRC_DIR ?= ./src

SRCS := $(wildcard $(SRC_DIR)/*.cxx)
# replace the name of the sources with .o in the build directory
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# create dependencies from object files
DEPS := $(OBJS: .o=.d)

INCLUDES = -I ./include

CPPFLAGS ?= $(INCLUDES) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o ~/temp/$(TARGET_EXEC) $(LDFLAGS)

$(BUILD_DIR)/%.cxx.o: %.cxx
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) ~/temp/$(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p 
