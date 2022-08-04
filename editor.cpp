/**
 * @file editor.c
 * @author Manas
 * @brief A console based text editor in C++
 * @version 0.1
 * @date 2022-08-04
 */

#include <ctype.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

# define CTRL_KEY(k) ((k) &0x1f)

struct editorConfig {
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

struct editorConfig E;

using namespace std;

class Window {
    public:
        int getWindowSize(int *rows, int *cols) {
            struct winsize ws;
            if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
                return -1;
            }
            else {
                *cols = ws.ws_col;
                *rows = ws.ws_row;
                return 0;
            }
        }
};

class  Editor {
    public:
        void static die(const char *s) {
            perror(s);
            exit(1);
        }

        void static disableRawMode() {
            if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) 
                die("tcgetattr");
        }

        void enableRawMode() {
            if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) {
                die("tcgetattr");
            }
            atexit(disableRawMode);

            struct termios raw = E.orig_termios;

            raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
            raw.c_oflag &= ~(OPOST);
            raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
            raw.c_cflag |= (CS8);

            raw.c_cc[VMIN] = 0;
            raw.c_cc[VTIME] = 1;

            if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
                die("tcsetattr");
            }
        }

        char editorReadKey() {
            int nread;
            char c;
            while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
                if(nread == -1 && errno != EAGAIN) {
                    die("read");
                }
            }
            return c;
        }

        void editorProcessKeypress() {
            char c = editorReadKey();

            switch (c) {
                case CTRL_KEY('q'):
                    write(STDOUT_FILENO, "\x1b[2J", 4);
                    write(STDOUT_FILENO, "\x1b[H", 3);
                    exit(0);
                    break;
            }
        }

        void editorDrawRows() {
            int x;
            for(x = 0; x < E.screenrows; x++) {
                write(STDOUT_FILENO, "~\r\n", 3);
            }
        }

        void editorRefreshScreen() {
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
        }

        Window newWindow;

        void initEditor() {
            if(newWindow.getWindowSize(&E.screenrows, &E.screencols) == -1) {
                die("getWindowSize");
            }
        }
};

int main(void) {
    // Create an editor object of editor class
    Editor myEditor; 
    
    // Access function
    myEditor.enableRawMode();
    myEditor.initEditor();

    while(1) {
        myEditor.editorRefreshScreen();
        myEditor.editorProcessKeypress();   
    }
    return 0;
}