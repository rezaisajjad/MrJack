void doMenu(enum Print_Menu_mode);
void doRound();
///////////////
void doMenu(enum Print_Menu_mode mode)
{
    CLS();
    Print_Menu(mode);
    char c;
    scanf(" %c", &c);
    CLS();
    switch (c)
    {
    case '1':
        if (mode == New)
        {
            GetDefultMapItems(ItemList);
            FirstHeroes = RandomHeroes();
            SecondHeroes = SecondList(FirstHeroes);
            MrJack = RandomMrJack();
        }
        break;
    case '2':
        doSaveLoadMenu(Save);
        doMenu(mode);
        break;
    case '3':
        doSaveLoadMenu(Load);
        Print_continue();
        doMenu(Continue);
        break;
    case '4':
        Print_Help();
        Print_continue();
        doMenu(mode);
        break;
    case '5':
        Print_NotMrJackList();
        Print_continue();
        doMenu(mode);
        break;
    case '6':
        exit(0);
        break;
    default:
        doMenu(mode);
        break;
    }
}
void doSaveLoadMenu(enum SaveLoad_enum mode)
{
    Print_SaveLoadMenu(mode);
    int c;
    scanf(" %d", &c);
    if (c >= 1 && c <= __SaveCounts__)
    {
        switch (mode)
        {
        case Save:
            SaveGame(c);
            break;
        case Load:
            LoadGame(c);
            break;
        }
    }
}
void doRound()
{
    int trn[2][4] = {{Police, Jack, Jack, Police}, {Jack, Police, Police, Jack}};
    char c;
    MapItem *Player;
    Hero *SelectedHero;

    for (char SetNum = 0; SetNum < 2; SetNum++)
    {
        for (char UnderSetNum = 0; UnderSetNum < 4; UnderSetNum++)
        {
        StartWhile:
            CLS();
            CheckSetColor(ItemList);
            print_Map(ItemList);
            Print_MapOptions(FirstHeroes, trn[SetNum][UnderSetNum], trn[SetNum][0]);
            scanf(" %c", &c);
            if (c == '+')
            {
                CLS();
                doMenu(Continue);
                goto StartWhile;
            }
            SelectedHero = FirstHeroes;
            for (int j = 1; j < c - 48; j++)
            {
                SelectedHero = SelectedHero->next;
            }
            Player = FindItemByHeroID(SelectedHero->HeroID, ItemList);
            doAction(Player, ItemList);
            if (UnderSetNum != 3)
            {
                FirstHeroes = DeleteHero(FirstHeroes, SelectedHero->HeroID);
            }
            else
            {
                FirstHeroes = SecondHeroes;
            }
        }
        AddNotMrJacks(Print_MrJackState(MrJack, ItemList));
    }
}