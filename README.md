# LINUX-bingo-game
THE IDEA: 
 -User executes A2 with a seed (integer) and a Card (a file 
  containing a 5x5 matrix of integers). 
 -A2.c "calls" (provides) unique random numbers one-by-one. Each time 
  a number is called, if that number appears on the user's Card, it 
  is "marked". 
 -User wins when a row, or column, or all 4 corners, become marked.
 
CARD:
 -A Card has 5 columns of 5 numbers each.
 -The number in the middle must ALWAYS be zero (gets marked for free).
  column 1 contains 5 unique integers in [01-15]
  column 2 contains 5 unique integers in [16-30]
  column 3 contains 4 unique integers in [31-45] plus middle integer 00
  column 4 contains 5 unique integers in [46-60]
  column 5 contains 5 unique integers in [61-75]
 -Card numbers must have exactly 2 digits, and be separated by one space, 
  with no extraneous whitespace, not even at the start or end of a line.
 -example of a Card:
> cat goodInput
12 23 42 55 74
04 19 34 46 72
07 17 00 51 69
11 30 44 56 62
09 27 40 47 67
>
 
A2.c PROGRAM INPUT:
 -User runs A2 with 2 command line arguments: seed and CardFile.
 -The seed is expected to be an integer.
 -The CardFile is expected to be a readable file containing a Card.
 -A correctly-formatted Card would look like the example above.
 -For example, you might run your game as follows, where goodInput
  is the file shown above:
> A2 1063 goodInput


PLAY THE GAME ALONE:
 -A2 will display the list of unique called numbers so far followed by 
  the marked Card (initially, call list is empty and only 00 is marked.)
 -A2 always displays Card with column titles "L", "I", "N", "U", "X".
 -Then, numbers in [01-75] are called until you WIN (which stops program).
 -User triggers the next call by entering any non-enter character. Note
  that input is buffered, so user must hit enter key to get previously-
  typed characters read in, but the enter key itself should not result 
  in a separate call.
 -Called numbers are printed with an appropriate prefix of "L", "I", etc. 
  e.g., I33.  If that called number is in the Card, the number is 
  "marked" on the Card. 
 -A2 displays a marked number by printing 'm' after it (no whitespace
  between number and 'm'). 
 -Each time user triggers a new call, A2 clears the screen, and displays
  the call list followed by the marked Card. To clear the screen from
  a C program, use:  system("clear");
 -User may quit A2 at any time, by entering character "q" (any other
  character (except enter) triggers another call).
 -Note that the enter key itself triggers no call. Thus, if user hits
  enter 14 times, no call occurs. When user hits key 'x' (followed by
  enter), only one call occurs.

PLAY THE GAME WITH OTHERS:
 -2 or more people may play, but they need some extra means of
  communication (so they can coordinate).
 -Each player runs A2 with the SAME SEED, but a different Card. 
 -Players coordinate entering characters at the same time.
 -When one player wins, this player must alert the others. 

WINNING:
 -User wins when their Card has one of these winning conditions:
    all 5 numbers in a column are marked
    all 5 numbers in a row    are marked
    all 4 numbers in the corners are marked
 -When a Card wins, WINNER is printed below the final displayed 
  marked Card, and A2 terminates. 
  
CALLED NUMBERS:
 -Are in [01,75].
 -Are displayed by A2 with appropriate prefix, e.g., L09
 -Are unique (no repeats).
 -Are obtained using C's pseudo-random number generator (functions
  srand and rand).
 -If two runs of A2 both use the same seed, both runs will get
  the SAME stream of random numbers, and thus the same call list. 

EXIT STATUS:
 -Incorrect seed and/or input file causes A2 to exit before playing 
  the game; it MUST send these messages to STDERR and EXIT with 
  these codes:

 -Wrong number of command-line arguments (not 2):
  exit 1. "Usage: A2 seed cardFile"  where "A2" is the name of the
          executing program (thus, would print a different name if 
          program were renamed).
 -Invalid seed (first command line argument is not an integer):
  exit 2. "Expected integer seed, but got XX" where "XX" is the 
          user-supplied seed (first command line argument).
 -CardFile not readable or doesn't exist:
  exit 3. "XX is nonexistent or unreadable"  where "XX" is the name
          of the user-supplied input file (second command line argument).
 -CardFile has incorrect format:
  exit 4. "XX has bad format"  where "XX" is the name of the 
          user-supplied input file (second command line argument).

 -If A2 finishes because user quits prematurely (enters q), or wins:
    exit 0.
 -If you discover other error conditions, have your program handle them
  as above. If the error fits into one of those above, you MUST use that 
  above code and message. If not, use codes 5, 6, etc., and your own 
  appropriate error message to stderr.

FUNCTIONS:
 -Use functions to make your code more readable and modular. 
 -Function and variable names should indicate their purpose. 
 -We will not answer questions such as "how many functions do 
  I need?", "can I use static functions?". etc.

FILES:
 -Your code must be in these files:
    A2.c:       Code containing main and functions it uses
    list.h:     Header file for your List ADT
    list.c:     Code containing your List ADT
    A2Makefile: A makefile to compile your program

LIST ADT:
 -Your List ADT must implement a list of INTEGER items, which could be
  used by A2 to hold a CallList, and any other useful lists.
 -It must include public functions to:
    -ADD an item to list end (item and list are arguments). 
    -CHECK if item is already on list (item and list are arguments).
    -PRINT list (list is argument). It may print the required "L", "I", etc 
     in front of each item. (From CPS305, you know this is not how you
     should implement a list print; however, it is allowed here to simplify 
     your implementation.) If your main requires a plain print also (just 
     the items) you may implement a second print function.
    -INITIALIZE list (max potential size is an argument, possibly list is
     argument).
 -Each function above must be implemented correctly, even if main does
  not use it. TAs will compile your list with a driver to test all
  functions.
 -Your List ADT may also contain any private functions you wish.

MAKEFILE:
 -A2Makefile must contain at least these targets:
    A2, A2.o, list.o, clean
  where clean has no dependencies, and simply removes any executable
  and object code files in the directory.
 -TAs will compile your code with: make -f A2Makefile
  so A2 must be the default target.

DOCUMENTATION:
 -Include ALL your group members' info at the top of A2.c only.
   -CS Userid, Last Name, First Name, Student ID Number, Section
 -Limit your comments. Only document tricky, or non-obvious, code. 
 -If a function requires arguments, then include a comment describing
  the arguments, if not obvious. 
