void HeroSpell(MapItem *, MapItem *);
void doAction(MapItem *, MapItem *);
////////////////////
void HeroSpell(MapItem *HeroItem, MapItem *List)
{
    char c;
    system("cls");
    CheckSetColor(List);
    print_Map(List);
    printf("\n%sYou Choosed: %s%s\t", Color_Green, GetEnumName(HeroItem->item), Color_Off);
    switch (HeroItem->item)
    {
    case WG:
    {
        int A, B;
    Start_WG:
        printf("who do you want to swich with???\t");
        scanf(" %d %d", &A, &B);
        MapItem *swich;
        swich = FindItemByPosition(A, B, List);
        if (swich != NULL)
        {
            if (swich->item >= 0 && swich->item <= 7)
            {
                int tmp = swich->item;
                swich->item = HeroItem->item;
                HeroItem->item = tmp;
            }
            else
            {
                printf("ERROR ! ! !");
                goto Start_WG;
            }
        }
        else
        {
            printf("ERROR ! ! !");
            goto Start_WG;
        }
        break;
    }
    case JS:
    {
        int A, B, C, D;
    Start_JS:
        printf("which light do you want to turn off???\t");
        scanf(" %d %d", &A, &B);
        printf("which light do you want to turn on???\t");
        scanf(" %d %d", &C, &D);
        MapItem *OFF, *ON;
        ON = FindItemByPosition(A, B, List);
        OFF = FindItemByPosition(C, D, List);
        if (ON != NULL && OFF != NULL)
        {
            if (ON->item == 11 && OFF->item == 12)
            {
                ON->item = 12;
                OFF->item = 11;
            }
            else
            {
                printf("ERROR ! ! !");
                goto Start_JS;
            }
        }
        else
        {
            printf("ERROR ! ! !");
            goto Start_JS;
        }
        break;
    }
    case JB:
    {
        int A, B, C, D;
    Start_JB:
        printf("which tunnel do you want to close???\t");
        scanf(" %d %d", &A, &B);
        printf("which tunnel do you want to open???\t");
        scanf(" %d %d", &C, &D);
        MapItem *OFF, *ON;
        ON = FindItemByPosition(A, B, List);
        OFF = FindItemByPosition(C, D, List);
        if (ON != NULL && OFF != NULL)
        {
            if (ON->item == 8 && OFF->item == 13)
            {
                ON->item = 13;
                OFF->item = 8;
            }
            else
            {
                printf("ERROR ! ! !");
                goto Start_JB;
            }
        }
        else
        {
            printf("ERROR ! ! !");
            goto Start_JB;
        }
        break;
    }
    case SG:
    {
        int A, B;
        for (int i = 0; i < 3; i++)
        {
        StartSG:
            printf("\nWho do you want to move???\t\n");
            scanf(" %d %d", &A, &B);
            MapItem *hero = FindItemByPosition(A, B, ItemList);
            if (hero != NULL && hero->item < 8 && hero->item >= 0)
            {
                HeroMover(hero, ItemList, 1);
                CLS();
                CheckSetColor(ItemList);
                print_Map(ItemList);
            }
            else
            {
                goto StartSG;
            }
        }
        break;
    }
    case IL:
    {
        int A, B, C, D;
    Start_IL:
        printf("which door do you want to close???\t");
        scanf(" %d %d", &A, &B);
        printf("which door do you want to open???\t");
        scanf(" %d %d", &C, &D);
        MapItem *OFF, *ON;
        ON = FindItemByPosition(A, B, List);
        OFF = FindItemByPosition(C, D, List);
        if (ON != NULL && OFF != NULL)
        {
            if (ON->item == 14 && OFF->item == 10)
            {
                ON->item = 10;
                OFF->item = 14;
            }
            else
            {
                printf("ERROR ! ! !");
                goto Start_IL;
            }
        }
        else
        {
            printf("ERROR ! ! !");
            goto Start_IL;
        }
        break;
    }
    case JW:
    {
        printf("Enter JW Orientation");
        scanf(" %c", &JW_orientation);
        break;
    }
    case SH:
    {
        if (NotMrJack->HeroID != -1)
        {
            Hero *i;
            int list[8] = {0};
            list[MrJack->HeroID] = -1;
            for (i = NotMrJack; i != NULL; i = i->next)
            {
                list[i->HeroID] = -1;
            }
            for (int j = 0; j < 8; j++)
            {
                if (list[j] != -1)
                {
                    AddHero(NotMrJack, j);
                    Print_NotMrJack(j);
                    break;
                }
            }
        }
        else
        {
            NotMrJack->HeroID = MrJack->HeroID == 0 ? 1 : 0;
            Print_NotMrJack(NotMrJack->HeroID);
        }
        break;
    }
    }
}
void doAction(MapItem *HeroItem, MapItem *List)
{
    char c = '\0';
    if (HeroItem->item == JS || HeroItem->item == SG || HeroItem->item == WG || HeroItem->item == JB)
    {
        printf("Please Select Next Action: %sMove(1) %s, %sUseSpell(2)%s   ", Color_Red, Color_Off, Color_Red, Color_Off);
        scanf(" %c", &c);
    }
    if (c == '2')
    {
        if (HeroItem->item == WG)
        {
            HeroSpell(HeroItem, List);
            return;
        }
        HeroSpell(HeroItem, List);
        HeroMover(HeroItem, List, 0);
    }
    else
    {
        if (HeroItem->item == WG)
        {
            HeroMover(HeroItem, List, 0);
            return;
        }
        HeroMover(HeroItem, List, 0);
        HeroSpell(HeroItem, List);
    }
}