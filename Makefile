CMP=gcc
FLG=-g
OUT=./bin/parser.out

SRC=./src/*.c \
	./src/map_loading/tokenizer/*.c \
	./src/map_loading/parser/*.c \
	./src/map_loading/ir/*.c \
	./src/map_loading/utilities/*.c \

.phony: clean

all: $(SRC)
	$(CMP) $(FLG) $(SRC) -o $(OUT)

run: $(OUT)
	$(OUT)

clean:
	rm $(OUT)
