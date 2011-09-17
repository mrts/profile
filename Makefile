CFLAGS=-Iinclude -Wall -pg
LDFLAGS=-lrt # -lc_p -static-libgcc -- had problems with these
BIN=test

all: $(BIN)

clean:
	rm -f $(BIN)
	rm -f obj/*.o
	rm -f *.json *.out

obj/%.o: src/%.c
	@echo "  COMPILE OBJECT $<"
	@$(CC) -c $(CFLAGS) -o $@ $<

$(BIN): obj/util.o obj/vector.o obj/profile_hooks.o main.c
	@echo "  COMPILE AND LINK $@ WITH $^"
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
