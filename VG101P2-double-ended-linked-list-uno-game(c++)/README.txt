VG101 2019 summer
project2

name:XuPengcheng
student_ID:518370910177




Structure:
1.player
    int state;//record the state of every player
    int card[N][2];// a two dimensional array to store the card of each player
2.gameSet
    int person_n;//the number of players
    int r;//the round of games
    int c;//the number of initial cards for each player
    int d;//the deck of the card
    int player_t;//The number of the current player
    int accuAttk;//The Accumulated attack number
    FILE *fp;
    Player player[];//The players of the game(a struct)


Input:
  printf("Please the number of the players n,n must be larger than 2(default:4):\n");
  scanf("%d",&game.person_n);
  printf("Please the number of the cards per player c,c must be at least 2(default:5):\n");
  printf("Please the number of the decks d(52 cards each),d must be at least 2(default:2):\n");
  scanf("%d",&game.d);
  printf("Please the rounds of the game r,r must be at least 1(default:1):\n");




Output:
gameSet



