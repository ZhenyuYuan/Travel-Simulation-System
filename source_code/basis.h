#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include<cstdio>
#include<thread>
#include<mutex>
#include <map>

using namespace std;

#define OK    1
#define ERROR 0
#define VEXNUM 10//������
#define MAXCAR 100//���������ڽ�����ĳ�����
#ifdef INFINITY
#undef INFINITY
#endif
#ifndef INFINITY
#define INFINITY 10000000
#endif

typedef struct//��ʾ����ĳ��������Ϣ
{
	int beginplace;//������
	int toplace;//�ó���Ŀ�ĵ�
	int starttime;//����ʱ��
	int arrivetime;//����ʱ��
	int money;//Ʊ��
	string line;//����
	string kind;//��ͨ��������
}realcar;

typedef struct CarArc//�������������г���
{
	int pointplace;//�ñ���ָ��Ķ���
	struct CarArc *nextcar;//ָ����һ������ָ��
	//int minarrivetime;//���г����е���Ŀ�ĵ�ʱ�������
	realcar minmoney;// ���г����м۸���͵�
	int carnum;//���������ܳ�����
	realcar truecar[MAXCAR];//���еĳ���
}Car;


typedef struct PlaceNode
{
	string name;//��������
	Car *firstcar;//ָ��ö����ȥ�ĵ�һ����
}Place, adjList[VEXNUM+1];

typedef struct
{
	adjList  citymap;//��������
	int places, cars;//��¼�������ͱ���
}Graph;

typedef struct
{
	int year;
	int month;
	int day;
	int hour;
}Timer;

typedef struct
{
	int strategy;//���β���
	int name;//��¼�ÿ͵ı��
	int startplace;//������
	int summoney;//���軨�ѵ��ܷ���
	int currentplace;//��ǰ���ڵĵص�
	int state;//����״̬ʱ��ʾ��ǰ״̬��1Ϊ�ȳ���2Ϊ�ڳ��ϣ�3Ϊ�ѵ����յ�
	int endplace;//Ŀ�ĵ�
	int starttime;//��ʼʱ��
	int limittime;//ʱ������
	int arrivetime;//���ﵱǰ�ص�ʱ��huo������������ʱ��
	Timer startday;
	int visited[VEXNUM + 1];//��·���ѷ��ʹ��Ľ��
	realcar  line[VEXNUM + 1];//��;Ҫ�����ĳ�
	int linenum;//��ʾ��ǰline���м�����
}Traveler;//��ʾ�滮��������·��


extern string cityname[VEXNUM + 1];
extern Graph mygraph;
extern Traveler djst[11][11];
extern int tjd[VEXNUM + 1];//��¼;����
//extern const clock_t systemstarttime;
extern Traveler  alltraveler[100];
extern int travnum;
extern int startcity;
extern int endcity;
extern int starttime;
extern int timelimit;
extern int strategy;
extern Timer systime;
extern int seq; //��ǰ��ѯ���ÿͺ�
extern ofstream out1;
extern ofstream out2;

void dijkstra();
int Initialize();
Traveler mintime(int a, int b, int starttime);
Traveler limitmm(int a, int b, int starttime, int limittime);
Traveler shortmoney(int a, int b);
void settime();
void addtimer();
void InitBackground();		//��ʼ������
void InitMap();				//��ʼ����ͼ
void InitButton();			//��ʼ����ť
void InitWin();				//��ʼ������
void Operation();			//�û�ִ�в���