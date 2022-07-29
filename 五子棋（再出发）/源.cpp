#include <iostream>
using namespace std;
#include <Windows.h>
#include <graphics.h>// 图形库
#include <mmsystem.h>	// 背景音乐
#include<stdlib.h>
#include <time.h>
#include <conio.h> 
#include <cstdio>
#pragma comment(lib,"winmm.lib")



#define PLATE_X	 50				//////
#define PLATE_Y  50				/////	棋盘的矩形的坐标值
#define	OFFSET   50	// 每个棋盘空格相隔50像素
int a[15][15] = {0};
int Player_Black = 0;
int Player_White = 1;
int Time_num = 30;
int num = 1;

void gameInterface();
void MouseHit1();
void music();
void PlayChess();
void Playershow();
void PlayGame();
void Overhit();
void ifVictory();
int time(int LK);
void deleteHints(int a, int b);



// 游戏选手
typedef struct PLAYER {
	int white;
	int black;
};
PLAYER player;	// 用于左上角提示选手下棋

// frame of reference 坐标
typedef struct FOR {
	int x;
	int y;
};
FOR fofr;	// 用于更新数组

// 鼠标坐标
typedef struct MOUSES {
	int x;
	int y;
};
MOUSES mouses;	// 用于下棋




//掷骰子
int rollDice()
{
	int dice = 1 + rand() % 6;
	return dice;
}
//显示点数
void Jieguo()
{
	initgraph(1080, 720);
	// 将图片应用于界面中
	loadimage(0, _T("begin-1.jpg"));
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);
	outtextxy(280, 250, _T("请裁判输入一个随机数："));
	outtextxy(280, 300, _T("白棋选手的点数为："));
	outtextxy(280, 350, _T("黑棋选手的点数为："));
	char T1[20]; char T2[20]; char T3[20];
	unsigned seed;
	cin >> seed;
	sprintf(T1, " % 2d", seed);
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);
	outtextxy(745, 255, T1);
	srand(seed);
	int B, W;
	B = rollDice();
	W = rollDice();
	sprintf(T2, "%2d", B);
	sprintf(T3, "%2d", W);
	outtextxy(665, 305, T3);
	outtextxy(665, 355, T2);
	
	
	//确定谁先走
	settextcolor(RGB(255, 0, 0));
	settextstyle(120, 0, _T("黑体"));
	setbkmode(TRANSPARENT);
	if (B > W)
	{
		outtextxy(110,100,_T("黑棋选手先下棋！"));
		Player_Black = 1;
		Player_White = 0;
		Sleep(2000);
		
	}
	else if (B < W)
	{
		outtextxy(110, 100, _T("白棋选手先下棋！"));
		Player_Black = 0;
		Player_White = 1;
		Sleep(2000);
		
	}
	else
	{
		settextcolor(RGB(255, 0, 0));
		settextstyle(80, 0, _T("黑体"));
		setbkmode(TRANSPARENT);
		outtextxy(150, 100, _T("点数相同，请重新输入！"));
		Sleep(2000);
		Jieguo();
	}
	closegraph();
	gameInterface();
}



//欢迎界面
void initgraphGam() 
{
	music();
	initgraph(1080, 720);
	// 将图片应用于界面中
	loadimage(0, _T("begin-1.jpg"));
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 5);

	// 画一个空心矩形
	rectangle(355, 405, 730, 535);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(120, 0, _T("微软雅黑"));
	// 设置字体的背景颜色为透明
	setbkmode(TRANSPARENT);

	// 写字
	outtextxy(144, 190, _T("欢迎进入五子棋游戏"));

	// 设置字体颜色
	settextcolor(RGB(255, 200, 88));

	// 写字
	outtextxy(360, 410, _T("开始游戏"));
	while (1) 
	{
		ExMessage mouse;
		mouse = getmessage(EM_MOUSE);
		if (mouse.message == WM_LBUTTONDOWN)
			if ((mouse.x > 355 && mouse.x < 730) && (mouse.y > 405 && mouse.y < 535))
			{
				break;
			}
	}
	closegraph();
	Jieguo();
}

//清除提示
void deleteHints()
{
	IMAGE image;
	loadimage(&image, _T("cheng1.jpg"));
	putimage(781, 51, &image);
}
void deleteHints(int a ,int b)
{
	IMAGE image;
	loadimage(&image, _T("捕获.PNG"));
	putimage(a, b, &image);
}

//绘制棋盘
void CreateBoard()
{
	int i;
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);
	for (i = 0; i<15; i++)
	{
		line(PLATE_X, PLATE_Y + i * OFFSET, PLATE_X + 14 * OFFSET, PLATE_Y + i * OFFSET);
		line(PLATE_X + i * OFFSET, PLATE_Y, PLATE_X + i * OFFSET, PLATE_Y + 14 * OFFSET);
	}
}



//开始游戏  结束游戏  悔棋标志
void gameButton()
{
	//设置画笔粗细
	setlinestyle(PS_SOLID, 2);
	//设置字体颜色
	settextcolor(RGB(0, 0, 0));
	//设置字体
	settextstyle(25, 0, _T("微软雅黑"));
    //设置外框
	rectangle(780, 200, 870, 250);
	rectangle(780, 270, 870, 320);
	rectangle(780, 340, 870, 390);
	rectangle(780, 410, 870, 460);
	rectangle(780, 480, 870, 530);
	rectangle(780, 550, 870, 600);
	rectangle(780, 50, 870, 170);
	//写字
	outtextxy(787, 210, _T("开始游戏"));
	outtextxy(787, 280, _T("结束游戏"));
	outtextxy(787, 350, _T("音乐开关"));
	outtextxy(787, 420, _T("重新开始"));
	outtextxy(805, 490, _T("悔棋"));
	outtextxy(787, 560, _T("时间："));
	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, _T("黑体"));
	outtextxy(796, 80, _T("请点击"));
	outtextxy(787, 110, _T("开始游戏"));
	MouseHit1();
}



//音乐开关
void music() {
	mciSendString("play 高山流水.mp3 repeat", 0, 0, 0);
}

// 背景音乐标识
bool gameMusicFlag = true;

// 游戏背景音乐开关
void musicFlag() {
	if (gameMusicFlag) {
		gameMusicFlag = false;
		mciSendString("pause 高山流水.mp3", 0, 0, 0);	// 暂停
		//mciSendString("close 高山流水.mp3",NULL,0,NULL);	// 停止
	}
	else {
		gameMusicFlag = true;
		music();
	}
}



//游戏界面
void gameInterface() 
{
	//初始化图像界面
	initgraph(900, 800);
	// 设置图像的背景颜色
	setbkcolor(RGB(255, 200, 88));
	// 应用到图像中
	cleardevice();

	// 设置画笔颜色
	setlinecolor(RGB(0, 0, 0));

	// 设置画笔粗细
	setlinestyle(PS_SOLID, 3);

	// 画一个空心矩形
	rectangle(50, 50, 750, 750);
	//画棋盘
	CreateBoard();
	gameButton();
}



//重新开始游戏
void newgame()
{
	for (int i = 0; i < 15; i++) {	// 地图全部置为零
		for (int j = 0; j < 15; j++) {
			a[i][j] = 0;
		}
	}
	initgraphGam();
}

//鼠标点击开始游戏结束游戏等
void MouseHit1()
{
	ExMessage mouse;
	while (1)
	{
		mouse = getmessage(EM_MOUSE);
		if (mouse.message == WM_LBUTTONDOWN)
		{
			if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 200 && mouse.y < 250))//点击开始游戏
			{
				deleteHints();
				PlayGame();
			}
			else if((mouse.x > 780 && mouse.x < 870) && (mouse.y > 270 && mouse.y < 320))//点击结束游戏
			{
				musicFlag();
				closegraph();
			}
			else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 340 && mouse.y < 390))//点击音乐开关
			{
				musicFlag();
				continue;
			}
			else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 410 && mouse.y < 460))//点击重新开始
			{
				closegraph();
				newgame();
			}
			
		}
	}
}


//提示选手下棋
void Playershow()
{
	deleteHints();
	if (Player_Black==1)
	{
		//setlinestyle(PS_SOLID, 2);
		settextstyle(35, 0, _T("微软雅黑"));
		rectangle(780, 50, 870, 170);
		settextcolor(RGB(255, 255, 255));
		outtextxy(796, 80, _T("黑方"));
		outtextxy(796, 110, _T("下棋"));
		
	}
	else 
	{
		settextcolor(RGB(255, 255, 255));
		settextstyle(35, 0, _T("微软雅黑"));
		outtextxy(796, 80, _T("白方"));
		outtextxy(796, 110, _T("下棋"));
	}
}





//下棋
void  PlayGame()
{
	clock_t start = clock(), end = clock();
	while (time(num))
	{
		Playershow();
		end = clock();
		ExMessage mouse;
		num = Time_num - ((end - start) / 1000);
		mouse = getmessage(EM_MOUSE);
		if (mouse.message == WM_LBUTTONDOWN)
		{
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {		// 判断鼠标的坐标是否在该区域
					if ((mouse.x >= i * 50 + PLATE_X - 15 && mouse.x <= i * 50 + PLATE_X + 15) &&
						(mouse.y >= j * 50 + PLATE_Y - 15 && mouse.y <= j * 50 + PLATE_Y + 15))
					{
						if (a[i][j] == 0)
						{
							start = clock();
							fofr.x = i;
							fofr.y = j;
							mouses.x = 50 + i * 50;
							mouses.y = 50 + j * 50;
							PlayChess();
							end = clock();
							ifVictory();
							continue;
						}
						else
						{
							deleteHints(781, 51);

							// 设置画笔粗细
							setlinestyle(PS_SOLID, 2);

							// 设置字体
							settextcolor(RGB(255, 0, 0));
							settextstyle(20, 0, _T("黑体"));
							outtextxy(796, 80, _T("此处"));
							outtextxy(787, 110, _T("已有棋子"));
							continue;
						}
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 270 && mouse.y < 320))//点击结束游戏
					{
						musicFlag();
						closegraph();
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 340 && mouse.y < 390))//点击音乐开关
					{
						musicFlag();
						continue;
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 410 && mouse.y < 460))//点击重新开始
					{
						closegraph();
						newgame();
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 480 && mouse.y < 530))//点击悔棋
					{

					}
				}
			}

		}
	}
	

}



//提示此处已有棋子
void Overhit()
{
	deleteHints(781,51);
	
	/// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));
	rectangle(780, 50, 870, 170);
	outtextxy(796, 80, _T("此处"));
	outtextxy(787, 110, _T("已有棋子"));
}


//贴棋子  改变数组赋值
void PlayChess()
{
	if (Player_Black == 1)
	{
		a[fofr.x][fofr.y] = 1;
		setfillcolor(BLACK);
		setfillstyle(BS_SOLID);
		fillcircle(mouses.x, mouses.y, 20);
		Player_Black = 0;
		Player_White = 1;
	}
	else
	{
		a[fofr.x][fofr.y] = 2;
		setfillcolor(WHITE);
		setfillstyle(BS_SOLID);
		fillcircle(mouses.x, mouses.y, 20);
		Player_Black = 1;
		Player_White = 0;
	}

}


//判断输赢
void Victory(int victory)
{
	settextstyle(77, 0, _T("微软雅黑"));

	// 设置字体的背景颜色为透明
	setbkmode(TRANSPARENT);

	if (victory == 1) {
		settextcolor(RGB(255, 255, 255));
		outtextxy(180, 150, _T("恭喜黑棋获胜"));
		MouseHit1();

	}
	else if (victory == 2) {
		settextcolor(RGB(0, 0, 0));
		outtextxy(180, 150, _T("恭喜白棋获胜"));
		MouseHit1();

	}
	else {
		outtextxy(200, 150, _T("参数有问题！"));
	}
	
}
void ifVictory()
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (a[i][j] == 1 && a[i][j - 1] == 1 && a[i][j - 2] == 1 && a[i][j - 3] == 1 && a[i][j - 4] == 1 ||
				a[i][j] == 1 && a[i][j + 1] == 1 && a[i][j + 2] == 1 && a[i][j + 3] == 1 && a[i][j + 4] == 1 ||
				a[i][j] == 1 && a[i - 1][j] == 1 && a[i - 2][j] == 1 && a[i - 3][j] == 1 && a[i - 4][j] == 1 ||
				a[i][j] == 1 && a[i + 1][j] == 1 && a[i + 2][j] == 1 && a[i + 3][j] == 1 && a[i + 4][j] == 1 ||
				a[i][j] == 1 && a[i - 1][j - 1] == 1 && a[i - 2][j - 2] == 1 && a[i - 3][j - 3] == 1 && a[i - 4][j - 4] == 1 ||
				a[i][j] == 1 && a[i + 1][j + 1] == 1 && a[i + 2][j - 2] == 1 && a[i + 3][j - 3] == 1 && a[i + 4][j - 4] == 1 ||
				a[i][j] == 1 && a[i - 1][j + 1] == 1 && a[i - 2][j + 2] == 1 && a[i - 3][j + 3] == 1 && a[i - 4][i + 4] == 1 ||
				a[i][j] == 1 && a[i + 1][j - 1] == 1 && a[i + 2][j - 2] == 1 && a[i + 3][j - 3] == 1 && a[i + 4][i - 4] == 1)
			{
				Victory(1);
			}
			else if (a[i][j] == 2 && a[i][j - 1] == 2 && a[i][j - 2] == 2 && a[i][j - 3] == 2 && a[i][j - 4] == 2 ||
				a[i][j] == 2 && a[i][j + 1] == 2 && a[i][j + 2] == 2 && a[i][j + 3] == 2 && a[i][j + 4] == 2 ||
				a[i][j] == 2 && a[i - 1][j] == 2 && a[i - 2][j] == 2 && a[i - 3][j] == 2 && a[i - 4][j] == 2 ||
				a[i][j] == 2 && a[i + 1][j] == 2 && a[i + 2][j] == 2 && a[i + 3][j] == 2 && a[i + 4][j] == 2 ||
				a[i][j] == 2 && a[i - 1][j - 1] == 2 && a[i - 2][j - 2] == 2 && a[i - 3][j - 3] == 2 && a[i - 4][j - 4] == 2 ||
				a[i][j] == 2 && a[i + 1][j + 1] == 2 && a[i + 2][j - 2] == 2 && a[i + 3][j - 3] == 2 && a[i + 4][j - 4] == 2 ||
				a[i][j] == 2 && a[i - 1][j + 1] == 2 && a[i - 2][j + 2] == 2 && a[i - 3][j + 3] == 2 && a[i - 4][i + 4] == 2 ||
				a[i][j] == 2 && a[i + 1][j - 1] == 2 && a[i + 2][j - 2] == 2 && a[i + 3][j - 3] == 2 && a[i + 4][i - 4] == 2)
			{
				Victory(2);
			}
		}
}



//计时器
int time(int LK)
{
	static int i;
	if (i != LK)
	{
		char T[20];
		// 设置画笔粗细
		setlinestyle(PS_SOLID, 2);

		// 设置字体颜色
		settextcolor(RGB(0, 0, 0));

		// 设置字体
		i = LK;
		settextstyle(28, 0, _T("微软雅黑"));
		sprintf(T, "%2d", i);
		outtextxy(835, 560, T);

	}
	while (i < 0) {
		outtextxy(820, 340, _T("已超时"));
		Beep(5000, 500);
		return 0;
	}
	return 1;
}



int main()
{
	initgraphGam();
}