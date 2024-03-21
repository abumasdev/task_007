CCF = gcc -Wall -std=c11
#CCF = gcc -Wall -Werror -Wextra -std=c11
CC = gcc
PROJECT_DIR = ../

all: show_str change_separator binary_div real_db

# task1 --------------------------------------------------------------
show_str : clean_bin
	$(CCF) $(PROJECT_DIR)src/task1.c $(PROJECT_DIR)src/sqlite3.o -o $(PROJECT_DIR)bin/show_str

# task2 --------------------------------------------------------------
change_separator : clean_bin
	$(CCF) $(PROJECT_DIR)src/task2.c $(PROJECT_DIR)src/sqlite3.o -o $(PROJECT_DIR)bin/change_separator

# task3 --------------------------------------------------------------
binary_div : clean_bin
	$(CCF) $(PROJECT_DIR)src/task3.c $(PROJECT_DIR)src/sqlite3.o -o $(PROJECT_DIR)bin/binary_div

# task4 --------------------------------------------------------------
real_db : clean_bin
	$(CCF) $(PROJECT_DIR)src/task4.c $(PROJECT_DIR)src/sqlite3.o -o $(PROJECT_DIR)bin/real_db

sqlite3.o :
	$(CC) -c $(PROJECT_DIR)src/sqlite3.c

# run -----------------------------------------------------------------
run :
	$(PROJECT_DIR)bin/show_str
	$(PROJECT_DIR)bin/change_separator
	$(PROJECT_DIR)bin/binary_div
	$(PROJECT_DIR)bin/real_db

clean: clean_obj clean_bin

clean_obj:
	rm -rf *.o 

clean_bin:
	rm -rf $(PROJECT_DIR)bin/* 

test: clang_test 

#valgrind_test:
#	valgrind --tool=memcheck --leak-check=yes  $(PROJECT_DIR)build/cipher

clang_test:
	clang-format -n task*.c 
