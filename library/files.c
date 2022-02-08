#define __Map_ItemList_Path__ "dataes\\MapItemList_1.txt"
#define __Save_Path__ "dataes\\Save.gs"
////////////////
void GetDefultMapItems(MapItem *List);
void LoadGame(int id);
void SaveGame(int id);
////////////////
void GetDefultMapItems(MapItem *List)
{
    FILE *f_ItemList = fopen(__Map_ItemList_Path__, "r");
    for (int i = 0; i < __SignCount__ && !feof(f_ItemList); i++)
    {
        fscanf(f_ItemList, " %d %d %d %d", &List[i].location.i, &List[i].location.j,
               &List[i].item, &List[i].color);
    }
    fclose(f_ItemList);
}
void LoadGame(int id)
{
    FILE *ff = fopen(__Save_Path__, "rb");
    if (ff == NULL)
    {
        printf("Error");
        Print_continue();
    }
    FilePack file;
    fseek(ff, sizeof(FilePack) * 5 * (id - 1), SEEK_SET);
    fread(&file, sizeof(FilePack), 1, ff);
    AddArrayToList(file.FirstHeroes, 4, &FirstHeroes);
    AddArrayToList(file.SecondHeroes, 4, &SecondHeroes);
    AddArrayToList(file.NotMrJack, 4, &NotMrJack);
    FillArray(file.List, ItemList);
    if (MrJack == NULL)
    {
        MrJack = (Hero *)malloc(sizeof(Hero));
    }
    MrJack->HeroID = file.MrJack;
    MrJack->next = NULL;
    Round = file.Round;
    JW_orientation = file.JW_orientation;
    SetNum = file.SetNum;
    UnderSetNum = file.UnderSetNum;
    fclose(ff);
}
void SaveGame(int id)
{
    FILE *ff = fopen(__Save_Path__, "rb+");
    if (ff == NULL)
    {
        printf("Error");
        Print_continue();
    }
    fseek(ff, sizeof(FilePack) * 5 * (id - 1), SEEK_SET);
    FilePack file;

    AddListToArray(file.FirstHeroes, 4, FirstHeroes);
    AddListToArray(file.SecondHeroes, 4, SecondHeroes);
    AddListToArray(file.NotMrJack, 4, NotMrJack);
    FillArray(ItemList, file.List);
    file.MrJack = MrJack != NULL ? MrJack->HeroID : 0;
    file.Round = Round;
    file.JW_orientation = JW_orientation;
    file.SetNum = SetNum;
    file.UnderSetNum = UnderSetNum;
    fwrite(&file, sizeof(FilePack), 1, ff);
    fclose(ff);
}
