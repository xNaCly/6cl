FLAGS := -std=c23 \
        -Wall \
        -Wextra \
        -Werror \
        -fdiagnostics-color=always \
        -fno-common \
        -Winit-self \
        -Wfloat-equal \
        -Wundef \
        -Wshadow \
        -Wpointer-arith \
        -Wcast-align \
        -Wstrict-prototypes \
        -Wstrict-overflow=5 \
        -Wwrite-strings \
        -Waggregate-return \
        -Wcast-qual \
        -Wswitch-default \
        -Wunreachable-code \
        -Wno-discarded-qualifiers \
		-Wno-unused-parameter \
		-Wno-unused-function \
		-Wno-unused-variable \
		-Wno-aggregate-return

FILES := $(shell find . -maxdepth 1 -name "*.c")
TEST_FILES := $(shell find ./tests -name "*.c")

.PHONY: test clean

E=calc
example: 
	$(CC) $(FLAGS) -g3 -fsanitize=address,undefined -DDEBUG=0 examples/$(E).c $(FILES) -o ./examples/$(E).out
	./examples/$(E).out

test:
	$(CC) $(FLAGS) -g3 -fsanitize=address,undefined -DDEBUG=0 $(TEST_FILES) $(FILES) -o ./tests/test.out
	./tests/test

clean:
	rm -fv **/**.out
