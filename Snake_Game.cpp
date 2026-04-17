#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>

#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

using namespace std;

// Hàm di chuyển con trỏ
void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

// Cấu trúc điểm
struct Point
{
    int x, y;
};

// Lớp con rắn
class CONRAN
{
public:
    Point A[100];
    int DoDai;

    CONRAN()
    {
        DoDai = 3;

        // Đầu rắn nằm bên phải để đi sang phải không bị cắn thân
        A[0].x = 12;
        A[0].y = 10;

        A[1].x = 11;
        A[1].y = 10;

        A[2].x = 10;
        A[2].y = 10;
    }

    void Ve(Point Qua)
    {
        for (int i = 0; i < DoDai; i++)
        {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }

        gotoxy(Qua.x, Qua.y);
        cout << "*";
    }

    void GameOver()
    {
        gotoxy(40, 10);
        cout << "GAME OVER";
        Sleep(2000);
        exit(0);
    }

    void DiChuyen(int Huong, Point& Qua)
    {
        // Dời thân rắn
        for (int i = DoDai; i > 0; i--)
        {
            A[i] = A[i - 1];
        }

        // Di chuyển đầu
        if (Huong == 0) A[0].x++;   // phải
        if (Huong == 1) A[0].y++;   // xuống
        if (Huong == 2) A[0].x--;   // trái
        if (Huong == 3) A[0].y--;   // lên

        // Kiểm tra đụng tường
        if (A[0].x <= MINX || A[0].x >= MAXX ||
                A[0].y <= MINY || A[0].y >= MAXY)
        {
            GameOver();
        }

        // Kiểm tra cắn vào thân
        for (int i = 1; i < DoDai; i++)
        {
            if (A[0].x == A[i].x && A[0].y == A[i].y)
            {
                GameOver();
            }
        }

        // Ăn quả
        if (A[0].x == Qua.x && A[0].y == Qua.y)
        {
            A[DoDai] = A[DoDai - 1];
            DoDai++;

            Qua.x = rand() % (MAXX - MINX - 1) + MINX + 1;
            Qua.y = rand() % (MAXY - MINY - 1) + MINY + 1;
        }
    }
};

// Vẽ khung
void VeKhung()
{
// Cạnh trên và cạnh dưới
    for (int i = MINX; i <= MAXX; i++)
    {
        gotoxy(i, MINY);
        cout << char(219);
        gotoxy(i, MAXY);
        cout << char(219);
    }
// Cạnh trái và cạnh phải
    for (int j = MINY; j <= MAXY; j++)
    {
        gotoxy(MINX, j);
        cout << char(219);
        gotoxy(MAXX, j);
        cout << char(219);
    }
}

// Hàm chính
int main()
{
    CONRAN r;
    int Huong = 0; // mặc định đi sang phải
    char t;
    Point Qua;

    srand(time(0));

    Qua.x = rand() % (MAXX - MINX - 1) + MINX + 1;
    Qua.y = rand() % (MAXY - MINY - 1) + MINY + 1;

    while (1)
    {
        if (kbhit())
        {
            t = getch();

            // Chống quay đầu
            if (t == 'a' && Huong != 0) Huong = 2;
            if (t == 'w' && Huong != 1) Huong = 3;
            if (t == 'd' && Huong != 2) Huong = 0;
            if (t == 's' && Huong != 3) Huong = 1;
        }

        system("cls");

        VeKhung();

        // Di chuyển trước, vẽ sau
        r.DiChuyen(Huong, Qua);
        r.Ve(Qua);

        Sleep(300);
    }

    return 0;
}

