GXX=/usr/local/bin/g++-4.8
#GXX=/usr/bin/g++

SRC=src
BUILD=build
BIN=bin
CPPFLAGS=-O0 -g
INC=-I include/$(CORE_DIR)

CORE_DIR=core
BUILD_KDTREE_DIR=build_kdtree
QUERY_KDTREE_DIR=query_kdtree

BUILD_KDTREE=$(BIN)/build_kdtree.out
QUERY_KDTREE=$(BIN)/query_kdtree.out

CORE_OBJS=
BUILD_KDTREE_OBJS=$(BUILD)/$(BUILD_KDTREE_DIR)/build_kdtree.o
QUERY_KDTREE_OBJS=$(BUILD)/$(QUERY_KDTREE_DIR)/query_kdtree.o

all: $(BUILD_KDTREE) $(QUERY_KDTREE)

$(BUILD_KDTREE): $(CORE_OBJS) $(BUILD_KDTREE_OBJS)
	$(GXX) $(CPPFLAGS) -o $@ $^

$(QUERY_KDTREE): $(CORE_OBJS) $(QUERY_KDTREE_OBJS)
	$(GXX) $(CPPFLAGS) -o $@ $^

$(BUILD)/$(CORE_DIR)/%.o: $(SRC)/$(CORE_DIR)/%.cpp
	mkdir -p $(BUILD)/$(CORE_DIR)
	$(GXX) $(CPPFLAGS) $(INC) -o $@ -c $<

$(BUILD)/$(BUILD_KDTREE_DIR)/%.o: $(SRC)/$(BUILD_KDTREE_DIR)/%.cpp
	mkdir -p $(BUILD)/$(BUILD_KDTREE_DIR)
	$(GXX) $(CPPFLAGS) $(INC) -o $@ -c $<

$(BUILD)/$(QUERY_KDTREE_DIR)/%.o: $(SRC)/$(QUERY_KDTREE_DIR)/%.cpp
	mkdir -p $(BUILD)/$(QUERY_KDTREE_DIR)
	$(GXX) $(CPPFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(BUILD)/*
	rm -f $(BIN)/*

.PHONY: clean
