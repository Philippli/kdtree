#GXX=/usr/local/bin/g++-4.8
GXX=/usr/bin/g++
CPPFLAGS=--std=c++11 -g

SRC=src
BUILD=build
BIN=bin
TEST=test
CORE_DIR=core

INC=-I include/$(CORE_DIR)

BUILD_KDTREE_DIR=build_kdtree
QUERY_KDTREE_DIR=query_kdtree

BUILD_KDTREE=$(BIN)/build_kdtree.out
QUERY_KDTREE=$(BIN)/query_kdtree.out
TESTS=\
	  $(BIN)/point.t.out \
	  $(BIN)/kdtree.t.out \
	  $(BIN)/kdtree_static.t.out

CORE_OBJS=
BUILD_KDTREE_OBJS=$(BUILD)/$(BUILD_KDTREE_DIR)/build_kdtree.o
QUERY_KDTREE_OBJS=$(BUILD)/$(QUERY_KDTREE_DIR)/query_kdtree.o

.SECONDARY: $(TEST_OBJS)
TEST_OBJS=\
	  $(BUILD)/$(TEST)/point.t.o \
	  $(BUILD)/$(TEST)/kdtree.t.o \
	  $(BUILD)/$(TEST)/kdtree_static.t.o

all: $(BUILD_KDTREE) $(QUERY_KDTREE) $(TESTS)

$(BUILD_KDTREE): $(CORE_OBJS) $(BUILD_KDTREE_OBJS)
	mkdir -p $(BIN)
	$(GXX) $(CPPFLAGS) -o $@ $^

$(QUERY_KDTREE): $(CORE_OBJS) $(QUERY_KDTREE_OBJS)
	mkdir -p $(BIN)
	$(GXX) $(CPPFLAGS) -o $@ $^

$(BIN)/%.t.out: $(CORE_OBJS) $(BUILD)/$(TEST)/%.t.o
	mkdir -p $(BIN)
	$(GXX) $(CPPFLAGS) -o $@ $^

$(BUILD)/$(BUILD_KDTREE_DIR)/%.o: $(SRC)/$(BUILD_KDTREE_DIR)/%.cpp
	mkdir -p $(BUILD)/$(BUILD_KDTREE_DIR)
	$(GXX) $(CPPFLAGS) $(INC) -o $@ -c $<

$(BUILD)/$(QUERY_KDTREE_DIR)/%.o: $(SRC)/$(QUERY_KDTREE_DIR)/%.cpp
	mkdir -p $(BUILD)/$(QUERY_KDTREE_DIR)
	$(GXX) $(CPPFLAGS) $(INC) -o $@ -c $<

$(BUILD)/$(TEST)/%.o: $(TEST)/core/%.cpp
	mkdir -p $(BUILD)/$(TEST)
	$(GXX) $(CPPFLAGS) $(INC) -o $@ -c $<


clean:
	rm -rf $(BUILD)/*
	rm -f $(BIN)/*

.PHONY: clean
