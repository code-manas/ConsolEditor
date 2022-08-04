# GNU Make 4.3
# Tell the makefile to compile a file named editor.c

editor: editor.c
			$(CC) editor.c -std=c99 -o editor -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG