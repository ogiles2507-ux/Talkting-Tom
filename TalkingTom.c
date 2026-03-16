#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void clearScreen();

void printLogo();

void tomAgeGetter(int ageOfTom, bool *gettingAge);

void getAction();

void helpInfo();

void (*printTom)();

void youngTomArt();

void oldTomArt();

void printUI(int tomHappiness, int tomFeeding, int tomBathroom, int tomSleep);

void drawGame(int h, int f, int b, int s);

int main()
{

   bool isGameRunning = true,
        gettingAge    = true;
   int  gameRan       = 0,
        ageOfTom      = 0,
        tomHappiness  = 0,
        tomFeeding    = 50,
        tomSleep      = 50,
        tomBathroom   = 50;
   char actionLetter,
        enter,
        yesNoAnswer;

   //Clears the terminal
   clearScreen();

   //Prints the Tom logo
   printLogo();
   
   printf("Do you have a save code?  Y / N: ");
   scanf(" %c", &yesNoAnswer);

   switch (yesNoAnswer)
   {
      case 'Y':
         printf("\nWelcome back! Please enter your save code now: ");
         scanf(" %d %d %d %d %d", &tomSleep, &tomFeeding, &ageOfTom, 
                  &tomBathroom, &tomHappiness);

         // Set printTom based on loaded age
         if (ageOfTom >= 1 && ageOfTom <= 17)
         {
            printTom = youngTomArt;
         }
         else
         {
            printTom = oldTomArt;
         }
         break;
      //No save code
      default:
         do
         {
            //prints Talking Tom logo
            printLogo();

            printf("===========================================\n\n");
            printf("Before we jump right in, how old would you\nlike Tom to be?\n");
            printf("Enter age here: ");

            //Takes age and checks
            if (scanf("%d", &ageOfTom) != 1)
            {
            printf("\nInvalid input. Please enter a number.\n\n");
            while (getchar() != '\n');
            continue;
            }
            while (getchar() != '\n');

            //determines what age Tom will print
            tomAgeGetter(ageOfTom, &gettingAge);

            if (ageOfTom < 1 || ageOfTom > 99)
            {
              printf("\nSorry Tom can't be that age today, try an age between"
                        "1 and 99.\n\n");
            }

         } while (gettingAge);
   }
   
   printf("Press ENTER to move on.");
   getchar();

   //Main gameloop
   do 
   {
      drawGame(tomHappiness, tomFeeding, tomBathroom, tomSleep);
        
      // Asks user what they want to do
      getAction();
      scanf(" %c", &actionLetter);

      //Does game logic for Tom's feelings 
      switch(actionLetter)
      {
         //Happy logic
         case 'h':
            printf("Tom loves the scratches behind the ear.\n");
            tomHappiness += 10;
            tomFeeding -= 10;
            tomBathroom -= 5;
            tomSleep -=20;

            gameRan++;
            break;
         //Feeding logic
         case 'f':
            printf("Tom loves a good cookie.\n");
            tomHappiness += 5;
            tomFeeding += 10;
            tomBathroom -= 10;
            tomSleep -=10;

            gameRan++;
           break;
         //Bathroom logic
         case 'b':
            printf("Tom's a kid and doesn't waste time showering.\n");
            tomHappiness -= 5;
            tomFeeding -= 5;
            tomBathroom += 10;
            tomSleep +=5;

            gameRan++;
            break;
         //Sleepy logic
         case 's':
            printf("'Zzz' shhh 'Zzz' Tom's getting his beauty sleep.\n");
            tomHappiness +=25;
            tomFeeding -= 15;
            tomBathroom -=10;
            tomSleep +=10;

            gameRan++;
            break;
         //Help print
         case 'H':
            //Prints the help info.
            helpInfo();
            break;
         //Quit logic
         case 'q':
            isGameRunning = false;
            printf("Thanks for playing with Tom. Have a beautiful day!\n");
            break;
         //Save logic
         case 'S':
            printf("Here is your save code: ");
            printf("%d %d %d %d %d", tomSleep, tomFeeding, ageOfTom, 
                           tomBathroom, tomHappiness);
            printf("\nKeep this code to pick up where you are when you play again\n");
            break;
         //Error
         default:
            printf("\n\nERROR. Character not recognized. Try again.\n");
            printf("Tip: actions should be lowercased when entered.\n");
      }

      //Clears buffer and continues program
      printf("\nPress ENTER to continue.");
      while (getchar() != '\n');
      getchar();

      //Checks if player has lost
      if (tomFeeding <= 0 || tomBathroom <= 0 || tomSleep <= 0 || 
            tomHappiness < 0)
      {
         drawGame(tomHappiness, tomFeeding, tomBathroom, tomSleep);

         printf("You made Tom sad today :(\n");
         printf("Run the program again to retry.\n");
         printf("You failed in %d moves\n", gameRan);
         isGameRunning = false;
      }
      //Checks if player had a perfect day????
      else if (tomFeeding >= 100 && tomBathroom >= 100 && tomSleep >= 100 && 
                  tomHappiness >=100)
      {
         drawGame(tomHappiness, tomFeeding, tomBathroom, tomSleep);

         printf("A perfect day!!! WOW, what a lucky cat.");
         printf("You finished the game in %d moves\n", gameRan);
         printf("Would you like to play again?  Y / N:");
         isGameRunning = false;
      }
      //Checks if player has won
      else if (tomHappiness >= 100)
      {
         drawGame(tomHappiness, tomFeeding, tomBathroom, tomSleep);

         printf("Yay!! Tom is happy again. You win!\n");
         printf("You finished the game in %d moves\n", gameRan);
         printf("For an even harder challenge, make all vitals 100?\n");
         isGameRunning = false;
      }

   }  while (isGameRunning);

   return 0;
}

 /*****************************************************************************
  Clears the terminal screen.
 *****************************************************************************/
void clearScreen()
{
   //system("clear"); //use for Mac and Linux // This is slow and it depends on shell
   //system("cls");   //use for Windows
   printf("\033[2J\033[H"); // faster than system("clear");
}

 /*****************************************************************************
  Determines what Tom art to print
 *****************************************************************************/
void tomAgeGetter(int ageOfTom, bool *gettingAge)
{
   if (ageOfTom <= 17 && ageOfTom >= 1)
   {
      printTom = youngTomArt;
      *gettingAge = false;
   }
   else if (ageOfTom <= 99)
   {
     printTom = oldTomArt;
     *gettingAge = false;
   }
}
 /*****************************************************************************
  Prints the Tom logo.
 *****************************************************************************/
void printLogo()
{
      printf("Welcome to...\n");
      printf("   ###* /\\  #  #/ * #==  ##   \n");
      printf("    ::  \\@\\ #= #\\ # # *  _>\n");
      printf("*#########+*#########   ####-    ####\n");
      printf("*#########* ########### #####   #####\n");
      printf("    ###* **###*   *####*-####* ######\n");
      printf("    #### ####*     ####* #####*######\n");
      printf("    *### #####*   ##### *#*##########\n");
      printf("    *###  ############* ##  #### *###*\n");
      printf("    *###*   ######### *###  ###* *###*\n");
      printf("For those who couldn't read: 'Talking TOM'\n");
      return;
}

 /*****************************************************************************
  Prompts user for what they will do.
 *****************************************************************************/
void getAction()
{
   printf("How would you like to make Tom happy? ");
}

 /*****************************************************************************
  Prints help guide info.
 *****************************************************************************/
void helpInfo()
{
   printf("\nHere are all the usable commands:\n");
   printf("1. 'h' for happy\n");
   printf("    -  Giving Tom a good scratch around the ear\n");
   printf("    -  Adds 10 to the Happiness stat\n");
   printf("2. 'f' for feed\n");
   printf("    -  Give Tom grandmas famous cookies\n");
   printf("    -  Adds 10 to the Feeding stat\n");
   printf("3. 'b' for bathroom\n");
   printf("    -  Tom is stinky, give him a bath\n");
   printf("    -  Adds 10 to the Bathroom stat\n");
   printf("4. 's' for sleep\n");
   printf("    -  After a long day Tom needs some rest\n");
   printf("    -  Adds 10 to the Sleepy stat\n");
   printf("5. 'q' for quit\n");
   printf("    -  You don't want to play with Tom :(\n");
   printf("    -  Ends playing with Tom\n");
   printf("6. 'S' for save code\n");
   printf("    -  Gives code so you can play with Tom again\n");
   printf("    -  Keep the code safe so Ben doesn't steal it\n");
}
 /*****************************************************************************
  Prints the younger Tom character. 
 *****************************************************************************/
void youngTomArt()
{
   printf("\n          ......                                            \n");
   printf("         ..++-++---............--.......                      \n");
   printf("        ..+-.--....--++++++--...-++-+##+-...                  \n");
   printf("        .--.  ..+..                     ..++-.....            \n");
   printf("        .--     .+..                        .-++#+++------..  \n");
   printf("        .-.     .+..                               ......-+.  \n");
   printf("        .-.    ..+.                              ..-++....+-. \n");
   printf("        .--    .+..                              .+-.    .+-. \n");
   printf("        .--.  .+-.                              ..+.     .+.  \n");
   printf("        ..+-..-..  ..+++..                      .-+.    .--.  \n");
   printf("         ..++-.   #+...-##+.                    ..+.    .+..  \n");
   printf("          .-+..   ...####+#+.         .-####+.  ..-.   .+-.   \n");
   printf("         .--.      .###+   +.       .+####-..+.  ... ..+-.    \n");
   printf("        .--.       .#####+##.      .++   ###..   ....-+..     \n");
   printf("       ..+.        .-######.       .+#+-+###- .   .-+..       \n");
   printf("       .-+---.       ......        .-#######.      .--        \n");
   printf("       .-+..+-            ...---... ..-++--.       .--.       \n");
   printf("        .+++-. ....       .--...-+-.               .-+.       \n");
   printf("    ...-++#--+++-++.       .--+---.            ..+++++.       \n");
   printf("   ..-+...-++.. .-#.                           .-+..--.       \n");
   printf("   ..+.    .-+-.-+..   ..+###++#####-.   .+++-...+--+.        \n");
   printf("    .-+-..   .-++-..    ..+-...-+#+..    +- ..++--#-.         \n");
   printf("      ..++-... ..-++-..   ..++++-.       .#....+#-.           \n");
   printf("         ..-++-... ..+++---......    .....-#++-..             \n");
   printf("             ..-+--... ....-++++++++++##+-..                  \n");
   printf("                 ..+#.            .+-.. ...                   \n");
   printf("                  .+-              -+..  ...                  \n");
   printf("                 .++.              .+-.  ...                  \n");
   printf("                .-+..               .+.. +..                  \n");
   printf("                .#..                .+-.  ..                  \n");
   printf("                -+.                  -+.  ..                  \n");
   printf("                --.                  .+.. ..                  \n");
   printf("                +-.                  .+.- ..                  \n");
   printf("           .....-+.                  -++-...                  \n");
   printf("         .-+   ++#..   ..++---.     .+-. ..                   \n");
   printf("         .-+-  -+#-.   ..-#.-+.     -+..                      \n");
   printf("          ..+.  -##..  ..##++#-   ..+-.                       \n");
   printf("            ..- -..++--++.   -++--++--+-.                     \n");
   printf("              ..-++++++--     --+++++--..                     \n");
}

 /*****************************************************************************
  Prints older Tom character. 
 *****************************************************************************/
void oldTomArt()
{
   printf("                              ..  ..                            \n");
   printf("                     . ...-...-       ..  .    ...              \n");
   printf("               .+=. . ++--.   .......   .+..-.                  \n");
   printf("                -  .-.  ..  -+      .-.. . -..--+++-.-          \n");
   printf("                -.    -...--           .-. ..  .---  -.         \n");
   printf("                -.     +..    .           .  -+.    ..          \n");
   printf("                .-     # --...#.    .+. .-.  -      -.          \n");
   printf("     .-.         .-   -+--.##.+-   .--...-.. -     ..           \n");
   printf("    .-  -.         -.-- .-###++.   .-.##+ ++ .-   +.            \n");
   printf("  .  -  ..-..+      --  .+ .+--    --.### ++   ++-              \n");
   printf("--  --   .-  +     -+--.    .-      --..---    .-               \n");
   printf(".-..        .-     +..-..  ..--....---    ....-.-.              \n");
   printf(" -++.       -.    .-...      .-- .+-.  .....-.   +              \n");
   printf("-.           .+.   +  -   +-           --.    --.+..            \n");
   printf(".--+--++--     --  .-...    -++-.-+#+-+     ....-.              \n");
   printf("          --     -- .- .     -......--      ...-                \n");
   printf("           .-      .-..--.    .#-.--.     +.-.                  \n");
   printf("            .-         -+-#-            .-.                     \n");
   printf("              +-            .-...---..-...                      \n");
   printf("               .-.              ...       ...                   \n");
   printf("                 .-.                         .+                 \n");
   printf("                    ..        .-+--+-.         .-               \n");
   printf("                       +    .-        ..         --             \n");
   printf("                       #   +.           .          -.           \n");
   printf("                      .-  +.            ..          .-          \n");
   printf("                      +   +              .   ---      +.        \n");
   printf("                      #  ..              -   -. .-.    ..-..    \n");
   printf("                     .-  ..              -   ..   .-        .-. \n");
   printf("                     +.  ..              ..   -     -.      -+. \n");
   printf("                     +   ..               -   +     -.     . .- \n");
   printf("                     +   ..               -   +    .- .+-  ---- \n");
   printf("                    .-   -                -   ..    +++--. -    \n");
   printf("                    ..   -                -    -         --     \n");
   printf("                    ..   ..               +    ..               \n");
   printf("                    -.    +              +.    .+-              \n");
   printf("                    -.     .           .+.     .- - .+-.        \n");
   printf("                    -.       ........--         -.-  ...-.      \n");
   printf("                   .-        -...---...-        -.   .. +.      \n");
   printf("                   .-        +         -        --     +-       \n");
   printf("                   .-       ..         .-       -. .--.         \n");
   printf("                   .-       -.          -.      ..              \n");
   printf("                    .       -.          -.       -              \n");
   printf("                    ..     .-            -       -              \n");
   printf("                .---       .-            -.       .-..          \n");
   printf("             .-..   .      .-             #         ..+.        \n");
   printf("             ++-.  +       +               +.     #. +-+        \n");
   printf("             .++#-.#+...-+.                 .-.  -+-.-.         \n");
   printf("                                              .---.             \n");
}

 /*****************************************************************************
  Prints Tom stats UI
 *****************************************************************************/
void printUI(int tomHappiness, int tomFeeding, int tomBathroom, int tomSleep)
{
   printf("======================================================   \n" );
   printf(" type |   ____       ____      ____      ____  |         \n" );
   printf(" 'H'  |  /    \\     /    \\    /    \\    /    \\ |GOAL: \n");
   printf("if you|  |%3d%%|     |%3d%%|    |%3d%%|    |%3d%%| |make  \n", 
               tomHappiness, tomFeeding, tomBathroom, tomSleep);
   printf(" need |  \\____/     \\____/    \\____/    \\____/ |happy\n" );
   printf(" help | Happiness  Feeding   Bathroom   Sleepy |\n"          );
   printf("======================================================\n"    );
}

void
drawGame(int h, int f, int b, int s)
{
    clearScreen(); // Cleans the screen
    printTom(); // Prints the tom character
    printUI(h, f, b, s);
}
