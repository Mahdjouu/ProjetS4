.PHONY: all clean
CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lgmp
OBJFILES = phase1.o rsa_tools_gmp.o rsa_tools.o bezout.o other_base64.o rsa_file_char.o rsa_print_tools.o crypt_decrypt.o Sha-256/sha256_utils.o Sha-256/sha256.o rsa_sign.o rsa_file_blocks.o
TARGET = phase1

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
