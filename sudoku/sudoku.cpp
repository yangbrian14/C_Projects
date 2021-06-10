/***********************************************************************                            
* Program:                                                                                          
*    Project 13, Sudoku                                                                             
*    Brother Foushee, CS124                                                                         
* Author:                                                                                           
*    Brian Yang                                                                                     
* Summary:                                                                                          
*    Writing a program to implement the rules of sudoku.                                            
*                                                                                                   
*    Estimated:  2 hours                                                                            
*    Actual:     6 hours                                                                            
*      The most difficult part is implementing the rules of sudoku into                             
*      the editNumber function to make sure it doesn't save the wrong                               
*      input number into the board.                                                                 
************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readFile(      int board[][9]                              );
void displayOptions(int board[][9]                              );
void option(        int board[][9], char userInput[], int value);
void displayboard(  int board[][9]                              );
int editSquare(     int board[][9], char userInput[], int value);
void saveFile(      int board[][9]                              );
void coordinate(                    char userInput[]            );
bool correctNumber( int board[][9], char userInput[], int value);
int showValues(     int board[][9], char userInput[]            );

/**********************************************************************                               
 * This function will read a file from the user and save the sudoku                                   
 * into a multidimensional array                                                                      
 ***********************************************************************/
void readFile(int board[][9])
{
   ifstream fin;
   char fileName[256];
   cout << "Where is your board located? ";
   cin >> fileName;

   fin.open(fileName);
   if (fin.fail())
   {
      cout << "Invalid file!\n";
      return;
   }

   for (int row = 0; row < 9; row++)
   {
      for (int col = 0; col < 9; col++)
         fin >> board[row][col];

   }
   fin.close();
   return;
}

/**********************************************************************                               
 * options- will display options                                                                      
 ***********************************************************************/
void displayOptions(int board[][9])
{
   cout << "Options:\n"
        << "   ?  Show these instructions\n"
        << "   D  Display the board\n"
        << "   E  Edit one square\n"
        << "   S  Show the possible values for a square\n"
        << "   Q  Save and Quit\n";

   cout << endl;
}

/**********************************************************************                               
 * displayBoard function will display the board from the read file                                    
 ***********************************************************************/
void displayBoard(int board[][9])
{
   int row;
   int col;
   cout << "   A B C D E F G H I\n";
   for (row = 0; row < 9; row++)
   {
      if ((row == 3) ||
          (row == 6))
      {
         cout << "   -----+-----+-----\n";
      }

      cout << row + 1 << "  ";

      for (col = 0; col < 9; col++)
      {
         if ((board[row][col] == 0))
            cout << ' ';

         else if (board[row][col] > 0)
            cout << abs(board[row][col]);
         else
            cout << abs(board[row][col]);

         if ((col == 2) ||
             (col == 5))
            cout << "|";
         else if (col == 8)
            cout << '\n';
         else
            cout << ' ';
      }
   }

   cout << endl;
}

/**********************************************************************                               
 * This function will allow the user to choose an option                                              
 ***********************************************************************/
void option(int board[][9], char userInput[], int value)
{
   char input;
   cout << "> ";
   cin >> input;

   switch (input)
   {
      case '?':
         displayOptions(board);
         cout << "\n";
         break;
      case 'D':
      case 'd':
         displayBoard(board);
         break;
      case 'E':
      case 'e':
         editSquare(board, userInput, value);
         break;
      case 'S':
      case 's':
         showValues(board, userInput);
         break;
      case 'Q':
      case 'q':
         saveFile(board);
         return;
      default:
      {
         cout << "ERROR: Invalid command\n";
         displayOptions(board);
      }
   }

   option(board, userInput, value);
}

/**********************************************************************                               
 * editSquare will allow the user to choose a square and edit it                                      
 ***********************************************************************/
int editSquare(int board[][9],char userInput[], int value)
{
   int row = 0;
   int col = 0;

   coordinate(userInput);

   for (char *i = userInput; *i; i++)
   {

      if (isalpha(*i))
      {
         *i = toupper(*i);
         switch (*i)
         {
            case 'A':
               col = 0;
               break;

            case 'B':
               col = 1;
               break;

            case 'C':
               col = 2;
               break;

            case 'D':
               col = 3;
               break;

            case 'E':
               col = 4;
               break;

            case 'F':
               col = 5;
               break;

            case 'G':
               col = 6;
               break;

            case 'H':
               col = 7;
               break;

            case 'I':
               col = 8;
               break;

            default:
               cout << "ERROR: Square '" << userInput << "' is invalid\n";
         }
      }

      if (isdigit(*i))
         row = atoi(i) - 1;

   }

   if (board[row][col] > 0)
      cout << "ERROR: Square '" << userInput << "' is filled\n";
   else
   {
      cout << "What is the value at '" << userInput << "': ";
      cin >> value;

      if ((board[row][col] < 9) && (board[row][col] > 0) ||
          (correctNumber(board, userInput, value) == true))
         board[row][col] = - value;
      else
         cout << "ERROR: Value '" << value << "' in square '"
              << userInput << "' is invalid\n";

   }

   cout << endl;

   return 0;
}

/**********************************************************************                               
 * The saveFile will let the user save their edited board onto the file                               
 * of their choice                                                                                    
 **********************************************************************/
void saveFile(int board[][9])
{
   ofstream fout;
   char save[256];
   cout << "What file would you like to write your board to: ";
   cin >> save;
   fout.open(save);

   for (int row = 0; row < 9; row++)
   {
      for (int col = 0; col < 9; col++)
         fout << board[row][col] << ' ';
   }

   cout << "Board written successfully\n";

   fout.close();
}

/**********************************************************************                               
 * prompt for user to input the coordinates for sudoku board                                          
 ***********************************************************************/
void coordinate(char userInput[])
{
   cout << "What are the coordinates of the square: ";
   cin.ignore();
   cin.getline(userInput, 256);
}

/**********************************************************************                               
 * the possible values from the rules of sudoku.                                                      
 **********************************************************************/
bool correctNumber(int board[][9], char userInput[], int value)
{
   int row = userInput[0];
   int col = userInput[1];

   for (char *j = userInput; *j; j++)
   {

      if (isalpha(*j))      // read even if it is lower case                                          
      {
         *j = toupper(*j);
         switch (*j)
         {
            case 'A':
               col = 0;
               break;

            case 'B':
               col = 1;
               break;

            case 'C':
               col = 2;
               break;

            case 'D':
               col = 3;
               break;

            case 'E':
               col = 4;
               break;

            case 'F':
               col = 5;
               break;

            case 'G':
               col = 6;

            case 'H':
               col = 7;
               break;

            case 'I':
               col = 8;
               break;
         }
      }

      if (isdigit(*j))
         row = atoi(j) - 1;
   }

   bool isTrue = true;

   for (int i = 0; i < 9; i++)
   {
      if ((board[row][i] == value) ||
          (board[i][col] == value))
         isTrue = false;
   }

   for (int ij = 3 * (row / 3); ij < (3 * (row / 3) + 3); ij++)
   {
      for (int ji = 3 * (col / 3); ji < (3 * (col / 3) + 3); ji++)
         if (board[ij][ji] == value)
            isTrue = false;
   }

   return isTrue;
}

/**********************************************************************                               
 * This function will show the possible values due to the rule of                                     
 * sudoku                                                                                             
 **********************************************************************/
int showValues(int board[][9], char userInput[])
{
   int row = 0;
   int col = 0;

   coordinate(userInput);

   for (char *i = userInput; *i; i++)
   {
      if (isalpha(*i))
      {
         *i = toupper(*i);
         switch (*i)
         {
            case 'A':
               col = 0;
               break;

            case 'B':
               col = 1;
               break;

            case 'C':
               col = 2;
               break;

            case 'D':
               col = 3;
               break;

            case 'E':
               col = 4;
               break;

            case 'F':
               col = 5;
               break;

            case 'G':
               col = 6;
               break;

            case 'H':
               col = 7;
               break;

            case 'I':
               col = 8;
               break;
         }
      }

      if (isdigit(*i))
         row = atoi(i) - 1;
   }

   if (board[row][col] > 0)
      cout << "ERROR: Square '" << userInput << "' is read-only\n\n";

   int list[10] = {0, 1, 2, 3, 4, 5 , 6, 7, 8, 9};

   int c;
   for (int r = 0; r < 9; r++)
   {
      for (c = 0; c < 10; c++)
      {

         if (((board[row][r]) == (list[c])) ||
             ((board[r][col]) == (list[c])))
            list[c] = 0;

        for (int ij = 3 * (row / 3); ij < (3 * (row / 3) + 3); ij++)
         {
            for (int ji = 3 * (col / 3); ji < (3 * (col / 3) + 3); ji++)
               if (board[ij][ji] == list[c])
                  list[c] = 0;
         }
      }
   }

   int letscount = 0;

   cout << "The possible values for '" << userInput << "' are: ";
   for (c = 0; c < 10; c++)
   {
      if (list[c] != 0)
      {
         if (letscount != 0)
            cout << ", ";

         cout << list[c];
         letscount++;
      }
   }

   cout << "\n\n";

   return 0;
}

/**********************************************************************                               
 * Main will run the whole program by calling on functions                                            
 ***********************************************************************/
int main()
{
   int value;
   char userInput[256];
   int board[9][9];

   // read file from user                                                                             
   readFile(board);

   // display the options for user to see                                                             
   displayOptions(board);

   // display the board for the user to see                                                           
   displayBoard(board);

   // will call on other function through the                                                         
   // letter of options that the user input                                                           
   option(board, userInput, value);

   return 0;
}

            
