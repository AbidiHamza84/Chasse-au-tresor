#ifndef _DIAGRAMS_INPUT_H
#define _DIAGRAMS_INPUT_H

#include <string>
#include "Cord.h"

#if defined(_WIN32) || defined(_WIN64)

#define UP 'Z'
#define RIGHT 'D'
#define DOWN 'S'
#define LEFT 'Q'
#define ESC 27
#define SAVE 1
#define QUIT 0
#define ENT 13
#define SPACE 32
#define E 'E'
#define A 'A'
#define H 'H'

#include <windows.h> // \brief Windows API permettant de controler la console

class Input {
	public:
		Input();
		~Input();
		void updateTermSize();
		Cord getTermSize();
		unsigned char keyboard();
		Cord getCursorPosition();
		void setCursorPosition(Cord position);
		void setCursorPosition(int, int);
		int inInt();
		std::string inString(int);
		std::string inString();
	private:
		Cord TermSize;

		HANDLE rhnd;
		DWORD Events;
		DWORD EventsRead;
};

#elif defined(__unix__) || defined(__unix)

#define UP 'z'
#define RIGHT 'd'
#define DOWN 's'
#define LEFT 'q'
#define ESC 27
#define SAVE 1
#define QUIT 0
#define ENT 10
#define SPACE 32
#define E 'e'
#define A 'a'
#define H 'h'

#include <termios.h>

class Input {
	public:
		Input();
		~Input();
		void updateTermSize();
		Cord getTermSize();
		unsigned char keyboard();
		Cord getCursorPosition();
		void setCursorPosition(Cord position);
		void setCursorPosition(int, int);
		int inInt();
		std::string inString(int);
		std::string inString();
	private:
		Cord TermSize;

		struct termios* old_tio;
};

#else
#   error unsupported platform
#endif

#endif
