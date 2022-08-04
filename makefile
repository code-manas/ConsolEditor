# GNU Make 4.3
# Tell the makefile to compile a file named editor.cpp

editor: editor.cpp
			$(CXX) editor.cpp -std=c++17 -o editor -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

# Explaination for the debugging flags 
# $(CXX)			: C++ comilation for GNU C standard g++
# -std				: c++17 C++ compiler version
# editor			: Name of the executable compiled source program
# -Wshadow,-Wall 	: Turn on all Warnings