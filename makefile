GXX=/usr/bin/g++

SRC=src
BUILD=build
BIN=bin
INC=-I include

OBJS=$(BUILD)/test.m.o $(BUILD)/kdtree.o
TARGET=$(BIN)/a.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GXX) -o $@ $^

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(BUILD)
	$(GXX) $(INC) -o $@ -c $<

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: clean
