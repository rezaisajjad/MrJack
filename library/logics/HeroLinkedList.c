void AddHero(Hero *, int);
Hero *DeleteHero(Hero *, Item_enum);
Hero *SecondList(Hero *hero);
Hero *RandomHeroes();
Hero *RandomMrJack();
void ClearHeroList(Hero *);
void AddArrayToList(char *, int, Hero **);
void AddListToArray(char *, int, Hero *);
void FillArray(MapItem *, MapItem *);
////////////////
void AddHero(Hero *first, int ID)
{
    Hero *new = (Hero *)malloc(sizeof(Hero));
    new->HeroID = ID;
    new->next = NULL;

    Hero *i;
    for (i = first; i->next != NULL; i = i->next)
    {
    }
    i->next = new;
}
Hero *DeleteHero(Hero *first, Item_enum HeroID)
{
    if (first->HeroID == HeroID)
    {
        return first->next;
    }
    Hero *i;
    for (i = first; first->next != NULL && i->next->HeroID != HeroID; i = i->next)
    {
    }
    if (i->next->next != NULL)
    {
        Hero *hh = i->next;
        i->next = i->next->next;
        free(hh);
    }
    else
    {
        free(i->next);
        i->next = NULL;
    }
    return first;
}
Hero *SecondList(Hero *hero)
{
    Hero *h = hero, *tmp;
    for (int i = 0; i < 3; i++)
    {
        h = h->next;
    }
    tmp = h->next;
    h->next = NULL;

    return tmp;
}
Hero *RandomHeroes()
{
    srand(time(0));
    char HeroID[] = {0, 1, 2, 3, 4, 5, 6, 7};

    Hero *first = (Hero *)malloc(sizeof(Hero));
    first->next = NULL;
    char id = rand() % 8;
    first->HeroID = HeroID[id];
    HeroID[id] = -1;

    for (int i = 7; i > 0; i--)
    {
        id = rand() % i;
        while (HeroID[id] == -1)
        {
            id++;
        }
        AddHero(first, id);
        HeroID[id] = -1;
    }

    return first;
}
Hero *RandomMrJack()
{
    Hero *mrJack = (Hero *)malloc(sizeof(Hero));
    mrJack->next = NULL;
    mrJack->HeroID = rand() % 8;
    return mrJack;
}
void ClearHeroList(Hero *hero)
{
    Hero *tmp = hero;
    while (tmp != NULL)
    {
        tmp = hero->next;
        free(hero);
    }
}
void AddArrayToList(char *Array, int lenght, Hero **List)
{
    ClearHeroList(*List);
    for (int i = 0; i < lenght; i++)
    {
        if (Array[i] == -1)
        {
            break;
        }
        else if (i == 0)
        {
            *List = (Hero *)malloc(sizeof(Hero));
            (*List)->HeroID = Array[i];
            (*List)->next = NULL;
        }
        else
        {
            AddHero(*List, Array[i]);
        }
    }
}
void AddListToArray(char *Array, int lenght, Hero *List)
{
    for (int i = 0; i < lenght; i++)
    {
        if (List != NULL)
        {
            Array[i] = List->HeroID;
            List = List->next;
        }
        else
        {
            Array[i] = -1;
        }
    }
}
void FillArray(MapItem *Source, MapItem *Destination)
{
    for (int i = 0; i < __SignCount__; i++)
    {
        Destination[i] = Source[i];
    }
}
void AddNotMrJacks(Color_enum color)
{
    color = color == Yellow ? Purple : Yellow;
    MapItem *itm;
    Hero *tmp;
    for (int i = 0; i < 8; i++)
    {
    Start:
        itm = FindItemByHeroID(i, ItemList);
        if (itm != NULL && itm->color == color)
        {
            for (tmp = NotMrJack; tmp != NULL; tmp = tmp->next)
            {
                if (tmp->HeroID == itm->item)
                {
                    i++;
                    goto Start;
                }
            }
            if (NotMrJack->HeroID == -1)
            {
                NotMrJack->HeroID = i;
            }
            else
            {
                AddHero(NotMrJack, i);
            }
        }
    }
}