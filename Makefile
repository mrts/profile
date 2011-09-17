CFLAGS=-Iinclude -Wall

# Problems with profiling malloc due to
#  https://bugs.launchpad.net/ubuntu/+source/glibc/+bug/667470
# -pg in CFLAGS and -lc_p -static-libgcc in LDFLAGS disabled for now
#
# Using Google Performance Tools instead
#  sudo apt-get install google-perftools libgoogle-perftools-dev
#
LDFLAGS=-lrt -lprofiler

BIN=test

all: run

run: $(BIN)
	CPUPROFILE=profile.out ./$<
	google-pprof --text ./test profile.out

clean:
	rm -f $(BIN)
	rm -f obj/*.o
	rm -f *.json *.out

src/%.c: include/%.h

obj/%.o: src/%.c
	@echo "  COMPILE OBJECT $<"
	@$(CC) -c $(CFLAGS) -o $@ $<

$(BIN): obj/util.o obj/vector.o obj/profile_hooks.o main.c
	@echo "  COMPILE AND LINK $@ WITH $^"
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
