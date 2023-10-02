TRASH = *.o *.a *.so prog prog-a prog-so *_out_*
TEST_PARAM_ONE = QWERTY
TEST_PARAM_TRI = QWERTY 123456 hidden

all:			prog prog-a prog-so

prog:			prog.o fun.o const.o
			cc $^ -o $@

prog-a:			prog.o liboutput_static.a
			cc -L. $< -loutput_static -o $@ 

prog-so:		prog.o liboutput.so
			cc -L. $< -loutput -o $@ 

%.o:			%.c outlib.h
			cc $< -c -fPIC -o $@

liboutput_static.a:	fun.o const.o
			ar -rcs $@ $^

liboutput.so:		fun.o const.o
			cc -shared $^ -o $@

clean:
			rm -f $(TRASH)

test:			all run compare

run:
			-./prog > prog_out_0 2>&1
			-./prog-a > prog-a_out_0 2>&1
			-LD_LIBRARY_PATH=`pwd` ./prog-so > prog-so_out_0 2>&1
			-./prog $(TEST_PARAM_ONE) > prog_out_1 2>&1
			-./prog-a $(TEST_PARAM_ONE) > prog-a_out_1 2>&1
			-LD_LIBRARY_PATH=`pwd` ./prog-so $(TEST_PARAM_ONE) > prog-so_out_1 2>&1
			-./prog $(TEST_PARAM_TRI) > prog_out_3 2>&1
			-./prog-a $(TEST_PARAM_TRI) > prog-a_out_3 2>&1
			-LD_LIBRARY_PATH=`pwd` ./prog-so $(TEST_PARAM_TRI) > prog-so_out_3 2>&1

compare:		
			@echo "\n ---- COMPARE ---- \n" 
			@if cmp prog_out_0 prog-a_out_0; then \
				echo "prog_out_0 == prog-a_out_0\n"; \
			else \
				echo "prog_out_0 != prog-a_out_0 but it's OK\n"; \
			fi
			@if cmp prog_out_0 prog-so_out_0; then \
				echo "prog_out_0 == prog-so_out_0\n"; \
			else \
				echo "prog_out_0 != prog-so_out_0 but it's OK\n"; \
			fi
			@if cmp prog_out_1 prog-a_out_1; then \
				echo "prog_out_1 == prog-a_out_1\n"; \
			else \
				echo "prog_out_1 != prog-a_out_1\n"; \
			fi
			@if cmp prog_out_1 prog-so_out_1; then \
				echo "prog_out_1 == prog-so_out_1\n"; \
			else \
				echo "prog_out_1 != prog-so_out_1\n"; \
			fi
			@if cmp prog_out_3 prog-a_out_3; then \
				echo "prog_out_3 == prog-a_out_3\n"; \
			else \
				echo "prog_out_3 != prog-a_out_3\n"; \
			fi
			@if cmp prog_out_3 prog-so_out_3; then \
				echo "prog_out_3 == prog-so_out_3\n"; \
			else \
				echo "prog_out_3 != prog-so_out_3\n"; \
			fi
