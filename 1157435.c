/* Program to print and play checker games.

  Skeleton program written by Artem Polyvyanyy, artem.polyvyanyy@unimelb.edu.au,
  September 2021, with the intention that it be modified by students
  to add functionality, as required by the assignment specification.

  Student Authorship Declaration:

  (1) I certify that except for the code provided in the initial skeleton file,
  the program contained in this submission is completely my own individual
  work, except where explicitly noted by further comments that provide details
  otherwise. I understand that work that has been developed by another student,
  or by me in collaboration with other students, or by non-students as a result
  of request, solicitation, or payment, may not be submitted for assessment in
  this subject. I understand that submitting for assessment work developed by
  or in collaboration with other students or non-students constitutes Academic
  Misconduct, and may be penalized by mark deductions, or by other penalties
  determined via the University of Melbourne Academic Honesty Policy, as
  described at https://academicintegrity.unimelb.edu.au.

  (2) I also certify that I have not provided a copy of this work in either
  softcopy or hardcopy or any other form to any other student, and nor will I
  do so until after the marks are released. I understand that providing my work
  to other students, regardless of my intention or any undertakings made to me
  by that other student, is also Academic Misconduct.

  (3) I further understand that providing a copy of the assignment specification
  to any form of code authoring or assignment tutoring service, or drawing the
  attention of others to such services and code that may have been made
  available via such a service, may be regarded as Student General Misconduct
  (interfering with the teaching activities of the University and/or inciting
  others to commit Academic Misconduct). I understand that an allegation of
  Student General Misconduct may arise regardless of whether or not I personally
  make use of such solutions or sought benefit from such actions.

  Signed by: Hung Long Nguyen
  Dated:     10/10/2021

*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

/* some #define's from my sample solution ------------------------------------*/
#define BOARD_SIZE          8       // board size
#define ROWS_WITH_PIECES    3       // number of initial rows with pieces
#define CELL_EMPTY          '.'     // empty cell character
#define CELL_BPIECE         'b'     // black piece character
#define CELL_WPIECE         'w'     // white piece character
#define CELL_BTOWER         'B'     // black tower character
#define CELL_WTOWER         'W'     // white tower character
#define COST_PIECE          1       // one piece cost
#define COST_TOWER          3       // one tower cost
#define TREE_DEPTH          3       // minimax tree depth
#define COMP_ACTIONS        10      // number of computed actions

/* one type definition from my sample solution -------------------------------*/
typedef unsigned char board_t[BOARD_SIZE][BOARD_SIZE];  // board type


/*******************************************************************/
#include <stdbool.h>
#include <string.h>

#define ALPHABET		   "ABCDEFGH"   // For String - Number conversion
#define NUMBER			   "12345678"   // For String - Number conversion
#define ERROR			   -1           // Error
#define OUT                -1           // Out of the board
#define MOVE_LEN            6           // Length of Move (Eg: 'A1-B2\0')    
#define TWO                 2           // to find a number is odd or even
#define TOCHAR             '0'          // To convert number to character   
#define NEXT                1           // for iterating the next element
#define W_START_ROW         3           // White are placed in first 3 rows
#define B_START_ROW         4           // Black are placed in last 3 rows
#define ZERO				0			// For iteration
#define FIRST               1           // For iteration  
#define SECOND              2           // For iteration  
#define THIRD               3           // For iteration 
#define FORTH               4           // For iteration 
#define FIFTH               5           // For iteration 
#define SIXTH               6           // For iteration
#define ERROR1             -1           // ERROR TYPE
#define ERROR2             -2           // ERROR TYPE
#define ERROR3             -3           // ERROR TYPE
#define ERROR4             -4           // ERROR TYPE
#define ERROR5             -5           // ERROR TYPE
#define ERROR6             -6           // ERROR TYPE
#define N                  -1           // North direction
#define S                   1           // South direction
#define W                  -1           // West direction
#define E                   1           // East direction
#define NN                 -2           // double North direction
#define SS                  2           // double South direction
#define WW                 -2           // double West direction
#define EE                  2           // double East direction
#define DIR                 4           // four direction
#define ABS                 0           // absolute - find negative
#define TRUE                1           // true
#define DOUBLE              2           // doube
#define ROW_1               0           // first row
#define ROW_7               7           // the last row
#define DASH               '-'          // dash character
#define NUL                '\0'         // NUL character
#define S1                 'A'          // stage 1 action call
#define S2                 'P'          // stage 2 action call
#define INPUTLENGTH         4          // Length of input


/*******************************************************************/
typedef struct 
{
    char move[MOVE_LEN];
    int point;
}   theMove_t;

typedef theMove_t *move_t;

/*******************************************************************/

bool isOdd(int turn);
int  c2d(char character);
char d2c(int num);
void prinbrd(board_t board);
void setup(board_t board);
int  board_cost(board_t board);
void display_board(int turn, char* moves, board_t board);
int  isVal(board_t board, char* move, int turn);
void do_move(board_t board, char move[]);
int  find_next_move(board_t board, int tDepth, int turn);
bool do_stage1(board_t board, int turn);
void do_stage2(board_t board, int turn);
int  do_stage0(board_t board);

/*******************************************************************/
int
main(int argc, char *argv[]) 
{
    // YOUR IMPLEMENTATION OF STAGES 0-2
    board_t board;
    setup(board);

    do_stage0(board);
    return EXIT_SUCCESS;       // exit program with the success code
}


/* The function will if the given number is odd or even*/
bool isOdd(int turn)
{
	return (turn % TWO)?	true : false;
}


/* The function will convert the input from character type to
   number type equivalent (short for character to digit) */
int c2d(char character)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
    {
		if (character == ALPHABET[i])	return i;
		if (character ==   NUMBER[i])	return i;
	}
	return ERROR;
}


/* The function will convert the input from number to
   character type equivalent (short for digit to character) */
char d2c(int num)
{
    return num + TOCHAR;
}


/* The function will print out the board */
void print_brd(board_t board)
{
	printf("     A   B   C   D   E   F   G   H\n");
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		printf("   +---+---+---+---+---+---+---+---+\n");
		printf(" %d |", row + NEXT);

		for (int cell = 0; cell < BOARD_SIZE; ++cell)	
        printf(" %c |", board[row][cell]);
		printf("\n");
	}
	printf("   +---+---+---+---+---+---+---+---+\n");
}


/* The function will setup the board */
void setup(board_t board)
{
    for (int row = 0; row < BOARD_SIZE; ++row)	
    {
        for (int cell = 0; cell < BOARD_SIZE; ++cell)		
        {
            // White pieces in 3 lines of board
            if (isOdd(row) && (!(isOdd(cell))))
            {
                if (row < W_START_ROW)
                {
                	board[row][cell] = CELL_WPIECE;     
					continue;
                }
				else if (row > B_START_ROW)
				{
					board[row][cell] = CELL_BPIECE;
					continue;
				}
            }

            // Black pieces in 3 lines of board
			else if ((!(isOdd(row))) && (isOdd(cell)))
			{
                if (row < W_START_ROW)
                {
                	board[row][cell] = CELL_WPIECE;
					continue;
                }
				else if (row > B_START_ROW)
				{
					board[row][cell] = CELL_BPIECE;
					continue;
				}
			}
            board[row][cell] = CELL_EMPTY;
        }
    }
	printf("BOARD SIZE: 8x8\n");
	printf("#BLACK PIECES: 12\n");
	printf("#WHITE PIECES: 12\n");
	print_brd(board);
}


/* Calculate the board cost of the current play */
int board_cost(board_t board)
{
	int boardCost = 0;
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		for (int cell = 0; cell < BOARD_SIZE; ++cell)
		{
			if (board[row][cell] == CELL_BPIECE) 
                ++boardCost;
			else if (board[row][cell] == CELL_BTOWER) 
                boardCost += COST_TOWER;
			else if (board[row][cell] == CELL_WPIECE) 
                --boardCost;
			else if (board[row][cell] == CELL_WTOWER) 
                boardCost -= COST_TOWER;
		}
	}
	return boardCost;
}


/* The function will display the formatted version of the board */
void display_board(int turn, char* moves, board_t board) 
{
    // odd turn -> white
    // even turn -> black
	char player[] = "BLACK";
	if (isOdd(turn)) strcpy(player, "WHITE");

    // print
	printf("%s ACTION #%d: %s\n", player, turn + NEXT, moves);
	printf("BOARD COST: %d\n", board_cost(board));
	print_brd(board);
}


/* Function will check the validity of the current play */
int isVal(board_t board, char* move, int turn)
{
    bool isLegal = false;
    int    s_Col = c2d(move[ZERO]);
    int    s_Row = c2d(move[FIRST]);
    int    t_Col = c2d(move[THIRD]);
    int    t_Row = c2d(move[FORTH]);
	char   piece = board[s_Row][s_Col];
	char t_piece = board[t_Row][t_Col];

	// Check if the move violate any errors
    if ((s_Col == OUT) || (s_Row == OUT))           	return ERROR1;

    if ((t_Col == OUT) || (t_Row == OUT))	            return ERROR2;

    if (piece == CELL_EMPTY)                            return ERROR3;

    if (t_piece != CELL_EMPTY)                          return ERROR4;

	if (isOdd(turn) && 
     (piece == CELL_BPIECE || piece == CELL_BTOWER))  	return ERROR5;

    else if (!isOdd(turn) && 
     (piece == CELL_WPIECE || piece == CELL_WTOWER))    return ERROR5;

	// all posible move combinations of a piece.
	int    row_move[] = { N, S, S, N };
	int    col_move[] = { E, E, W, W };
	int row_capture[] = { NN, SS, SS, NN };
	int col_capture[] = { EE, EE, WW, WW };

    // Checking error 6: examine all the valid move, if not -> error 6
	for (int i = 0; i < DIR; ++i)
	{
        // White turns;
	    if (isOdd(turn))
        {
            // checking regular moves
			if (t_Row == s_Row + row_move[i] && t_Col == s_Col + col_move[i])	
                isLegal = true; 

            // checking capturing
			else if (t_Row == s_Row + row_capture[i]
                     && t_Col == s_Col + col_capture[i])
			{
				switch(board[(s_Row + row_move[i])][(s_Col + col_move[i])])
				{
					case CELL_BPIECE:
					case CELL_BTOWER:
						isLegal = TRUE;
						break;	
				}
			}

            // piece can only move forward
			if ((board[s_Row][s_Col] == CELL_WPIECE) && t_Row - s_Row < ABS) 
                return ERROR6;
		}

        // Black turns;
		else
		{
            // checking regular moves
			if (t_Row == s_Row + row_move[i] && t_Col == s_Col + col_move[i])	
                isLegal = true;

            // checking capturing
			else if (t_Row == s_Row + row_capture[i]
                     && t_Col == s_Col + col_capture[i])
			{
				switch(board[(s_Row + row_move[i])][(s_Col + col_move[i])])
				{
					case CELL_WTOWER:
					case CELL_WPIECE:
						isLegal = TRUE;
						break;
				}
			}

            // piece can only move forward
			if ((board[s_Row][s_Col] == CELL_BPIECE) && t_Row - s_Row > ABS ) 
                return ERROR6;
		}
	}
    return (!isLegal) ? ERROR6 : TRUE;
}


/* The function will make the input play onto the input board */
void do_move(board_t board, char move[])
{
    // storing source and target position
	int	s_Col = c2d(move[ZERO]);
	int	s_Row = c2d(move[FIRST]);
	int	t_Col = c2d(move[THIRD]);
	int	t_Row = c2d(move[FORTH]);

    // moving the piece (swapping the source and target)
	board[t_Row][t_Col] = board[s_Row][s_Col];	
	board[s_Row][s_Col] = CELL_EMPTY;

    // Capturing the opponent piece
    if (abs(s_Row - t_Row) == DOUBLE) 
     board[(s_Row + t_Row) / DOUBLE][(s_Col + t_Col) / DOUBLE] = CELL_EMPTY;

    // Promote piece
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		if (board[ROW_1][i] == CELL_BPIECE) 	board[ROW_1][i] = CELL_BTOWER;
		if (board[ROW_7][i]  == CELL_WPIECE)	board[ROW_7][i]  = CELL_WTOWER;
	}
}


/* The function will find the best next move using MiniMaxTree decision */
int find_next_move(board_t board, int tDepth, int turn)
{
    // making struct pointer to store the next move.
    move_t nextMove;
    nextMove = (move_t)malloc(sizeof(theMove_t));
    int point = isOdd(turn)? INT_MAX : INT_MIN;

    // all posible move combinations of a piece.
	int row_move[] = { N, NN, S, SS, S, SS, N, NN };
	int col_move[] = { E, EE, E, EE, W, WW, W, WW };
	char move[MOVE_LEN];

    // The following "chunk of code" will use recursive to replicate
    // the Minmax Tree Decision.
    // Since the data will be used once only; instead of storing it, 
    // This code will COMPARE AND CHOOSE the best move right away 
    // as the code runs.
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		for (int cell = 0; cell < BOARD_SIZE; ++cell)
		{
			move[ZERO] = ALPHABET[cell];
			move[FIRST] = NUMBER[row];
			move[SECOND] = DASH;
            move[FIFTH] = NUL;

			for (int i = 0; i < BOARD_SIZE; ++i)
			{
				move[THIRD] = move[ZERO] + col_move[i];
				move[FORTH] = move[FIRST] + row_move[i];
				if (isVal(board, move, turn) == TRUE)
                {
                    board_t t_brd;
                    memcpy(t_brd, board, sizeof(char)*BOARD_SIZE*BOARD_SIZE);
                    if (!tDepth) return board_cost(t_brd);
                    do_move(t_brd, move);



                    int elem = find_next_move(t_brd,
                                              tDepth - NEXT, turn + NEXT);

                    
                    if ((isOdd(turn) && point > elem) 
                     || (!(isOdd(turn)) && point < elem))
                    {
                        point = elem;
                        nextMove->point = point;
                        strcpy(nextMove->move, move);
                    }
                }
			}
		}
	}
    if (tDepth == TREE_DEPTH) 
    {
        do_move(board, nextMove->move);
    	printf("=====================================\n");
	    printf("*** ");
	    display_board(turn, nextMove->move, board);
    }
    free(nextMove);
    nextMove = NULL;
    return point;
}	

/* Executing stage 1 */
bool do_stage1(board_t board, int turn)
{   
    // find_next_move function will initialise 'point'variable with INT_MAX 
    // or INT_MIN if 'point' still holds INT_MAX/MIN value after running that 
    // function, it means there are not more available moves -> the match ends.
    int point = find_next_move(board, TREE_DEPTH, turn);
    if (point == INT_MAX || point == INT_MIN)
    {
        if (isOdd(turn))    printf("WHITE WIN!");
        else                printf("BLACK WIN!");
        return false;
    }
    return true;
}


/* Executing stage 2 */
void do_stage2(board_t board, int turn)
{
    // The function will resume until it looped 10 times 
    // or the match ends
    int  count  = 0;
    bool resume = true;
    while(count < COMP_ACTIONS && resume)
    {
        resume = do_stage1(board, turn + count);
        ++count;
    }
}

/* Executing stage 0 */
int do_stage0(board_t board)
{
    // read input by "%c%d-%c%d\n" format to prevent infinite/leak loop errors
    char s_col, t_col;               // s is short for source
    int  s_row, t_row, turn = 0;     // t is short for target
    char move[MOVE_LEN];
    while(scanf("%c%d-%c%d\n", &s_col, &s_row, &t_col, &t_row) == INPUTLENGTH)
    {

        // converting the input to string/character type
        move[ZERO]   = s_col;
        move[FIRST]  = d2c(s_row);
        move[SECOND] = DASH;
        move[THIRD]  = t_col;
        move[FORTH]  = d2c(t_row);
        move[FIFTH]  = NUL;

        // Checking Invalid moves
        switch(isVal(board, move, turn))
        {
            case ERROR1:
                printf("ERROR: Source cell is outside of the board.\n");	
                return 0;
            case ERROR2:
                printf("ERROR: Target cell is outside of the board.\n");	
                return 0;
            case ERROR3:
                printf("ERROR: Source cell is empty.\n");	
                return 0;
            case ERROR4:
                printf("ERROR: Target cell is not empty.\n");	
                return 0;
            case ERROR5:
                printf("ERROR: Source cell holds opponent's piece/tower.\n");	
                return 0;
            case ERROR6:
                printf("ERROR: Illegal action.\n");	
                return 0;
        }

        // If the move does not have any error, play the move and print out
        do_move(board, move);
    	printf("=====================================\n");
        display_board(turn, move, board);
        ++turn;                                 
        s_row = NUL;
    }

    // Checking if there is an additional action
    if (s_row == NUL)
    {
        // examine the s_row because even if the input action in s_col 
        // reads 'A', it may still be part of a turn (Example: 'A' in 'A1-B2')
        // by making s_row = '\0' at the end of scan will prevent any miss read.
        if (s_col == S1) do_stage1(board, turn);
        if (s_col == S2) do_stage2(board, turn);
    }
    return 0;
}
                        /* Algorithms are fun *
                         * Algorithms are fun *
                         * Algorithms are fun */

/* THE END -------------------------------------------------------------------*/