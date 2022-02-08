void AddNextMoveToList(int Moves[4][2], char count, char c, MapItem *HeroItem)
{
    switch (c)
    {
    case '1':
        if (HeroItem->location.j % 2 == 0)
        {
            Moves[count][0] = 0;
            Moves[count][1] = -1;
        }
        else
        {
            Moves[count][0] = 1;
            Moves[count][1] = -1;
        }
        break;
    case '2':
        Moves[count][0] = 1;
        Moves[count][1] = 0;
        break;
    case '3':
        if (HeroItem->location.j % 2 == 0)
        {
            Moves[count][0] = 0;
            Moves[count][1] = 1;
        }
        else
        {
            Moves[count][0] = 1;
            Moves[count][1] = 1;
        }
        break;
    case '7':
        if (HeroItem->location.j % 2 == 0)
        {
            Moves[count][0] = -1;
            Moves[count][1] = -1;
        }
        else
        {
            Moves[count][0] = 0;
            Moves[count][1] = -1;
        }
        break;
    case '8':
        Moves[count][0] = -1;
        Moves[count][1] = 0;
        break;
    case '9':
        if (HeroItem->location.j % 2 == 0)
        {
            Moves[count][0] = -1;
            Moves[count][1] = 1;
        }
        else
        {
            Moves[count][0] = 0;
            Moves[count][1] = 1;
        }
        break;
    }
}
void Move(int Moves[4][2], char count, MapItem *HeroItem)
{
    HeroItem->location.i += Moves[count][0];
    HeroItem->location.j += Moves[count][1];
}
int NewPlaceIsAvailable(int Moves[4][2], char count, MapItem *HeroItem, MapItem **NewPlaceCharector, MapItem *List)
{
    if (HeroItem->item == MS)
    {
        MapItem *tmpNewPlace = FindItemByPosition(HeroItem->location.i + Moves[count][0], HeroItem->location.j + Moves[count][1], List);
        *NewPlaceCharector = tmpNewPlace;
        return 1;
    }

    if ((HeroItem->location.j + Moves[count][0] % 2 == 0 && HeroItem->location.i + Moves[count][0] > 9) ||
        (HeroItem->location.j + Moves[count][0] % 2 == 1 && HeroItem->location.i + Moves[count][0] > 8) ||
        HeroItem->location.j + Moves[count][1] < 1 ||
        HeroItem->location.j + Moves[count][1] > 13 ||
        HeroItem->location.i + Moves[count][0] < 1)
    {
        printf("\n%sYou Can't move%s\nSelect Another Direction\n", Color_Red, Color_Off);
        return 0;
    }
    MapItem *tmpNewPlace = FindItemByPosition(HeroItem->location.i + Moves[count][0], HeroItem->location.j + Moves[count][1], List);
    if (tmpNewPlace != NULL)
    {
        if (tmpNewPlace->item >= 9 && tmpNewPlace->item <= 13)
        {
            printf("\n%sYou Can't move%s\nSelect Another Direction\n", Color_Red, Color_Off);
            return 0;
        }
    }
    *NewPlaceCharector = tmpNewPlace;
    return 1;
}
int CheckEnterTunnel(MapItem *List, int Moves[4][2], MapItem *HeroItem, char count, char MaxCount, MapItem **NewPlaceCharector)
{
    int c1, c2;
    if (NewPlaceCharector != NULL && *NewPlaceCharector != NULL && (*NewPlaceCharector)->item == 8 && count + 1 < MaxCount)
    {
        printf("Do you Want To Enter Tunnel ??? Yes(1) No(2)\n");
        scanf(" %c", &c1);
        if (c1 == '1')
        {
            MapItem *NextTunnel;
            do
            {
                printf("Please Send Location Tunnel: ");
                scanf(" %d %d", &c1, &c2);
                NextTunnel = FindItemByPosition(c1, c2, List);
            } while (!(NextTunnel != NULL && NextTunnel->item == 8));
            Moves[count][0] = c1 - HeroItem->location.i;
            Moves[count][1] = c2 - HeroItem->location.j;
            *NewPlaceCharector = NextTunnel;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
void GetDirection(char *c)
{
    printf("Direction= ");
    scanf(" %c", c);
}
int CheckIsEnd(char c, int Moves[4][2])
{
    if (c == '0')
    {
        if (Moves[0][0] == 0 && Moves[0][1] == 0)
        {
            printf("\n%sYou Must Move at least 1 time%s\nSelect Direction\n", Color_Red, Color_Off);
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 2;
}
void HeroMover(MapItem *HeroItem, MapItem *List, int IsSpell)
{
    /// Set Max movement /// List of Moves /// Move Counts
    int MaxCount = 3, Moves[4][2] = {0}, count = 0;
    MaxCount = HeroItem->item == MS ? MaxCount + 1 : MaxCount;
    /// temp character
    char c = 0;
    /// Charector of New Place
    MapItem *NewPlaceCharector = NULL;
    /// Start Moving
    if (IsSpell)
    {
        MaxCount = 1;
    }

    for (count = 0; count < MaxCount; count++)
    {
    StartWhile0:
        CLS();
        CheckSetColor(List);
        print_Map(List);
        printf("\n%sYou Choosed: %s%s\t", Color_Green, GetEnumName(HeroItem->item), Color_Off);
    StartWhile1:
        if (CheckEnterTunnel(List, Moves, HeroItem, count, MaxCount, &NewPlaceCharector))
        {
            Move(Moves, count, HeroItem);
            count++;
            goto StartWhile0;
        }
        /// GetDirection
        GetDirection(&c);
        /// CheckEnd
        while (CheckIsEnd(c, Moves) == 0)
        {
            GetDirection(&c);
        }
        if (CheckIsEnd(c, Moves) == 1)
        {
            break;
        }
        /// Add Next Move
        AddNextMoveToList(Moves, count, c, HeroItem);
        /// Check Availability
        if (!NewPlaceIsAvailable(Moves, count, HeroItem, &NewPlaceCharector, List))
        {
            goto StartWhile1;
        }
        /// Move
        Move(Moves, count, HeroItem);
    }
    if (NewPlaceCharector != NULL)
    {
        if (NewPlaceCharector->item == Door)
        {
            system("cls");
            if (HeroItem->item != MrJack->HeroID)
            {
                printf("\n\n\t\tPolice Win ! ! ! ! !\n\n");
            }
            else
            {
                printf("\n\n\t\tMrJack Win ! ! ! ! !\n\n");
            }
            exit(0);
        }

        if (NewPlaceCharector->item >= 0 && NewPlaceCharector->item <= 7)
        {
            printf("do you want to arrest MrJack??? Yes(1) No(2)");
            scanf(" %c", &c);
            if (c == '1')
            {
                system("cls");
                if ((MrJack)->HeroID == NewPlaceCharector->item)
                {
                    printf("\n\n\t\tPolice Win ! ! ! ! !\n\n");
                }
                else
                {
                    printf("\n\n\t\tMrJack Win ! ! ! ! !\n\n");
                }
                exit(0);
            }
        }
        while (NewPlaceCharector != NULL && count > 0)
        {
            count--;
            NewPlaceCharector = FindItemByPosition(HeroItem->location.i -= Moves[count][0], HeroItem->location.j -= Moves[count][1], List);
            HeroItem->location.i -= Moves[count][0];
            Moves[count][0] = 0;
            HeroItem->location.j -= Moves[count][1];
            Moves[count][1] = 0;
        }
        goto StartWhile0;
    }
}
