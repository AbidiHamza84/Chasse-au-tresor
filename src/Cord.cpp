#include "../include/Cord.h"
#include <stdio.h>

void printCord(Cord c) {
	printf("x:%d y:%d", c.x, c.y);
}

bool equal(Cord a,Cord b){
	return a.x == b.x && a.y == b.y ;
}
