#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <MMSystem.h>


char tmp_map[18][38];//map height and width

char map[18][38] = //map layout
{
	"+###################################+",
	"|                                   |",
	"|## ########### #   #######  #  ### |",
	"|   |               |             | |",
	"|   |    |  |       |   |    #####| |",
	"| | |### |  |       |   |           |",
	"| |      |  | |###  |   |  |      | |",
	"| | #####|  | |      ## |         | |",
	"| |           |###  |      |######| |",
	"| |##### ###         ##           | |",
	"| |    |   ######  ####### ###      |",
	"|                                   |",
	"|# ### ####      ###   ######  ###  |",
	"|                |                  |",
	"|#######  ###### ########  ### ###  |",
	"|         |                |     |  |",
	"|                                   |",
	"+###################################+"

};
char userLetter, computerLetter;
void names() //this function gives the letters to use as sprites in the game
{
	std::string userName, computerName;
	
	std::cout << "Please enter your first name: ";
	std::cin >> userName;
	std::cout << "Please enter a name for the computer: ";
	std::cin >> computerName;
	for (unsigned i = 0; i < userName.length(); i++)
		userLetter = userName.at(0);
	for (unsigned i = 0; i < computerName.length(); i++)
		computerLetter = computerName.at(0);
}
void intro() //this function just prints out the intro/start menu of the game 
{
	std::cout << "                  ###############              " << std::endl;
	std::cout << "                ##################        " << std::endl;
	std::cout << "              #######################         " << std::endl;
	std::cout << "            ##############   ###########                  " << std::endl;
	std::cout << "          ###############################                  " << std::endl;
	std::cout << "         #########################                 " << std::endl;
	std::cout << "        #######################            " << std::endl;
	std::cout << "       ####################            " << std::endl;
	std::cout << "       ##################               " << std::endl;
	std::cout << "       ################                 " << std::endl;
	std::cout << "       #############                       " << std::endl;
	std::cout << "        ###############            " << "PACMAN" << std::endl;
	std::cout << "         ####################          " << std::endl;
	std::cout << "          ########################         " << std::endl;
	std::cout << "            ##########################                 " << std::endl;
	std::cout << "             ############################                  " << std::endl;
	std::cout << "               #######################                 " << std::endl;
	std::cout << "                 ####################              " << std::endl;
	std::cout << "                   ################            \n" << std::endl;


	std::cout << "Instructions:\n1. Use arrow Keys to move your character\n2. Eat the dots made by the Ghost to gain poins\n3. Don't get caught by the Ghost\n\n";
	std::cout << "E = Easy\nN = Normal\nH = Hard\n\nChoose your difficulty : ";  
}
void ShowMap()//this functions prints out the map array
{
	for (int i = 0; i < 18; i++) 
	{
		printf("%s\n", map[i]);
	}
}
void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}

class entity {
public:
	entity(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void move_x(int p)
	{
		if (map[y][x + p] == ' ') x += p;
	}

	void move_y(int p)
	{
		if (map[y + p][x] == ' ') y += p;
	}

	void move(int p, int q){
		x += p;
		y += q;
	}

	int get_x(){ return x; }
	int get_y(){ return y; }

	void draw(char p){
		map[x][y] = p;
		gotoxy(x, y); printf("%c", p);
	}

private:
	int x;
	int y;
};

struct walk 
{
	short walk_count;
	short x;
	short y;
	short back;
};

struct target 
{
	short x;
	short y;
};

std::vector<target> walk_queue;

std::vector<walk> BFSArray;

void AddArray(int x, int y, int wc, int back) //this function adds the changing elements to the map
{
	if (tmp_map[y][x] == ' ' || tmp_map[y][x] == '.')
	{
		tmp_map[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		BFSArray.push_back(tmp);
	}
}

void FindPath(int sx, int sy, int x, int y)
{
	memcpy(tmp_map, map, sizeof(map));
	BFSArray.clear();
	walk tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.walk_count = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);

	int i = 0;
	while (i < BFSArray.size()){
		if (BFSArray[i].x == x && BFSArray[i].y == y)
		{
			walk_queue.clear();
			target tmp2;
			while (BFSArray[i].walk_count != 0){
				tmp2.x = BFSArray[i].x;
				tmp2.y = BFSArray[i].y;
				walk_queue.push_back(tmp2);

				i = BFSArray[i].back;
			}

			break;
		}

		AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);

		i++;
	}

	BFSArray.clear();
}


int main()
{ 
	//size();
	bool running = true;
	int x = 15; // hero spawn
	int y = 16; // hero spawn
	int old_x;
	int old_y;
	std::string response;
	int ex = 1; //computer spawn
	int ey = 1; //computer spawn


	int pts = 0;

	intro();
	
	char difficulty;
	int speedmod = 3;

	std::cin >> difficulty;

	names();

	if (difficulty == 'N' || difficulty == 'n'){
		speedmod = 2;
	}
	else if (difficulty == 'H' || difficulty == 'h'){
		speedmod = 1;
	}

	system("cls");//clears screen
	ShowMap();
	PlaySound(TEXT("introSound.wav"), NULL, SND_SYNC);
	gotoxy(x, y); std::cout << "H";

	int frame = 0;

	FindPath(ex, ey, x, y);

	while (running){
		gotoxy(x, y); std::cout << " ";

		old_x = x;
		old_y = y;

		if (GetAsyncKeyState(VK_UP)){
			if (map[y - 1][x] == '.'){ y--; pts++ << PlaySound(TEXT("pacMan.wav"), NULL, SND_FILENAME  | SND_ASYNC); }
			else
			if (map[y - 1][x] == ' ') y--;
		}
		if (GetAsyncKeyState(VK_DOWN)){
			if (map[y + 1][x] == '.'){ y++; pts++ << PlaySound(TEXT("pacMan.wav"), NULL, SND_FILENAME | SND_ASYNC); }
			else
			if (map[y + 1][x] == ' ') y++;
		}
		if (GetAsyncKeyState(VK_LEFT)){
			if (map[y][x - 1] == '.'){ x--; pts++ << PlaySound(TEXT("pacMan.wav"), NULL, SND_FILENAME | SND_ASYNC); }
			else
			if (map[y][x - 1] == ' ') x--;
		}
		if (GetAsyncKeyState(VK_RIGHT)){
			if (map[y][x + 1] == '.'){ x++; pts++ << PlaySound(TEXT("pacMan.wav"), NULL, SND_FILENAME  | SND_ASYNC); }
			else
			if (map[y][x + 1] == ' ') x++;
		}

		if (old_x != x || old_y != y){
			FindPath(ex, ey, x, y);
		}

		

			
		

		gotoxy(x, y); std::cout << userLetter;

		map[ey][ex] = '.';
		gotoxy(ex, ey); std::cout << ".";

		if (frame%speedmod == 0 && walk_queue.size() != 0){
			ex = walk_queue.back().x;
			ey = walk_queue.back().y;
			walk_queue.pop_back();
		}

		gotoxy(ex, ey); std::cout << computerLetter;

		if (ex == x && ey == y)
		{
			PlaySound(TEXT("pacdies.wav"), NULL, SND_SYNC);
			break;
		}


		gotoxy(32, 18);
		gotoxy(32, 1); std::cout << pts;
		Sleep(100);
		frame++;
	}

	system("cls");
	std::cout << "You Lose and your score is: " << pts << std::endl;
	std::cout << "Would you like to play again? ";
	std::cin >> response;
	if (response == "Yes" || response == "yes" || response == "Y" || response == "y")
	{
		main();
	}
	system("pause");

	return 0;
}