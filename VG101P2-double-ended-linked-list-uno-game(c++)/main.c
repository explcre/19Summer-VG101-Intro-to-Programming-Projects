#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SUITN 4
//NUMBER OF SUITS
#define ADECK 52
//NUMBER OF CARDS IN A DECK

#define UPDATESIZE 64
//This is the size added to updated discard pile if discard pile is full

#ifndef DOUBLE_CIRCULAR_LINKED_LIST_H
#define DOUBLE_CIRCULAR_LINKED_LIST_H

typedef struct Node
{
    int state;
    int no;//The No. of player,first is 0,second is 1...
    int *card;
    int card_n;
    int lastcard;
    int *score;
    struct Node *pNext;
    struct Node *pPre;
}NODE, *pNODE;


typedef struct pile{
    int n;//number of cards in the pile
    int* card;
}pile;


typedef struct players{
    int state;//record the state of every player
    //int card[N][2];// a two dimensional array to store the card of each player
    int* card;
    int lastcard;
    int score;
    int no;//The No. of player,first is 0,second is 1...
    struct players * pre,*next;
}players;


typedef struct gameset{
    int n;//the number of players
    int r;//the round of games
    int c;//the number of initial cards for each player
    int d;//the deck of the card
    int player_t;//The number of the current player
    int iniplayer;//the first player which is decided by the first round of
    int accuAttk;//The Accumulated attack number
    int dir;// direction:1 ->next->next...   -1:->pre->pre...
    int mode;//1 is demo, 0 is manual mode
    int roundend;//1 when there's on player uses up all card. 0 when a round is still on;

    int lastCard;//record the last card
    FILE *fp;
    pile* stock,discard;
    pNODE player;//The players of the game(a struct)
}gameSet;





pNODE CreateDbCcLinkList(gameSet *game);


void TraverseDbCcLinkList(pNODE pHead);


int IsEmptyDbCcLinkList(pNODE pHead);


int GetLengthDbCcLinkList(pNODE pHead);


int InsertEleDbCcLinkList(pNODE pHead, int pos, int state);


int DeleteEleDbCcLinkList(pNODE pHead, int pos);


void FreeMemory(pNODE *ppHead);

#endif










#define N 1000
#define spades 1
#define hearts 2
#define diamonds 3
#define clubs 4
#define jack 11
#define queen 12
#define king 13
#define ace 14


/*
typedef struct cards{
    int num;
    //from 2-14
    //  14 is Ace
    int suit;
    //1:spades
    // 2:hearts
    // 3:diamonds
    // 4:clubs
    int no;
    //from 1-52 Spades 2 ->1; Hearts 2->2
}cards;
*/




void initialPlayer(players p[],int n,int state);
void fileWrite(FILE *fp,gameSet game);
gameSet input(void);
void printGame(gameSet game);


int cmp(const void *a,const void *b);
void printCard(int* card,int head,int tail);
void shuffle(int* card,int n);
pile* stockCards(pile* pstock,int d);
pile* stockini(int d);
int offer0Card(pNODE playero,pile* stock,int p);
void offercCard(pNODE playero,pile* stock,int p,int c);
int* discardCards();
pile discardini();
int card2rank(int i);
int card2suit(int i);
int ranksuit2card(int rank,int suit);
gameSet* playerini(gameSet* game);
int binarySearch(int card[],int key, int low, int high);
int findAvailableCard(gameSet* pgame,pNODE playert,int lastcard,int* available);
int underAttack(gameSet* pgame,pNODE playert,int lastcard,int* available);
void sortPlayerCard(pNODE playero);
void sortPlayersCard(pNODE playero);
void play(gameSet* pgame, pNODE playert,int ran);
void randomPlay(gameSet *pgame,pNODE playert);
void nextPlayer(int dir,pNODE *playert);
void drawCard(pNODE playero,pile* stock,int draw_n);
gameSet* oneRound(gameSet* pgame,int r_t);
gameSet* rounds(gameSet* pgame);
int test(void);

int main() {

    players p[3];//={{5,{}},{3,{}},{2,{}}};

    gameSet game;
    game=input();
    game.dir=1;
    printGame(game);

//    pile discard;

    game.stock=stockini(game.d);
 //   discard=discardini();


    game.player=CreateDbCcLinkList(&game);
/*
    pNODE playert=(game.player);
    for(int i=1;i<=game.n;i++){
        InsertEleDbCcLinkList(game.player,i,i);
        playert->card[0]=i;
        printCard((playert)->card,0,0);
        playert=playert->pNext;
    }*/


    game.iniplayer=offer0Card((game.player),game.stock,game.n);
    printf("The first player is No.%d\n",game.iniplayer);

    //pNODE playert=(game.player);
    //TraverseDbCcLinkList(game.player);

    /*for(int i=1;i<=game.n;i++)
    {   printCard(((*playert)->card),0,0);
        (*playert)=(*playert)->pNext;
    }*/

    /*for(int i=0;i<game.iniplayer;i++)
    {
        game.player=(game.player)->pNext;
    }*/
     //let the first player changed

    rounds(&game);

    //game=*playerini(&game);
    //offerCard(p,pstock,game.n);
    srand(time(NULL));
    //int num = rand() % N;
    //int num=1+(int)(52.0*rand()/(RAND_MAX+1.0));

    for(int i=0;i<3;i++){
        p[i].state=i;
    }

    initialPlayer(p,2,5);


    fileWrite(game.fp,game);
return 0;
}




pNODE CreateDbCcLinkList(gameSet* game) {
    //p is the number of players,c is the card of initial card
    int c=game->c,r=game->r,p=game->n;


    pNODE p_new = NULL, pTail = NULL;
    pNODE pHead = (pNODE) malloc(sizeof(NODE));

    if (NULL == pHead) {
        printf("Fail to allocate memory of player!\n");
        exit(EXIT_FAILURE);
    }

    int i,*card=(int *)calloc(c+1,sizeof(int));
    if (NULL == card) {
        printf("Fail to allocate the memory of cards!\n");
        exit(EXIT_FAILURE);
    }
    int *score=(int *)calloc(r+1,sizeof(int));
    if (NULL == score) {
        printf("Fail to allocate the memory of cards!\n");
        exit(EXIT_FAILURE);
    }
    memset(score,0,sizeof(int)*(r+1));
    pHead->state = 1;
    pHead->no = 0;
    pHead->card_n = 0;
    pHead->score = score;
    pHead->card = card;
    pHead->pNext = pHead;
    pHead->pPre = pHead;
    pTail = pHead;
/*
    printf("Please input the length of linkedlist you want to create:");
    scanf("%d", &length);*/

    for (i = 1; i <= p-1; i++) {
        p_new = (pNODE) malloc(sizeof(NODE));

        if (NULL == p_new) {
            printf("Fail to allocate the memory of player!\n");
            exit(EXIT_FAILURE);
        }
        /*
        printf("PLease input value of No.%d node：", i);
        scanf("%d", &state);*/



        int *card_new=(int *)calloc(c+1,sizeof(int));
        if (NULL == card_new) {
            printf("Fail to allocate the memory!\n");
            exit(EXIT_FAILURE);
        }

        int *score_new=(int *)calloc(r+1,sizeof(int));
        if (NULL == score_new) {
            printf("Fail to allocate the memory of cards!\n");
            exit(EXIT_FAILURE);
        }
        memset(score,0,sizeof(int)*(r+1));
        p_new->card = card_new;
        p_new->score = score_new;
        p_new->state = i;
        p_new->no = i;
        pHead->card_n = 0;

        p_new->pPre = pTail;
        p_new->pNext = pHead;
        pTail->pNext = p_new;
        pHead->pPre = p_new;
        pTail = p_new;
    }

    return pHead;
}



void TraverseDbCcLinkList(pNODE pHead)
{
    pNODE pt = pHead->pNext;

    printf("The Linkedlist is:");
    while (pt != pHead)
    {
        printf("%d ", pt->state);
        printCard(pHead->card,0,0);
        pt = pt->pNext;
    }
    putchar('\n');
}


int IsEmptyDbCcLinkList(pNODE pHead)
{
    pNODE pt = pHead->pNext;

    if (pt == pHead)
        return 1;
    else
        return 0;
}


int GetLengthDbCcLinkList(pNODE pHead)
{
//If there're x players it will return x-1  ,because no. is 1 to x-1
    int length = 0;
    pNODE pt = pHead->pNext;

    while (pt != pHead)
    {
        length++;
        pt = pt->pNext;
    }
    return length;
}




int InsertEleDbCcLinkList(pNODE pHead, int pos, int state)
{
    pNODE p_new = NULL, pt = NULL;
    if (pos > 0 && pos < GetLengthDbCcLinkList(pHead) + 2)
    {
        p_new = (pNODE)malloc(sizeof(NODE));

        if (NULL == p_new)
        {
            printf("Fail to allocate memory!\n");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            pos--;
            if (0 == pos)
                break;
            pHead = pHead->pNext;
        }

        p_new->state = state;
        pt = pHead->pNext;
        p_new->pNext = pt;
        p_new->pPre = pHead;
        pHead->pNext = p_new;
        pt->pPre = p_new;

        return 1;
    }
    else
        return 0;
}


int	DeleteEleDbCcLinkList(pNODE pHead, int pos)
{
    pNODE pt = NULL;
    if (pos > 0 && pos < GetLengthDbCcLinkList(pHead) + 1)
    {
        while (1)
        {
            pos--;
            if (0 == pos)
                break;
            pHead = pHead->pNext;
        }
        pt = pHead->pNext->pNext;
        free(pHead->pNext);
        pHead->pNext = pt;
        pt->pPre = pHead;

        return 1;
    }
    else
        return 0;
}




void FreeMemory(pNODE *ppHead)
{
    pNODE pt = NULL;
    while (*ppHead != NULL)
    {
        pt = (*ppHead)->pNext->pNext;


        if ((*ppHead)->pNext == *ppHead)
        {
            free(*ppHead);
            *ppHead = NULL;
        }
        else
        {
            free((*ppHead)->pNext);
            (*ppHead)->pNext = pt;
            pt->pPre = *ppHead;
        }
    }
}



int test(void)
{
    int flag = 0, length = 0;
    int position = 0, value = 0;
    pNODE head = NULL;

    gameSet game;
    game=input();
    head = CreateDbCcLinkList(&game);

    flag = IsEmptyDbCcLinkList(head);
    if (flag)
        printf("Double Circular Linkedlist is empty\n");
    else
    {
        length = GetLengthDbCcLinkList(head);
        printf("The length of DbCclinkedlist is:%d\n", length);
        TraverseDbCcLinkList(head);
    }

    printf("please input the position and the value you want to plug in (2values divided by space):");
    scanf("%d %d", &position, &value);
    flag = InsertEleDbCcLinkList(head, position, value);
    if (flag)
    {
        printf("successfully plug in node!\n");
        TraverseDbCcLinkList(head);
    }
    else
        printf("fail to plug in node!\n");

    flag = IsEmptyDbCcLinkList(head);
    if (flag)
        printf("DbCclinkedlist is empty,cannot delete!\n");
    else
    {
        printf("please input the position you want to delete:");
        scanf("%d", &position);
        flag = DeleteEleDbCcLinkList(head, position);
        if (flag)
        {
            printf("Successfully delete the node!\n");
            TraverseDbCcLinkList(head);
        }
        else
            printf("fail to delete the node!\n");
    }

    FreeMemory(&head);
    if (NULL == head)
        printf("Successfully deleted the DbCcLinkedlist,finished releasing memory\n");
    else
        printf("Fail to delete the DbCcLinkedlist,not finish releasing memory!\n");
    return 0;
}


void play(gameSet* pgame, pNODE playert,int ran){
//play the n th card on thr player's hand
pgame->lastCard=playert->card[ran];
playert->lastcard=playert->card[ran];
playert->pNext->lastcard=playert->card[ran];

for(int i=ran;i<playert->card_n;i++){
    playert->card[i]=playert->card[i+1];
}

playert->card_n=playert->card_n-1;

pgame->discard.n=pgame->discard.n+1;
pgame->discard.card[pgame->discard.n]=playert->card[ran];



printf("The No.%d player plays ",playert->no);
printCard(playert->card,ran,ran);

}

void randomPlay(gameSet *pgame,pNODE playert){
    srand (time(NULL));
    int ran = 1 + (int) (playert->card_n * rand() / (RAND_MAX + 1.0));
    //generate a number (the ran th card of the player)
    play(pgame, playert, ran);
}

gameSet* oneRound(gameSet* pgame,int r_t){//r_t is the temperary round
    pile* discard=(pile *)malloc(1*sizeof(pile));
    discard->card=(int *)malloc(UPDATESIZE*sizeof(int));
    discard->n=0;
    pgame->discard=*discard;


    shuffle((pgame->stock)->card,ADECK*pgame->d);
    printCard((pgame->stock)->card,1,ADECK*pgame->d);
    //pgame->player=CreateDbCcLinkList(pgame);
    printf("Round %d The first player is No.%d\n",r_t,pgame->iniplayer);
    offercCard(pgame->player,pgame->stock,pgame->n,pgame->c);

    pNODE playert=pgame->player;

    //int odiscard_n=pgame->discard.n;
    pgame->roundend=0;
    pgame->accuAttk=0;

    while(playert->no != pgame->iniplayer)
    {playert=playert->pNext;}

    srand(time(NULL));
    int ran=1+(int)(playert->card_n*rand()/(RAND_MAX+1.0));
    //generate a number (the ran th card of the player)
    play(pgame,playert,ran);
    int tt=0;//if tt=0,it's the first player who plays card
    while(pgame->roundend==0){

        printf("\n");
        if(tt==1) {

            if(playert->no % 3 ==1 )
            randomPlay(pgame,playert);
             /*
            int available[playert->card_n];
            switch (card2rank(pgame->lastCard)) {
                case 12:
                    pgame->dir = pgame->dir * (-1);
                    break;
                case 11:
                    nextPlayer(pgame->dir,&playert);
                    break;
                case 2:
                    pgame->accuAttk = pgame->accuAttk + 2;
                    underAttack(pgame, playert,pgame->lastCard,available);
                    break;
                case 3:
                    pgame->accuAttk = pgame->accuAttk + 3;
                    underAttack(pgame, playert,pgame->lastCard,available);
                    break;
                default:findAvailableCard(pgame, playert,pgame->lastCard,available);
                    break;*/
            }
        tt = 1;
        nextPlayer(pgame->dir,&playert);

        if (playert->card_n <= 0) {
            printf("Player %d wins round %d!\n", playert->no, r_t);
            printf("Round %d Scores:\n",r_t);
            for (int i = 1; i <= pgame->n; i++) {
                playert->score[r_t] = playert->score[r_t-1] - playert->card_n;
                printf("No.%d player:%d\n",playert->no,playert->score[r_t]);
                playert = playert->pNext;
            }
            pgame->iniplayer = playert->no;
            pgame->roundend = 1;
            break;
        }
        }
    return pgame;
    }



void nextPlayer(int dir,pNODE *playert) {
    if (dir == 1) {
        *playert = ((*playert)->pNext);
    } else if (dir == -1) {
       * playert = ((*playert)->pPre);
    }
}



int findAvailableCard(gameSet* pgame,pNODE playert,int lastcard,int* available){
//if no available card return 0
// if have , change the array "available"
    int suit=card2suit(lastcard);
int rank=card2rank(playert->lastcard);
    int flag=0;
    int count=1;
    for(int i=1;i<=playert->card_n;i++){

        if(suit==card2suit(playert->card[i])||rank==2||rank==3||rank==11||rank==12){
            flag=1;available[count]=i;count++;
            }
        else{drawCard(playert,pgame->stock,pgame->accuAttk);pgame->accuAttk=0;count++;}

        }


    available[0]=count-1;//it store the size of available
    return flag;
}



int underAttack(gameSet* pgame,pNODE playert,int lastcard,int* available){
//if no available card return 0
// if have , change the array "available"

int suit=card2suit(lastcard);
//int attack=card2rank(playert->lastcard);
    int flag=0;
int count=1;
    for(int i=1;i<=playert->card_n;i++){

        if(suit==card2suit(playert->card[i])){

            switch(card2rank(playert->card[i])){
                case 2:flag=1;available[count]=i;count++;break;
                case 3:flag=1;available[count]=i;count++;break;
                case 7:flag=1;available[count]=i;count++;break;
                case 11:flag=1;available[count]=i;count++;break;
                case 12:flag=1;available[count]=i;count++;break;
                default:drawCard(playert,pgame->stock,pgame->accuAttk);pgame->accuAttk=0;break;


            }
        }
    }
available[0]=count-1;//it store the size of available
    return flag;

}






gameSet* rounds(gameSet* pgame){


    for(int i=1;i<=pgame->r;i++)
    {//i th round
        pgame->roundend=0;
        oneRound(pgame,i);
    }
    //The following is finding the player with highest score
    pNODE playert=pgame->player;
    int maxscore=playert->score[pgame->r],maxplayer[pgame->n],t=1;
    memset(maxplayer,-1, sizeof(maxplayer));
    for(int j=1;j<=pgame->n;j++){

        if(maxscore<playert->score[pgame->r]){
            maxscore=playert->score[pgame->r];
            maxplayer[t]=playert->no;
        }
        playert=playert->pNext;
    }


    for(int j=1;j<=pgame->n;j++){
        if(maxscore==playert->score[pgame->r]  && playert->no != maxplayer[t])
        {t=t+1;maxplayer[t]=playert->no;}
    }

    int p=1;
    while(maxplayer[p]!=-1){
        printf("winner %d is No.%d, score:%d",p,maxplayer[p],maxscore);
        p=p+1;
    }


    return pgame;
}








gameSet input(void){
    gameSet game;
    printf("Please the number of the players n,n must be larger than 2(default:4):\n");
    scanf("%d",&game.n);
    printf("Please the number of the cards per player c,c must be at least 2(default:5):\n");
    scanf("%d",&game.c);
    printf("Please the number of the decks d(52 cards each),d must be at least 2(default:2):\n");
    scanf("%d",&game.d);

    if(game.d*ADECK<(game.c*game.n)){
        while(game.d*ADECK<(game.c*game.n)){
            printf("The number of decks is to small to offer n player c cards,please input data again:\n");
            printf("Please the number of the players n,n must be larger than 2(default:4):\n");
            scanf("%d",&game.n);
            printf("Please the number of the cards per player c,c must be at least 2(default:5):\n");
            scanf("%d",&game.c);
            printf("Please the number of the decks d(52 cards each),d must be at least 2(default:2):\n");
            scanf("%d",&game.d);
        }
    }
    printf("Please the rounds of the game r,r must be at least 1(default:1):\n");
    scanf("%d",&game.r);
    return game;
}
void printGame(gameSet game){
    printf("There are %d players.\n",game.n);
    printf("There are %d cards per player.\n",game.c);
    printf("There are %d decks.\n",game.d);
    printf("There are %d rounds.\n",game.r);

}
void initialPlayer(players p[],int n,int state)
{
    p[n].state=state;
}

void fileWrite(FILE *fp,gameSet game)
{
    fp = fopen("gamelog.txt","w");//打开文档，写入

    fprintf(fp,"There are ");
    //fprintf(fp,itoa(game.n,s[],1));
    fprintf(fp,"players.\n");
    fprintf(fp,"There are ");
    //fprintf(fp,itoa(game.c,s[],1));
    fprintf(fp,"cards per player.\n");
    fprintf(fp,"There are ");
    //fprintf(fp,itoa(game.d,s[],1));
    fprintf(fp,"decks.\n");
    fprintf(fp,"There are ");
    //fprintf(fp,itoa(game.d,s[],1));
    fprintf(fp,"rounds.\n");
    fclose(fp);
}
/*
int* num2card(int* card,int t,int i)
{
//to set 't' th element in card[] from number 'i'(1-52) to a card struct with num and suit
    (*(card+t)).num=ceil(1.0+ceil(i/4.0));
    (*(card+t)).suit=((i-1) % 4+1);
return card;
}

int card2num(int card[], int i){

    return (int)(SUITN*(ceil(1.0+ceil(i/4.0))-1)+((i-1) % 4+1));
}*/


int card2rank(int i){
    return (int)ceil(1.0+ceil(i/4.0));
}
int card2suit(int i){
    return ((i-1) % 4+1);
}
int ranksuit2card(int rank,int suit)
{
    return (SUITN*(rank-2)+suit);
}


pile* stockCards(pile* pstock,int d)
{
    pstock->card= (int *)calloc(d*ADECK,sizeof(int));
    if ( pstock->card== 0) /*内存申请失败,提示退出*/
    {
        printf("out of memory,press any key to quit...\n");
        exit(0); /*终止程序运行,返回操作系统*/
    }


    for(int j=1;j<=d;j++)
        for(int i=1;i<=ADECK;i++)
        {
            //pstock->card=num2card(pstock->card,(j-1)*ADECK+i,i);
            int rank=ceil(1.0+ceil(i/4.0));
            int suit=((i-1) % 4+1);
            pstock->card[(j-1)*ADECK+i]=ranksuit2card(rank,suit);
        }
    return pstock;
}


pile* stockini(int d){
    pile* pstock=(pile *)malloc(sizeof(pile));
    if ( pstock== 0)
    {
        printf("out of memory,press any key to quit...\n");
        exit(0);
    }

    pstock->card= (int *)malloc(d*ADECK*sizeof(int));
    if ( pstock->card== 0)
    {
        printf("out of memory,press any key to quit...\n");
        exit(0);
    }


    for(int j=1;j<=d;j++)
        for(int i=1;i<=ADECK;i++)
        {
            //pstock->card=num2card(pstock->card,(j-1)*ADECK+i,i);
            int rank=ceil(1.0+ceil(i/4.0));
            int suit=((i-1) % 4+1);
            pstock->card[(j-1)*ADECK+i]=ranksuit2card(rank,suit);
            /*pstock->card[(j-1)*ADECK+i].num=ceil(1.0+ceil(i/4.0));
            pstock->card[(j-1)*ADECK+i].suit=((i-1) % 4+1);*/
        }
    //pstock=stockCards(pstock,d);
    pstock->n=d*ADECK;
    return pstock;
}

int* discardCards(){

    int* card = (int *)malloc(sizeof(int)*1);
    if (card == 0)
    {
        printf("out of memory,press any key to quit...\n");
        exit(0);
    }
    return card;
}


pile discardini(){
    pile discard;
    discard.card=discardCards();
    discard.n=0;
    return discard;
}


gameSet* playerini(gameSet* game){


    players* player=(players *)malloc(sizeof(players));
    if ( player== 0)
    {
        printf("out of memory,press any key to quit...\n");
        exit(0);
    }
    player->card= (int *)malloc(game->c*sizeof(int));
    if ( player->card== 0)
    {
        printf("out of memory,press any key to quit...\n");
        exit(0);
    }


    for(int j=1;j<=game->n;j++)
        for(int i=1;i<=ADECK;i++)
        {
            //pstock->card=num2card(pstock->card,(j-1)*ADECK+i,i);

           // pstock->card[(j-1)*ADECK+i].num=ceil(1.0+ceil(i/4.0));
           // pstock->card[(j-1)*ADECK+i].suit=((i-1) % 4+1);
        }

    //pstock=stockCards(pstock,d);
   // pstock->n=d;
    return game;
}

/*
int cmp(const void *a,const void *b)
{
    //this is a compare function used in "qsort"function
    cards aa=*(cards*)a;
    cards bb=*(cards*)b;

    int aaa=SUITN*(aa.num-1)+aa.suit;
    //This is a map to transfer the card struct with both num and suit to a 1-52 value
    int bbb=SUITN*(bb.num-1)+bb.suit;
    return aaa-bbb;
}*/


void printCard(int* card,int head,int tail)
{
    for(int i=head;i<=tail;i++)
    {
        printf("The No.%d card is ",i);
        switch(card2suit(card[i])){
            case 1:printf("Spades");break;
            case 2:printf("Hearts");break;
            case 3:printf("Diamonds");break;
            case 4:printf("Clubs");break;
            default:;
        }
        printf(" ");
        switch(card2rank(card[i])){
            case 11:printf("J");break;
            case 12:printf("Q");break;
            case 13:printf("K");break;
            case 14:printf("A");break;
            default:printf("%d",card2rank(card[i]));
        }
        printf("\n");
    }
}



void shuffle(int* card,int n)
{

    int cardt[n+5];//the rearranged cards
    memset(cardt,0,sizeof(int)*(n+5));
    for(int j=1;j<=n;j++)
    {
        cardt[j]=card[j];
    }//generate a copy of card[]
    int v[n+5];

    memset(v,0,sizeof(v));
    for(int i=1;i<=n;i++)
    {
        srand(time(NULL));
        int ran=1+(int)(n*rand()/(RAND_MAX+1.0));//generate a number between1-52
        while(v[ran]==1)//loop until the v[ran] is not 0
        {
            ran=1+(int)(n*rand()/(RAND_MAX+1.0));}
        if(v[ran]==0 )
        {
            card[ran]=cardt[i];
            v[ran]=1;
        }

    }
    //return card;
}

int offer0Card(pNODE playero,pile* stock,int p)
//The function is offer 1 card to each player and decide who's first(return an int)
//p is the number of players
{
    //srand(time(NULL));
    //int ran=1+(int)((stock->n)*rand()/(RAND_MAX+1.0));
    pNODE player=(playero);
    int min=(stock->card[stock->n]), t=0;//t record the t th player has minimum card
    for(int i=0;i<p;i++)
    {

        (player)->card[0]=stock->card[(stock->n)-i];//get the card from the stock to the player
        printf("The No.%d's player's No.0 card is",i);
        printCard(stock->card,(stock->n)-i,(stock->n)-i);


        if(stock->card[stock->n-i]<min)
        {
            min = stock->card[stock->n - i];
            t=i;
        }
        player->card[0]=0;
        player=player->pNext;
    }
    stock->n=(stock->n)-p;//the card number of the pile decreased by p

    return t;
}



void offercCard(pNODE playero,pile* stock,int p,int c)
//The function is offer c card to each player
//p is the number of players
{
    //srand(time(NULL));
    //int ran=1+(int)((stock->n)*rand()/(RAND_MAX+1.0));
    pNODE player=playero;
    int i,j;
    for(j=1;j<=c;j++) {
        for (i = 0; i < p; i++) {

            (player)->card[j] = stock->card[(stock->n) - i];//get the card from the stock to the player
            printf("The No.%d's player's No.%d card is",i,j);
            printCard(stock->card, (stock->n) - i, (stock->n) - i);
            if(j==c){player->card_n=c;}
            player = player->pNext;
        }
        stock->n=(stock->n)-p;//the card number of the pile decreased by p
        if(j==c){
            sortPlayersCard(player);
        }
    }
}
void drawCard(pNODE playero,pile* stock,int draw_n)
//The function is offer c card to each player
//p is the number of players
{
    //srand(time(NULL));
    //int ran=1+(int)((stock->n)*rand()/(RAND_MAX+1.0));
    pNODE player=playero;
    int i,j;
    for(j=1;j<=draw_n;j++) {
        for (i = 0; i < 1; i++) {

            (player)->card[player->card_n+1] = stock->card[(stock->n) - 0];//get the card from the stock to the player
            printf("The No.%d's player draw ",i);
            printCard(stock->card, (stock->n) - i, (stock->n) - i);
            if(j==draw_n){player->card_n=player->card_n+draw_n;}
            //player = player->pNext;
        }
        stock->n=(stock->n)-1;//the card number of the pile decreased by p
        if(j==draw_n){
            sortPlayersCard(player);
        }
    }
}




int binarySearch(int card[],int key,int low, int high)
{
    if(low > high)
        return -1;
    int mid = (low + (high-low)/2);
    if((card[mid]<=key)&&(key<=card[mid+1]))return mid;
    else if(card[mid] > key)
        return binarySearch(card,key,low,mid -1);
    else
        return binarySearch(card,key,mid + 1,high);
}


int cmp (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

void sortPlayerCard(pNODE playero){
    int no=playero->no,card_n=playero->card_n;
    pNODE player=playero;
    //int high=(int)sizeof((player)-> card)-1;
    printf("\nsize of No.%d's player's cards is %d\n",no,card_n  );

    qsort((((player)->card) + 1), card_n, sizeof(typeof((player)->card[0])), cmp);
    printf("The No.%d's player's cards:\n", no);
    printCard(((player)->card), 1, card_n);
}


void sortPlayersCard(pNODE playero){
    pNODE player=playero;
    int i,length=GetLengthDbCcLinkList(player);
    printf("\nThere are %d players.\n",length+1);
    for(i=0;i<=length;i++) {
        sortPlayerCard(player);
        player=player->pNext;
    }


}