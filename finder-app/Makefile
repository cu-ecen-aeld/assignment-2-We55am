CC = gcc
CC_ARM = arm-none-eabi-gcc 

SRC = writer.c
TARGET = writer
TARGET_ARM = armWriter

all: $(TARGET)

CROSS_COMPILE: $(TARGET_ARM)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

$(TARGET_ARM): $(SRC)
	$(CC_ARM) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o $(TARGET_ARM)

.PHONY: all clean
