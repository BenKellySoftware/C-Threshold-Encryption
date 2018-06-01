
CC = gcc
CFLAGS = -Wall -Werror -ansi -lm
DEBUG = 0
VERBOSE = 0
TRAINING_DIR = training
TRAINING_LINK = https://www.dropbox.com/s/g1ppavcuz90auip/training.zip
RECIPES_DIR = recipes
RECIPES_LINK = https://www.dropbox.com/s/5wk98372u0qbm5b/recipes.zip

build : huffman.codes
	@if [ ! -e $(RECIPES_DIR) ]; then \
		echo "Training set doesn't exist, downloading now"; \
		wget $(RECIPES_LINK); \
		unzip -o recipes.zip; \
		rm recipes.zip; \
	fi

	mkdir -p storage

	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -o bepis.out bepis.c
	@echo "Build complete, run ./bepis.out with either -a or -v"

rebuild : clean build

huffman.codes : generate_huffman.out
	@if [ ! -e $(TRAINING_DIR) ]; then \
		echo "Training set doesn't exist, downloading now"; \
		wget $(TRAINING_LINK); \
		unzip -o training.zip; \
		rm training.zip; \
	fi

	@echo "Generating huffman code from training set"
	@./generate_huffman.out $(TRAINING_DIR)/*

generate_huffman.out : generate_huffman.c
	@echo "Compiling huffman generator"
	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -DVERBOSE=$(VERBOSE) -o generate_huffman.out generate_huffman.c

clean :
	echo "Removing all non-code files"
	rm -rf storage/ recipes/ training/ huffman.codes bepis.out generate_huffman.out