
CC = gcc
CFLAGS = -Wall -Werror -ansi -lm
DEBUG = 0
VERBOSE = 0
TRAINING_DIR = training
TRAINING_LINK = https://www.dropbox.com/s/l0vocyiy5zm9q9q/training.zip
RECIPES_DIR = recipes
RECIPES_LINK = https://www.dropbox.com/s/l0vocyiy5zm9q9q/recipes.zip

build : huffman.codes
	@if [ ! -e $(RECIPES_DIR) ]; then \
		echo "Training set doesn't exist, downloading now"; \
		wget $(RECIPES_LINK); \
		unzip recipes.zip; \
	fi

	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -o bepis.out bepis.c
	@echo "Build complete, run ./bepis.out with either -a or -v"

rebuild : clean build

huffman.codes : generate_huffman.out
	@if [ ! -e $(TRAINING_DIR) ]; then \
		echo "Training set doesn't exist, downloading now"; \
		wget $(TRAINING_LINK); \
		unzip training.zip; \
	fi

	@echo "Generating huffman code from training set"
	@./generate_huffman.out $(TRAINING_DIR)/*

generate_huffman.out : generate_huffman.c
	@echo "Compiling huffman generator"
	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -DVERBOSE=$(VERBOSE) -o generate_huffman.out generate_huffman.c

clean :
	echo "Removing all non-code files"
	rm -rf storage/ recipes/ training/ training.zip huffman.codes bepis.out generate_huffman.out