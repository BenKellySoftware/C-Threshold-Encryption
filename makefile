
CC = gcc
CFLAGS = -Wall -Werror -ansi -lm
DEBUG = 0
VERBOSE = 0
TRAINING_DIR = training

build : huffman.codes
	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -o bepis.out bepis.c
	@echo "Build complete, run ./bepis.out with either -a or -v"

rebuild : clean build

huffman.codes : generate_huffman.out
	
	@if [ ! -e $(TRAINING_DIR) ]; then \
			echo "Training set doesn't exist, downloading now"; \
	fi

	@echo "Generating huffman code from training set"
	@./generate_huffman.out training 5
	
generate_huffman.out : generate_huffman.c
	@echo "Compiling huffman generator"
	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -DVERBOSE=$(VERBOSE) -o generate_huffman.out generate_huffman.c

clean :
	echo "Removing all non-code files"
	rm -rf storage/ recipes/ training/ huffman.codes bepis.out generate_huffman.out