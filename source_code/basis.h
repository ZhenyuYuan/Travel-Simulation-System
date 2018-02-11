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
#define VEXNUM 10//结点个数
#define MAXCAR 100//连接两相邻结点最多的车辆数
#ifdef INFINITY
#undef INFINITY
#endif
#ifndef INFINITY
#define INFINITY 10000000
#endif

typedef struct//表示具体某辆车的信息
{
	int beginplace;//出发地
	int toplace;//该车的目的地
	int starttime;//发车时间
	int arrivetime;//到达时间
	int money;//票价
	string line;//车次
	string kind;//交通工具种类
}realcar;

typedef struct CarArc//包含两点间的所有车辆
{
	int pointplace;//该边所指向的顶点
	struct CarArc *nextcar;//指向下一条弧的指针
	//int minarrivetime;//所有车辆中到达目的地时间最早的
	realcar minmoney;// 所有车辆中价格最低的
	int carnum;//这两点间的总车辆数
	realcar truecar[MAXCAR];//所有的车辆
}Car;


typedef struct PlaceNode
{
	string name;//城市名称
	Car *firstcar;//指向该顶点出去的第一辆车
}Place, adjList[VEXNUM+1];

typedef struct
{
	adjList  citymap;//顶点数组
	int places, cars;//记录顶点数和边数
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
	int strategy;//旅游策略
	int name;//记录旅客的编号
	int startplace;//出发地
	int summoney;//所需花费的总费用
	int currentplace;//当前所在的地点
	int state;//更新状态时表示当前状态，1为等车，2为在车上，3为已到达终点
	int endplace;//目的地
	int starttime;//开始时间
	int limittime;//时间限制
	int arrivetime;//到达当前地点时间huo出发后所花费时间
	Timer startday;
	int visited[VEXNUM + 1];//该路线已访问过的结点
	realcar  line[VEXNUM + 1];//沿途要乘坐的车
	int linenum;//表示当前line里有几辆车
}Traveler;//表示规划出的旅行路线


extern string cityname[VEXNUM + 1];
extern Graph mygraph;
extern Traveler djst[11][11];
extern int tjd[VEXNUM + 1];//记录途经点
//extern const clock_t systemstarttime;
extern Traveler  alltraveler[100];
extern int travnum;
extern int startcity;
extern int endcity;
extern int starttime;
extern int timelimit;
extern int strategy;
extern Timer systime;
extern int seq; //当前查询的旅客号
extern ofstream out1;
extern ofstream out2;

void dijkstra();
int Initialize();
Traveler mintime(int a, int b, int starttime);
Traveler limitmm(int a, int b, int starttime, int limittime);
Traveler shortmoney(int a, int b);
void settime();
void addtimer();
void InitBackground();		//初始化背景
void InitMap();				//初始化地图
void InitButton();			//初始化按钮
void InitWin();				//初始化窗口
void Operation();			//用户执行操作