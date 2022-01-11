//manandan, Anandanadeswaran, Melaany, 501030889, 011
//pjgonzal, Gonzales, Patricia Marie, 500730614, 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "list.h"

#define CARD_ROWS 5
#define CARD_COLS 5

typedef struct Card {
    int array[CARD_ROWS][CARD_COLS];
    int marks[CARD_ROWS][CARD_COLS];
} Card_t;

static void read_card ( const char * filename, struct Card * card );
static void print_card( const struct Card * card );
static void mark_card (       struct Card * card, int value );
static void check_args( int argc, char**argv, unsigned *seed );
static int  call_rand ( int lower, int upper );
static int  check_win ( const struct Card * card );


int main(int argc, char**argv)
{
    unsigned seed;

    struct Card card;

    struct List list;


    int enter, rand_integer, running = 1;

    memset ( &card, 0, sizeof(card) );

    check_args ( argc, argv, &seed );

    read_card  ( argv[2], &card );

    srand ( seed );

    INITIALIZE ( CARD_COLS * CARD_ROWS, &list );

    card.marks[2][2] = 1;

    while (running)
    {
        system("clear");

        printf("CallList:");

        PRINT (&list);

        puts ("\n");

        print_card ( &card );

        if ( check_win ( &card ) )
        {
            printf("WINNER\n");
            fflush(stdout);
            running = 0;
            break;
        }

        printf("enter any non-enter key for Call (q to quit): ");
        fflush(stdout);

        while( (enter=fgetc(stdin)) )
        {
            if ( enter == 'q')
            {
                running = 0;
                break;
            }
            if ( enter == '\n' )
                break;

            do 
            {
                rand_integer = call_rand ( 1, 75 );
            } while ( CHECK(rand_integer, &list ) );

            ADD ( rand_integer, &list );

            mark_card ( &card, rand_integer );

        }
    }

    FREE ( &list );

    return 0;
}

static void check_args ( int argc, char**argv, unsigned *seed )
{
    unsigned long seed_;
    char * endptr = NULL;
    if ( argc != 3 )
    {
        fprintf(stderr,"Usage: %s seed cardFile", argv[0]);
        exit ( 1 );
    }

    errno = 0;

    seed_ = strtoul ( argv[1], &endptr, 10 );

    if ( errno || (endptr && *endptr) )
    {
        fprintf(stderr,"Expected integer seed, but got %s\n",argv[1]);
        exit ( 2 );
    }

    *seed = (unsigned)seed_;
}


static void read_card ( const char * filename, struct Card * card )
{
    FILE * fr = fopen (filename, "r");

    int v1, v2, v3, v4, v5, line = 0, bad_format = 0;

    int L[5];
    int I[5];
    int N[5];
    int U[5];
    int X[5];

    if ( !fr )
    {   fprintf(stderr,"%s is nonexistent or unreadable\n", filename );
        exit ( 3 );
    }

    while ( !feof(fr ) )
    {
        if ( 5 != fscanf(fr, "%d %d %d %d %d\n", &v1, &v2, &v3, &v4, &v5 ) )
        {   bad_format = 1;
            break;
        }

        if ( v1 < 1 || v1 > 75 || v2 < 1 || v2 > 75 || v3 < 0 || v3 > 75 || v4 < 1 || v4 > 75 || v5 < 1 || v5 > 75 )
        {   bad_format = 1;
            break;
        }

        //Check if middle is 0
        if(card -> array[2][2]!=0)
        {   bad_format = 1;
            break;
        }

        if( !(v1>=1&&v1<=15) || !(v2>=16&&v2<=30) || (!(v3>=31&&v3<=45) && v3!=0) || !(v4>=46&&v4<=60) || !(v5>=61&&v5<=75))
        {   bad_format = 1;
            break;
        }

        if ( line >= CARD_ROWS )
        {   bad_format = 1;
            break;
        }

        L[line] = v1;
        I[line] = v2;
        N[line] = v3;
        U[line] = v4;
        X[line] = v5;

        card -> array[line][0] = v1;
        card -> array[line][1] = v2;
        card -> array[line][2] = v3;
        card -> array[line][3] = v4;
        card -> array[line][4] = v5;

        line++;
        
    }

    for(int i=0; i<5; i++)
    {    for(int j=i+1; j<5; j++)
            {   if(L[i] == L[j] || I[i] == I[j] || N[i] == N[j] || U[i] == U[j] || X[i] == X[j])
                { bad_format = 1;
                break;
                }
            }
    }
    
    fclose ( fr );

    if ( bad_format )
    {
        fprintf(stderr,"%s has bad format\n",filename);
        exit ( 4 );
    }
}

static void print_card( const struct Card * card )
{
    int r, c;
    char header [CARD_COLS] = {'L','I','N','U','X'};

    for ( c = 0; c < CARD_COLS-1; ++c )
    {
        printf("%-4c",header[c]);
    }

    printf("%-3c\n",header[c]);

    for ( r = 0; r < CARD_ROWS; ++r )
    {
        for ( c = 0; c < CARD_COLS; ++c )
        {
            printf("%02d%-2c",card->array[r][c],card->marks[r][c] ? 'm':' ');
        }
        puts("");
    }
}

static int  call_rand  ( int lower, int upper )
{
    return lower + (rand() % (upper-lower+1));
}

static void mark_card ( struct Card * card, int value )
{
    int r, c;
    for ( r = 0; r < CARD_ROWS; ++r)
        for ( c = 0; c < CARD_COLS; ++c )
            if ( card -> array[r][c] == value )
                card -> marks[r][c] = 1;
}

static int  check_win ( const struct Card * card )
{
    int r, c;
    for ( r = 0; r < CARD_ROWS; ++r)
    {
        for ( c = 0; c < CARD_COLS; ++c )
            if ( !card -> marks[r][c] )
                break;
        if ( c == CARD_COLS )
            return 1;
    }

    for ( c = 0; c < CARD_COLS; ++c )
    {
        for ( r = 0; r < CARD_ROWS; ++r )
            if ( !card -> marks[r][c] )
                break;
        if ( r == CARD_ROWS )
            return 1;
    }

    if ( card -> marks[0][0] 
      && card -> marks[0][CARD_COLS-1] 
      && card -> marks[CARD_ROWS-1][0] 
      && card -> marks[CARD_ROWS-1][CARD_COLS-1] )
        return 1;

    return 0;
}