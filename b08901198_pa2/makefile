# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: main_opt.o
			$(CC) $(OPTFLAGS) main_opt.o -o bin/mps
main_opt.o 	   	: src/main.cpp
			$(CC) $(CFLAGS) $< -o $@
#sort_tool_opt.o	: src/sort_tool.cpp src/sort_tool.h
#			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/mps_dbg
	@echo -n ""

bin/mps_dbg	: main_dbg.o
			$(CC) $(DBGFLAGS) main_dbg.o -o bin/mps_dbg
main_dbg.o 	   	: src/main.cpp
			$(CC) $(CFLAGS) $< -o $@
#sort_tool_dbg.o	: src/sort_tool.cpp src/sort_tool.h
#			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

#lib: lib/libtm_usage.a

#lib/libtm_usage.a: tm_usage.o
#	$(AR) $(ARFLAGS) $@ $<
#tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
#	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o bin/*