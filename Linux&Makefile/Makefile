# ARM cross toolchain prefix; override as needed, e.g. CROSS_COMPILE=aarch64-linux-gnu-
CROSS_COMPILE ?= arm-buildroot-linux-gnueabihf-
CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Wextra -std=c11 -O2
TARGET := hello
SRC := hello.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
