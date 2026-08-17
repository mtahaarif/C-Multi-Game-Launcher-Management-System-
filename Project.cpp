#include <iostream>
#include <SFML/Graphics.hpp>
#include<Windows.h>
#include<thread>
#include<time.h> //to generate random entity
#include<conio.h> //using functions such as getsh/ getshe
#include<stdlib.h>
#include<string.h>

using namespace std;

void win_checker(sf::RectangleShape& line, sf::RectangleShape& line2, sf::RectangleShape& line3, sf::RectangleShape& line4, char Arr[], sf::Text& text);
void Tic_Tac_Toe(sf::RenderWindow& window, sf::Text& text , sf::Texture &Background,sf::Sprite &bgSprite, sf::Font &ARIAL);
void Flappy_bird();
void Tetris();
sf::RenderWindow window;


int main() {

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 750, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(1500, 900), "Tic Tac Toe");
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
	sf::Font ARIAL;
	sf::Text Menu;
	ARIAL.loadFromFile("psfont.otf");
	Menu.setFillColor(sf::Color::White);
	Menu.setCharacterSize(50);
	Menu.setFont(ARIAL);
	sf::Texture Background;
	Background.loadFromFile("bg.jpeg");
	sf::Sprite bgSprite;
	bgSprite.setTexture(Background);


	while (window.isOpen()){
		sf::Event Event;
		while (window.pollEvent(Event)) {
			switch (Event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}
		window.clear(sf::Color::White);
		window.draw(bgSprite);
		Menu.setString("Welcome to Gameboy");
		Menu.setPosition(500, 20);
		window.draw(Menu);
		Menu.setString("Select Your Option");
		Menu.setPosition(50, 200);
		window.draw(Menu);
		Menu.setString("1.Tic Tac Toe.");
		Menu.setPosition(50, 280);
		window.draw(Menu);
		Menu.setString("2.Flappy Bird.");
		Menu.setPosition(50, 330);
		window.draw(Menu);
		Menu.setString("3.Tetris.");
		Menu.setPosition(50, 380);
		window.draw(Menu);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			Tic_Tac_Toe(window, Menu, Background, bgSprite, ARIAL);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
			window.close();
			Flappy_bird();
		
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			window.close();
			Tetris();

		}
		
		window.display();
	}


	return 0;
}
void Tic_Tac_Toe(sf::RenderWindow& window, sf::Text &text, sf::Texture& Background, sf::Sprite& bgSprite,sf::Font &ARIAL) {
	int counter = 3;
	Background.loadFromFile("R.jpeg");
	bgSprite.setTexture(Background);
	sf::RectangleShape L1(sf::Vector2f(20, 565)), L2(sf::Vector2f(565, 20)), L3(sf::Vector2f(800, 20.f)), L4(sf::Vector2f(800, 20.f));
	
	L3.rotate(45);
	L4.rotate(135);
	L3.setFillColor(sf::Color::Yellow);
	L4.setFillColor(sf::Color::Yellow);
	L3.setPosition(440, 80);
	L4.setPosition(1040, 100);

	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Yellow);

	sf::Text input;
	input.setCharacterSize (200);
	ARIAL.loadFromFile("ARIAL.ttf");
	input.setFont(ARIAL);
	input.setFillColor(sf::Color::Blue);
	input.setString("X");

	sf::Text Com;
	Com.setCharacterSize(200);
	Com.setFillColor(sf::Color::Green);
	Com.setFont(ARIAL);
	Com.setString("O");

	bool displayCharacter[18] = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
	char Arr[10] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

	while (window.isOpen()) {
		srand(time(NULL));
		int* num = new int;
			*num= rand() % 9 + 1;
		sf::Event Event;
		while (window.pollEvent(Event)) {
			switch (Event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}
		
		if (counter % 2 == 0) {
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && Arr[1] == ' ') {
				displayCharacter[0] = true;
				Arr[1] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && Arr[2] == ' ') {
				displayCharacter[1] = true;
				Arr[2] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && Arr[3] == ' ') {
				displayCharacter[2] = true;
				Arr[3] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && Arr[4] == ' ') {
				displayCharacter[3] = true;
				Arr[4] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && Arr[5] == ' ') {
				displayCharacter[4] = true;
				Arr[5] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && Arr[6] == ' ') {
				displayCharacter[5] = true;
				Arr[6] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && Arr[7] == ' ') {
				displayCharacter[6] = true;
				Arr[7] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && Arr[8] == ' ') {
				displayCharacter[7] = true;
				Arr[8] = 'w';
				counter++;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && Arr[9] == ' ') {
				displayCharacter[8] = true;
				Arr[9] = 'w';
				counter++;
			}
		}

		if (counter % 2 != 0 && sf::Keyboard::isKeyPressed) {
			for(int i=1; i<10;i++){
				if (*num == i && Arr[i] == ' ') {
					displayCharacter[i+8] = true;
					Arr[i] = 'p';
					counter++;

				}
			}
		}
		window.clear(sf::Color::White);
		window.draw(bgSprite);
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				if (displayCharacter[i + (j * 3)]) {
					input.setPosition(450 + (200 * i), 50 + (j * 200));
					window.draw(input);
				}
			}
		}
	
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				if (displayCharacter[i + (j * 3)+9]) {
					Com.setPosition(450 + (200 * i), 50 + (j * 200));
					window.draw(Com);
				}
			}
		}
			L1.setFillColor(sf::Color::Red);
			L2.setFillColor(sf::Color::Red);
			
			L1.setPosition({ 612,88 });
			window.draw(L1);
			L1.setPosition({ 807,88 });
			window.draw(L1);
			L2.setPosition({ 437,263 });
			window.draw(L2);
			L2.setPosition({ 437,458 });
			window.draw(L2);

			L1.setFillColor(sf::Color::Yellow);
			L2.setFillColor(sf::Color::Yellow);

			win_checker(L2, L1, L3,L4 ,Arr, text);
			text.setString("Welcome to Tic Tac Toe ");
			text.setPosition(500, 20);
			window.draw(text);
			window.display();
			delete num;
		}
	}
	
void win_checker(sf::RectangleShape& line, sf::RectangleShape& line2, sf::RectangleShape& line3, sf::RectangleShape& line4, char Arr[], sf::Text& text) {

	for (int i = 0; i < 3; i++) {
	if (Arr[1+(i*3)] != ' ' && Arr[1 + (i * 3)] == Arr[2 + (i * 3)] && Arr[2 + (i * 3)] == Arr[3 + (i * 3)]) {
		line.setPosition(420, 150+(i*200));
		window.draw(line);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (Arr[1+i] != ' ' && Arr[1+i] == Arr[4+i] && Arr[4+i] == Arr[7+i]) {
			line2.setPosition(500+(200*i), 100);
			window.draw(line2);
		}
	}
		if (Arr[1] != ' ' && Arr[1] == Arr[5] && Arr[5] == Arr[9]) {
			line3.setPosition(440, 80);
			window.draw(line3);
		}
		else if (Arr[3] != ' ' && Arr[3] == Arr[5] && Arr[5] == Arr[7]) {
			line4.setPosition(1040, 100);
			window.draw(line4);
		}
	}

#define SCREEN_WIDTH 90
#define WIN_WIDTH 70
#define SCREEN_HEIGHT 26
#define GAP_SIZE 7

using namespace std;

void play();
void instructions();
void drawBorder();
void genPipe(int);
void updateScore();
void drawBird();
void drawPipe(int);
int collision();
void gameover();
void eraseBird();
void erasePipe(int);
void setcursor(bool, DWORD);
void instructions();
void gotoxy(int, int);

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3], gapPos[3], pipeFlag[3];
int birdPos{ 6 }, score{ 0 };
char bird[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };

void Flappy_bird(){
	setcursor(0, 0);
	srand((unsigned)time(NULL));

	do {
		system("cls");
		gotoxy(10, 5); cout << "--------------------------------";
		gotoxy(10, 6); cout << "|          Flappy Bird   	    |";
		gotoxy(10, 7); cout << "--------------------------------";

		gotoxy(10, 9); cout << "1. Start Game";
		gotoxy(10, 10); cout << "2. Instructions";
		gotoxy(10, 11); cout << "3. Quit";

		gotoxy(10, 13); cout << "Select option:  ";
		char op = _getche();

		if (op == '1')
		{
			play();
		}
		else if (op == '2')
		{
			instructions();
		}
		else if (op == '3')
		{
			exit(0);
		}

	} while (true);


}

void play()
{
	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 1;
	pipePos[0] = pipePos[1] = 4;

	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();

	gotoxy(WIN_WIDTH + 5, 2); cout << "Flappy Bird";
	gotoxy(WIN_WIDTH + 6, 4); cout << "- - - - - - -";
	gotoxy(WIN_WIDTH + 6, 6); cout << "- - - - - - -";
	gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
	gotoxy(WIN_WIDTH + 7, 13); cout << "- - - - - - ";
	gotoxy(WIN_WIDTH + 2, 14); cout << "Spacebar = jump";

	gotoxy(10, 5); cout << "Press any key to start";
	_getch();
	gotoxy(10, 5); cout << "                       ";

	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 32) // space ascii
			{
				if (birdPos > 3)
				{
					birdPos -= 4;
				}
			}
			if (ch == 27) //esc button - return to main
			{
				break;
			}
		}
		drawBird();
		drawPipe(0);
		drawPipe(1);

		if (collision() == 1) {
			gameover();
			return;
		}
		Sleep(100);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2) {
			gameover();
			return;
		}

		if (pipeFlag[0] == 1)
		{
			pipePos[0] += 2;

		}
		if (pipeFlag[1] == 1)
			pipePos[1] += 2;
		if (pipePos[0] >= 40 && pipePos[0] < 42)
		{
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}

		if (pipePos[0] > 68) {
			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}


	}


}

void drawBorder()
{
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		gotoxy(i, 0);  cout << " | | ";
		gotoxy(i, SCREEN_HEIGHT); cout << "| | ";

	}
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(0, i);  cout << " | | ";
		gotoxy(i, SCREEN_WIDTH); cout << "| | ";

	}
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(WIN_WIDTH, i); cout << " | | ";

	}

}

void genPipe(int index)
{
	gapPos[index] = 3 + rand() % 14;
}

void updateScore() {
	gotoxy(WIN_WIDTH + 7, 5);
	cout << "Score: " << score << endl;
}

void drawBird() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + birdPos);
			cout << bird[i][j];
		}
	}
}

void drawPipe(int ind)
{
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
			cout << "E M E";
		}
		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "E M E";

		}
	}
}

int collision() {
	if (pipePos[0] >= 61) {
		if (birdPos < gapPos[0] || birdPos>gapPos[0] + GAP_SIZE) {
			return 1;
		}
	}
	return 0;
}

void gameover()
{
	system("cls");
	cout << endl;
	cout << "\t\t - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "\t\t - - - - - - - - - - - Game Over - - - - - - - - - -" << endl;
	cout << "\t\t - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
	cout << "\t\tPress any key to go back to menu.";
	_getch();

}

void eraseBird() {
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 6; j++)
		{
			gotoxy(j + 2, i + birdPos);
			cout << " ";
		}
	}
}

void erasePipe(int ind)
{
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
			cout << "     ";
		}
		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "     ";

		}
	}
}


void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);

}

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void instructions()
{
	system("cls");
	cout << "Instructions";
	cout << "\n- - - - - - - - - - - - ";
	cout << "\n Press Spacebar to make bird fly";
	cout << "\n\nPress any key to go back to menu";
	_getch();
}

wstring gameblock[7];
int spacewidth = 12;                 //        __|  17
int spaceheight = 18;               //         12 
unsigned char* pspace = nullptr;    //pointer for playing space currently pointing nowhere

int screenwidth = 80;       // console screen size height 
int screenheight = 30;     //conslode screen size width


int rotate(int px, int py, int r) {                         ///////step 2///////
	switch (r % 4) {										/// ROTATION FUNCTION/////
	case 0: return py * 4 + px;								//a function that takes in the degree of rotation as R and returns the new location of array of a block
		break;
	case 1:return 12 + py - (px * 4);
		break;
	case 2: return 15 - (py * 4) - px;
		break;
	case 3: return 3 - py + (px * 4);
		break;
	}
}

bool Doesfit(int ngameblock, int rotation, int posx, int posy) {
	for (int px = 0; px < 4; px++) {
		for (int py = 0; py < 4; py++) {

			int pi = rotate(px, py, rotation);    //getting the index after rotation

			int fi = (posy + py) * spacewidth + (posx + px);   //get index in the psace	

			if ((posx + px) >= 0 && posx + px < spacewidth) {
				if ((posy + py) >= 0 && posy + py < spaceheight) {
					if (gameblock[ngameblock][pi] == L'X' && pspace[fi] != 0) {
						return false;
					}
				}
			}

		}
	}



	return true;
}


void Tetris() {

	gameblock[0].append(L"..X.");      //////////////step 1 //////////
	gameblock[0].append(L"..X.");      //we have created a wide string and made 7 most common Peices used in tetris aand stored them in a 1d array
	gameblock[0].append(L"..X.");      //we used wstring because the lenghh of the string has become fairly large due to appending.
	gameblock[0].append(L"..X.");

	gameblock[1].append(L"....");
	gameblock[1].append(L".XX.");
	gameblock[1].append(L".XX.");
	gameblock[1].append(L"....");

	gameblock[2].append(L".X..");
	gameblock[2].append(L".XX.");
	gameblock[2].append(L"..X.");
	gameblock[2].append(L"....");

	gameblock[3].append(L"..X.");
	gameblock[3].append(L".XX.");
	gameblock[3].append(L"..X.");
	gameblock[3].append(L"....");

	gameblock[4].append(L"....");
	gameblock[4].append(L".XX.");
	gameblock[4].append(L"..X.");
	gameblock[4].append(L"..X.");

	gameblock[5].append(L"....");
	gameblock[5].append(L".XX.");
	gameblock[5].append(L".X..");
	gameblock[5].append(L".X..");

	gameblock[6].append(L"..X.");
	gameblock[6].append(L".XX.");
	gameblock[6].append(L".X..");
	gameblock[6].append(L"....");



	pspace = new unsigned char[spacewidth * spaceheight];     ////step 4/// creeating playing space
	for (int x = 0; x < spacewidth; x++) {
		for (int y = 0; y < spaceheight; y++) {
			pspace[y * spacewidth + x] = (x == 0 || y == spaceheight - 1 || x == spacewidth - 1) ? 9 : 0;
		}
	}


	wchar_t* screen = new wchar_t[screenwidth * screenheight];  /////step 5////////
	for (int i = 0; i < screenwidth * screenheight; i++) {       /////using windows liabrary we are making a screen of wchar type and storing it with emoty spaces.
		screen[i] = L' ';
	}
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);    /////using the windows.h liabrary to initaialize the screen with read and write functionalities.
	SetConsoleActiveScreenBuffer(hConsole);						//we can access the screen using handle and the screen is stored in hconsole variable.
	DWORD dwBytesWritten = 0;


	//game varable///
	int currentpeice = 2;
	int currentrotation = 0;
	int currentX = spacewidth / 2;
	int currentY = 0;
	bool bkey[4];
	bool brotatehold = true;

	int speed = 20;
	int speedcounter = 0;
	bool bforcedown = false;
	int score = 0;


	bool GameOver = false;       /////step 6/////game loop

	while (!GameOver) {


		/////game timings///

		this_thread::sleep_for(50ms);
		speedcounter++;
		bforcedown = (speedcounter == speed);



		/////input///
		for (int k = 0; k < 4; k++)								// R   L   D   Z
			bkey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;    //get a sync key, hexdecimals value for keyboard keys =, an array of n=boolean


		/////game logic/////
		if (bkey[1]) {
			if (Doesfit(currentpeice, currentrotation, currentX - 1, currentY)) {
				currentX = currentX - 1;
			}
		}

		if (bkey[0]) {
			if (Doesfit(currentpeice, currentrotation, currentX + 1, currentY)) {
				currentX = currentX + 1;
			}
		}

		if (bkey[2]) {
			if (Doesfit(currentpeice, currentrotation, currentX, currentY + 1)) {
				currentY = currentY + 1;
			}
		}

		if (bkey[3]) {
			if (Doesfit(currentpeice, currentrotation + 1, currentX, currentY)) {
				if (brotatehold) {
					currentrotation = currentrotation + 1;
					brotatehold = false;
				}
			}

		}
		else {
			brotatehold = true;
		}


		if (bforcedown) {
			if (Doesfit(currentpeice, currentrotation, currentX, currentY + 1)) {
				currentY++;
			}
			else {
				//locking mechanism

				for (int px = 0; px < 4; px++) {
					for (int py = 0; py < 4; py++) {
						if (gameblock[currentpeice][rotate(px, py, currentrotation)] == L'X') {
							pspace[(currentY + py) * spacewidth + (currentX + px)] = currentpeice + 1;
						}
					}
				}

				//check lines
				for (int py = 0; py < 4; py++) {
					if (currentY + py < spaceheight - 1) {

						bool bline = true;
						for (int px = 0; px < spacewidth - 1; px++) {
							bline &= (pspace[(currentY + py) * spacewidth + px]) != 0;
						}
						if (bline) {
							// Removing line
							for (int px = 1; px < spacewidth - 1; px++) { // Start from px = 1 instead of 0
								for (int py2 = currentY + py; py2 > 0; py2--) {
									pspace[py2 * spacewidth + px] = pspace[(py2 - 1) * spacewidth + px];
								}
								pspace[px] = 0; // Set the top row to empty

								score += 25;
							}
						}

					}
				}

				//chose next peice
				currentX = spacewidth / 2;
				currentY = 0;
				currentrotation = 0;
				currentpeice = rand() % 7;

				//peice does not fit
				GameOver = !Doesfit(currentpeice, currentrotation, currentX, currentY);

			}
			speedcounter = 0;
		}

		// Draw Score
		swprintf_s(&screen[2 * screenwidth + screenheight + 6], 16, L"SCORE: %8d", score);

		//game space
		for (int x = 0; x < spacewidth; x++) {
			for (int y = 0; y < spaceheight; y++) {
				screen[(y + 2) * screenwidth + (x + 2)] = L" OOOOOOO=#"[pspace[y * spacewidth + x]];
			}
		}

		//current peice
		for (int px = 0; px < 4; px++) {
			for (int py = 0; py < 4; py++) {
				if (gameblock[currentpeice][rotate(px, py, currentrotation)] == L'X') {
					screen[(currentY + py + 2) * screenwidth + (currentX + px + 2)] = L'O';
				}
			}
		}
		//display screen
		WriteConsoleOutputCharacter(hConsole, screen, screenwidth * screenheight, { 0,0 }, &dwBytesWritten);    //printing our screen starts according to the dimensions and starting positions

	}

	CloseHandle(hConsole);
	cout << "Game Over!! Score:" << score << endl;
	system("pause");
}