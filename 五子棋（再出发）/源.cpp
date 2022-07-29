#include <iostream>
using namespace std;
#include <Windows.h>
#include <graphics.h>// ͼ�ο�
#include <mmsystem.h>	// ��������
#include<stdlib.h>
#include <time.h>
#include <conio.h> 
#include <cstdio>
#pragma comment(lib,"winmm.lib")



#define PLATE_X	 50				//////
#define PLATE_Y  50				/////	���̵ľ��ε�����ֵ
#define	OFFSET   50	// ÿ�����̿ո����50����
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



// ��Ϸѡ��
typedef struct PLAYER {
	int white;
	int black;
};
PLAYER player;	// �������Ͻ���ʾѡ������

// frame of reference ����
typedef struct FOR {
	int x;
	int y;
};
FOR fofr;	// ���ڸ�������

// �������
typedef struct MOUSES {
	int x;
	int y;
};
MOUSES mouses;	// ��������




//������
int rollDice()
{
	int dice = 1 + rand() % 6;
	return dice;
}
//��ʾ����
void Jieguo()
{
	initgraph(1080, 720);
	// ��ͼƬӦ���ڽ�����
	loadimage(0, _T("begin-1.jpg"));
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("΢���ź�"));
	setbkmode(TRANSPARENT);
	outtextxy(280, 250, _T("���������һ���������"));
	outtextxy(280, 300, _T("����ѡ�ֵĵ���Ϊ��"));
	outtextxy(280, 350, _T("����ѡ�ֵĵ���Ϊ��"));
	char T1[20]; char T2[20]; char T3[20];
	unsigned seed;
	cin >> seed;
	sprintf(T1, " % 2d", seed);
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("΢���ź�"));
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
	
	
	//ȷ��˭����
	settextcolor(RGB(255, 0, 0));
	settextstyle(120, 0, _T("����"));
	setbkmode(TRANSPARENT);
	if (B > W)
	{
		outtextxy(110,100,_T("����ѡ�������壡"));
		Player_Black = 1;
		Player_White = 0;
		Sleep(2000);
		
	}
	else if (B < W)
	{
		outtextxy(110, 100, _T("����ѡ�������壡"));
		Player_Black = 0;
		Player_White = 1;
		Sleep(2000);
		
	}
	else
	{
		settextcolor(RGB(255, 0, 0));
		settextstyle(80, 0, _T("����"));
		setbkmode(TRANSPARENT);
		outtextxy(150, 100, _T("������ͬ�����������룡"));
		Sleep(2000);
		Jieguo();
	}
	closegraph();
	gameInterface();
}



//��ӭ����
void initgraphGam() 
{
	music();
	initgraph(1080, 720);
	// ��ͼƬӦ���ڽ�����
	loadimage(0, _T("begin-1.jpg"));
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 5);

	// ��һ�����ľ���
	rectangle(355, 405, 730, 535);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(120, 0, _T("΢���ź�"));
	// ��������ı�����ɫΪ͸��
	setbkmode(TRANSPARENT);

	// д��
	outtextxy(144, 190, _T("��ӭ������������Ϸ"));

	// ����������ɫ
	settextcolor(RGB(255, 200, 88));

	// д��
	outtextxy(360, 410, _T("��ʼ��Ϸ"));
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

//�����ʾ
void deleteHints()
{
	IMAGE image;
	loadimage(&image, _T("cheng1.jpg"));
	putimage(781, 51, &image);
}
void deleteHints(int a ,int b)
{
	IMAGE image;
	loadimage(&image, _T("����.PNG"));
	putimage(a, b, &image);
}

//��������
void CreateBoard()
{
	int i;
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);
	for (i = 0; i<15; i++)
	{
		line(PLATE_X, PLATE_Y + i * OFFSET, PLATE_X + 14 * OFFSET, PLATE_Y + i * OFFSET);
		line(PLATE_X + i * OFFSET, PLATE_Y, PLATE_X + i * OFFSET, PLATE_Y + 14 * OFFSET);
	}
}



//��ʼ��Ϸ  ������Ϸ  �����־
void gameButton()
{
	//���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);
	//����������ɫ
	settextcolor(RGB(0, 0, 0));
	//��������
	settextstyle(25, 0, _T("΢���ź�"));
    //�������
	rectangle(780, 200, 870, 250);
	rectangle(780, 270, 870, 320);
	rectangle(780, 340, 870, 390);
	rectangle(780, 410, 870, 460);
	rectangle(780, 480, 870, 530);
	rectangle(780, 550, 870, 600);
	rectangle(780, 50, 870, 170);
	//д��
	outtextxy(787, 210, _T("��ʼ��Ϸ"));
	outtextxy(787, 280, _T("������Ϸ"));
	outtextxy(787, 350, _T("���ֿ���"));
	outtextxy(787, 420, _T("���¿�ʼ"));
	outtextxy(805, 490, _T("����"));
	outtextxy(787, 560, _T("ʱ�䣺"));
	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, _T("����"));
	outtextxy(796, 80, _T("����"));
	outtextxy(787, 110, _T("��ʼ��Ϸ"));
	MouseHit1();
}



//���ֿ���
void music() {
	mciSendString("play ��ɽ��ˮ.mp3 repeat", 0, 0, 0);
}

// �������ֱ�ʶ
bool gameMusicFlag = true;

// ��Ϸ�������ֿ���
void musicFlag() {
	if (gameMusicFlag) {
		gameMusicFlag = false;
		mciSendString("pause ��ɽ��ˮ.mp3", 0, 0, 0);	// ��ͣ
		//mciSendString("close ��ɽ��ˮ.mp3",NULL,0,NULL);	// ֹͣ
	}
	else {
		gameMusicFlag = true;
		music();
	}
}



//��Ϸ����
void gameInterface() 
{
	//��ʼ��ͼ�����
	initgraph(900, 800);
	// ����ͼ��ı�����ɫ
	setbkcolor(RGB(255, 200, 88));
	// Ӧ�õ�ͼ����
	cleardevice();

	// ���û�����ɫ
	setlinecolor(RGB(0, 0, 0));

	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 3);

	// ��һ�����ľ���
	rectangle(50, 50, 750, 750);
	//������
	CreateBoard();
	gameButton();
}



//���¿�ʼ��Ϸ
void newgame()
{
	for (int i = 0; i < 15; i++) {	// ��ͼȫ����Ϊ��
		for (int j = 0; j < 15; j++) {
			a[i][j] = 0;
		}
	}
	initgraphGam();
}

//�������ʼ��Ϸ������Ϸ��
void MouseHit1()
{
	ExMessage mouse;
	while (1)
	{
		mouse = getmessage(EM_MOUSE);
		if (mouse.message == WM_LBUTTONDOWN)
		{
			if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 200 && mouse.y < 250))//�����ʼ��Ϸ
			{
				deleteHints();
				PlayGame();
			}
			else if((mouse.x > 780 && mouse.x < 870) && (mouse.y > 270 && mouse.y < 320))//���������Ϸ
			{
				musicFlag();
				closegraph();
			}
			else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 340 && mouse.y < 390))//������ֿ���
			{
				musicFlag();
				continue;
			}
			else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 410 && mouse.y < 460))//������¿�ʼ
			{
				closegraph();
				newgame();
			}
			
		}
	}
}


//��ʾѡ������
void Playershow()
{
	deleteHints();
	if (Player_Black==1)
	{
		//setlinestyle(PS_SOLID, 2);
		settextstyle(35, 0, _T("΢���ź�"));
		rectangle(780, 50, 870, 170);
		settextcolor(RGB(255, 255, 255));
		outtextxy(796, 80, _T("�ڷ�"));
		outtextxy(796, 110, _T("����"));
		
	}
	else 
	{
		settextcolor(RGB(255, 255, 255));
		settextstyle(35, 0, _T("΢���ź�"));
		outtextxy(796, 80, _T("�׷�"));
		outtextxy(796, 110, _T("����"));
	}
}





//����
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
				for (int j = 0; j < 15; j++) {		// �ж����������Ƿ��ڸ�����
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

							// ���û��ʴ�ϸ
							setlinestyle(PS_SOLID, 2);

							// ��������
							settextcolor(RGB(255, 0, 0));
							settextstyle(20, 0, _T("����"));
							outtextxy(796, 80, _T("�˴�"));
							outtextxy(787, 110, _T("��������"));
							continue;
						}
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 270 && mouse.y < 320))//���������Ϸ
					{
						musicFlag();
						closegraph();
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 340 && mouse.y < 390))//������ֿ���
					{
						musicFlag();
						continue;
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 410 && mouse.y < 460))//������¿�ʼ
					{
						closegraph();
						newgame();
					}
					else if ((mouse.x > 780 && mouse.x < 870) && (mouse.y > 480 && mouse.y < 530))//�������
					{

					}
				}
			}

		}
	}
	

}



//��ʾ�˴���������
void Overhit()
{
	deleteHints(781,51);
	
	/// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(25, 0, _T("΢���ź�"));
	rectangle(780, 50, 870, 170);
	outtextxy(796, 80, _T("�˴�"));
	outtextxy(787, 110, _T("��������"));
}


//������  �ı����鸳ֵ
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


//�ж���Ӯ
void Victory(int victory)
{
	settextstyle(77, 0, _T("΢���ź�"));

	// ��������ı�����ɫΪ͸��
	setbkmode(TRANSPARENT);

	if (victory == 1) {
		settextcolor(RGB(255, 255, 255));
		outtextxy(180, 150, _T("��ϲ�����ʤ"));
		MouseHit1();

	}
	else if (victory == 2) {
		settextcolor(RGB(0, 0, 0));
		outtextxy(180, 150, _T("��ϲ�����ʤ"));
		MouseHit1();

	}
	else {
		outtextxy(200, 150, _T("���������⣡"));
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



//��ʱ��
int time(int LK)
{
	static int i;
	if (i != LK)
	{
		char T[20];
		// ���û��ʴ�ϸ
		setlinestyle(PS_SOLID, 2);

		// ����������ɫ
		settextcolor(RGB(0, 0, 0));

		// ��������
		i = LK;
		settextstyle(28, 0, _T("΢���ź�"));
		sprintf(T, "%2d", i);
		outtextxy(835, 560, T);

	}
	while (i < 0) {
		outtextxy(820, 340, _T("�ѳ�ʱ"));
		Beep(5000, 500);
		return 0;
	}
	return 1;
}



int main()
{
	initgraphGam();
}