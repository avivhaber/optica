TARGET_EXEC ?= optica

BUILD_DIR ?= ./build
OUT_DIR ?= ./out
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
CXXFLAGS ?= -std=c++1z -Ofast -flto -g -Wall -Werror

# build binary
$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

print-%  : ; @echo $* = $($*)

.PHONY: all
all:
	$(CXX) $(INC_FLAGS) $(CXXFLAGS) -o $(TARGET_EXEC) $(SRCS)

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
