#define __SignCount__ 66
#define __SaveCounts__ 5
///////////// Color Defines
#define Color_Black "\033[0;30m"
#define Color_Red "\033[0;31m"
#define Color_Green "\033[0;32m"
#define Color_Yellow "\033[0;33m"
#define Color_Blue "\033[0;34m"
#define Color_Purple "\033[0;35m"
#define Color_Cyan "\033[0;36m"
#define Color_White "\033[0;37m"
#define Color_Off "\033[0m"
/////////////
void Alarm(int a, int b, int c)
{
    printf("\033[0;31m\nCode::\033[0;36m %d \033[0;31m::\033[0;36m %d \033[0;31m::\033[0;36m %d\n\033[0m", a, b, c);
}
struct Location_str
{
    int i;
    int j;
};
typedef struct Location_str Location_str;
enum Item_enum
{
    WG,
    JS,
    JB,
    SG,
    IL,
    JW,
    SH,
    MS,
    Tunnel,
    Home,
    CloseDoor,
    LightOn,
    LightOff,
    CloseTunnel,
    Door
};
typedef enum Item_enum Item_enum;
enum Color_enum
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Purple,
    Cyan,
    White,
    Off = -1
};
typedef enum Color_enum Color_enum;
struct MapItem
{
    Location_str location;
    Item_enum item;
    Color_enum color;
};
typedef struct MapItem MapItem;
enum SaveLoad_enum
{
    Save,
    Load
};
typedef enum SaveLoad_enum SaveLoad_enum;
struct Hero
{
    struct Hero *next;
    Item_enum HeroID;
};
typedef struct Hero Hero;

struct SaveLoad_str
{
    MapItem List[__SignCount__];
    char FirstHeroes[4];
    char SecondHeroes[4];
    char NotMrJack[8];
    char MrJack;
    int Round;
    char JW_orientation;
    char SetNum;
    char UnderSetNum;
};
typedef struct SaveLoad_str FilePack;

char *GetEnumName(char code)
{
    char *name = (char *)(3 * sizeof(char));
    name = "  ";
    switch (code)
    {
    case 0:
        name = "WG";
        break;
    case 1:
        name = "JS";
        break;
    case 2:
        name = "JB";
        break;
    case 3:
        name = "SG";
        break;
    case 4:
        name = "IL";
        break;
    case 5:
        name = "JW";
        break;
    case 6:
        name = "SH";
        break;
    case 7:
        name = "MS";
        break;
    case 8:
        name = "()";
        break;
    case 9:
        name = "##";
        break;
    case 10:
        name = "XX";
        break;
    case 11:
        name = "ON";
        break;
    case 12:
        name = "OF";
        break;
    case 13:
        name = ")(";
        break;
    case 14:
        name = "[]";
        break;
    }
    return name;
}
void SetColor(Color_enum code)
{
    switch (code)
    {
    case 0:
        printf("%s", Color_Black);
        break;
    case 1:
        printf("%s", Color_Red);
        break;
    case 2:
        printf("%s", Color_Green);
        break;
    case 3:
        printf("%s", Color_Yellow);
        break;
    case 4:
        printf("%s", Color_Blue);
        break;
    case 5:
        printf("%s", Color_Purple);
        break;
    case 6:
        printf("%s", Color_Cyan);
        break;
    case 7:
        printf("%s", Color_White);
        break;
    case 8:
        printf("%s", Color_Off);
        break;
    }
}