#define __MapPath__ "style\\Map_1.txt"
#define __Menu_ItemStyle_Path__ "style\\MenuItem.txt"
#define __Menu_OptionStyle_Path__ "style\\options.txt"
#define __Menu_SaveLoadStyle_Path__ "style\\SaveMenuItem.txt"
#define __Help_Path__ "dataes\\Help.txt"
////////////////
#define __EmptyLine_Start__ 1
#define __EmptyLine_End__ 1
#define __MenuItemCount__ 7
#define __MenuItem_1_1__ "New Game"
#define __MenuItem_1_2__ "Continue"
#define __MenuItem_3__ "Save"
#define __MenuItem_4__ "Load"
#define __MenuItem_5__ "Help"
#define __MenuItem_6__ "List"
#define __MenuItem_7__ "Exit"
////////////////
enum Print_Menu_mode
{
    New,
    Continue
};
enum Print_MapOptions_Turn
{
    Jack,
    Police
};
//////////////// Decelaration
void Print_Menu(enum Print_Menu_mode);
void Print_MapOptions(Hero *, enum Print_MapOptions_Turn, enum Print_MapOptions_Turn);
void print_Map(MapItem *);
void Print_SaveLoadMenu(enum SaveLoad_enum);
void Print_MrJack(Hero *);
void Print_NotMrJack(char);
void Print_continue();
int Print_MrJackState(Hero *, MapItem *);
void Print_NotMrJackList();
//////////////// Codes
void Print_Menu(enum Print_Menu_mode mode)
{
    char items[__MenuItemCount__][10] = {__MenuItem_1_1__, __MenuItem_1_2__, __MenuItem_3__,
                                         __MenuItem_4__, __MenuItem_5__, __MenuItem_6__, __MenuItem_7__};
    Print_Emptyline(__EmptyLine_Start__);
    FILE *f_menu = fopen(__Menu_ItemStyle_Path__, "r");
    char text;
    for (int i = 0; i < __MenuItemCount__; i++)
    {
        while (!feof(f_menu))
        {
            text = fgetc(f_menu);
            if (text == '*')
            {
                if (i == 0)
                {
                    printf("%s (%d)", items[mode], i + 1);
                    fseek(f_menu, strlen(items[mode]) + 3, SEEK_CUR);
                    i = 1;
                }
                else
                {
                    printf("%s (%d)", items[i], i);
                    fseek(f_menu, strlen(items[i]) + 3, SEEK_CUR);
                }
            }
            else
            {
                printf("%c", text);
            }
        }
        fseek(f_menu, 1, 0);
    }
    fclose(f_menu);
    Print_Emptyline(__EmptyLine_End__);
}
void Print_MapOptions(Hero *hero, enum Print_MapOptions_Turn Nowturn, enum Print_MapOptions_Turn Starterturn)
{
    Print_Emptyline(__EmptyLine_Start__);
    FILE *ff = fopen(__Menu_OptionStyle_Path__, "r");
    char text;
    char i = 0;
    while (!feof(ff))
    {
        text = fgetc(ff);
        if (text == '*' && hero != NULL)
        {
            i++;
            printf("%s (%d)", GetEnumName(hero->HeroID), i);
            fseek(ff, strlen(GetEnumName(hero->HeroID)) + 3, SEEK_CUR);
            hero = hero->next;
        }
        else if (text == '#')
        {
            char turntxt[][13] = {"turn: Jack", "turn: Police"};
            printf("%s", turntxt[Nowturn]);
            fseek(ff, strlen(turntxt[Nowturn]) - 1, SEEK_CUR);
        }
        else if (text == '@')
        {
            char TurnList[2][15] = {"J - P - P - J", "P - J - J - P"};
            printf("%s", TurnList[Starterturn]);
            fseek(ff, strlen(TurnList[Starterturn]) - 1, SEEK_CUR);
        }
        else
        {
            printf("%c", text);
        }
    }
    Print_Emptyline(__EmptyLine_End__);
}
void print_Map(MapItem MapItemList[])
{
    Print_Emptyline(__EmptyLine_Start__);
    FILE *f_map = fopen(__MapPath__, "r");
    char text;
    while (!feof(f_map))
    {
        text = fgetc(f_map);
        if (IsNumber(text))
        {
            char a = getc(f_map), b = getc(f_map);
            if (IsNumber(b))
            {
                a = CharToNumber(a);
                b = CharToNumber(b);
                a *= 10;
                a += b;
                a += 48;
            }
            MapItem *Item = FindItemByPosition(CharToNumber(text), a - 48, MapItemList);
            if (Item == NULL)
            {
                printf("  ");
            }
            else
            {
                SetColor(Item->color);
                printf("%s%s", GetEnumName(Item->item), Color_Off);
            }
            printf(" ");
        }
        else
        {
            printf("%c", text);
        }
    }
    fclose(f_map);
    Print_Emptyline(__EmptyLine_End__);
}
void Print_SaveLoadMenu(enum SaveLoad_enum mode)
{
    Print_Emptyline(__EmptyLine_Start__);
    FILE *f_menu = fopen(__Menu_SaveLoadStyle_Path__, "r");
    char text;
    char menutext[2][5] = {"Save", "Load"};
    for (int i = 0; i < __SaveCounts__; i++)
    {
        while (!feof(f_menu))
        {
            text = fgetc(f_menu);
            if (text == '*')
            {
                printf("%s (%d)", menutext[mode], i + 1);
                fseek(f_menu, strlen(menutext[mode]) + 3, SEEK_CUR);
            }
            else
            {
                printf("%c", text);
            }
        }
        fseek(f_menu, 1, 0);
    }
    fclose(f_menu);
    Print_Emptyline(__EmptyLine_End__);
}
void Print_MrJack(Hero *hero)
{
    printf("\tMr Jack is ( %s )\n\n", GetEnumName(hero->HeroID));
    Print_continue();
}
void Print_NotMrJack(char id)
{
    printf("\tMr Jack is'nt ( %s )\n\n", GetEnumName(id));
    Print_continue();
}
void Print_Help()
{
    char c;
    Print_Emptyline(__EmptyLine_Start__);
    FILE *ff = fopen(__Help_Path__, "r");
    c = getc(ff);
    while (!feof(ff))
    {
        switch (c)
        {
        case '!':
            printf("%s", Color_Yellow);
            break;
        case '~':
            printf("%s", Color_Purple);
            break;
        case '$':
            printf("%s", Color_Off);
            break;
        default:
            printf("%c", c);
            break;
        }
        c = getc(ff);
    }
    fclose(ff);
    Print_Emptyline(__EmptyLine_End__);
}
void Print_continue()
{
    char a;
    printf("\tDo you want to continue ???    press 1\n\n\t");
    scanf(" %c", &a);
}
int Print_MrJackState(Hero *mrJack, MapItem *List)
{
    CheckSetColor(List);
    if (FindItemByHeroID(mrJack->HeroID, List)->color == Yellow)
    {
        printf("\tMr Jack is yellow !!!\n\n\t");
        Print_continue();
        return Yellow;
    }
    else
    {
        printf("\tMr Jack is purple\n\n\t");
        Print_continue();
        return Purple;
    }
}
void Print_NotMrJackList()
{
    Hero *hr = NotMrJack;
    for (; hr != NULL; hr = hr->next)
    {
        printf("\t%s\n\n", GetEnumName(hr->HeroID));
    }
}
