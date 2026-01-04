#include<iostream>
#include<string>
#include <ctime>
#include <windows.h>
#include<conio.h>
#include <fstream>
using namespace std;


//function prototypes
void setRandomShips(char board[10][10]);
void vsComputer(char playerBoard[10][10], char computerBoard[10][10]);
void computerAttack(char playerBoard[10][10], int &computerScore);
void clearBoard(char board[10][10]);
void updateScore(int &score);
void displayresult(int player1Score, int player2Score);
void showgamemenu();
void playerattack(char opponentboard[10][10], int &playerScore);
void initializeboard(char board[10][10]);
void printboard(char board[10][10], bool hideShips);
void vsplayer(char board1[10][10], char board2[10][10]);
void manuallysetships(char board[10][10]);
void clearScreen();
void setcolor(int textColor, int bgColor);
int choosecolor();
void tripleboard(char myboard[10][10], char enemyboard[10][10]);

void saveToLeaderboard(string name, int score);
void viewLeaderboard();

//global variables
//player ships health
int p1h[5] = {5, 4, 3, 3, 2};
int p2h[5] = {5, 4, 3, 3, 2};

//number of ships alive
int p1ship = 5;
int p2ship = 5;

// Player Info
string p1name = "Player 1";
string p2name = "Player 2";
int p1c = 14; 
int p2c = 14;

// Turn player
int turn = 1; 


//clear board function
void clearBoard(char board[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = '~';
        }
    }
}
void updateScore(int &score) {
    score += 10;
}


//random placement of ships by computer
void setRandomShips(char board[10][10]) {
    srand(time(0));
    int size_ships[5] = {5,4,3,3,2}; //ye ships k sizes hain

    for (int i = 0; i < 5; i++) {
        int size = size_ships[i];
        char konsi_ship = '1' + i;
        bool placed = false;

        while (!placed) {
            int row, col;
            //since 0-9
            row = rand() % 10;
            col = rand() % 10;
            //checking the placement whether vertical or horizontal 
            bool pos = rand() % 2;
            //validtion
            bool is_valid = true;


            //ship placement validation
            if (pos == true) {
                //yahan validation of size before placing
                if (col + size > 10) {  //for horizontal
                    is_valid = false;
                }
                else {
                    //if not empty
                    for (int i = 0; i < size; i++) {
                        if (board[row][col + i] != '~') {
                            is_valid = false;
                        }
                    }
                }
            }
            else {//for vertical
                if (row + size > 10) {
                    is_valid = false;
                }
                else {
                    //if not empty
                    for (int i = 0; i < size; i++) {
                        if (board[row + i][col] != '~') {
                            is_valid = false;
                        }
                    }
                }
            }
            //now placing ship if valid
            if (is_valid) {
                if (pos) {
                    for (int i = 0; i < size; i++) {
                        board[row][col + i] = konsi_ship; 
                    }
                }
                else {
                    for (int i = 0; i < size; i++) {
                        board[row + i][col] = konsi_ship;
                    }
                }
                placed = true; //placed
            }
        }
    }
}

//computer attack st a
void computerAttack(char playerBoard[10][10], int &computerScore) {
    int row, col;
    //infinite shots loop
    while (true) {
        row = rand() % 10;
        col = rand() % 10;
        //checking if already attacked
    if (playerBoard[row][col] != 'X' && playerBoard[row][col] != 'O' && playerBoard[row][col] != 'P')
    {
        break;
    }
    }

    cout <<"computer is attacking: " << row << ","<< col<<endl;


    //hitting logic
    if (playerBoard[row][col] >= '1' && playerBoard[row][col] <= '5') 
    {
        char konsi_ship = playerBoard[row][col];
        int index = konsi_ship - '1';
        playerBoard[row][col] = 'X'; //this means hit
        computerScore += 10;//gives scores to computer
        p1h[index]--;

        //now check if 0
        if (p1h[index] == 0) 
        {
            cout << "SUNK ";
            p1ship--;
            for (int r = 0; r < 10; r++) 
            {
                for (int c = 0; c < 10; c++) 
                {
                    if (playerBoard[r][c] == konsi_ship) {
                        playerBoard[r][c] = 'P'; //mark as sunk
                    }
                }
            }
        }
    }
    else {
        playerBoard[row][col] = 'O';//means miss
        computerScore -= 1;
    }
}


//gameplay
void vsComputer(char playerBoard[10][10], char computerBoard[10][10]) {
    int player_score = 0, comp_score = 0;

    //resetting the board
    clearBoard(playerBoard);
    clearBoard(computerBoard);

    turn = 1;




    //apna code yahan daalo player ship placement waala
    manuallysetships(playerBoard);
    


    //computer ships placement
    setRandomShips(computerBoard);


    bool gameover = false;
    
    while (!gameover) {
        // turn = 1;
        clearScreen();
        turn = 1;
        cout << "=== " << p1name << "'s turn ===" << endl;
        tripleboard(playerBoard, computerBoard);
        //player waala attack yahan aye ga
        playerattack(computerBoard, player_score);

        //now checkiing if player wins
        if (p2ship == 0) 
        {
            clearScreen();
            cout << "==== " << p1name << " won! ===" << endl;
            tripleboard(playerBoard, computerBoard);
            displayresult(player_score, comp_score);
            gameover = true;
            break;
        }
        


        //now computer turn
        clearScreen();
        turn = 2;
        cout << "=== Computers turn ===\n";
        tripleboard(computerBoard, playerBoard);


        //mein yahan computer attack daal rha
        computerAttack(playerBoard, comp_score);

        cout << "press key to continue\n";
        getch();

        clearScreen();
        //showing boards after computer attack
        tripleboard(playerBoard, computerBoard);


        //now checking if comp wins
        if (p1ship == 0) 
        {
            clearScreen();
            cout << "==== computer won ===" << endl;
            tripleboard(playerBoard, computerBoard);
            displayresult(player_score, comp_score);
            gameover = true;
            break;
        }
        


        //ship detection waaala yahan code 
        

        //end pe gameover waaly ko break krna kisi tarah usko true krke
    }

    //winner
    

}

// colours const
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;



//change color backgroung and text
void setcolor(int textColor, int bgColor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
//clear screen
void clearScreen()
{
    system("CLS");
}
// by inputing colour change to int code
int choosecolor()
{
    string c;
    cout << "Color List :" <<endl <<endl;
    cout << " GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE" << endl <<endl; 
    cout << "Type color name: ";
    cin >> c ;

    if(c == "GREEN" || c == "green")
    {
        return 10;   
    } 
    if(c == "CYAN" || c == "cyan") 
    {
        return 11;      
    }
    if(c == "RED" || c == "red")
    {
      return 12;        
     }
    if(c == "MAGENTA" || c == "magenta") 
    {
        return 13; 
    }
    if(c == "WHITE" || c == "white")
    {
      return 15;    
    }
    return 14; 
}
//initialize the board
void initializeboard(char board[10][10])
{
    for(int i=0 ;i<10; i++)
        for(int j=0 ; j<10 ; j++)
            board[i][j]= '~';
            
    // reset variables 
    p1ship = 5;
    p2ship = 5;
    int d[5] = {5, 4, 3, 3, 2};
    for(int k=0; k<5; k++) 
    { 
        p1h[k] = d[k]; 
        p2h[k] = d[k]; 
    }
}
//print board t=hide f=ship
void printboard(char board[10][10], bool hideships)
{   int c;
    // Use global to decide color
     if(turn== 1) 
    {
      c=  p1c ; 
    }
    else
    {
      c= p2c ;
    }

    cout << "    0   1   2   3   4   5   6   7   8   9" << endl;
    cout << "  +---+---+---+---+---+---+---+---+---+---+" << endl;
    //print the board
    for (int i = 0; i < 10; i++) 
    {
        cout << i << " |";
        for (int j = 0; j < 10; j++) 
        {	//store value to a variable
            char cell = board[i][j];
            
            //check if a to e 
            if (cell >= 'A' && cell <= 'E') 
            { // Hit print X
            	//change colour to text white and red background 
                setcolor(15,12); 
                //print x
                cout << " X ";
				//set colours to normal 
                setcolor(7,0); 
            }
            else if (cell == '0') 
            { // Miss colour change
                setcolor(0, 8); 
                cout << " 0 ";
                setcolor(7,0); 
            }
            else if (cell == 'P')
             { 
            // Sunk	colour change
                setcolor(15, 13); 
                cout << " P "; 
                setcolor(7,0); 
            }
            // 1 - 5 are ships 
            else if (cell >= '1' && cell <= '5') 
            { // Ship
                if(hideships) 
                {	// make water with blue background
                     setcolor(15, 1); 
                     cout << " ~ "; 
                     setcolor(7,0); 
                } 
                else
                {	// make its colour as the user tell
                     setcolor(15, c); 
                     cout << " S "; 
                     setcolor(7,0); 
                }
            }
            else { // Water
                setcolor(15, 1); 
                cout << " ~ "; 
                setcolor(7,0); 
            }
            cout << "|"; 
        }
        cout << endl << "  +---+---+---+---+---+---+---+---+---+---+" << endl;
    }
}
//function to print 3 board
void tripleboard(char myboard[10][10], char enemyboard[10][10])
{   int c ;

    if(turn == 1) 
    {
        c = p1c ; 
    }
    else
    {
        c = p2c ;
    }

     cout << "               ENEMY BOARD                              Opponent                                   PLAYER BOARD" << endl << endl;
    cout << "       0  1  2  3  4  5  6  7  8  9       0   1   2   3   4   5   6   7   8   9             0  1  2  3  4  5  6  7  8  9" << endl;
    cout << "                                        +---+---+---+---+---+---+---+---+---+---+" << endl;

    for (int i = 0; i < 10; i++)
    {
        //  Enemy Mini
        cout << "   " << i << "   "; 
        for(int j=0; j<10; j++) 
        {   char c ;
            c = enemyboard[i][j];
            
            if(c >= 'A' && c <= 'E') 
            {
                cout << "X  ";
            }
            else if(c == '0') 
            {
                cout << "0  ";
            }
            else if(c == 'P') 
            { 
            cout << "P  "; 
            }
            else 
            {
                cout << ".  ";
            }
        }
        cout << " "; 

        // Opponent Main
        cout << i << " |"; 
        for(int j=0; j<10; j++)
         {  
		 	char c ;
         
             c = enemyboard[i][j];
            if(c >= 'A' && c <= 'E') 
            { 
            setcolor(15, 12); 
            cout << " X "; 
            setcolor(7,0);
            }       
            else if(c == '0') 
            { 
            setcolor(0, 8); 
            cout << " 0 "; 
            setcolor(7,0);
            }    
            else if(c == 'P')
             { 
            setcolor(15, 13);
            cout << " P ";
            setcolor(7,0);
                } 
            else 
            {
            setcolor(7, 1);
            cout << " ~ ";
            setcolor(7,0);
                }                     
            cout << "|";
        }
        cout << "        ";

        //  Player Mini
         cout << i << "  ";  
        for(int j=0; j<10; j++)
         {  
            char c ;
             c = myboard[i][j];
            if(c >= '1' && c <= '5') 
            { 
            cout << "S  ";
              } 
            else if(c >= 'A' && c <= 'E') 
            {
            cout << "X  ";
            }
            else if(c == '0')
            {
            cout << "0  ";
            } 
            else if(c == 'P') 
            { 
            cout << "P  ";
            }
            else 
            {
            cout << ".  ";                  
            }
        }
        cout << endl; 
       cout << "                                        +---+---+---+---+---+---+---+---+---+---+" << endl;
    }
}

// Manually Set Ships
void manuallysetships(char board[10][10])
{
    string names[5] = {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
    int sizes[5] = {5, 4, 3, 3, 2};
    
    // Determine name based on global
    string pname ;
    if(turn == 1)  
    {
        pname = p1name ; 
    }
    else
    {
     pname = p2name;
    }

    for(int i = 0; i < 5; i++)
    {	// assign id to each ship
        char shid = '1' + i; 
        
        bool success = false;
        while(!success)
        {	//clearscreen after placement of ship
            clearScreen();
            cout << "PLAYER: " << pname << endl;
            cout << "Placing: " << names[i] << " (Size " << sizes[i] << ")" << endl;
            
            // printboard to place ships ,false means to show ships
            printboard(board, false); 
            
            char op;
            cout << "1 = Manual, 2 = Random: "; 
            cin >> op;

            if (op == '1') 
            {	//row col in int
                int row, col; 
                // vertical choice
                char rot; 
                // vertical false
                bool v = false;
                // taking input in string from user for validation
                string r, c; 
				// input as a string
    			cout << "Row: ";
			    cin >> r;
			
			    // Validation for Row
			    if(r == "0")
				{
					row = 0;
				} 
			    else if(r == "1")
				{
				 row = 1;
				} 
			    else if(r == "2") 
				{
					row = 2;
				}
			    else if(r == "3")
				{
				 row = 3;
				 } 
			    else if(r == "4") 
				{
				row = 4;
				}
			    else if(r == "5") 
				{
				row = 5;
				}
			    else if(r == "6")
				{
				 row = 6;
				}
			    else if(r == "7")
				{
				 row = 7;
				 } 
			    else if(r == "8")
				{
				 row = 8;
				 } 
			    else if(r == "9") 
				{
				row = 9;
				}
			    else 
				{
				row = -1; 
				// Invalid
				}
				//input for column in string
			    cout << "Col: ";
			    cin >> c;
			
			    // Validation for column
			    if(c == "0")
				{
				  col = 0;
				}
			    else if(c == "1") 
				{
				col = 1;
				}
			    else if(c == "2") 
				{
				col = 2;
				}
			    else if(c == "3") 
				{
				col = 3;
				}
			    else if(c == "4") 
				{
				col = 4;
				}
			    else if(c == "5")
				{
				 col = 5;
				 } 
			    else if(c == "6")
				{
				 col = 6;
				 } 
			    else if(c == "7")
				{
				  col = 7;
				 }
			    else if(c == "8")
				{
				  col = 8;
				 }
			    else if(c == "9")
				{
				  col = 9;
				 }
			    else 
				{
					//invalid
				col = -1;
				}
			
			    // validation condition 
			    if (row == -1 || col == -1) 
			    {
			        cout << "Invalid Number Use 0-9.";
			        getch(); 
			        continue; // Restart the loop
			    }
                cout << "Vertical? (y/n): "; 
                cin >> rot;
                if(rot == 'y' || rot == 'Y') 
                {
                 v = true;
                }
					// for placement of ship which means yes we can place ship
                bool p = true;
                
                // checking boundary for vertical
                if(v) 
                {	//row + size of ship  ,  10 is the board size
                    if(row + sizes[i] > 10) 
                    {
                    	p = false;
                    }
                    // check for other ship
                    else 
                    { 	//loop upto shipsize , places of the cell where ship 
                        for(int k=0; k<sizes[i]; k++) 
                        {	// check if there any other ship on the spaces
                            if(board[row+k][col] != '~') 
                            {
                                p = false; 
                            }   
                        }
                    }
                }
                else //check for horizontal
                { 	//col + size of ship . 10 is the board size
                    if(col + sizes[i] > 10) 
                    {
                        p = false;
                    }
                    //check for ships
                    else 
                    { 	//lopp until the shisize to check other ship 
                        for(int k=0; k<sizes[i]; k++) 
                        {	// check if other ship exist on that cell or not
                            if(board[row][col+k] != '~') 
                            {
                                    p = false;
                            }
                        }
                    }
				}
				// if all condition survive than place is free for the ship or user select correct row col which is in the board
                if(p) 
                {	// loop until ship size
                    for(int k=0; k<sizes[i]; k++)
                     {	//vertical placement
                        if(v)
                        {	// store the number to the cell 1,2,3,4,5,
                        	board[row+k][col] = shid;
                        } 
                        //horizontall placement
                        else 
                        {	// store the number to the cell 1,2,3,4,5,
                        	board[row][col+k] = shid;
                        }
                    }
                    success = true; 
                } 
                //if p false than cant place ship error message
				else 
                {
                    cout << "Invalid ";
                    getch();
                }
            }
             else if(op == '2')
            {
             clearBoard(board);
             setRandomShips(board);
             return;
        	}	
			// invalid entry other than manual and random 	
			else
			{
				cout << " Invalid Entry " ;
				cout << "Press any key to continue";
				getch();
			}        
		}
    }
}

void playerattack(char opponentboard[10][10], int &playerscore)
{
    int row, col;
    // showinh no attack take place
    bool att = false;

    while(!att)
    {
    string r, c; // variable  string     

    cout << endl << "Row: ";
    cin >> r;
    
    // for validation and change string input to int
    if(r == "0") 
	{
	row = 0;
	}
    else if(r == "1")
	{
	 row = 1;
	}
    else if(r == "2") 
	{
	row = 2;
	}
    else if(r == "3")
	{
	 row = 3;
	 } 
    else if(r == "4")
	{
	  row = 4;
	 }
    else if(r == "5")
	{
	  row = 5;
	 }
    else if(r == "6")
	{
	  row = 6;
	 }
    else if(r == "7")
	{
	  row = 7;
	 }
    else if(r == "8")
	{
	  row = 8;
	 }
    else if(r == "9") 
	{
	row = 9;
	}
    else
	{ // Invalid input
	row = -1; 
	}
    cout << "Col: ";
    cin >> c;

    // validation for col or give value in int
    if(c == "0")
	{
	 col = 0;
	 } 
    else if(c == "1")
	{
	  col = 1;
	 }
    else if(c == "2") 
	{
	col = 2;
	}
    else if(c == "3")
	{
	  col = 3;
	}
    else if(c == "4")
	{
	  col = 4;
	}
    else if(c == "5")
	{
	  col = 5;
	 }
    else if(c == "6")
	{
	  col = 6;
	}
    else if(c == "7") 
	{
	col = 7;
	}
    else if(c == "8") 
	{
	col = 8;
	}
    else if(c == "9")
	{
	  col = 9;
	}
    else
	{
	  col = -1;
	}
		// wrong input message
        if(row < 0 || row > 9 || col < 0 || col > 9)
         {
            cout << " Invalid ";
        } 
        	// check if already attack
        else if(opponentboard[row][col] == '0' || opponentboard[row][col] == 'P' || 
               (opponentboard[row][col] >= 'A' && opponentboard[row][col] <= 'E')) 
        {
            cout << "Already attacked!";
        } 
        else 
        {	// if 1-5 in a cell than means ship attack
            if(opponentboard[row][col] >= '1' && opponentboard[row][col] <= '5') 
            {
                cout << "HIT ";
                //add score 10
                playerscore += 10; 
				
				// checking which ship attack
                char shid = opponentboard[row][col];
                
                // id to determine the ship
                int idindex = shid - '1'; 
                
                // store the generated alphabet of the ship
                char hitmarker = 'A' + idindex;
                //place it on the board
                opponentboard[row][col] = hitmarker;

                // Check Sinking using Global 
                if(turn == 1) 
                { // P1 attacking P2
                	//reduce the health in global of the specific ship
                    p2h[idindex]--;
                    //check if that ship health to zero
                    if(p2h[idindex] == 0)
                     {	// than sunk
                        cout << "SUNK  ";
                        //reduce the count of ship
                        p2ship--;
                        
                        // when helath ship reduce to zero check whole board
                        for(int r=0; r<10; r++)
                        {
                            for(int c=0; c<10; c++)
                                if(opponentboard[r][c] == hitmarker) 
                                {	// make it P
                                    opponentboard[r][c] = 'P';
                                }
                         } 
                    }
                }
                else 
                { // P2 attacking P1
                	//reduce health of ship
                    p1h[idindex]--;
                    //if that beacomes zero
                    if(p1h[idindex] == 0) 
                    {	//message sunk
                        cout << "SUNK ";
                        //reduce count
                        p1ship--;
                        
                        // when helath ship reduce to zero check whole board
                        for(int r=0; r<10; r++) 
                        {
                            for(int c=0; c<10; c++)
                                if(opponentboard[r][c] == hitmarker) 
                                {	// make it P
                                    opponentboard[r][c] = 'P';
                                }
                        }
                    }
                }
            } 
            // other than that it would be miss
			else 
            {
                cout << "MISS ";
                //make board 0
                opponentboard[row][col] = '0';
				//reduce the score 
                playerscore -= 1; 
            }
            //attack take place without error make it true
            att = true; 
        }
    }
}
//  VS Player
void vsplayer(char board1[10][10], char board2[10][10])
{
    int score1 = 0;
    int score2 = 0;
    bool gover = false;

    while(!gover)
    {
        // PLAYER 1
        turn = 1; 
        clearScreen(); 
        cout << "=== " << p1name << "'s TURN ===" << endl;
        // triple board
        tripleboard(board1, board2); 
        
        //variable for shots
        int shots = p1ship + 1;
        //generate the message of shots 
        cout << "Ships: " << p1ship << " | Shots: " << shots << endl;
        //loop for number of shots of the player
        for(int i=0; i<shots; i++) 
        {	//message of shot 
            cout << "Shot " << i+1 << " || ";
            
            //attack 
            playerattack(board2, score1);
            
            //ships counter to 0
            if(p2ship == 0) 
            { 
            // game over outside the loop
            gover = true; 
            break; 
            } 
        }
        // all sunk ship counter to zero
        if(gover)
        {
        	//break the loop
         break;
        } 
        cout << " Turn Done."; 
        getch();

        // PLAYER 2
        turn = 2; 
        // clear screen 
        clearScreen();
        cout << "Pass to " << p2name; 
        getch();
        clearScreen(); 
        cout << "=== " << p2name << "'s TURN ===" << endl;
        //tripleboard
        tripleboard(board2, board1); 
        //number of shots
        shots = p2ship + 1;
        cout << "Ships: " << p2ship << " | Shots: " << shots << endl;
        //lopp until shots complete
        for(int i=0; i<shots; i++) 
        {
            cout << "Shot " << i+1 << " || ";
            //attack
            playerattack(board1, score2);
            //if counter zero
            if(p1ship == 0) 
            { //exit loop
            gover = true; 
            break; 
            }
        }
        if(gover) 
        {	//exit vs mode 
            break;
        }
        
        cout << " Turn Done "; 
        getch();
        clearScreen(); 
        cout << "Pass to " << p1name; 
        getch();
    }
    //score function ,chicken dinner
    displayresult(score1, score2);
}

// Display Result
void displayresult(int player1Score, int player2Score)
{
    clearScreen();
    
    cout << "GAME OVER" << endl;
    //write the name
    cout << p1name << ": " << player1Score << endl;
    cout << p2name << ": " << player2Score << endl;
	//check score p1 greater
    if (player1Score > player2Score) 
    {
        cout << p1name << " WINS!" << endl;
        saveToLeaderboard(p1name, player1Score); 
    }
    //check score p2 greater
    else if (player2Score > player1Score) 
    {
        cout << p2name << " WINS!" << endl;
        saveToLeaderboard(p2name, player2Score); 
    }
    //otherwise draw
    else 
    {
        cout << "DRAW!" << endl;
    }
    cout << "\nScore saved to Leaderboard!" << endl;
    getch();
}

void saveToLeaderboard(string name, int score) {
    // Open file in Append Mode (ios::app) so we don't overwrite previous games
    ofstream file("leaderboard.txt", ios::app);
    
    if(file.is_open()) {
        file << name << " " << score << endl;
        file.close();
    } else {
        cout << "Error: Could not save score to file." << endl;
    }
}

void viewLeaderboard() {
    ifstream file("leaderboard.txt");
    
    clearScreen();
    cout << " -----------------------------------------------" << endl;
    cout << "\t\t LEADERBOARD " << endl;
    cout << " -----------------------------------------------" << endl;
    
    if(file.is_open()) {
        string name;
        int score;
        
        cout << "NAME\t\tSCORE" << endl;
        cout << "----\t\t-----" << endl;
        
        // Read file line by line
        while(file >> name >> score) {
            cout << name << "\t\t" << score << endl;
        }
        file.close();
    } else {
        cout << "No records found yet. Play a game first!" << endl;
    }
    cout << endl << "Press any key to return to menu...";
    getch();
}

// Menu
void showgamemenu() {
    char choice;
    do {
        //  MAIN MENU
        clearScreen();
        cout << " ===============================================" << endl;
        cout << "\t---WELCOME TO BATTLESHIP GAME---" << endl;
        cout << " ===============================================" << endl;
        cout << endl << endl;
        cout << "\t\t-- MAIN MENU -- " << endl;
        cout << " -----------------------------------------------" << endl << endl;
        cout << " 1.  Start New Game " << endl << endl;
        cout << " 2.  Instructions " << endl << endl;
        cout << " 3.  View Leaderboard " << endl << endl;
        cout << " 4.  Exit " << endl << endl;
        cout << " -----------------------------------------------" << endl;
        cout << endl << endl;
        cout << " Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
        case '1': //START NEW GAME
            {
                char game;
                //  INTERIOR LOOP 
                do {
                    clearScreen();
                    cout << " -----------------------------------------------" << endl;
                    cout << "\t\t START NEW GAME " << endl;
                    cout << " -----------------------------------------------" << endl << endl;
                    cout << "1. Player VS Player" << endl << endl;
                    cout << "2. Player Vs CPU " << endl << endl;
                    cout << "3. Go Back" << endl << endl;
                    cout << " -----------------------------------------------" << endl << endl;
                    cout << "Enter your Choice (1-3) : ";
                    cin >> game;

                    switch (game) {
                    case '1': // PvP 
                        {
                            cout << "Player 1 Enter Your Name: ";
                            cin >> p1name;
                            cout << "Choose Battleship Color: ";
                            p1c = choosecolor();
                            cout << "Player 2 Enter Your Name: ";
                            cin >> p2name;
                            cout << "Choose Battleship Color: ";
                            p2c = choosecolor();

                            char b1[10][10];
                            char b2[10][10];
                            initializeboard(b1);
                            initializeboard(b2);
							//player 1 turn
                            turn = 1;
                            manuallysetships(b1);
							
                            clearScreen();
                            // message 
                            cout << "Switching turn";
                            getch();
							//player 2 turn
                            turn = 2;
                            manuallysetships(b2);

                            clearScreen();
                            //message
                            cout << "START ";
                            getch();
                            
                            // game process here in this
                            vsplayer(b1, b2);
                            break; 
                        } 
                        
                    case '2': // PvC Logic
                        {
                            cout << "Player Enter Your Name: ";
                            cin >> p1name;  
                            cout << "Choose Battleship Color: ";
                            p1c = choosecolor();
                            p2name = "COMPUTER";
                            p2c = 4; //red for computer
                            char playerBoard[10][10];
                            char computerBoard[10][10];
                            initializeboard(playerBoard);
                            initializeboard(computerBoard);
                            vsComputer(playerBoard, computerBoard);

                            break;
                        }

                    case '3':
                        {
                            break;
                        }

                    default:
                        {
                            cout << "Invalid Entry\nPlease enter 1, 2 or 3." << endl;
                            cout << "Press any key to try again";
                            getch(); 
                            // for invalid entry
                            break;
                        }
                    }
                // Continue looping if not 1 2 3
                } while (game != '1' && game != '2' && game != '3'); 

                break; // Break for case 1
            }

        case '2': // INSTRUCTIONS
            {
            clearScreen();
            cout << " -----------------------------------------------" << endl;
            cout << "\t\t INSTRUCTIONS " <<endl ;       
            cout << " -----------------------------------------------" << endl;
            cout << endl ;
            cout << "1. Place your ships on the board." <<endl<<endl ;
            cout << "2. You and the computer take turns firing shots." <<endl <<endl;
            cout << "3. 'O' means MISS, 'X means HIT." <<endl <<endl;
            cout << "4. Sink all enemy ships to win!" <<endl <<endl;
            cout << "5. Your score is based on accuracy and speed." <<endl <<endl;
            cout << " -----------------------------------------------" << endl <<endl;
            cout << "Enter any key to move to MAIN MENU " ;
            getch();
            break ;
            }

        case '3': // LEADERBOARD
            {
                viewLeaderboard(); 
                break;
            }

        case '4': // EXIT
            {
                cout << "---THANK YOU FOR PLAYING THE GAME---";
                break;
            }

        default:
            {
                cout << "Invalid Entry" << endl;
                cout << "Press any key to Continue " ;
                getch();
                break;
            }
        }
    } while (choice != '4');
}
int main()
{
    showgamemenu();
    return 0;
}
