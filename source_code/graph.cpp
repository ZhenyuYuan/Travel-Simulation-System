#include "basis.h"
using namespace std;

/*
	������605,270��
	��������750,150��
	������695,240��
	�Ϻ���710,420��
	���ݣ�600,560��
	������425,540��
	�ɶ���445,455��
	������515,395��
	������250,440��
	��³ľ�루235,195��
	���п� {880,300,1265,355}
*/

bool ADDING = 0;			//��������ÿ�
bool ADDTRA_OK = 0;			//�ÿ�������
bool SETSTARTING = 0;		//�������ó�������
bool SETSTART_OK = 0;		//���������������
bool SETENDING = 0;			//��������Ŀ�ĵ�
bool SETEND_OK = 0;			//Ŀ�ĵ��������
bool SETTHROUGHING = 0;		//��������;������
bool SETTHROUGH_OK = 0;		//;�������������
bool SETSTRING = 0;			//����ѡ�����
bool SETSTR_OK = 0;			//����ѡ�����
bool ISDEMAND = 0;			//�Ƿ��ѯ
bool SETSTARTTIME = 0;      //���ó���ʱ��
bool SETLIMITTIME = 0;		//������ʱ���ٷ��õ�ʱ������
bool SETSTR3 = 0;			//���ò����������ʱ��

int travnum = 0;			//�ÿ�����	
int timelimit = 0;			//�������е�ʱ������
int starttime = 0;			//�ÿ����п�ʼʱ��
int startcity = 0;			//�ÿͳ�������
int endcity = 0;			//�ÿ�Ŀ�ĳ���
int strategy = 0;			//�ÿ���ѡ����
int seq = 0;				//��ѯ�ÿ�״̬ʱ��������ÿ����
ofstream out2("������Ϣ.txt", ios::app);
Traveler alltraveler[100] = { 0 };//�洢�����ÿ���Ϣ

//ʮ���޶�����
LPCTSTR city[10] = { "����", "����", "����", "�Ϻ�", "����", "����", "�ɶ�", "����", "����", "����" };
//����ÿ͵�������ذ�ť��ʾ
LPCTSTR button[7] = { "���","","ѡ��","ѡ��","ѡ��","���","�˳�" };			
//��ѯ���е������Ŀ
LPCTSTR projectitem[7] = { "���","�յ�","����","����","����","Ʊ��","��ͨ����" }; 
//��ͼ��10�����е�����
int citycoord[10][2] = { {605,270},{750,150},{695,240},{710,420},{600,560},{425,540},{445,455},{515,395},{250,440},{235,195} };
//���о��ΰ�ť
int rectbutton[8][4] = { {1015,118,1050,135},{1215,118,1260,135},{990,175,1055,195},{1200,175,1265,195},
						 {1060,230,1160,250}/*���;������*/,{1200,230,1260,250}/*������;������*/,{1245,665,1275,680}/*�˳���ѯ*/,{880,535,965,555}/*������*/ };
//ѡ����а�ť
int citybutton[10][4] = { {880,300,945,320},{960,300,1025,320},{1040,300,1105,320},{1120,300,1185,320},{1200,300,1265,320},
						  {880,335,945,355},{960,335,1025,355},{1040,335,1105,355},{1120,335,1185,355},{1200,335,1265,355}};
//ѡ����԰�ť
int strabutton[3][2] = { {920,435},{1120,435},{920,463} };
//�����������
int iowin[11][4] = { {1215,118,1260,135},{1160,395,1200,415},{1130,475,1195,500},{1205,535,1260,555},{960,577,1050,600},
					  {960,605,1050,628},{940,655,1030,678},{1145,575,1270,598},{1145,605,1200,628},{1126,630,1200,650},{760,645,820,670} };
//��ͼ����ʾ�ÿ�����·��
int project[1][4] = { 20,460,380,680 };

void InitBackground()				//��ʼ������
{
	IMAGE img;
	loadimage(&img, "����.jpg");
	putimage(0, 0, &img);
}

void InitMap()						//��ʼ����ͼ	
{
	IMAGE img;
	loadimage(&img, "��ͼ.jpg");
	putimage(20, 20, &img);
	setfillcolor(YELLOW);
	for(int i = 0; i < 10; i++)		//��10���޶����б��
		solidcircle(citycoord[i][0], citycoord[i][1], 5);
}

void InitButton()					//��ʼ����ť
{
    setfillcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
    
	int i = 0;
	for (i = 0; i < 7; i++)			//��ʼ�����ΰ�ť
	{
		bar(rectbutton[i][0], rectbutton[i][1], rectbutton[i][2], rectbutton[i][3]);
		outtextxy(rectbutton[i][0], rectbutton[i][1], button[i]);
	}
		
	for (i = 0; i < 10; i++)		//��ʼ�����а�ť
	{
		bar(citybutton[i][0], citybutton[i][1], citybutton[i][2], citybutton[i][3]);
		outtextxy(citybutton[i][0], citybutton[i][1], city[i]);
	}
		
	for (i = 0; i < 11; i++)		//��ʼ�������������
		bar(iowin[i][0], iowin[i][1], iowin[i][2], iowin[i][3]);

	for (i = 0; i < 3; i++)			//��ʼ������ѡ��ť
	{
		setfillcolor(CYAN);
		solidcircle(strabutton[i][0], strabutton[i][1], 8);
	}
}

void InitWin()						//��ʼ������
{
	initgraph(1300, 700);		
	InitBackground();
	InitMap();
	InitButton();
}

void Operation()					//��Ӧ������
{
    MOUSEMSG m;
	while (true)
	{   
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			case WM_MOUSEMOVE:		//��Ӧ����ƶ�
				for (int i = 0; i < 10; i++)	//��س��а�ť��ɫ
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
            
			case WM_LBUTTONDOWN:	//��Ӧ����������
				if ((!ADDING) && (!ISDEMAND) && (rectbutton[0][0] <= m.x) && (m.x <= rectbutton[0][2]) && (rectbutton[0][1] <= m.y) && (m.y <= rectbutton[0][3]))
				{//����û�û����������ÿ���û�����ڲ�ѯ�ÿ�������������ӡ���ť
					setfillcolor(YELLOW);
					bar(rectbutton[0][0], rectbutton[0][1], rectbutton[0][2], rectbutton[0][3]);
					settextcolor(BLACK);
					outtextxy(rectbutton[0][0], rectbutton[0][1], button[0]);
					//�����ÿͣ������ÿͺ�
					travnum++;           //������ÿ�
					setfillcolor(WHITE);
					settextcolor(BLACK);
					char s[5];
					sprintf_s(s, "%d", travnum);
					bar(rectbutton[0][0], rectbutton[0][1], rectbutton[0][2], rectbutton[0][3]);
					outtextxy(iowin[0][0], iowin[0][1], s);
					bar(iowin[10][0], iowin[10][1], iowin[10][2], iowin[10][3]);
					outtextxy(iowin[10][0], iowin[10][1], s);
					//��ʼ����ر���
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
				if (ADDING)//�����������ÿ�
				{
					if ((!SETSTART_OK) && (!SETENDING) && (!SETTHROUGHING) && (rectbutton[2][0] <= m.x) && (m.x <= rectbutton[2][2]) && (rectbutton[2][1] <= m.y) && (m.y <= rectbutton[2][3]))
					{//������ó����ذ�ť
						setfillcolor(YELLOW);
						bar(rectbutton[2][0], rectbutton[2][1], rectbutton[2][2], rectbutton[2][3]);
						settextcolor(BLACK);
						outtextxy(rectbutton[2][0], rectbutton[2][1], button[2]);
						SETSTARTING = 1;
					}
					else if ((!SETEND_OK) && (!SETSTARTING) && (!SETTHROUGHING) && (rectbutton[3][0] <= m.x) && (m.x <= rectbutton[3][2]) && (rectbutton[3][1] <= m.y) && (m.y <= rectbutton[3][3]))
					{//�������Ŀ�ĵذ�ť
						setfillcolor(YELLOW);
						bar(rectbutton[3][0], rectbutton[3][1], rectbutton[3][2], rectbutton[3][3]);
						settextcolor(BLACK);
						outtextxy(rectbutton[3][0], rectbutton[3][1], button[3]);
						SETENDING = 1;
					}
					else
					{
						if ((!SETTHROUGH_OK) && (!SETSTARTING) && (!SETENDING) && (rectbutton[4][0] <= m.x) && (m.x <= rectbutton[4][2]) && (rectbutton[4][1] <= m.y) && (m.y <= rectbutton[4][3]))
						{//�������;�����а�ť
							setfillcolor(YELLOW);
							bar(rectbutton[4][0], rectbutton[4][1], rectbutton[4][2], rectbutton[4][3]);
							settextcolor(BLACK);
							outtextxy(rectbutton[4][0], rectbutton[4][1], button[4]);
							for (int i = 1; i <= 10; i++)
								tjd[i] = 0;
							SETTHROUGHING = 1;
						}
						if ((!SETTHROUGH_OK) && (!SETSTARTING) && (!SETENDING) && ((rectbutton[5][0] <= m.x) && (m.x <= rectbutton[5][2]) && (rectbutton[5][1] <= m.y) && (m.y <= rectbutton[5][3])))
						{//����������;�����а�ť
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
					{//���ó�����
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
					{//����Ŀ�ĵ�
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
					{//����;������
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
					{//���ò���
						if ((strabutton[0][0] - 8 <= m.x) && (m.x <= strabutton[0][0] + 8) && (strabutton[0][1] - 8 <= m.y) && (m.y <= strabutton[0][1] + 8))
						{
							setfillcolor(GREEN);
							solidcircle(strabutton[0][0], strabutton[0][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[1][0], strabutton[1][1], 8);
							setfillcolor(CYAN);
							solidcircle(strabutton[2][0], strabutton[2][1], 8);
							//ѡ���ԣ�����ʱ��
							
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
							//ѡ���ԣ����ٷ���
							
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
							//ѡ���ԣ���ʱ���ٷ���
							strategy = 3;

							SETSTR3 = 1;
							SETSTARTTIME = 1;
							SETLIMITTIME = 1;
						}

						if (SETSTR3)
						{//���ѡ��������������ó���ʱ�������ʱ��
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
						{//������ǲ�������ֻ���ó���ʱ��
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
					{//����������С�Ŀ�ĳ��С�;�����кͲ���ȫ���������
						if ((rectbutton[7][0] <= m.x) && (m.x <= rectbutton[7][2]) && (rectbutton[7][1] <= m.y) && (m.y <= rectbutton[7][3]))
						{//��������Ӱ�ť
							ADDING = 0;
							ADDTRA_OK = 1;

							InitButton();
							setfillcolor(WHITE);
							settextcolor(BLACK);
							bar(iowin[10][0], iowin[10][1], iowin[10][2], iowin[10][3]);
							char s[10];
							sprintf_s(s, "%d", travnum);
							outtextxy(iowin[10][0], iowin[10][1], s);//�����ǰ�ÿ�����
							if (strategy == 1)//���ٻ���
							{
								//��ȡ���ٷ���·��
								alltraveler[travnum] = shortmoney(startcity, endcity);
								alltraveler[travnum].starttime = starttime;
							}
							else if (strategy == 2)    //����ʱ��
							{
								alltraveler[travnum] = mintime(startcity, endcity, starttime);
							}
							else if (strategy == 3)    //��ʱ���ٷ���
							{

								alltraveler[travnum] = limitmm(startcity, endcity, starttime, timelimit);
							}
							alltraveler[travnum].name = travnum;
							alltraveler[travnum].startday = systime;
							if (alltraveler[travnum].starttime < alltraveler[travnum].startday.hour)
							{
								alltraveler[travnum].startday.day++;
							}
							out2 << systime.year << "��" << systime.month << "��" << systime.day << "��" << systime.hour << ":00 ";
							out2 << "�ÿ�" << travnum << "����ϵͳ,ѡ�����" << strategy << ",������Ϊ" << cityname[startcity] << ",�յ�Ϊ" << cityname[endcity] << "����ʱ��Ϊ" << starttime << endl;
						}
					}
				}
				if(ADDTRA_OK && !ADDING)//��ǰ������ÿͲſɲ�ѯ
				{
					if ((iowin[3][0] <= m.x) && (m.x <= iowin[3][2]) && (iowin[3][1] <= m.y) && (m.y <= iowin[3][3]))
					{//�������ѯ��
						ISDEMAND = 1;
						setfillcolor(WHITE);
						settextcolor(BLACK);
						
						char s[100];
						cin >> seq;					//����Ҫ��ѯ���ÿ����
						sprintf_s(s, "%d", seq);
						outtextxy(iowin[3][0], iowin[3][1], s);			//��ʾҪ��ѯ���ÿ����

						if (seq > travnum)
						{
							outtextxy(iowin[4][0], iowin[4][1],"�޸��ÿ�");
						}
						else
						{
							outtextxy(iowin[4][0], iowin[4][1], city[alltraveler[seq].startplace - 1]);		//����ÿͳ�����
							outtextxy(iowin[5][0], iowin[5][1], city[alltraveler[seq].endplace - 1]);		//����ÿ�Ŀ�ĵ�
							sprintf_s(s, "%d", alltraveler[seq].summoney);
							outtextxy(iowin[9][0], iowin[9][1], s);			//����ÿ͵��ܻ���
							switch (alltraveler[seq].strategy)				//����ÿ���ѡ���Լ��������ʱ����Ϣ
							{
							case 1:
								outtextxy(iowin[6][0], iowin[6][1], "���ٷ���");
								outtextxy(iowin[8][0], iowin[8][1], "������");
								break;
							case 2:
								outtextxy(iowin[6][0], iowin[6][1], "����ʱ��");
								outtextxy(iowin[8][0], iowin[8][1], "������");
								break;
							case 3:
								outtextxy(iowin[6][0], iowin[6][1], "��ʱ���ٷ���");
								sprintf_s(s, "%d", alltraveler[seq].limittime);
								outtextxy(iowin[8][0], iowin[8][1], s);
								break;
							}

							//����־�ĵ��������
							out2 << systime.year << "��" << systime.month << "��" << systime.day << "��" << systime.hour << ":00 ";
							out2 << "��ѯ�ÿ�" << alltraveler[seq].name << "��״̬��Ϣ��" << endl;

							//��ʾʱ��
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
							{	//�ڵ�ͼ����ʾ���ɵ����з���
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

								//�ڵ�ͼ����ʾ·��
								setlinecolor(RED);
								setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
								line(citycoord[alltraveler[seq].line[n + 1].beginplace - 1][0], citycoord[alltraveler[seq].line[n + 1].beginplace - 1][1], citycoord[alltraveler[seq].line[n + 1].toplace - 1][0], citycoord[alltraveler[seq].line[n + 1].toplace - 1][1]);

							}
							switch (alltraveler[seq].state)
							{//�ÿ�״��ʼ̬����ʱ���߳��и���
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
					{//�˳���ѯ
						InitMap();
						InitButton();
						ISDEMAND = 0;
						ADDING = 0;
						seq = 0;
						//�����ǰ�ÿ�����
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
		FlushMouseMsgBuffer();		//�����껺����
		fflush(stdin);				//��ռ��̻�����
	}
}

