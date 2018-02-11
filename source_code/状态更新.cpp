#include"basis.h"
#include<Windows.h>

ofstream out1("״̬����.txt", ios::app);
mutex g_mutex;
Timer systime = { 2016,5,1,4};
void addtimer()
{
	systime.hour++;
	if (systime.hour >= 24)
	{
		systime.day++;
		systime.hour -= 24;
	}
}

void settime()
{
	int CityCoord[10][2] = { { 605,270 },{ 750,150 },{ 695,240 },{ 710,420 },{ 600,560 },
							 { 425,540 },{ 445,455 },{ 515,395 },{ 250,440 },{ 235,195 } };
	while (1)
	{
		
		//���ϵͳʱ��
		setfillcolor(WHITE);
		settextcolor(BLACK);
		bar(925, 73, 1018, 88);
		char s[10];
		sprintf_s(s, "%d", systime.year); 
		outtextxy(925, 73, s);
		outtextxy(956, 73, "/");
		sprintf_s(s, "%d", systime.month); 
		outtextxy(960, 73, s);
		outtextxy(967, 73, "/");
		sprintf_s(s, "%d", systime.day);
		outtextxy(973, 73, s);
		outtextxy(980, 73, "/");
		sprintf_s(s, "%d", systime.hour);
		outtextxy(985, 73, s);
		outtextxy(1000, 73, ":00");
		
		Sleep(10000);
		addtimer();

		for (int i = 1; i <= travnum; i++)
		{
			lock_guard<std::mutex> lg(g_mutex);
			switch (alltraveler[i].state)
			{
			case 1:
				if (systime.hour == alltraveler[i].line[alltraveler[i].currentplace].starttime)  //�жϸ�ʱ���Ƿ񷢳�
				{
					out1 << systime.year << "��" << systime.month << "��" << systime.day << "��" << systime.hour << ":00  ";
					out1 << "�ÿ�" << alltraveler[i].name << "����" << alltraveler[i].line[alltraveler[i].currentplace].line << alltraveler[i].line[alltraveler[i].currentplace].kind
						<<",��"<< cityname[alltraveler[i].line[alltraveler[i].currentplace].beginplace] << "ǰ��" << cityname[alltraveler[i].line[alltraveler[i].currentplace].toplace] << endl;

					alltraveler[i].state = 2;
					if (i == seq)
					{
						setfillcolor(YELLOW);
						solidcircle(CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][1], 5);
						//�����ڳ��ϵ������ʾ
						setlinecolor(GREEN);
						setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
						line(CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][1], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][1]);
						
					}
				}
				break;
			case 2:
				if (systime.hour == alltraveler[i].line[alltraveler[i].currentplace].arrivetime)
				{
					if (i == seq)
					{
						setlinecolor(RED);
						line(CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][1], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][1]);
					}

					out1 << systime.year << "��" << systime.month << "��" << systime.day << "��" << systime.hour << ":00  ";
					out1 << "�ÿ�" << alltraveler[i].name << "����" << cityname[alltraveler[i].line[alltraveler[i].currentplace].toplace] << endl;

					alltraveler[i].currentplace++;

					if (alltraveler[i].currentplace <= alltraveler[i].linenum)
					{
						if (systime.hour == alltraveler[i].line[alltraveler[i].currentplace].starttime)
						{
							out1 << systime.year << "��" << systime.month << "��" << systime.day << "��" << systime.hour << ":00  ";
							out1 << "�ÿ�" << alltraveler[i].name << "����" << alltraveler[i].line[alltraveler[i].currentplace].line << alltraveler[i].line[alltraveler[i].currentplace].kind
								<< ",��" << cityname[alltraveler[i].line[alltraveler[i].currentplace].beginplace] << "ǰ��" << cityname[alltraveler[i].line[alltraveler[i].currentplace].toplace] << endl;

							alltraveler[i].state = 2;
							//��������һ�����ϵ������ʾ
							if (i == seq)
							{
								setlinecolor(GREEN);
								setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
								line(CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][1], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][1]);

							}
						}
						else//���е�����һ����������ʾ
						{	
							alltraveler[i].state = 1;
							if (i == seq)
							{
								setfillcolor(GREEN);
								solidcircle(CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][1], 5);

							}
						}	
						
					}
					else
					{
						alltraveler[i].state = 3;
						//���е����յ�����ͼ����ʾ
						out1 << systime.year << "��" << systime.month << "��" << systime.day << "��" << systime.hour << ":00  ";
						out1 << "�ÿ�" << alltraveler[i].name << "�����յ㣬" << cityname[alltraveler[i].endplace] << endl;
						if (i == seq)
						{
							setfillcolor(GREEN);
							solidcircle(CityCoord[alltraveler[i].endplace - 1][0], CityCoord[alltraveler[i].endplace - 1][1], 5);
						}
					}
				}
				break;
			case 3:
				break;

			}
		}
	}
}



