int IsNumber(char);
int CharToNumber(char);
void Print_Emptyline(int);
MapItem *FindItemByPosition(int, int, MapItem *);
int IsTunnelByPosition(int, int, MapItem *);
MapItem *FindItemByHeroID(int, MapItem *);
void CheckSetColor(MapItem *);
void LineOfLight(int *, char, int);
void CLS(void);
////////////////
int IsNumber(char c)
{
    if (c >= 48 && c <= 57)
        return 1;
    return 0;
}
int CharToNumber(char c)
{
    if (IsNumber(c))
    {
        return c - 48;
    }
    else
    {
        return -1;
    }
}
void Print_Emptyline(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n");
    }
}
MapItem *FindItemByPosition(int i, int j, MapItem MapItemList[])
{
    for (int k = 0; k < __SignCount__; k++)
    {
        if (MapItemList[k].location.i == i && MapItemList[k].location.j == j)
        {
            return &MapItemList[k];
        }
    }
    return NULL;
}
int IsTunnelByPosition(int i, int j, MapItem MapItemList[])
{
    for (int k = 0; k < __SignCount__; k++)
    {
        if (MapItemList[k].location.i == i && MapItemList[k].location.j == j && MapItemList[k].item == Tunnel)
        {
            return 1;
        }
    }
    return 0;
}
MapItem *FindItemByHeroID(int id, MapItem MapItemList[])
{
    for (int k = 0; k < __SignCount__; k++)
    {
        if (MapItemList[k].item == id)
        {
            return &MapItemList[k];
        }
    }
    return NULL;
}
void LineOfLight(int Moves[2], char c, int PosJ)
{
    switch (c)
    {
    case '1':
        if (PosJ % 2 == 0)
        {
            Moves[0] = 0;
            Moves[1] = -1;
        }
        else
        {
            Moves[0] = 1;
            Moves[1] = -1;
        }
        break;
    case '2':
        Moves[0] = 1;
        Moves[1] = 0;
        break;
    case '3':
        if (PosJ % 2 == 0)
        {
            Moves[0] = 0;
            Moves[1] = 1;
        }
        else
        {
            Moves[0] = 1;
            Moves[1] = 1;
        }
        break;
    case '7':
        if (PosJ % 2 == 0)
        {
            Moves[0] = -1;
            Moves[1] = -1;
        }
        else
        {
            Moves[0] = 0;
            Moves[1] = -1;
        }
        break;
    case '8':
        Moves[0] = -1;
        Moves[1] = 0;
        break;
    case '9':
        if (PosJ % 2 == 0)
        {
            Moves[0] = -1;
            Moves[1] = 1;
        }
        else
        {
            Moves[0] = 0;
            Moves[1] = 1;
        }
        break;
    }
}
void CheckSetColor(MapItem MapItemList[])
{
    for (int i = 0; i < __SignCount__; i++)
    {
        if (MapItemList[i].item == 12)
        {
            MapItemList[i].color = Off;
        }
        else if (MapItemList[i].item == 11)
        {
            MapItemList[i].color = Yellow;
        }
        else if (MapItemList[i].item >= 0 && MapItemList[i].item <= 7)
        {
            MapItemList[i].color = Purple;
            int chekes[6][2] = {{-1, 0}, {+1, 0}, {0, +1}, {0, -1}, {-1, 1}, {-1, -1}};
            if (MapItemList[i].location.j % 2 == 1)
            {
                chekes[4][0] = chekes[5][0] = 1;
            }
            MapItem *tmp;
            for (int j = 0; j < 6; j++)
            {
                tmp = FindItemByPosition(MapItemList[i].location.i + chekes[j][0],
                                         MapItemList[i].location.j + chekes[j][1],
                                         MapItemList);
                if (tmp != NULL)
                {
                    if (tmp->item == LightOn || (tmp->item <= 7 && tmp >= 0))
                    {
                        MapItemList[i].color = Yellow;
                    }
                }
            }
        }
    }
    MapItem *itm = FindItemByHeroID(JW, MapItemList);
    int next[2] = {0};
    int Nowpos[2] = {itm->location.i, itm->location.j};
    while (Nowpos[0] >= 1 && Nowpos[1] >= 1 && Nowpos[1] <= 13)
    {
        if (JW_orientation != '1' && JW_orientation != '2' && JW_orientation != '3' &&
            JW_orientation != '7' && JW_orientation != '8' && JW_orientation != '9')
        {
            break;
        }
        if (itm != NULL && itm->item == Home)
        {
            break;
        }
        if (Nowpos[0] % 2 == 1 && Nowpos[0] > 8)
        {
            break;
        }
        if (Nowpos[0] > 9)
        {
            break;
        }
        if (itm != NULL && itm->item >= 0 && itm->item <= 7 && itm->item != 5)
        {
            itm->color = Yellow;
        }
        LineOfLight(next, JW_orientation, Nowpos[1]);
        Nowpos[0] += next[0];
        Nowpos[1] += next[1];
        itm = FindItemByPosition(Nowpos[0], Nowpos[1], MapItemList);
    }
}
void CLS(void)
{
    system("cls");
}