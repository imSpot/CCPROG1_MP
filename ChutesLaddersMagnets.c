#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
    Project Name :          Chutes, Ladders and Magnets 
 
    Project Background :    A derivative of Snakes and Ladders, also known as Moksha Patam, is an  
                            ancient Indian board game for two or more players that is considered a 
                            worldwide classic today. It is played on a gridded game board with 
                            numbered squares. On the board, several "ladders" and "chutes" are 
                            depicted, each linking two different board squares. The goal of the game 
                            is to guide one's game piece from the start (bottom square) to the end 
                            (top square) using die rolls, aided by climbing ladders but hampered by 
                            tumbling down snakes.
*/

void startPrompt();
void endPrompt();
void gameRules();
int numOpp(int nOpponent);
void playerHuman(int nPlayers, int nCurPos1, int nCurPos2, int nCurPos3, int nCurPos4);
void playerAI(int nPlayers, int nCurPos1, int nAIPos2, int nAIPos3, int nAIPos4);
void dispBoard(int nCurPos1, int nCurPos2, int nCurPos3, int nCurPos4);
int posLadder(int nTile);
int posChutes(int nTile);
int posMagnets(int nTile);
int overTurn(int nTile);
void posWin(int nPlayers, int nCurPos1, int nCurPos2, int nCurPos3, int nCurPos4);

int main()
{
    // int nCurPlayer = 1;
    int nOpponent, nPlayers;
    int nCurPos1 = 0, nCurPos2 = 0, nCurPos3 = 0, nCurPos4 = 0;
    int nAIPos1 = 0, nAIPos2 = 0, nAIPos3 = 0, nAIPos4 = 0;  
    char cPlayAgain;

    startPrompt();    
    gameRules();

    /*
        The game can be played by a combination of 2 to 4 human and/or 
        pseudo-AI players. 
            a. There is an option that you can also play the game with a 
            pseudo-AI player. 
    */

    do
    {
        do
        {
            /*
                print a debug statement when the user enters an invalid choice
            */
        
            printf("%65s\n", "Press [1] to play against a human player.");
            printf("%65s\n", "Press [2] to play against the computer.\n");
            printf("%53s", "Enter your choice: ");
            scanf("%d", &nOpponent);

            nPlayers = numOpp(nOpponent);

        } while (nOpponent != 1 && nOpponent != 2);

        /*
            loop a user-defined key to roll a virtual die per player turn.
        */

        system("pause");
        system("cls");

        if(nOpponent == 1)
            playerHuman(nPlayers, nCurPos1, nCurPos2, nCurPos3, nCurPos4);
        else if(nOpponent == 2)
            playerAI(nPlayers, nCurPos1, nCurPos2, nCurPos3, nCurPos4);

        getchar();
        endPrompt();

        printf("%62s", "Do you want to play again? [Y/N]: ");
        scanf("%c", &cPlayAgain);
        system("cls");
        
    // ask the user if they want to play again
    } while(cPlayAgain == 'Y' || cPlayAgain == 'y');


    return 0;
}

void startPrompt()
{
    /*
        Description:
            This function displays the game title and a brief description of the game.
        
        Parameters:
            None.
        
        Return:
            None.
    */
    system("cls");

    {
        printf(" _______________________________________________________________________________________ \n");
        printf("|                                                                                       |\n");
        printf("|                                                                                       |\n");
        printf("%66s\n", "Welcome to Chutes, Ladders and Magnets!\n");
        printf("%64s\n", "A derivative of Snakes and Ladders.\n");
        printf("%64s\n", "It is played on a gridded game board\n");
        printf("%68s\n", "w/ numbered squares and features \"LADDERS\"\n");
        printf("%69s\n", "and \"CHUTES\" that connect different squares.\n");
        printf("%64s\n", "\"LADDERS\" and \"chutes are depicted.\n");
        printf("%66s\n", "The objective is to move your game piece\n");
        printf("%66s\n", "from the starting point to the end point\n");
        printf("%63s\n", "by rolling a die, while exploiting\n");
        printf("%59s\n", "the ladders to CLIMB UP!\n");
        printf("%64s\n", "and avoiding chutes which can cause\n");
        printf("%53s\n", "to FALL BACK!\n\n");
        printf("%60s\n", "Press [ENTER] to see the game");
        printf("%58s\n", "board and instructions.\n");
        printf("|                                                                                       |\n");
        printf("|_______________________________________________________________________________________|\n");
    }
     
    getchar();

    system("cls");
}       

void endPrompt()
{
    /*
        Description:
            This function displays an ending prompt to the user and asks the user to exit the game.
        
        Parameters:
            None.

        Return:
            None.
    */

    system("cls");

    {
        printf(" _______________________________________________________________________________________ \n");
        printf("|                                                                                       |\n");
        printf("|                                                                                       |\n");
        printf("%70s\n", "Thank you for playing Chutes, Ladders and Magnets!\n");
        printf("%59s\n", "Press [ENTER] to exit the game");
        printf("|                                                                                       |\n");
        printf("|_______________________________________________________________________________________|\n");
    }
     
    getchar();

    system("cls");
}

void gameRules()
{
    /*
        Description:
            This function displays the game rules to the user. It also displays the game board to be used
            during the game.
        
        Parameters:
            None.

        Return:
            None.
    */
    int nRow, nCol, nTile;

    system("cls");
    
    printf(" _______________________________________________________________________________________ \n");
    printf("|                                                                                       |\n");
    printf("|                                                                                       |\n");
    printf("%53s\n", "Game Rules:\n");
    printf("%69s\n", "- Can be played against 2-4 Human/AI players\n");
    printf("%68s\n", "- Player takes turn to roll a virtual die to");
    printf("%68s\n", "move their token across the entire baord.\n");
    printf("%50s\n", "Board:\n");
    
    /* print 10 x 10 board */
    
    for(nRow = 10; nRow >= 1; nRow--)
	{
		if( (nRow % 2) == 0 ) 							//even nRow
		{
		    for(nCol = 10; nCol >= 1; nCol--)
		    {
		        nTile = ((nRow - 1) * 10 + nCol);		//prints highest to lowest in the nRow starting from left to right; ex. (10-1)*10 + 10 = 100--
                printf("\t%d ", nTile);
		    }
		    printf("\n\n");
		}
		else 											//odd nRow
		{
			for(nCol = 1; nCol <= 10; nCol++)
			{
			    nTile = ((nRow - 1) * 10 + nCol);		//prints lowest to highest number in the nRow starting from left to right; ex. (9-1)*10 + 1 = 81++
                printf("\t%d ", nTile);
			}
			printf("\n\n");
		}
	}

    printf("%50s\n", "Goal:\n");
    printf("%66s\n", "- The first player to reach the 100th tile");
    printf("%41s\n", "wins the game.\n");
    printf("%52s\n", "Die roll:\n");
    printf("%67s\n", "- The number of the die roll will determine");
    printf("%68s\n", "the number of tiles the player will move.\n");
    printf("%70s\n", "- If the player rolls a 6, they'll get another");
    printf("%69s\n", "turn to roll the die. Otherwise play passes");
    printf("%46s\n", "to the next player.\n");
    printf("%63s\n", "- If the die roll is too big to end the");
    printf("%67s\n", "game, the player will overshoot the 100th");
    printf("%59s\n", "tile and will have to move back.\n");
    printf("%51s\n", "Ladders:\n");
    printf("%69s\n", "- If a player lands on a tile with the bottom");
    printf("%69s\n", "part of a ladder, they will move to the top");
    printf("%47s\n", "part of that ladder.\n");
    printf("%50s\n", "Chutes:\n");
    printf("%66s\n", "- If a player lands on a tile with the top");
    printf("%64s\n", "part of a chute, they will move to the");
    printf("%53s\n", "bottom part of that chute.\n");
    printf("%51s\n", "Magnets:\n");
    printf("%70s\n", "- When a player lands on a tile with a magnet,");
    printf("%69s\n", "the player's token will move to the closest");
    printf("%52s\n", "\"LADDER\" or \"CHUTE\" tile.\n");
    printf("%63s\n", "Press [ENTER] to start the game.\n");
    printf("|                                                                                       |\n");
    printf("|_______________________________________________________________________________________|\n");

    getchar();

    system("cls");
}

int numOpp(int nOpponent)
{
    /*
        Description:
            This function asks the user to choose between playing against a human player or an AI player.
            It also asks the user to choose the number of players if they choose to play against a human player.

        Parameters:
            nOpponent - the number of opponents the user chooses to play against.

        Returns:
            nPlayers - the number of players playing the game.
    */

    int nPlayers;

    if(nOpponent == 1)
    {
        printf("\n");
        printf("%60s\n", "You've chosen vs. human player!");
        
        printf("%65s\n", "How many players will be playing? (2-4)\n");
        printf("%56s", "Enter number of players: ");

        scanf("%d", &nPlayers);
    
        while(nPlayers < 2 || nPlayers > 4)
        {
            printf("%61s\n", "Invalid input. Please try again.\n");
            printf("%65s\n", "How many players will be playing? (2-4)\n");
            printf("%56s", "Enter number of players: ");
            scanf("%d", &nPlayers);
        }

        if(nPlayers == 2)
        {
            printf("%68s\n", "You have chosen to play with 2 (Human) players.");
        }
        else if(nPlayers == 3)
        {
            printf("%68s\n", "You have chosen to play with 3 (Human) players.");
        }
        else if(nPlayers == 4)
        {
            printf("%68s\n", "You have chosen to play with 4 (Human) players.");
        }
        else
        {
            printf("%61s\n", "Invalid input. Please try again.");
        }

        /*
        else if(nPlayerChoice == 2)
        {
            printf("%61s\n", "You have chosen to play against the computer.");

            printf("%64s\n", "How many players will be playing? (2-4)");
            printf("%57s", "Enter number of players: ");

            scanf("%d", &nPlayers);

            system("cls");
        }
        */
    }
    else if (nOpponent == 2)
    {
        printf("\n");
        printf("%68s\n", "You have chosen to play against the computer.");

        printf("%64s\n", "How many players will be playing? (2-4)\n");
        printf("%57s", "Enter number of players: ");

        scanf("%d", &nPlayers);

        while(nPlayers < 2 || nPlayers > 4)
        {
            printf("%61s\n", "Invalid input. Please try again.\n");
            printf("%65s\n", "How many players will be playing? (2-4)\n");
            printf("%56s", "Enter number of players: ");
            scanf("%d", &nPlayers);
        }
    
        if(nPlayers == 2)
        {
            printf("%68s\n", "You have chosen to play with 1 (AI) players.");
        }
        else if(nPlayers == 3)
        {
            printf("%68s\n", "You have chosen to play with 2 (AI) players.");
        }
        else if(nPlayers == 4)
        {
            printf("%68s\n", "You have chosen to play with 3 (AI) players.");
        }
        else
        {
            printf("%61s\n", "Invalid input. Please try again.");
        }
    }

    else
    {
        printf("%61s\n", "Invalid input. Please try again.\n");
        // playerPrompt(nOpponent, nPlayers);
    }

    return nPlayers;        // returns the number of players to main()
}

void playerHuman(int nPlayers, int nCurPos1, int nCurPos2, int nCurPos3, int nCurPos4)
{
    /*
        Description:
            This function is the main game loop for the game. It
            loops the sequence of turns for each human player until
            a winner is found. It also display the board, roll the
            dice, and move the player's token. It will also check
            for any special tiles and execute the appropriate action.
            It will also check for a winner and display the winner.

        Parameters:
            nPlayers - the number of players playing the game.
            nCurPos1 - the current position of player 1.
            nCurPos2 - the current position of player 2.
            nCurPos3 - the current position of player 3.
            nCurPos4 - the current position of player 4.

        Returns:
            None.
            
    */
    int nRoll = 0;
    int nCurPlayer = 1;
    int nLastPos1 = 0, nLastPos2 = 0, nLastPos3 = 0, nLastPos4 = 0;

    do
    {
        getchar();
        srand(time(NULL));
        nRoll = rand() % 6 + 1;

        printf(" _______________________________________________________________________________________ \n");
        printf("|                                                                                       |\n");
        printf("|                                                                                       |\n");
        printf("%66s\n", "LET'S PLAY CHUTES, LADDERS, AND MAGNETS!");
        printf("%58s\n", "Human vs. Human Opponent");
        printf("\n");
        printf("%66s\n", "LADDERS POSITION         CHUTES  POSITION");
        printf("\n");
        printf("%66s\n", "|-- 1  --->  38 --|     \\  17  --->   3  /");
        printf("%66s\n", "|-- 4  --->  14 --|     \\  32  --->  10  /");
        printf("%66s\n", "|-- 8  --->  30 --|     \\  36  --->   6  /");
        printf("%66s\n", "|-- 21 --->  42 --|     \\  48  --->  26  /");
        printf("%66s\n", "|-- 28 --->  65 --|     \\  62  --->  18  /");
        printf("%66s\n", "|-- 50 --->  67 --|     \\  87  --->  24  /");
        printf("%66s\n", "|-- 71 --->  92 --|     \\  95  --->  56  /");
        printf("%66s\n", "|-- 88 ---> 100 --|     \\  97  --->  78  /");
        printf("\n");
        printf("%53s\n", "MAGNET POSITION"); 
        printf("%48s\n", "[ 25 ]");
        printf("%48s\n", "[ 33 ]");
        printf("%48s\n", "[ 64 ]");
        printf("%48s\n", "[ 85 ]");
        printf("%48s\n", "[ 93 ]");
        printf("|                                                                                       |\n");
        printf("|_______________________________________________________________________________________|\n\n");
        
        /*
            loop this per player turn. For example:

                    Player 1:
            Press [ENTER] to roll the die.
                    You rolled: 6
                You're now on tile: 6
            
            display the board after with the player's current position
            marked with P%d, where %d is the player number.

            Press [ENTER] to continue.

                    Player 2:
            Press [ENTER] to roll the die.
                    You rolled: 8
                You're now on tile: 8
            
            display the board after with the player's current position
            marked with P%d, where %d is the player number.
        */

        printf("%48s", "Player ");
        printf("%d\n", nCurPlayer);
        printf("%61s\n", "Press [ENTER] to roll the die.\n");
        getchar();

        printf("%50s\n", "You rolled:");
        printf("\t\t\t\t\t  >  %d\n", nRoll);

        if(nCurPlayer == 1)
        {
            if(nRoll == 6)
            {
                nCurPos1 += nRoll;
                nLastPos1 = nCurPos1 - nRoll;

                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos1);

                printf("%61s\n", "Lucky 6! You get another turn!\n"); // \n
                nRoll = rand() % 6 + 1;
                nCurPos1 += nRoll;
                printf("%50s\n", "You rolled:");
                printf("\t\t\t\t\t  >  %d\n\n", nRoll);
                printf("%45s", "Player 1 moves to tile ");
                printf("%d, ", nCurPos1);
                printf("print [P1] on tile ");
                printf("%d.\n\n", nCurPos1);                

                nCurPos1 = posLadder(nCurPos1);
                nCurPos1 = posChutes(nCurPos1);
                nCurPos1 = posMagnets(nCurPos1);
                nCurPos1 = overTurn(nCurPos1);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos1);
            }

            else  
            {          
                nCurPos1 += nRoll;
                nLastPos1 = nCurPos1 - nRoll;
                
                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos1);
                printf("%45s", "Player 1 moves to tile ");
                printf("%d, ", nCurPos1);
                printf("print [P1] on tile ");
                printf("%d.\n\n", nCurPos1);

                nCurPos1 = posLadder(nCurPos1);
                nCurPos1 = posChutes(nCurPos1);
                nCurPos1 = posMagnets(nCurPos1);
                nCurPos1 = overTurn(nCurPos1);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos1);
            }
        }

        else if(nCurPlayer == 2)
        {
            if(nRoll == 6)
            {
                nCurPos2 += nRoll;
                nLastPos2 = nCurPos2 - nRoll;

                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos2);

                printf("%61s\n", "Lucky 6! You get another turn!\n");
                nRoll = rand() % 6 + 1;
                nCurPos2 += nRoll;
                printf("%50s\n", "You rolled:");
                printf("\t\t\t\t\t  >  %d\n\n", nRoll);
                printf("%45s", "Player 2 moves to tile ");
                printf("%d, ", nCurPos2);
                printf("print [P2] on tile ");
                printf("%d.\n\n", nCurPos2);                

                nCurPos2 = posLadder(nCurPos2);
                nCurPos2 = posChutes(nCurPos2);
                nCurPos2 = posMagnets(nCurPos2);
                nCurPos2 = overTurn(nCurPos2);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos2);
            }

            else  
            {          
                nCurPos2 += nRoll;
                nLastPos2 = nCurPos2 - nRoll;
                
                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos2);
                printf("%45s", "Player 2 moves to tile ");
                printf("%d, ", nCurPos2);
                printf("print [P2] on tile ");
                printf("%d.\n\n", nCurPos2);

                nCurPos2 = posLadder(nCurPos2);
                nCurPos2 = posChutes(nCurPos2);
                nCurPos2 = posMagnets(nCurPos2);
                nCurPos2 = overTurn(nCurPos2);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos2);
            }
        }
        
        else if(nCurPlayer == 3)   
        {
            if(nRoll == 6)
            {
                nCurPos3 += nRoll;
                nLastPos3 = nCurPos3 - nRoll;

                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos3);

                printf("%61s\n", "Lucky 6! You get another turn!\n");
                nRoll = rand() % 6 + 1;
                nCurPos3 += nRoll;
                printf("%50s\n", "You rolled:");
                printf("\t\t\t\t\t  >  %d\n\n", nRoll);
                printf("%45s", "Player 3 moves to tile ");
                printf("%d, ", nCurPos3);
                printf("print [P3] on tile ");
                printf("%d.\n\n", nCurPos3);                

                nCurPos3 = posLadder(nCurPos3);
                nCurPos3 = posChutes(nCurPos3);
                nCurPos3 = posMagnets(nCurPos3);
                nCurPos3 = overTurn(nCurPos3);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos3);
            }

            else
            {
                nCurPos3 += nRoll;
                nLastPos3 = nCurPos3 - nRoll;

                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos3);
                printf("%45s", "Player 3 moves to tile ");
                printf("%d, ", nCurPos3);
                printf("print [P3] on tile ");
                printf("%d.\n\n", nCurPos3);

                nCurPos3 = posLadder(nCurPos3);
                nCurPos3 = posChutes(nCurPos3);
                nCurPos3 = posMagnets(nCurPos3);
                nCurPos3 = overTurn(nCurPos3);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos3);
            }
        }
        
        else if(nCurPlayer == 4)
        {
            if(nRoll == 6)
            {
                nCurPos4 += nRoll;
                nLastPos4 = nCurPos4 - nRoll;

                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos4);

                printf("%61s\n", "Lucky 6! You get another turn!\n");
                nRoll = rand() % 6 + 1;
                nCurPos4 += nRoll;
                printf("%50s\n", "You rolled:");
                printf("\t\t\t\t\t  >  %d\n\n", nRoll);
                printf("%46s", "Player 4 moves to tile ");
                printf("%d", nCurPos4);
                printf("print [P4] on tile ");
                printf("%d.\n\n", nCurPos4);                

                nCurPos4 = posLadder(nCurPos4);
                nCurPos4 = posChutes(nCurPos4);
                nCurPos4 = posMagnets(nCurPos4);
                nCurPos4 = overTurn(nCurPos4);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos4);                
            }

            else
            {
                nCurPos4 += nRoll;
                nLastPos4 = nCurPos4 - nRoll;

                printf("%52s\n", "Last Position:");
                printf("\t\t\t\t\t  >  %d\n\n", nLastPos4);
                printf("%46s", "Player 4 moves to tile ");
                printf("%d", nCurPos4);
                printf("print [P4] on tile ");
                printf("%d.\n\n", nCurPos4);

                nCurPos4 = posLadder(nCurPos4);
                nCurPos4 = posChutes(nCurPos4);
                nCurPos4 = posMagnets(nCurPos4);
                nCurPos4 = overTurn(nCurPos4);

                printf("%56s", "You're now on tile:\n");
                printf("\t\t\t\t\t  >  %d\n\n", nCurPos4);
            }
        }

        dispBoard(nCurPos1, nCurPos2, nCurPos3, nCurPos4);
        
        if(nPlayers == 2)
        {
            switch(nCurPlayer)
            {
                case 1:
                    nCurPlayer = 2;
                    break;
                case 2:
                    nCurPlayer = 1;
                    break;
            }
        }
            
        else if(nPlayers == 3)
        {
            switch(nCurPlayer)
            {
                case 1:
                    nCurPlayer = 2;
                    break;
                case 2:
                    nCurPlayer = 3;
                    break;
                case 3:
                    nCurPlayer = 1;
                    break;
            }
        }
        
        else if(nPlayers == 4)
        {
            switch(nCurPlayer)
            {
                case 1:
                    nCurPlayer = 2;
                    break;
                case 2:
                    nCurPlayer = 3;
                    break;
                case 3:
                    nCurPlayer = 4;
                    break;
                case 4:
                    nCurPlayer = 1;
                    break;
            }
        }

        printf("%60s\n", "Press [ENTER] to continue.\n");
        getchar();
        system("cls");

    } while (nCurPos1 < 100 && nCurPos2 < 100 && nCurPos3 < 100 && nCurPos4 < 100);

    if(nCurPos1 == 100 || nCurPos2 == 100 || nCurPos3 == 100 || nCurPos4 == 100)
        posWin(nPlayers, nCurPos1, nCurPos2, nCurPos3, nCurPos4);

}

void playerAI(int nPlayers, int nCurPos1, int nAIPos2, int nAIPos3, int nAIPos4)
{
    /*
        Description:
            This function is the main game loop for the game. It
            loops the sequence of turns for a human player and its
            AI opponents until a winner is found. It also display
            the board, roll the dice, and move the player's token.
            It will also check for any special tiles and execute
            the appropriate action. It will also check for a winner
            and display the winner.

        Parameters:
            nPlayers - The number of players in the game.
            nCurPos1 - The current position of human player
            nAIPos2 - The current position of AI player 1.
            nAIPos3 - The current position of AI player 2.
            nAIPos4 - The current position of AI player 3.

        Return:
            None.
    */
    
    int nRoll = 0;
    int nCurPlayer = 1;
    int nLastPos1 = 0, nLastPos2 = 0, nLastPos3 = 0, nLastPos4 = 0;

    do
    {
        // system("pause");
        // system("cls");

        srand(time(NULL));
        nRoll = rand() % 6 + 1;

        printf(" _______________________________________________________________________________________ \n");
        printf("|                                                                                       |\n");
        printf("|                                                                                       |\n");
        printf("%66s\n", "LET'S PLAY CHUTES, LADDERS, AND MAGNETS!");
        printf("%59s\n", "Human vs. A.I. Opponent\n ");
        printf("\n");
        printf("%66s\n", "LADDERS POSITION         CHUTES  POSITION");
        printf("\n");
        printf("%66s\n", "|-- 1  --->  38 --|     \\  17  --->   3  /");
        printf("%66s\n", "|-- 4  --->  14 --|     \\  32  --->  10  /");
        printf("%66s\n", "|-- 8  --->  30 --|     \\  36  --->   6  /");
        printf("%66s\n", "|-- 21 --->  42 --|     \\  48  --->  26  /");
        printf("%66s\n", "|-- 28 --->  65 --|     \\  62  --->  18  /");
        printf("%66s\n", "|-- 50 --->  67 --|     \\  87  --->  24  /");
        printf("%66s\n", "|-- 71 --->  92 --|     \\  95  --->  56  /");
        printf("%66s\n", "|-- 88 ---> 100 --|     \\  97  --->  78  /");
        printf("\n");
        printf("%53s\n", "MAGNET POSITION"); 
        printf("%48s\n", "[ 25 ]");
        printf("%48s\n", "[ 33 ]");
        printf("%48s\n", "[ 64 ]");
        printf("%48s\n", "[ 85 ]");
        printf("%48s\n", "[ 93 ]");
        printf("|                                                                                       |\n");
        printf("|_______________________________________________________________________________________|\n\n");
        
        /*
            loop this per player turn. For example:

                    Player 1:
            Press [ENTER] to roll the die.
                    You rolled: 6
                You're now on tile: 6
            
            display the board after with the player's current position
            marked with P%d, where %d is the player number.

            Press [ENTER] to continue.

                    Player 2:
            Press [ENTER] to roll the die.
                    You rolled: 8
                You're now on tile: 8
            
            display the board after with the player's current position
            marked with P%d, where %d is the player number.
        */
                
        printf("%49s", "Player ");
        printf("%d\n", nCurPlayer);
        printf("%62s\n", "Press [ENTER] to roll the die.\n");
        getchar();

        //if nRoll is 6, roll again
        while (nRoll == 6)
        {
            printf("%51s\n", "You rolled:");
            printf("\t\t\t\t\t   >  %d\n", nRoll);
            printf("%75s\n", "You rolled 6! Press [ENTER] to roll the die again.\n");
            getchar();
            nRoll = rand() % 6 + 1;
        }

        printf("%51s\n", "You rolled:");
        printf("\t\t\t\t\t   >  %d\n", nRoll);

        if(nCurPlayer == 1)
        {
            if(nRoll == 6)
            {
                nCurPos1 += nRoll;
                nLastPos1 = nCurPos1 - nRoll;

                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos1);

                printf("%62s\n", "Lucky 6! You get another turn!\n");
                nRoll = rand() % 6 + 1;
                nCurPos1 += nRoll;
                printf("%51s\n", "You rolled:");
                printf("\t\t\t\t\t   >  %d\n\n", nRoll);
                printf("%46s", "Player 1 moves to tile ");
                printf("%d, ", nCurPos1);
                printf("print [P1] on tile ");
                printf("%d.\n\n", nCurPos1);

                nCurPos1 = posLadder(nCurPos1);
                nCurPos1 = posChutes(nCurPos1);
                nCurPos1 = posMagnets(nCurPos1);
                nCurPos1 = overTurn(nCurPos1);

                printf("%57s", "You're now on tile:\n");
                printf("\t\t\t\t\t   >  %d\n\n", nCurPos1);
            }

            else  
            {          
                nCurPos1 += nRoll;
                nLastPos1 = nCurPos1 - nRoll;
                
                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos1);
                printf("%46s", "Player 1 moves to tile ");
                printf("%d, ", nCurPos1);
                printf("print [P1] on tile ");
                printf("%d.\n\n", nCurPos1);

                nCurPos1 = posLadder(nCurPos1);
                nCurPos1 = posChutes(nCurPos1);
                nCurPos1 = posMagnets(nCurPos1);
                nCurPos1 = overTurn(nCurPos1);

                printf("%57s", "You're now on tile:\n");
                printf("\t\t\t\t\t   >  %d\n\n", nCurPos1);
            }
        }

        else if(nCurPlayer == 2)
        {
            if(nRoll == 6)
            {
                nAIPos2 += nRoll;
                nLastPos1 = nAIPos2 - nRoll;

                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos1);

                printf("%62s\n", "Lucky 6! You get another turn!\n");
                nRoll = rand() % 6 + 1;
                nAIPos2 += nRoll;
                printf("%51s\n", "You rolled:");
                printf("\t\t\t\t\t   >  %d\n\n", nRoll);
                printf("%47s", "Computer 2 moves to tile ");
                printf("%d, ", nAIPos2);
                printf("print [P2] on tile ");
                printf("%d.\n\n", nAIPos2);

                nAIPos2 = posLadder(nAIPos2);
                nAIPos2 = posChutes(nAIPos2);
                nAIPos2 = posMagnets(nAIPos2);
                nAIPos2 = overTurn(nAIPos2);

                printf("%57s", "You're now on tile:\n");
                printf("\t\t\t\t\t   >  %d\n\n", nAIPos2);
            }

            else
            {
                printf("%49s\n", "AI Player 1");
                printf("%50s\n", "Rolled:");
                printf("\t\t\t\t\t   >  %d\n", nRoll);

                nAIPos2 += nRoll;
                nLastPos2 = nAIPos2 - nRoll;

                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos2);
                printf("%47s", "Computer 2 moves to tile ");
                printf("%d, ", nAIPos2);
                printf("print [P2] on tile ");
                printf("%d.\n\n", nAIPos2);

                nAIPos2 = posLadder(nAIPos2);
                nAIPos2 = posChutes(nAIPos2);
                nAIPos2 = posMagnets(nAIPos2);
                nAIPos2 = overTurn(nAIPos2);

                printf("%57s", "Computer 2 now on tile:\n");
                printf("\t\t\t\t\t   >  %d\n\n", nAIPos2);
            }
        }
        
        else if(nCurPlayer == 3)   
        {
            if(nRoll == 6)
            {
                nAIPos3 += nRoll;
                nLastPos1 = nAIPos3 - nRoll;

                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos1);

                printf("%62s\n", "Lucky 6! You get another turn!\n");
                nRoll = rand() % 6 + 1;
                nAIPos3 += nRoll;
                printf("%51s\n", "You rolled:");
                printf("\t\t\t\t\t   >  %d\n\n", nRoll);
                printf("%47s", "Computer 3 moves to tile ");
                printf("%d, ", nAIPos3);
                printf("print [P3] on tile ");
                printf("%d.\n\n", nAIPos3);

                nAIPos3 = posLadder(nAIPos3);
                nAIPos3 = posChutes(nAIPos3);
                nAIPos3 = posMagnets(nAIPos3);
                nAIPos3 = overTurn(nAIPos3);

                printf("%57s", "You're now on tile:\n");
                printf("\t\t\t\t\t   >  %d\n\n", nAIPos3);
            }
            
            else
            {            
                printf("%49s", "AI Player 2");
                printf("%50s\n", "Rolled:");
                printf("\t\t\t\t\t   >  %d\n", nRoll);

                nAIPos3 += nRoll;
                nLastPos3 = nAIPos3 - nRoll;

                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos3);
                printf("%47s", "Computer 3 moves to tile ");
                printf("%d, ", nAIPos3);
                printf("print [P3] on tile ");
                printf("%d.\n\n", nAIPos3);

                nAIPos3 = posLadder(nAIPos3);
                nAIPos3 = posChutes(nAIPos3);
                nAIPos3 = posMagnets(nAIPos3);
                nAIPos3 = overTurn(nAIPos3);

                printf("%57s", "Computer 3 now on tile:\n");
                printf("\t\t\t\t\t   >  %d\n\n", nAIPos3);
            }
        }
        
        else if(nCurPlayer == 4)
        {
            if(nRoll == 6)
            {
                nAIPos4 += nRoll;
                nLastPos1 = nAIPos4 - nRoll;

                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos1);

                printf("%62s\n", "Lucky 6! You get another turn!\n");
                nRoll = rand() % 6 + 1;
                nAIPos4 += nRoll;
                printf("%51s\n", "You rolled:");
                printf("\t\t\t\t\t   >  %d\n\n", nRoll);
                printf("%47s", "Computer 4 moves to tile ");
                printf("%d", nAIPos4);
                printf("print [P4] on tile ");
                printf("%d.\n\n", nAIPos4);

                nAIPos4 = posLadder(nAIPos4);
                nAIPos4 = posChutes(nAIPos4);
                nAIPos4 = posMagnets(nAIPos4);
                nAIPos4 = overTurn(nAIPos4);

                printf("%57s", "You're now on tile:\n");
                printf("\t\t\t\t\t   >  %d\n\n", nAIPos4);
            }
            
            else
            {            
                printf("%49s", "AI Player 3");
                printf("%50s\n", "Rolled:");
                printf("\t\t\t\t\t   >  %d\n", nRoll);
                
                nAIPos4 += nRoll;
                nLastPos4 = nAIPos4 - nRoll;
                
                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos4);
                printf("%47s", "Computer 4 moves to tile ");
                printf("%d", nAIPos4);
                printf("print [P4] on tile ");
                printf("%d.\n\n", nAIPos4);

                nAIPos4 = posLadder(nAIPos4);
                nAIPos4 = posChutes(nAIPos4);
                nAIPos4 = posMagnets(nAIPos4);
                nAIPos4 = overTurn(nAIPos4);

                printf("%53s\n", "Last Position:");
                printf("\t\t\t\t\t   >  %d\n\n", nLastPos4);
                printf("%47s", "Computer 4 moves to tile ");
                printf("\t\t\t\t\t   >  %d\n\n", nAIPos4);
            }
        }

        dispBoard(nCurPos1, nAIPos2, nAIPos3, nAIPos4);
        
        if(nPlayers == 2)
        {
            switch(nCurPlayer)
            {
                case 1:
                    nCurPlayer = 2;
                    break;
                case 2:
                    nCurPlayer = 1;
                    break;
            }
        }
            
        else if(nPlayers == 3)
        {
            switch(nCurPlayer)
            {
                case 1:
                    nCurPlayer = 2;
                    break;
                case 2:
                    nCurPlayer = 3;
                    break;
                case 3:
                    nCurPlayer = 1;
                    break;
            }
        }
        
        else if(nPlayers == 4)
        {
            switch(nCurPlayer)
            {
                case 1:
                    nCurPlayer = 2;
                    break;
                case 2:
                    nCurPlayer = 3;
                    break;
                case 3:
                    nCurPlayer = 4;
                    break;
                case 4:
                    nCurPlayer = 1;
                    break;
            }
        }

        printf("%60s\n", "Press [ENTER] to continue.\n");
        getchar();
        system("cls");

    } while (nCurPos1 < 100 && nAIPos2 < 100 && nAIPos3 < 100 && nAIPos4 < 100);

    if(nCurPos1 == 100 || nAIPos2 == 100 || nAIPos3 == 100 || nAIPos4 == 100)
        posWin(nPlayers, nCurPos1, nAIPos2, nAIPos3, nAIPos4);
}

void dispBoard(int nCurPos1, int nCurPos2, int nCurPos3, int nCurPos4)
{
    /*
        Description:
            Displays the board with the current positions of the players.
        
        Parameters:
            nCurPos1 - Current position of player 1.
            nCurPos2 - Current position of player 2.
            nCurPos3 - Current position of player 3.
            nCurPos4 - Current position of player 4.
        
        Return:
            None.
    */

    int nRow, nCol, nTile = 0;
    
	for(nRow = 10; nRow >= 1; nRow--)
	{
		if( (nRow % 2) == 0 ) 							//even nRow
		{
		    for(nCol = 10; nCol >= 1; nCol--)
		    {
		        nTile = ((nRow - 1) * 10 + nCol);		//prints highest to lowest in the nRow starting from left to right; ex. (10-1)*10 + 10 = 100--
                
                if (nTile == nCurPos1)
                    printf("\t[P1]");
                else if (nTile == nCurPos2)
                    printf("\t[P2]");
                else if (nTile == nCurPos3)
                    printf("\t[P3]");
                else if (nTile == nCurPos4)
                    printf("\t[P4]");
                else
                    printf("\t%d ", nTile);
		    }
		    printf("\n\n");
		}
		else 											//odd nRow
		{
			for(nCol = 1; nCol <= 10; nCol++)
			{
			    nTile = ((nRow - 1) * 10 + nCol);		//prints lowest to highest number in the nRow starting from left to right; ex. (9-1)*10 + 1 = 81++
                
                if (nTile == nCurPos1)
                    printf("\t[P1]");
                else if (nTile == nCurPos2)
                    printf("\t[P2]");
                else if (nTile == nCurPos3)
                    printf("\t[P3]");
                else if (nTile == nCurPos4)
                    printf("\t[P4]");
                else
                    printf("\t%d ", nTile);
			}
			printf("\n\n");
		}
	}
}

int posLadder(int nTile)
{
    /*
        Description:
            This function will determine the tile numbers where the player will be moved to if they
            land on a ladder.

        For ex.: If the player lands on tile 1, they advance to tile 38.
                 If the player lands on tile 4, they advance to tile 14.

        Parameters:
            nTile - The tile number where the player landed.
        
        Return:
            nLadderPos - The tile number where the player will be moved to.
    */

    int nLadderPos = nTile;

    switch(nTile)
    {
        case 1: nLadderPos = 38;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 38.\n");
                break;
        case 4: nLadderPos = 14;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 14.\n");
                break;
        case 8: nLadderPos = 30;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 30.\n");
                break;
        case 21: nLadderPos = 42;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 42.\n");
                break;
        case 28: nLadderPos = 65;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 65.\n");
                break;
        case 50: nLadderPos = 67;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 67.\n");
                break;
        case 71: nLadderPos = 92;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 92.\n");
                break;
        case 88: nLadderPos = 100;
                printf("%75s\n", "You climbed on a ladder! You will be moved to tile 100.\n");
                break;
    }

    return nLadderPos;

}

int posChutes(int nTile)
{
    /*
        Description:
            This function will determine the tile numbers where the player will be moved to if they
            land on a chute.

        For ex.: If the player lands on tile 17, they will be moved to tile 3.
                 If the player lands on tile 32, they will be moved to tile 10.
        
        Parameters:
            nTile - The tile number where the player landed.
        
        Return:
            nChutePos - The tile number where the player will be moved to.
    */

    int nChutePos = nTile;

    switch(nTile)
    {
        case 17: nChutePos = 3;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 3.\n");
                break;
        case 32: nChutePos = 10;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 10.\n");
                break;
        case 36: nChutePos = 6;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 6.\n");
                break;
        case 48: nChutePos = 26;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 26.\n");
                break;
        case 62: nChutePos = 18;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 18.\n");
                break;
        case 87: nChutePos = 24;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 24.\n");
                break;
        case 95: nChutePos = 56;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 56.\n");
                break;
        case 97: nChutePos = 78;
                printf("%73s\n", "You landed on a chute! You will be moved to tile 78.\n");
                break;
    }

    return nChutePos;
}

int posMagnets(int nTile)
{       
    /*
        Description:
            This function will determine the tile numbers where the player will be moved to if they
            land on a magnet.
            
            magnet positions: 25, 33, 64, 85, and 93

            a. If the player’s position is closer to the bottom of a ladder 
                compared to the top of a chute, the player’s peg will move to 
                the ladder. 
                    ex.
                            Player’s position: 25
                            Nearest ladder: 21
                            Nearest chute: 32
                            check if 25 is closer to 28 or 32
                            
                            if 25 is closer to 21,
                            The player’s peg will move to the nearest ladder (28)
                            and update player's position to 65.

            b. On the other hand, if the player’s position is nearer to the top of 
                a chute, the player’s peg will move to the chute.
                    ex.
                            Player’s position: 64
                            Nearest ladder: 71
                            Nearest chute: 62
                            check if 64 is closer to 71 or 62

                            since 64 is closer to 62,
                            The player’s peg will move to the nearest chute (62)
                            and update player's position to 18.

        Parameters:
            nTile - The tile number where the player landed.

        Return:
            nMagnetPos - The tile number where the player will be moved to.
    */

    int nMagnetPos = nTile;

    if(nTile == 25 || nTile == 33 || nTile == 64 || nTile == 85 || nTile == 93)
    {
        int nNearestLadder = 0;
        int nNearestChute = 0;
        int nLadderPos = 0;
        int nChutePos = 0;
        int nLadderDiff = 0;
        int nChuteDiff = 0;

        nLadderDiff = abs(nTile - nNearestLadder);
        nChuteDiff = abs(nTile - nNearestChute);

        if(nTile == 25)
        {
            nNearestLadder = 28;
            nNearestChute = 32;

            nLadderDiff = abs(nTile - nNearestLadder);
            nChuteDiff = abs(nTile - nNearestChute);
            
            if(nLadderDiff < nChuteDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest ladder.\n");
                nLadderPos = posLadder(nNearestLadder);
                nMagnetPos = nLadderPos;
            }
            else if(nChuteDiff < nLadderDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest chute.\n");
                nChutePos = posChutes(nNearestChute);
                nMagnetPos = nChutePos;
            }
        }

        else if(nTile == 33)
        {
            nNearestLadder = 28;
            nNearestChute = 32;

            nLadderDiff = abs(nTile - nNearestLadder);
            nChuteDiff = abs(nTile - nNearestChute);

            if(nLadderDiff < nChuteDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest ladder.\n");
                nLadderPos = posLadder(nNearestLadder);
                nMagnetPos = nLadderPos;
            }
            else if(nChuteDiff < nLadderDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest chute.\n");
                nChutePos = posChutes(nNearestChute);
                nMagnetPos = nChutePos;
            }            
        }

        else if(nTile == 64)
        {
            nNearestLadder = 71;
            nNearestChute = 62;

            nLadderDiff = abs(nTile - nNearestLadder);
            nChuteDiff = abs(nTile - nNearestChute);

            if(nLadderDiff < nChuteDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest ladder.\n");
                nLadderPos = posLadder(nNearestLadder);
                nMagnetPos = nLadderPos;
            }
            else if(nChuteDiff < nLadderDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest chute.\n");
                nChutePos = posChutes(nNearestChute);
                nMagnetPos = nChutePos;
            }
        }

        else if(nTile == 85)
        {
            nNearestLadder = 88;
            nNearestChute = 87;

            nLadderDiff = abs(nTile - nNearestLadder);
            nChuteDiff = abs(nTile - nNearestChute);

            if(nLadderDiff < nChuteDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest ladder.\n");
                nLadderPos = posLadder(nNearestLadder);
                nMagnetPos = nLadderPos;
            }
            else if(nChuteDiff < nLadderDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest chute.\n");
                nChutePos = posChutes(nNearestChute);
                nMagnetPos = nChutePos;
            }
        }

        else if(nTile == 93)
        {
            nNearestLadder = 88;
            nNearestChute = 95;

            nLadderDiff = abs(nTile - nNearestLadder);
            nChuteDiff = abs(nTile - nNearestChute);

            if(nLadderDiff < nChuteDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest ladder.\n");
                nLadderPos = posLadder(nNearestLadder);
                nMagnetPos = nLadderPos;
            }
            else if(nChuteDiff < nLadderDiff)
            {
                printf("%80s\n", "You landed on a magnet! You will be moved to the nearest chute.\n");
                nChutePos = posChutes(nNearestChute);
                nMagnetPos = nChutePos;
            }
        }
    }

    return nMagnetPos;
}

int overTurn(int nTile)
{
    /*
        Description:
            This function will determine if the user rolled over 100 and will
            subtract the difference from the current position and display the new position

        Parameters:
            nTile - the current position of the user
        
        Return:
            nBack - the new position of the user prior to rolling over 100
    */
    int nOverTurn = 0;
    int nBack = nTile;
    
    if(nTile > 100)
    {
        /*
            if user rolled over 100, subtract the difference from the current position
            and display the new position

            ex. if user rolled 6 and is on tile 96, add 4 to the current position
                to go to tile 100 then subtract the remaining 2 to go to tile 98
            
        */

        nOverTurn = nTile - 100;
        nBack = 100 - nOverTurn;
        // nCurPos1 = 100 - nOverTurn;

        if(nBack == 95 || nBack == 97)
        {
            printf("%65s", "You rolled too high. You have to move back to");
            printf(" %d tiles.\n\n", nBack);
            nBack = posChutes(nBack);
        }

        else
        {
            printf("%65s", "You rolled too high. You have to move back to");
            printf(" %d tiles.\n\n", nBack);
            // nTile = nBack;
        }
    }

    return nBack;
}

void posWin(int nPlayers, int nCurPos1, int nCurPos2, int nCurPos3, int nCurPos4)
{
    /*
        Description:
            This function will determine if the user has reached the 100th tile and
            will display a message if the user has won the game.

        Parameters:
            nPlayers - the number of players
            nCurPos1 - the current position of player 1
            nCurPos2 - the current position of player 2
            nCurPos3 - the current position of player 3
            nCurPos4 - the current position of player 4
        
        Return:
            None.
    */
    if(nPlayers == 2)
    {
        if(nCurPos1 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 1\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
        else if(nCurPos2 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 2\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
    }
    else if(nPlayers == 3)
    {
        if(nCurPos1 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 1\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
        else if(nCurPos2 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 2\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
        else if(nCurPos3 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 3\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
    }
    else if(nPlayers == 4)
    {
        if(nCurPos1 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 1\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
        else if(nCurPos2 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 2\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
        else if(nCurPos3 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 3\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
        else if(nCurPos4 == 100)
        {
            getchar();
            printf(" _______________________________________________________________________________________ \n");
            printf("|                                                                                       |\n");
            printf("|                                                                                       |\n");
            printf("%57s", "Congratulations Player 4\n");
            printf("%66s", "You have reached the 100th tile. You win!\n\n");
            printf("%58s\n", "Press [ENTER] to continue.\n");
            printf("|                                                                                       |\n");
            printf("|_______________________________________________________________________________________|\n");
        }
    }
}