# GNU Make 4.3
# Tell the makefile to compile a file named editor.cpp

editor: editor.c
			$(CC) editor.c -std=c99 -o editor -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

# Explaination for the debugging flags 
# $(CC)			: GCC compiler collection
# -std				: c99 compiler version
# editor			: Name of the executable compiled source program
# -Wshadow,-Wall 	: Turn on all Warnings