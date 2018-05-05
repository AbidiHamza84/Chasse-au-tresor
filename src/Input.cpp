#include "../include/Input.h"
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)

Input::Input() {
	rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console
	DWORD Events = 0;     // Event count
	DWORD EventsRead = 0; // Events read from console

	updateTermSize();
}

Input::~Input() {
}

void Input::updateTermSize() {
	COORD c = GetLargestConsoleWindowSize
	TermSize.x = c.x;
	TermSize.y = c.y;
}

unsigned char Input::keyboard() {
	for(;;) {
		// gets the systems current "event" count
		GetNumberOfConsoleInputEvents(rhnd, &Events);

		if(Events != 0) { // if something happened we will handle the events we want

			// create event buffer the size of how many Events
			INPUT_RECORD eventBuffer[Events];

			// fills the event buffer with the events and saves count in EventsRead
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

			// loop through the event buffer using the saved count
			for(DWORD i = 0; i < EventsRead; ++i) {
				switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_UP:
					case UP:
						return UP;
					break;
					case VK_DOWN:
					case DOWN:
						return DOWN;
					break;
					case VK_RIGHT:
					case RIGHT:
						return RIGHT;
					break;
					case VK_LEFT:
					case LEFT:
						return LEFT;
					break;
				}
			}
		}
	}
}

Cord Input::getCursorPosition() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		Cord c;

		if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
			c.x = csbi.dwCursorPosition.X;
			c.y = csbi.dwCursorPosition.Y;
		}
		else {
			c.x = 0;
			c.y = 0;
		}
		return c;
}

void Input::setCursorPosition(Cord position) {
	COORD c;
	c.X = position.x;
	c.Y = position.y;
	SetConsoleCursorPosition(rhnd, c);
}

void Input::setCursorPosition(int x, int y) {
	COORD c = {x, y};
	SetConsoleCursorPosition(rhnd, c);
}

int Input::inInt(){
	bool negative = false;
	int i = 0;
	int a =  0;
	Cord c;

	for(;;) {
		GetNumberOfConsoleInputEvents(rhnd, &Events);
		if(Events != 0) {
			INPUT_RECORD eventBuffer[Events];
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);
			for(DWORD i = 0; i < EventsRead; ++i) {
				if(i == 0 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == 109) {
					negative = true;
					printf("-");
					i++;
				}
				else if(a < 999999 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= '0' && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= '9') {
					a = a*10 + (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode -'0');
					printf("%c", eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					i++;
				}
				else if(a < 999999 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 96 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 105) {
					eventBuffer[i].Event.KeyEvent.wVirtualKeyCode -= 96;
					a = a*10 + eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
					printf("%d", eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == 8 && i >0) {
					if(i > 1 || negative == false) {
						a /= 10;
					}
					else {
						negative = false;
					}
					c = getCursorPosition();
					setCursorPosition(c.x, c.y-1);
					printf(" ");
					setCursorPosition(c.x, c.y-1);
					i--;
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == ENT) {
					return a;
				}
			}
		}
	}
}

std::string Input::inString(int l) {
	int i = 0;
	std::string s;

	for(;;) {
		GetNumberOfConsoleInputEvents(rhnd, &Events);
		if(Events != 0) {
			INPUT_RECORD eventBuffer[Events];
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);
			for(DWORD i = 0; i < EventsRead; ++i) {
				if(i < l && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 'A' && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 'Z') {
					printf("%c", eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					s.push_back(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					i++;
				}
				else if(i < l && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= '0' && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= '9') {
					printf("%c",c);
					s.push_back(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					i++;
				}
				else if(i < l && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 96 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 105) {
					eventBuffer[i].Event.KeyEvent.wVirtualKeyCode -= 48;
					printf("%c",c);
					s.push_back(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					i++;
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == 8 && i >0) {
					c = getCursorPosition();
					setCursorPosition(c.x, c.y-1);
					printf(" ");
					setCursorPosition(c.x, c.y-1);
					i--;
					s.resize(i);
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == ENT) {
					return s;
				}
			}
		}
	}
}

std::string Input::inString() {
	int i = 0;
	std::string s;

	for(;;) {
		GetNumberOfConsoleInputEvents(rhnd, &Events);
		if(Events != 0) {
			INPUT_RECORD eventBuffer[Events];
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);
			for(DWORD i = 0; i < EventsRead; ++i) {
				if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 'A' && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 'Z') {
					printf("%c", eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					s.push_back(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					i++;
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= '0' && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= '9') {
					printf("%c",c);
					s.push_back(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					i++;
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 96 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode >= 105) {
					eventBuffer[i].Event.KeyEvent.wVirtualKeyCode -= 48;
					printf("%c",c);
					s.push_back(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					i++;
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == 8 && i >0) {
					c = getCursorPosition();
					setCursorPosition(c.x, c.y-1);
					printf(" ");
					setCursorPosition(c.x, c.y-1);
					i--;
					s.resize(i);
				}
				else if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == ENT) {
					return s;
				}
			}
		}
	}
}

#elif defined(__unix__) || defined(__unix)
#include <unistd.h>

Input::Input() {
	old_tio = new termios;
	tcgetattr(STDIN_FILENO, old_tio);

	struct termios new_tio;
	new_tio = *old_tio;
	new_tio.c_lflag &=(~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

	updateTermSize();
}

Input::~Input() {
	tcsetattr(STDIN_FILENO,TCSANOW,old_tio);
}

void Input::updateTermSize() {
	printf("\033[s");
	printf("\033[999;999H");
	TermSize = getCursorPosition();
	printf("\033[u");
}


unsigned char Input::keyboard() {
	unsigned char c;
	for(;;) {
		c = getchar();
		if(c == 27) {
			if(getchar() == 91) {
				c = getchar();
				switch(c) {
				case 65:
					return UP;
					break;
				case 66:
					return DOWN;
					break;
				case 67:
					return RIGHT;
					break;
				case 68:
					return LEFT;
					break;
				}
			}
			else return ESC;
		}
		else if(c == UP || c == RIGHT || c == DOWN || c == LEFT || c == ENT || c == SPACE || c == ESC || c == E || c == H || c == A) return c;
		else if(c == '/') {
			printf("\033[s");
			unsigned char s[15];
			char i = 0;
			printf("/");
			while(c != 10 && i != 14 && i >= 0) {
				c = getchar();
				if(c == 127) {
					printf("\033[1D \033[1D");
					s[i] = '\0';
					i--;
				}
				else {
					printf("%c",c);
					s[i] = c;
					i++;
				}
			}
			s[i] = '\0';
			printf("\033[u");
			if(s[0] == 's')
				return SAVE;
			if(s[0] == 'q')
				return QUIT;
		}
	}
}

Cord Input::getCursorPosition() {
	Cord cursor;
	printf("\033[6n");
	unsigned char c = getchar(); //ESC
	getchar();
	cursor.x = getchar() - '0';
	c = getchar();
	while(c != ';') {
		cursor.x = cursor.x*10 + (c - '0');
		c = getchar();
	}
	cursor.y = getchar() - '0';
	c = getchar();
	while(c != 'R') {
		cursor.y = cursor.y*10 + (c - '0');
		c = getchar();
	}
	return cursor;
}

void Input::setCursorPosition(Cord position) {
	printf("\033[%d;%dH",position.x, position.y);
}

void Input::setCursorPosition(int x, int y) {
	printf("\033[%d;%dH", x, y);
}

int Input::inInt(){
	bool negative = false;
	int i = 0;
	int a =  0;
	unsigned char c = getchar();

	while(c != ENT) {
		if(i == 0 && c == '-') {
			negative = true;
			printf("-");
			i++;
		}
		if(a < 999999 && c >= '0' && c <= '9') {
			a = a*10 + (c -'0');
			printf("%c",c);
			i++;
		}
		if(c == 127 && i > 0) {
			if(i > 1 || negative == false) {
				a /= 10;
			}
			else {
				negative = false;
			}
			printf("\033[1D \033[1D");
			i--;
		}
		c = getchar();
	}
	if(negative) a *= -1;
	return a;
}

std::string Input::inString(int l) {
	int i = 0;
	std::string s;
	unsigned char c = getchar();

	while(c != ENT){
		if(i < l && c >= ' ' && c <= '~') {
			printf("%c",c);
			s.push_back(c);
			i++;
		}
		else if(c == 127 && i > 0) {
			printf("\033[1D \033[1D");
			i--;
			s.resize(i);
		}
		c = getchar();
	}
	return s;
}

std::string Input::inString() {
	int i = 0;
	std::string s;
	unsigned char c = getchar();

	while(c != ENT){
		if(c >= ' ' && c <= '~') {
			printf("%c",c);
			s.push_back(c);
			i++;
		}
		else if(c == 127 && i > 0) {
			printf("\033[1D \033[1D");
			i--;
			s.resize(i);
		}
		c = getchar();
	}
	return s;
}


#else
#   error unsupported platform
#endif

Cord Input::getTermSize() {
	return TermSize;
}
