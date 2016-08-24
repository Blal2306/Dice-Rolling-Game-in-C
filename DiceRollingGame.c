#include <stdio.h>
#include <stdlib.h>

/*** CLASS VARIABLES ***/
int r1, r2, r3; //Store the values for each roll
int chipCount [5]; //Die count for players
int prev, next, current; //Previous next and current position
int seed;

/*** FUNCTION PROTOTYPES ***/
int rollDie();
void drawDie(int diceValue);
void passChips(int die1, int die2, int die3);
int takePot(int die1, int die2, int die3);
int nextP(int x);
void passDie(int x);
void printChipTable();
void player(int x);


/*** MAIN METHOD ***/
main()
{
    int chipsCount;// count of chips for players
    int x;
    //Variable initialization
    r1 = r2 = r3 = 0;
    prev = 3;
    next = 2;
    current = 1;
    for(x = 0; x < 5; x++)
        chipCount[x] = 0;
    printf("Please enter random seed : ");
    scanf("%d", &seed);
    srand(seed); //create the seed for random number

    /****** GAME CONTROLS *********/

    printf("Let’s Play Left, Right, Center!\n");
    printf("How many chips would you like to play with (3-10): ");
    scanf("%d", &chipsCount);

    //Give the chips to all users
    for(x = 1; x <= 3; x++)
        chipCount[x] = chipsCount;

    printChipTable();
    //The game will continue until
    //only one player left with chips
    while(haveWinner() == 0)
    {
        player(current);

        //move on to the next player
        current = nextP(current);
        next = nextP(next);
        prev = nextP(prev);
    }
    printWinner();
    /******************************/

}
int rollDie()
{
    return (rand() % 6 + 1);
}
void drawDie(int diceValue)
{
    int z;
    printf("\n");
    for(z = 0; z < 5; z++)
        printf("*");
    printf("\n");

    switch(diceValue)
    {
        case 1 :
            printf("* L *\n");
            break;
        case 2 :
            printf("* R *\n");
            break;
        case 3 :
            printf("* C *\n");
            break;
        case 4 : case 5 : case 6 :
            printf("* * *\n");
            break;
    }

    for(z = 0; z < 5; z++)
        printf("*");
    printf("\n\n");
}
void passChips(int die1, int die2, int die3)
{
    //check the condition for taking the pot
    if(takePot(die1, die2, die3) == 1)
    {
        printf("Player %d rolled LCR! You’ve won the pot! Congratulations!\n", current);
        chipCount[current]+=chipCount[4];
        chipCount[4] = 0;
    }
    else //pass the die
    {
        passDie(die1);
        passDie(die2);
        passDie(die3);
    }
}
//check if there is a condition for pot
int takePot(int die1, int die2, int die3)
{
    if((die1 == 1) && (die2 == 3) && (die3 == 2))
        return 1;
    else
        return 0;
}
int nextP(int x)
{
    if(x == 3)
        return 1;
    else
        return (x+1);
}
void passDie(int x)
{
    switch(x)
    {
        case 1 : //L
            chipCount[prev]++;
            chipCount[current]--;
            printf("Player %d passes 1 chip(s) to Player %d\n", current, prev);
            break;

        case 2 : //R
            chipCount[next]++;
            chipCount[current]--;
            printf("Player %d passes 1 chip(s) to Player %d\n", current, next);
            break;

        case 3 : //C
            chipCount[4]++;
            chipCount[current]--;
            printf("Player %d passes 1 chip(s) to the Pot\n", current);
            break;

        case 4 : case 5 : case 6 : //DOTS
            break;

    }
}
void printChipTable()
{
    int y;
    printf("\nPlayer :\t");
    for(y = 1; y <= 3; y++)
        printf("%d\t", y);
    printf("Pot\n");

    for(y = 0; y <= 42; y++)
        printf("=");
    printf("\n\t\t");

    for(y = 1; y <= 4; y++)
        printf("%d\t", chipCount[y]);

    printf("\n\n");
}
void player(int x)
{
    char in;
    //Only 1 die left; therefore, only 1 roll
    if(chipCount[x] == 1)
    {
        do
        {
            printf("Player %d : Enter 'R' to roll the dice : ", current);
            scanf("\n%c", &in);
        }
        while(in != 'r');
        r1 = rollDie();
        drawDie(r1);

        //2nd and 3rd rolls will remain neutral
        r2 = 0;
        r3 = 0;

        passChips(r1, r2, r3);
    }
    else if(chipCount[x] == 2) //2 die = 2 rolls
    {
        //roll the 1st die
        do{
            printf("Player %d : Enter 'R' to roll the dice : ", current);
            scanf("\n%c", &in);
        }
        while(in != 'r');
        r1 = rollDie();
        drawDie(r1);

        //2nd roll
        do
        {
            printf("Player %d : Enter 'R' to roll the dice : ", current);
            scanf("\n%c", &in);
        }
        while(in != 'r');
        r2 = rollDie();
        drawDie(r2);

        //3rd roll neutral
        r3 = 0;

        passChips(r1, r2, r3);
    }

    //if the player doesn't have any chips pass it
    //to the next player
    else if(chipCount[x] == 0)
    {
        do
        {
            printf("Player %d : Enter 'P' to Pass : ", current);
            scanf("\n%c", &in);
        }
        while(in != 'p');

        return;
    }
    else
    {
        //1st roll
        do{
            printf("Player %d : Enter 'R' to roll the dice : ", current);
            scanf("\n%c", &in);
        }while(in != 'r');
        r1 = rollDie();
        drawDie(r1);

        //2nd roll
        do{
            printf("Player %d : Enter 'R' to roll the dice : ", current);
            scanf("\n%c", &in);
        }while(in != 'r');
        r2 = rollDie();
        drawDie(r2);

        //3rd roll
        do{
            printf("Player %d : Enter 'R' to roll the dice : ", current);
            scanf("\n%c", &in);
        }while(in != 'r');
        r3 = rollDie();
        drawDie(r3);

        passChips(r1, r2, r3);
    }
    printChipTable();
}
//return true or false indicating if we have a winner
int haveWinner()
{
    //The player left with the chip wins
    if(((chipCount[2] == 0) && (chipCount[3] == 0)) || //player 1 wins
        ((chipCount[1] == 0) && (chipCount[3] == 0)) || //player 2 wins
        ((chipCount[1] == 0) && (chipCount[2] == 0))) //player 3 wins

        return 1;
    else
        return 0;
}
//print winner of the game
void printWinner()
{
    if((chipCount[2] == 0) && (chipCount[3] == 0))
        printf("Player 1 won !\n");
    if((chipCount[1] == 0) && (chipCount[3] == 0))
        printf("Player 2 won !\n");
    if((chipCount[1] == 0) && (chipCount[2] == 0))
        printf("Player 3 won !\n");
}




