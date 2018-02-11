#include"basis.h"
#include<Windows.h>

ofstream out1("状态更新.txt", ios::app);
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
		
		//输出系统时间
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
				if (systime.hour == alltraveler[i].line[alltraveler[i].currentplace].starttime)  //判断该时间是否发车
				{
					out1 << systime.year << "年" << systime.month << "月" << systime.day << "日" << systime.hour << ":00  ";
					out1 << "旅客" << alltraveler[i].name << "乘坐" << alltraveler[i].line[alltraveler[i].currentplace].line << alltraveler[i].line[alltraveler[i].currentplace].kind
						<<",从"<< cityname[alltraveler[i].line[alltraveler[i].currentplace].beginplace] << "前往" << cityname[alltraveler[i].line[alltraveler[i].currentplace].toplace] << endl;

					alltraveler[i].state = 2;
					if (i == seq)
					{
						setfillcolor(YELLOW);
						solidcircle(CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][1], 5);
						//进行在车上的相关显示
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

					out1 << systime.year << "年" << systime.month << "月" << systime.day << "日" << systime.hour << ":00  ";
					out1 << "旅客" << alltraveler[i].name << "到达" << cityname[alltraveler[i].line[alltraveler[i].currentplace].toplace] << endl;

					alltraveler[i].currentplace++;

					if (alltraveler[i].currentplace <= alltraveler[i].linenum)
					{
						if (systime.hour == alltraveler[i].line[alltraveler[i].currentplace].starttime)
						{
							out1 << systime.year << "年" << systime.month << "月" << systime.day << "日" << systime.hour << ":00  ";
							out1 << "旅客" << alltraveler[i].name << "乘坐" << alltraveler[i].line[alltraveler[i].currentplace].line << alltraveler[i].line[alltraveler[i].currentplace].kind
								<< ",从" << cityname[alltraveler[i].line[alltraveler[i].currentplace].beginplace] << "前往" << cityname[alltraveler[i].line[alltraveler[i].currentplace].toplace] << endl;

							alltraveler[i].state = 2;
							//进行在下一辆车上的相关显示
							if (i == seq)
							{
								setlinecolor(GREEN);
								setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
								line(CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].beginplace - 1][1], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][0], CityCoord[alltraveler[i].line[alltraveler[i].currentplace].toplace - 1][1]);

							}
						}
						else//进行到达下一个点的相关显示
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
						//进行到达终点的相关图形显示
						out1 << systime.year << "年" << systime.month << "月" << systime.day << "日" << systime.hour << ":00  ";
						out1 << "旅客" << alltraveler[i].name << "到达终点，" << cityname[alltraveler[i].endplace] << endl;
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



