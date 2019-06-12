CMP=gcc
FLG=-g
OUT=./bin/ast.out

SRC=./src/*.c ./src/parser/*.c

.phony: clean

all: $(SRC)
	$(CMP) $(FLG) $(SRC) -o $(OUT)

run: $(OUT)
	$(OUT)

clean:
	rm $(OUT)
