#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
////////////////
#include "library\consts.h"
////////////////
Hero *MrJack = NULL;
char JW_orientation = 0;
Hero *NotMrJack = NULL;
Hero *FirstHeroes = NULL;
Hero *SecondHeroes = NULL;
MapItem *ItemList = NULL;
int Round = 1;
char SetNum;
char UnderSetNum;
////////////////
#include "library\tools.c"
#include "library\print.c"
#include "library\files.c"
#include "library\logics\HeroLinkedList.c"
#include "library\logics\Action.c"
////////////////
#include "library\logics\logic.c"
#include "library\logics\Move.c"
////////////////
int main()
{
    ItemList = (MapItem *)malloc(sizeof(MapItem) * __SignCount__);
    NotMrJack = (Hero *)(malloc(sizeof(Hero)));
    NotMrJack->HeroID = -1;
    NotMrJack->next = NULL;

    doMenu(New);
    Print_MrJack(MrJack);

    for (Round; Round <= 4; Round++)
    {
        doRound();
        FirstHeroes = RandomHeroes();
        SecondHeroes = SecondList(FirstHeroes);
    }

    printf("\n\n\t\tMrJack Win ! ! ! ! !\n\n");
    Print_continue();

    return 0;
}