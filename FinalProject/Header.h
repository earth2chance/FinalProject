/*#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>

char tmp_map[18][38];//map height and width
char map[18][38];
std::vector<target> walk_queue;
std::vector<walk> BFSArray;

void FindPath(int sx, int sy, int x, int y);
void AddArray(int x, int y, int wc, int back);
void gotoxy(short x, short y);
void ShowMap();
////class entity;
struct walk;
struct target;
//class entity
//{
//public:
//	entity(int x, int y);
//	void move_x(int p);	
//	void move_y(int p);
//	void move(int p, int q);
//	/*int get_x(){ return x; }
//	int get_y(){ return y; }*/
//	void draw(char p);
//
//private:
//	int x;
//	int y;
//};
//struct walk
//{
//	short walk_count;
//	short x;
//	short y;
//	short back;
//};
//struct target
//{
//	short x;
//	short y;
//}; */