#include "basis.h"
using namespace std;

/*
	北京（605,270）
	哈尔滨（750,150）
	沈阳（695,240）
	上海（710,420）
	广州（600,560）
	昆明（425,540）
	成都（445,455）
	西安（515,395）
	拉萨（250,440）
	乌鲁木齐（235,195）
	城市框 {880,300,1265,355}
*/

bool ADDING = 0;			//正在添加旅客
bool ADDTRA_OK = 0;			//旅客添加完成
bool SETSTARTING = 0;		//正在设置出发城市
bool SETSTART_OK = 0;		//出发城市设置完成
bool SETENDING = 0;			//正在设置目的地
bool SETEND_OK = 0;			//目的地设置完成
bool SETTHROUGHING = 0;		//正在设置途经城市
bool SETTHROUGH_OK = 0;		//途经城市设置完成
bool SETSTRING = 0;			//正在选择策略
bool SETSTR_OK = 0;			//策略选择完成
bool ISDEMAND = 0;			//是否查询
bool SETSTARTTIME = 0;      //设置出发时间
bool SETLIMITTIME = 0;		//设置限时最少费用的时间限制
bool SETSTR3 = 0;			//设置策略三的相关时间

int travnum = 0;			//旅客数量	
int timelimit = 0;			//策略三中的时间限制
int starttime = 0;			//旅客旅行开始时间
int startcity = 0;			//旅客出发城市
int endcity = 0;			//旅客目的城市
int strategy = 0;			//旅客所选策略
int seq = 0;				//查询旅客状态时所输入的旅客序号
ofstream out2("键入信息.txt", ios::app);
Traveler alltraveler[100] = { 0 };//存储所有旅客信息

//十个限定城市
LPCTSTR city[10] = { "北京", "哈市", "沈阳", "上海", "广州", "昆明", "成都", "西安", "拉萨", "乌市" };
//添加旅客的所有相关按钮显示
LPCTSTR button[7] = { "添加","","选择","选择","选择","完成","退出" };			
//查询栏中的相关条目
LPCTSTR projectitem[7] = { "起点","终点","车次","发点","到点","票价","交通工具" }; 
//地图上10个城市的坐标
int citycoord[10][2] = { {605,270},{750,150},{695,240},{710,420},{600,560},{425,540},{445,455},{515,395},{250,440},{235,195} };
//所有矩形按钮
int rectbutton[8][4] = { {1015,118,1050,135},{1215,118,1260,135},{990,175,1055,195},{1200,175,1265,195},
						 {1060,230,1160,250}/*添加途经城市*/,{1200,230,1260,250}/*完成添加途径城市*/,{1245,665,1275,680}/*退出查询*/,{880,535,965,555}/*完成添加*/ };
//选择城市按钮
int citybutton[10][4] = { {880,300,945,320},{960,300,1025,320},{1040,300,1105,320},{1120,300,1185,320},{1200,300,1265,320},
						  {880,335,945,355},{960,335,1025,355},{1040,335,1105,355},{1120,335,1185,355},{1200,335,1265,355}};
//选择策略按钮
int strabutton[3][2] = { {920,435},{1120,435},{920,463} };
//输入输出窗口
int iowin[11][4] = { {1215,118,1260,135},{1160,395,1200,415},{1130,475,1195,500},{1205,535,1260,555},{960,577,1050,600},
					  {960,605,1050,628},{940,655,1030,678},{1145,575,1270,598},{1145,605,1200,628},{1126,630,1200,650},{760,645,820,670} };
//地图上显示旅客旅行路线
int project[1][4] = { 20,460,380,680 };

void InitBackground()				//初始化背景
{
	IMAGE img;
	loadimage(&img, "背景.jpg");
	putimage(0, 0, &img);
}

void InitMap()						//初始化地图	
{
	IMAGE img;
	loadimage(&img, "地图.jpg");
	putimage(20, 20, &img);
	setfillcolor(YELLOW);
	for(int i = 0; i < 10; i++)		//将10个限定城市标黄
		solidcircle(citycoord[i][0], citycoord[i][1], 5);
}

void InitButton()					//初始化按钮
{
    setfillcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
    
	int i = 0;
	for (i = 0; i < 7; i++)			//初始化矩形按钮
	{
		bar(rectbutton[i][0], rectbutton[i][1], rectbutton[i][2], rectbutton[i][3]);
		outtextxy(rectbutton[i][0], rectbutton[i][1], button[i]);
	}
		
	for (i = 0; i < 10; i++)		//初始化城市按钮
	{
		bar(citybutton[i][0], citybutton[i][1], citybutton[i][2], citybutton[i][3]);
		outtextxy(citybutton[i][0], citybutton[i][1], city[i]);
	}
		
	for (i = 0; i < 11; i++)		//初始化输入输出窗口
		bar(iowin[i][0], iowin[i][1], iowin[i][2], iowin[i][3]);

	for (i = 0; i < 3; i++)			//初始化策略选择按钮
	{
		setfillcolor(CYAN);
		solidcircle(strabutton[i][0], strabutton[i][1], 8);
	}
}

void InitWin()						//初始化窗口
{
	initgraph(1300, 700);		
	InitBackground();
	InitMap();
	InitButton();
}

void Operation()					//响应鼠标操作
{
    MOUSEMSG m;
	while (true)
	{   
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			case WM_MOUSEMOVE:		//响应鼠标移动
				for (int i = 0; i < 10; i++)	//相关城市按钮变色
				{
					if ((citybutton[i][0] <= m.x) && (m.x <= citybutton[i][2]) && (citybutton[i][1] <= m.y) && (m.y <= citybutton[i][3]))
					{
						settextcolor(GREEN);
						outtextxy(citybutton[i][0], citybutton[i][1], city[i]);
					}
					else
					{
						settextcolor(BLACK);
						outtextxy(citybutton[i][0], citybutton[i][1], city[i]);
					}
				}
				break;
            
			case WM_LBUTTONDOWN:	//相应鼠标左键单击
				if ((!ADDING) && (!ISDEMAND) && (rectbutton[0][0] <= m.x) && (m.x <= rectbutton[0][2]) && (rectbutton[0][1] <= m.y) && (m.y <= rectbutton[0][3]))
				{//如果用户没有正在添加旅客且没有正在查询旅客且左键点击“添加”按钮
					setfillcolor(YELLOW);
					bar(rectbutton[0][0], rectbutton[0][1], rectbutton[0][2], rectbutton[0][3]);
					settextcolor(BLACK);
					outtextxy(rectbutton[0][0], rectbutton[0][1], button[0]);
					//增加旅客，设置旅客号
					travnum++;           //添加新旅客
					setfillcolor(WHITE);
					settextcolor(BLACK);
					char s[5];
					sprintf_s(s, "%d", travnum);
					bar(rectbutton[0][0], rectbutton[0][1], rectbutton[0][2], rectbutton[0][3]);
					outtextxy(iowin[0][0], iowin[0][1], s);
					bar(iowin[10][0], iowin[10][1], iowin[10][2], iowin[10][3]);
					outtextxy(iowin[10][0], iowin[10][1], s);
					//初始化相关变量
					ADDING = 1;
					SETSTART_OK = 0;
					SETSTARTING = 0;
					SETSTART_OK = 0;
					SETENDING = 0;
					SETEND_OK = 0;
					SETTHROUGHING = 0;
					SETTHROUGH_OK = 0;
					SETSTRING = 0;
					SETSTR_OK = 0;
				}
				if (ADDING)//如果正在添加旅客
				{
					if ((!SETSTART_OK) && (!SETENDING) && (!SETTHROUGHING) && (rectbutton[2][0] <= m.x) && (m.x <= rectbutton[2][2]) && (rectbutton[2][1] <= m.y) && (m.y <= rectbutton[2][3]))
					{//点击设置出发地按钮
						setfillcolor(YELLOW);
						bar(rectbutton[2][0], rectbutton[2][1], rectbutton[2][2], rectbutton[2][3]);
						settextcolor(BLACK);
						outtextxy(rectbutton[2][0], rectbutton[2][1], button[2]);
						SETSTARTING = 1;
					}
					else if ((!SETEND_OK) && (!SETSTARTING) && (!SETTHROUGHING) && (rectbutton[3][0] <= m.x) && (m.x <= rectbutton[3][2]) && (rectbutton[3][1] <= m.y) && (m.y <= rectbutton[3][3]))
					{//点击设置目的地按钮
						setfillcolor(YELLOW);
						bar(rectbutton[3][0], rectbutton[3][1], rectbutton[3][2], rectbutton[3][3]);
						settextcolor(BLACK);
						outtextxy(rectbutton[3][0], rectbutton[3][1], button[3]);
						SETENDING = 1;
					}
					else
					{
						if ((!SETTHROUGH_OK) && (!SETSTARTING) && (!SETENDING) && (rectbutton[4][0] <= m.x) && (m.x <= rectbutton[4][2]) && (rectbutton[4][1] <= m.y) && (m.y <= rectbutton[4][3]))
						{//点击设置途经城市按钮
							setfillcolor(YELLOW);
							bar(rectbutton[4][0], rectbutton[4][1], rectbutton[4][2], rectbutton[4][3]);
							settextcolor(BLACK);
							outtextxy(rectbutton[4][0], rectbutton[4][1], button[4]);
							for (int i = 1; i <= 10; i++)
								tjd[i] = 0;
							SETTHROUGHING = 1;
						}
						if ((!SETTHROUGH_OK) && (!SETSTARTING) && (!SETENDING) && ((rectbutton[5][0] <= m.x) && (m.x <= rectbutton[5][2]) && (rectbutton[5][1] <= m.y) && (m.y <= rectbutton[5][3])))
						{//点击完成设置途径城市按钮
							setfillcolor(YELLOW);
							bar(rectbutton[5][0], rectbutton[5][1], rectbutton[5][2], rectbutton[5][3]);
							settextcolor(BLACK);
							outtextxy(rectbutton[5][0], rectbutton[5][1], button[5]);
							SETTHROUGHING = 0;
							SETTHROUGH_OK = 1;
							SETSTRING = 1;
						}
					}
					if (SETSTARTING && !SETSTART_OK)
					{//设置出发地
						for (int i = 0; i < 10; i++)
						{
							if ((citybutton[i][0] <= m.x) && (m.x <= citybutton[i][2]) && (citybutton[i][1] <= m.y) && (m.y <= citybutton[i][3]))
							{
								setfillcolor(CYAN);
								bar(rectbutton[2][0], rectbutton[2][1], rectbutton[2][2], rectbutton[2][3]);
								settextcolor(BLACK);
								outtextxy(rectbutton[2][0], rectbutton[2][1], city[i]);
								startcity = i + 1;
								SETSTARTING = 0;
								SETSTART_OK = 1;
							}
						}
					}
					if (SETENDING && !SETEND_OK)
					{//设置目的地
						for (int i = 0; i < 10; i++)
						{
							if ((citybutton[i][0] <= m.x) && (m.x <= citybutton[i][2]) && (citybutton[i][1] <= m.y) && (m.y <= citybutton[i][3]))
							{
								setfillcolor(CYAN);
								bar(rectbutton[3][0], rectbutton[3][1], rectbutton[3][2], rectbutton[3][3]);
								settextcolor(BLACK);
								outtextxy(rectbutton[3][0], rectbutton[3][1], city[i]);
								endcity = i + 1;
								SETENDING = 0;
								SETEND_OK = 1;
							}
						}
					}
					if (SETTHROUGHING && !SETTHROUGH_OK)
					{//设置途经城市
						for (int i = 0; i < 10; i++)
						{
							if ((citybutton[i][0] <= m.x) && (m.x <= citybutton[i][2]) && (citybutton[i][1] <= m.y) && (m.y <= citybutton[i][3]))
							{
								setfillcolor(CYAN);
								bar(citybutton[i][0], citybutton[i][1], citybutton[i][2], citybutton[i][3]);
								settextcolor(BLACK);
								outtextxy(citybutton[i][0], citybutton[i][1], city[i]);
								tjd[i + 1] = 1;
							}
						}

					}

					if (SETSTRING && !SETSTR_OK)
					{//设置策略
						if ((strabutton[0][0] - 8 <= m.x) && (m.x <= strabutton[0][0] + 8) && (strabutton[0][1] - 8 <= m.y) && (m.y <= strabutton[0][1] + 8))
						{
							setfillcolor(GREEN);
							solidcircle(strabutton[0][0], strabutton[0][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[1][0], strabutton[1][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[2][0], strabutton[2][1], 8);
							//选策略：最少时间
							
							strategy = 2;
							SETSTR3 = 0;
							SETSTARTTIME = 1;
						}
						else if ((strabutton[1][0] - 8 <= m.x) && (m.x <= strabutton[1][0] + 8) && (strabutton[1][1] - 8 <= m.y) && (m.y <= strabutton[1][1] + 8))
						{
							setfillcolor(GREEN);
							solidcircle(strabutton[1][0], strabutton[1][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[0][0], strabutton[0][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[2][0], strabutton[2][1], 8);
							//选策略：最少费用
							
							strategy = 1;
							SETSTR3 = 0;
							SETSTARTTIME = 1;
						}
						else if ((strabutton[2][0] - 8 <= m.x) && (m.x <= strabutton[2][0] + 8) && (strabutton[2][1] - 8 <= m.y) && (m.y <= strabutton[2][1] + 8))
						{
							setfillcolor(GREEN);
							solidcircle(strabutton[2][0], strabutton[2][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[0][0], strabutton[0][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[1][0], strabutton[1][1], 8);
							//选策略：限时最少费用
							strategy = 3;

							SETSTR3 = 1;
							SETSTARTTIME = 1;
							SETLIMITTIME = 1;
						}

						if (SETSTR3)
						{//如果选择策略三，得设置出发时间和限制时间
							if (SETSTARTTIME && (iowin[1][0] <= m.x) && (m.x <= iowin[1][2]) && (iowin[1][1] <= m.y) && (m.y <= iowin[1][3]))
							{
								char s[5];
								cin >> starttime;
								sprintf_s(s, "%d", starttime);

								outtextxy(iowin[1][0], iowin[1][1], s);

								SETSTARTTIME = 0;
							}
							if (SETLIMITTIME && (iowin[2][0] <= m.x) && (m.x <= iowin[2][2]) && (iowin[2][1] <= m.y) && (m.y <= iowin[2][3]))
							{
								char s[5];
								cin >> timelimit;
								sprintf_s(s, "%d", timelimit);
								outtextxy(iowin[2][0], iowin[2][1], s);

								SETLIMITTIME = 0;
							}
							if (!(SETSTARTTIME) && !(SETLIMITTIME))
							{
								SETSTR3 = 0;
								SETSTRING = 0;
								SETSTR_OK = 1;
							}
						}
						if ((!SETSTR3) && SETSTARTTIME && (iowin[1][0] <= m.x) && (m.x <= iowin[1][2]) && (iowin[1][1] <= m.y) && (m.y <= iowin[1][3]))
						{//如果不是策略三，只设置出发时间
							char s[5];
							cin >> starttime;
							sprintf_s(s, "%d", starttime);
							outtextxy(iowin[1][0], iowin[1][1], s);

							SETSTARTTIME = 0;
							SETSTRING = 0;
							SETSTR_OK = 1;
						}

					}
					if (SETSTART_OK && SETEND_OK && SETTHROUGH_OK && SETSTR_OK)
					{//如果出发城市、目的城市、途经城市和策略全部完成设置
						if ((rectbutton[7][0] <= m.x) && (m.x <= rectbutton[7][2]) && (rectbutton[7][1] <= m.y) && (m.y <= rectbutton[7][3]))
						{//点击完成添加按钮
							ADDING = 0;
							ADDTRA_OK = 1;

							InitButton();
							setfillcolor(WHITE);
							settextcolor(BLACK);
							bar(iowin[10][0], iowin[10][1], iowin[10][2], iowin[10][3]);
							char s[10];
							sprintf_s(s, "%d", travnum);
							outtextxy(iowin[10][0], iowin[10][1], s);//输出当前旅客数量
							if (strategy == 1)//最少花费
							{
								//获取最少费用路线
								alltraveler[travnum] = shortmoney(startcity, endcity);
								alltraveler[travnum].starttime = starttime;
							}
							else if (strategy == 2)    //最少时间
							{
								alltraveler[travnum] = mintime(startcity, endcity, starttime);
							}
							else if (strategy == 3)    //限时最少费用
							{

								alltraveler[travnum] = limitmm(startcity, endcity, starttime, timelimit);
							}
							alltraveler[travnum].name = travnum;
							alltraveler[travnum].startday = systime;
							if (alltraveler[travnum].starttime < alltraveler[travnum].startday.hour)
							{
								alltraveler[travnum].startday.day++;
							}
							out2 << systime.year << "年" << systime.month << "月" << systime.day << "日" << systime.hour << ":00 ";
							out2 << "旅客" << travnum << "进入系统,选择策略" << strategy << ",出发地为" << cityname[startcity] << ",终点为" << cityname[endcity] << "出发时间为" << starttime << endl;
						}
					}
				}
				if(ADDTRA_OK && !ADDING)//当前如果有旅客才可查询
				{
					if ((iowin[3][0] <= m.x) && (m.x <= iowin[3][2]) && (iowin[3][1] <= m.y) && (m.y <= iowin[3][3]))
					{//若点击查询框
						ISDEMAND = 1;
						setfillcolor(WHITE);
						settextcolor(BLACK);
						
						char s[100];
						cin >> seq;					//输入要查询的旅客序号
						sprintf_s(s, "%d", seq);
						outtextxy(iowin[3][0], iowin[3][1], s);			//显示要查询的旅客序号

						if (seq > travnum)
						{
							outtextxy(iowin[4][0], iowin[4][1],"无该旅客");
						}
						else
						{
							outtextxy(iowin[4][0], iowin[4][1], city[alltraveler[seq].startplace - 1]);		//输出旅客出发地
							outtextxy(iowin[5][0], iowin[5][1], city[alltraveler[seq].endplace - 1]);		//输出旅客目的地
							sprintf_s(s, "%d", alltraveler[seq].summoney);
							outtextxy(iowin[9][0], iowin[9][1], s);			//输出旅客的总花费
							switch (alltraveler[seq].strategy)				//输出旅客所选策略及策略相关时间信息
							{
							case 1:
								outtextxy(iowin[6][0], iowin[6][1], "最少费用");
								outtextxy(iowin[8][0], iowin[8][1], "无限制");
								break;
							case 2:
								outtextxy(iowin[6][0], iowin[6][1], "最少时间");
								outtextxy(iowin[8][0], iowin[8][1], "无限制");
								break;
							case 3:
								outtextxy(iowin[6][0], iowin[6][1], "限时最少费用");
								sprintf_s(s, "%d", alltraveler[seq].limittime);
								outtextxy(iowin[8][0], iowin[8][1], s);
								break;
							}

							//向日志文档输出数据
							out2 << systime.year << "年" << systime.month << "月" << systime.day << "日" << systime.hour << ":00 ";
							out2 << "查询旅客" << alltraveler[seq].name << "的状态信息。" << endl;

							//显示时间
							sprintf_s(s, "%d", alltraveler[seq].startday.year);
							outtextxy(iowin[7][0], iowin[7][1], s);
							outtextxy(iowin[7][0] + 33, iowin[7][1], "/");
							sprintf_s(s, "%d", alltraveler[seq].startday.month);
							outtextxy(iowin[7][0] + 38, iowin[7][1], s);
							outtextxy(iowin[7][0] + 45, iowin[7][1], "/");
							sprintf_s(s, "%d", alltraveler[seq].startday.day);
							outtextxy(iowin[7][0] + 52, iowin[7][1], s);
							outtextxy(iowin[7][0] + 59, iowin[7][1], "/");
							sprintf_s(s, "%d", starttime);
							outtextxy(iowin[7][0] + 65, iowin[7][1], s);
							outtextxy(iowin[7][0] + 80, iowin[7][1], ":00");

							bar(project[0][0], project[0][1], project[0][2], project[0][3]);
							for (int i = 0, k = 0; i < 7; i++, k += 50)
								outtextxy(project[0][0] + k, project[0][1], projectitem[i]);
							for (int n = 0, k = 30; n < alltraveler[seq].linenum; n++, k += 20)
							{	//在地图上显示生成的旅行方案
								outtextxy(project[0][0], project[0][1] + k, city[alltraveler[seq].line[n + 1].beginplace - 1]);
								outtextxy(project[0][0] + 50, project[0][1] + k, city[alltraveler[seq].line[n + 1].toplace - 1]);
								const char *tline = alltraveler[seq].line[n + 1].line.c_str();
								outtextxy(project[0][0] + 100, project[0][1] + k, tline);
								sprintf_s(s, "%d", alltraveler[seq].line[n + 1].starttime);
								outtextxy(project[0][0] + 150, project[0][1] + k, s);
								sprintf_s(s, "%d", alltraveler[seq].line[n + 1].arrivetime);
								outtextxy(project[0][0] + 200, project[0][1] + k, s);
								sprintf_s(s, "%d", alltraveler[seq].line[n + 1].money);
								outtextxy(project[0][0] + 250, project[0][1] + k, s);
								const char *tkind = alltraveler[seq].line[n + 1].kind.c_str();
								outtextxy(project[0][0] + 300, project[0][1] + k, tkind);

								//在地图上显示路线
								setlinecolor(RED);
								setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
								line(citycoord[alltraveler[seq].line[n + 1].beginplace - 1][0], citycoord[alltraveler[seq].line[n + 1].beginplace - 1][1], citycoord[alltraveler[seq].line[n + 1].toplace - 1][0], citycoord[alltraveler[seq].line[n + 1].toplace - 1][1]);

							}
							switch (alltraveler[seq].state)
							{//旅客状初始态，在时间线程中更新
							case 1:
								setfillcolor(GREEN);
								solidcircle(citycoord[alltraveler[seq].line[alltraveler[seq].currentplace].beginplace - 1][0], citycoord[alltraveler[seq].line[alltraveler[seq].currentplace].beginplace - 1][1], 5);
								break;
							case 2:
								setlinecolor(GREEN);
								setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
								line(citycoord[alltraveler[seq].line[alltraveler[seq].currentplace].beginplace - 1][0], citycoord[alltraveler[seq].line[alltraveler[seq].currentplace].beginplace - 1][1], citycoord[alltraveler[seq].line[alltraveler[seq].currentplace].toplace - 1][0], citycoord[alltraveler[seq].line[alltraveler[seq].currentplace].toplace - 1][1]);
								break;
							case 3:
								setfillcolor(GREEN);
								solidcircle(citycoord[alltraveler[seq].endplace - 1][0], citycoord[alltraveler[seq].endplace - 1][1], 5);
								break;
							}
						}
					}
					if (!ADDING && ISDEMAND && (rectbutton[6][0] <= m.x) && (m.x <= rectbutton[6][2]) && (rectbutton[6][1] <= m.y) && (m.y <= rectbutton[6][3]))
					{//退出查询
						InitMap();
						InitButton();
						ISDEMAND = 0;
						ADDING = 0;
						seq = 0;
						//输出当前旅客数量
						setfillcolor(WHITE);
						settextcolor(BLACK);
						bar(iowin[10][0], iowin[10][1], iowin[10][2], iowin[10][3]);
						char s[10];
						sprintf_s(s, "%d", travnum);
						outtextxy(iowin[10][0], iowin[10][1], s);
					}
				}
				break;
		}
		FlushMouseMsgBuffer();		//清空鼠标缓存区
		fflush(stdin);				//清空键盘缓存区
	}
}

