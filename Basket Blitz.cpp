#include <iostream>
#include<conio.h>		//To include getch()
#include <windows.h>	//To include system(), setcursor()
#include <time.h>		//To include time()
#include <fstream>		//To save high score
#include <sstream>		//To convert string to integer

using namespace std;

#define SCREEN_WIDTH 119	//The Total width of window
#define SCREEN_HEIGHT 29	//The Total height of window
#define WIN_WIDTH 100		//The width of playzone

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//The Y_position of Diamonds
int diamondY[3];
//The X_position of Diamonds
int diamondX[3];

//The Y_position of Bombs
float bombY[1];
//The X_position of Bombs
int bombX[1];

//The Y_position of Ruby
float diamond2Y[1];
//The X_position of Ruby
int diamond2X[1];

//Number of Bombs
int bombFlag[1];
//Number of Diamonds
int diamondFlag[3];
//Number of Rubys
int diamond2Flag[1];
		
int BasketPos = WIN_WIDTH/2;
int score = 0;		//Final Score
int highscore;		//High Score
int preHighScore;	//Get the high score when the game is starting

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

//Make invisible the cursor
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

//Draw the Window boder
void drawBorder() {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		gotoxy(i, 0); cout << "#";
		gotoxy(i, SCREEN_HEIGHT); cout << "#";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(0, i); cout << "#";
		gotoxy(SCREEN_WIDTH, i); cout << "#";
	}
	for (int i = 1; i < SCREEN_HEIGHT; i++) {
		gotoxy(WIN_WIDTH, i); cout << "||";
	}
}

//Draw the middle line
void middleLine(){
	for (int i = 1; i < SCREEN_HEIGHT; i++){
		for(int j = 1; j < 6; j++){
			gotoxy(20 * j, i); cout << ":";
		}
	}
}

//Get the X_position of the Diamond where it should appear
void genDiamond(int ind){
	int X_Coordinate = 1 + rand() % 5;
	if		(X_Coordinate == 1) diamondX[ind] = 5;
	else if	(X_Coordinate == 2) diamondX[ind] = 25;
	else if	(X_Coordinate == 3) diamondX[ind] = 45;
	else if	(X_Coordinate == 4) diamondX[ind] = 65;
	else if	(X_Coordinate == 5) diamondX[ind] = 85;
}

//Get the X_position of the Bomb where it should appear
void genBomb(int ind){
	int BX_Coordinate = 1 + rand() % 5;
	if		(BX_Coordinate == 1) bombX[ind] = 5;
	else if	(BX_Coordinate == 2) bombX[ind] = 25;
	else if	(BX_Coordinate == 3) bombX[ind] = 45;
	else if	(BX_Coordinate == 4) bombX[ind] = 65;
	else if	(BX_Coordinate == 5) bombX[ind] = 85;
}

//Get the X_position of the Ruby where it should appear
void genDiamond2(int ind){
	int D2X_Coordinate = 1 + rand() % 5;
	if		(D2X_Coordinate == 1) diamond2X[ind] = 5;
	else if	(D2X_Coordinate == 2) diamond2X[ind] = 25;
	else if	(D2X_Coordinate == 3) diamond2X[ind] = 45;
	else if	(D2X_Coordinate == 4) diamond2X[ind] = 65;
	else if	(D2X_Coordinate == 5) diamond2X[ind] = 85;
}

//Drwa the Diamond
void drawDiamond(int ind){
	if( diamondFlag[ind] == true ){
		gotoxy(diamondX[ind], diamondY[ind]);   cout<< "   *   ";  
		gotoxy(diamondX[ind], diamondY[ind]+1); cout<< " ***** "; 
		gotoxy(diamondX[ind], diamondY[ind]+2); cout<< "*******"; 
		gotoxy(diamondX[ind], diamondY[ind]+3); cout<< " ***** "; 
        gotoxy(diamondX[ind], diamondY[ind]+4); cout<< "   *   ";  
	} 
}

//Erase the Diamond
void eraseDiamond(int ind){
	if( diamondFlag[ind] == true ){
		gotoxy(diamondX[ind], diamondY[ind])  ; cout<<"       ";  
		gotoxy(diamondX[ind], diamondY[ind]+1); cout<<"       "; 
		gotoxy(diamondX[ind], diamondY[ind]+2); cout<<"       "; 
		gotoxy(diamondX[ind], diamondY[ind]+3); cout<<"       "; 
		gotoxy(diamondX[ind], diamondY[ind]+4); cout<<"       "; 
	} 
}

//Draw the Bomb
void drawBomb(int ind){
	if( bombFlag[ind] == true ){
        gotoxy(bombX[ind], bombY[ind]);		cout<< " |±±±| ";
	    gotoxy(bombX[ind], bombY[ind]+1); 	cout<< "  /*\\ ";
	    gotoxy(bombX[ind], bombY[ind]+2); 	cout<< " |±±±| ";
	    gotoxy(bombX[ind], bombY[ind]+3); 	cout<< " |±±±| ";
	    gotoxy(bombX[ind], bombY[ind]+4); 	cout<< "  \\@/ "; 
	}
}

//Erase the Bomb
void eraseBomb(int ind){
	if( bombFlag[ind] == true ){
        gotoxy(bombX[ind], bombY[ind]); 	cout<< "       ";
	    gotoxy(bombX[ind], bombY[ind]+1); 	cout<< "       ";
	    gotoxy(bombX[ind], bombY[ind]+2); 	cout<< "       ";
	    gotoxy(bombX[ind], bombY[ind]+3); 	cout<< "       ";
	    gotoxy(bombX[ind], bombY[ind]+4); 	cout<< "       "; 
	}
}

//Drwa the Ruby
void drawDiamond2(int ind){
	if( diamondFlag[ind] == true ){
		gotoxy(diamondX[ind], diamondY[ind]);   cout<< "   *   ";  
		gotoxy(diamondX[ind], diamondY[ind]+1); cout<< " ***** "; 
		gotoxy(diamondX[ind], diamondY[ind]+2); cout<< "*******"; 
		gotoxy(diamondX[ind], diamondY[ind]+3); cout<< " ***** "; 
        gotoxy(diamondX[ind], diamondY[ind]+4); cout<< "   *   ";  
	} 
}

//Erase the Ruby
void eraseDiamond2(int ind){
	if( diamondFlag[ind] == true ){
		gotoxy(diamondX[ind], diamondY[ind])  ; cout<<"       ";  
		gotoxy(diamondX[ind], diamondY[ind]+1); cout<<"       "; 
		gotoxy(diamondX[ind], diamondY[ind]+2); cout<<"       "; 
		gotoxy(diamondX[ind], diamondY[ind]+3); cout<<"       "; 
		gotoxy(diamondX[ind], diamondY[ind]+4); cout<<"       "; 
	} 
}

//Reset the Diamond at the bottom of the window
void resetDiamond(int ind){
	eraseDiamond(ind);
	diamondY[ind] = 1;
	genDiamond(ind);
}

//Reset the Bomb at the bottom of the window
void resetBomb(int ind){
	eraseBomb(ind);
	bombY[ind] = 1;
	genBomb(ind);
}

//Reset the Ruby at the bottom of the window
void resetDiamond2(int ind){
	eraseDiamond2(ind);
	diamond2Y[ind] = 1;
	genDiamond2(ind);
}

//Drwa the Basket in position
void drawBasket() {
    gotoxy(BasketPos - 5, 24); cout << "#          #";		//BasketPos - 5, 24		45
    gotoxy(BasketPos - 5, 25); cout << "##        ##";		//BasketPos - 24, 24	26
    gotoxy(BasketPos - 5, 26); cout << " ##      ## ";		//BasketPos - 44, 24	6
    gotoxy(BasketPos - 5, 27); cout << "  ##    ##  ";		//BasketPos + 15, 24	65
    gotoxy(BasketPos - 5, 28); cout << "   ######   ";		//BasketPos + 35, 24	85
}

//Erase the basket
void eraseBasket() {
    gotoxy(BasketPos - 5, 24); cout << "            ";
    gotoxy(BasketPos - 5, 25); cout << "            ";
    gotoxy(BasketPos - 5, 26); cout << "            ";
    gotoxy(BasketPos - 5, 27); cout << "            ";
    gotoxy(BasketPos - 5, 28); cout << "            ";
}

//Collision of Bomb and basket
int bomb_collision(){
	if( bombY[0]+3 >= 24 ){
		if( bombX[0] + 4 - BasketPos >= 0 && bombX[0] + 4 - BasketPos < 9  ){
			return 1;
		}
	}
	return 0;
}

//Collision of Diamond_0 and basket
int collision_1(){
	if( diamondY[0] >= 23 ){
		if( diamondX[0] + 4 - BasketPos >= 0 && diamondX[0] + 4 - BasketPos < 9  ){
			return 1;
		}
	}
	return 0;
} 

//Collision of Diamond_1 and basket
int collision_2(){
	if( diamondY[1] >= 23 ){
		if( diamondX[1] + 4 - BasketPos >= 0 && diamondX[1] + 4 - BasketPos < 9  ){
			return 1;
		}
	}
	return 0;
}

//Collision of Diamond2 and basket
int diamond2_collision(){
	if( diamond2Y[0] >= 23 ){
		if( diamond2X[0] + 4 - BasketPos >= 0 && diamond2X[0] + 4 - BasketPos < 9  ){
			return 1;
		}
	}
	return 0;
}

//Dispaly GameOver messege at the end of the game
void gameover(){
	system("cls");
	gotoxy((SCREEN_WIDTH/2)-11, 4); cout << "--------------------------";
	gotoxy((SCREEN_WIDTH/2)-11, 6); cout << "-------- Game Over -------";
	gotoxy((SCREEN_WIDTH/2)-11, 8); cout << "--------------------------";
	gotoxy((SCREEN_WIDTH/2)-14, 10); cout << "Press any key to go back to menu.";
	gotoxy((SCREEN_WIDTH/2)-6, 12); cout << "Your score is: " << score;
	
	if(score > preHighScore){
		gotoxy((SCREEN_WIDTH/2)-6, 15); cout << "New High Score !!!";
	}
	getch();
}

//Display score in game window
void updateScore(){
	if(score >= highscore){
		highscore = score;
	}
	gotoxy(WIN_WIDTH + 5, 5); cout <<"Score: "<< score << endl;
}

int getHighScore() {
    string hscore;
    ifstream file("HighScore.txt");

    if (file.is_open()) {
        if (file >> hscore && !hscore.empty()) {
            istringstream(hscore) >> highscore;
        } else {
            highscore = 0; // Empty file or failed to read, set highscore to 0
        }
        file.close();
    } else {
        // File does not exist, create it and write 0
        ofstream newFile("HighScore.txt");
        newFile << "0";
        newFile.close();
        highscore = 0; // Initialize highscore to 0
    }
    return highscore;
}

//Save the new high score
void saveHighScore() {
    ofstream file("HighScore.txt"); 
    if (file.is_open()) {
        file << highscore; 
        file.close(); 
    }
}
//Dispaly instructions
void instructions(){
	system("cls");
	gotoxy((SCREEN_WIDTH/2)-6, 4); cout << "Instructions";
	gotoxy((SCREEN_WIDTH/2)-9, 5); cout << "------------------";
	gotoxy((SCREEN_WIDTH/2)-15, 8); cout << "Collect Diamonds to get score.";
		gotoxy((SCREEN_WIDTH/2)-15, 10); cout << "If you hit a bomb you will lose the game.";
	gotoxy((SCREEN_WIDTH/2)-15, 12); cout << "Press 'a' to move left.";
	gotoxy((SCREEN_WIDTH/2)-15, 14); cout << "Press 'd' to move right.";
	gotoxy((SCREEN_WIDTH/2)-15, 16); cout << "Press 'escape' to exit.";
	gotoxy((SCREEN_WIDTH/2)-15, 18); cout << "Press any key to go back to menu.";
	getch();
}

//Dispalt Press any key to start in game window
void pressAnyKey_inBoder(){
	gotoxy(6, SCREEN_HEIGHT/2);cout<<"Press";
	gotoxy(26, SCREEN_HEIGHT/2);cout<<"any";
	gotoxy(45, SCREEN_HEIGHT/2);cout<<"key";
	gotoxy(65, SCREEN_HEIGHT/2);cout<<"to";
	gotoxy(85, SCREEN_HEIGHT/2);cout<<"start";
	getch();
	gotoxy(6, SCREEN_HEIGHT/2);cout<<"     ";
	gotoxy(26, SCREEN_HEIGHT/2);cout<<"   ";
	gotoxy(45, SCREEN_HEIGHT/2);cout<<"   ";
	gotoxy(65, SCREEN_HEIGHT/2);cout<<"  ";
	gotoxy(85, SCREEN_HEIGHT/2);cout<<"     ";
}

void play(){
	
	BasketPos = -1 + WIN_WIDTH/2;
	score = 0;
	diamondFlag[0] = 1;
	diamondFlag[1] = 0;
	diamondY[0] = diamondY[1] = 1;
	
	bombFlag[0] = 1;
	bombY[0] = 1;
	
	diamond2Flag[0] = 1;
	diamond2Y[0] = 1;
	  
	system("cls");
	 
	drawBorder();
	middleLine(); 
	updateScore();
	genDiamond(0);
	genDiamond(1);
	
	genBomb(0);
	
	genDiamond2(0);
	
	//Some informations
	gotoxy(WIN_WIDTH + 4, 2);cout<<"BASKET BLITZ";
	gotoxy(WIN_WIDTH + 4, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 4, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 3, 12);cout<<"High Score:";
	gotoxy(WIN_WIDTH + 8, 14);cout<< highscore;
	gotoxy(WIN_WIDTH + 6, 22);cout<<"Control ";
	gotoxy(WIN_WIDTH + 6, 23);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 3, 24);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 3, 25);cout<<" D Key - Right";
	
	//Call the function
	pressAnyKey_inBoder();
	
	while(1){
//Position of basket when click A or D
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){		//To make basket move to left
				if( BasketPos > 25 )
					BasketPos -= 20;
			}
			if( ch=='d' || ch=='D' ){		//To make basket move to right
				if( BasketPos < 85 )
					BasketPos += 20;
			} 
			if(ch==27){						//Escape the game
				break;
			}
		} 
	
		drawBasket();
		middleLine(); 
		drawDiamond(0); 
		drawDiamond(1);
		drawBomb(0);
		drawDiamond2(0);
		
		if( collision_1() == 1){	//Check the diamond collide with the basket
			score++;				//increase score by 1
			updateScore();
		} 
		
		if( collision_2() == 1){	//Check the diamond collide with the basket
		score++;					//increase score by 1
		updateScore();
		} 
		
		if( diamond2_collision() == 1){	//Check the ruby collide with the basket
		score++;					//increase score by 1
		updateScore();
		}
		
		if( bomb_collision() == 1){	//Check the bomb collide with the basket
			gameover();				//End the game
			saveHighScore();		//save the new high score
			return;
		} 
		
		Sleep(75);		//Speed of Objects
			eraseBasket();
			eraseDiamond(0);
			eraseDiamond(1);
			eraseBomb(0);
			eraseDiamond2(0);
		
		if( diamondY[0] == 10 )
			if( diamondFlag[1] == 0)
				diamondFlag[1] = 1;
		
		if( diamondFlag[0] == 1)
			diamondY[0] += 1;
		
		if( diamondFlag[1] == 1)
			diamondY[1] += 1;
			
		if( bombFlag[0] == 1)
			bombY[0] += 1.7;
			
		if( diamond2Flag[0] == 1)
			diamond2Y[0] += 1.5;

//Disappear the diamond 0		 
		if( diamondY[0] > SCREEN_HEIGHT- 6){
			resetDiamond(0);
		}
//Disappear the diamond 1
		if( diamondY[1] > SCREEN_HEIGHT- 6){
			resetDiamond(1);
		}
//Disappear the bomb 0
		if( bombY[0] > SCREEN_HEIGHT- 6){
			resetBomb(0);
		}
//Disappear the ruby 0		
		if( diamond2Y[0] > SCREEN_HEIGHT- 6){
			resetDiamond2(0);
		}
	}
}

//Title
void title(){
	gotoxy(10, 4); 	cout << "±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
	gotoxy(10, 5); 	cout << "±±±±±±     ±±±±     ±±±±±    ± ±±±± ±     ±       ±±±±±±±±±     ±± ±±±±±       ±       ±      ±±±±±±";
	gotoxy(10, 6); 	cout << "±±±±±± ±±±± ±± ±±±±± ±± ±±±±±± ±±± ±± ±±±±±±±± ±±±±±±±±±±±± ±±±± ± ±±±±±±±± ±±±±±±± ±±±±±±±±± ±±±±±±";
	gotoxy(10, 7); 	cout << "±±±±±± ±±±± ± ±±±±±±± ± ±±±±±± ±± ±±± ±±±±±±±± ±±±±±±±±±±±± ±±±± ± ±±±±±±±± ±±±±±±± ±±±±±±±± ±±±±±±±";
	gotoxy(10, 8); 	cout << "±±±±±± ±  ±±± ±     ± ±±    ±±   ±±±±     ±±±± ±±±±±±±±±±±±  ±± ±± ±±±±±±±± ±±±±±±± ±±±±±±± ±±±±±±±±";
	gotoxy(10, 9); 	cout << "±±±±±± ±±±± ± ±±±±±±± ±±±±±± ± ±± ±±± ±±±±±±±± ±±±±±±±±±±±± ±±±± ± ±±±±±±±± ±±±±±±± ±±±±±± ±±±±±±±±±";
	gotoxy(10, 10); cout << "±±±±±± ±±±± ± ±±±±±±± ±±±±±± ± ±±± ±± ±±±±±±±± ±±±±±±±±±±±± ±±±± ± ±±±±±±±± ±±±±±±± ±±±±± ±±±±±±±±±±";
	gotoxy(10, 11); cout << "±±±±±±     ±± ±±±±±±± ±±    ±± ±±±± ±     ±±±± ±±±±±±±±±±±±     ±±     ±       ±±±± ±±±±      ±±±±±±";
	gotoxy(10, 12); cout << "±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
	
}

int main(){
	
	preHighScore = getHighScore();
	
	//Make the cursor disappear
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	
	do{
		system("cls");
		title();
		gotoxy((SCREEN_WIDTH/2)-5, 15); 	cout<<"1. Start Game";
		gotoxy((SCREEN_WIDTH/2)-5, 17); cout<<"2. Instructions";	 
		gotoxy((SCREEN_WIDTH/2)-5, 19); cout<<"3. Quit";
		gotoxy((SCREEN_WIDTH/2)-5, 21); cout<<"Select option: ";
		gotoxy((SCREEN_WIDTH/2)-5, 25); cout<<"High Score: " << highscore;
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;	
}
