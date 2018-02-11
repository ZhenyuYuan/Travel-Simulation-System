#include"basis.h"
#include<stack>

Graph mygraph ;
Traveler djst[11][11] = { 0 };
int tjd[VEXNUM + 1] = { 0 };//��¼;����
string cityname[VEXNUM + 1] = {"","����","������","����","�Ϻ�","����","����","�ɶ�","����","����","��³ľ��"};
void initdjst()//��ʼ�����·������
{
	int i, j;
	for (i = 1; i <= 10; i++)
	{
		for (j = 1; j <= 10; j++)
		{
			djst[i][j].startplace = i;
			djst[i][j].currentplace = 1;
			djst[i][j].endplace = j;
			djst[i][j].starttime = 0;
			djst[i][j].arrivetime = 0;
			djst[i][j].linenum = 0;
			djst[i][j].summoney = 0;
			djst[i][j].state = 1;
		}
	}
}

int checktjd(int visited[])
{
	for (int i = 1; i <= VEXNUM; i++)
	{
		if ((tjd[i] == 1)&& (visited[i] != 1))
		{
			return 0;
		}
	}
	return 1;
}

Traveler shortmoney(int a, int b)
{
	Traveler x = djst[a][b];
	x.summoney = 0;
	int jgd[VEXNUM + 1], top = 2;//��¼���辭�������е�,topΪ����Ԫ��
	jgd[1] = a;
	jgd[2] = b;
	int i,j;
	tjd[a] = 0;
	for (i = 1; i <= x.linenum; i++)
	{
		tjd[x.line[i].toplace] = 0;
	}
	for (i = 1; i <= VEXNUM; i++)
	{
		if (tjd[i] == 1)
		{
			jgd[top] = i;
			top++;
			jgd[top] = b;
		}
	}
	x.linenum = 0;
	for (i = 1; i < top; i++)
	{
		for (j = 1; j <= djst[jgd[i]][jgd[i + 1]].linenum; j++)
		{
			x.line[x.linenum + j] = djst[jgd[i]][jgd[i + 1]].line[j];
		}
		x.linenum += djst[jgd[i]][jgd[i + 1]].linenum;
		x.summoney += djst[jgd[i]][jgd[i + 1]].summoney;
	}
	x.strategy = 1;
	x.startplace = a;
	x.currentplace = 1;
	x.endplace = b;
	//��ʼʱ������������
	return x;
}

void dijkstra()
{//a��ʾ��ʵ���ţ�d[]�������·�����ȣ�path�������·��
	initdjst();
	int d[VEXNUM + 1],i,j,k;
	for (int a = 1; a <= VEXNUM; a++)
	{
		int s[VEXNUM + 1], min = 0;
		Car *ptr = mygraph.citymap[a].firstcar;
		for (i = 1; i <= VEXNUM; i++)
		{
			d[i] = INFINITY;
			s[i] = 0;
		}
		while (ptr != NULL)
		{
			d[ptr->pointplace] = ptr->minmoney.money;
			djst[a][ptr->pointplace].line[1] = ptr->minmoney;
			djst[a][ptr->pointplace].linenum++;
			djst[a][ptr->pointplace].summoney = d[ptr->pointplace];
			ptr = ptr->nextcar;
		}
		ptr = NULL;
		s[a] = 1;//����Ƿ���������·��
		d[a] = 0;
		while (min != INFINITY)
		{
			min = INFINITY;
			k = 0;//�����¼��С�Ľ����
			for (i = 1; i <= VEXNUM; i++)
			{
				if ((s[i] != 1) && (d[i] < min))
				{
					min = d[i];
					k = i;
				}
			}
			//cout << "/****" << endl;
			s[k] = 1;
			ptr = mygraph.citymap[k].firstcar;
			while (ptr != NULL)
			{
				if ((s[ptr->pointplace] != 1) && ((d[k] + ptr->minmoney.money) < d[
					ptr->pointplace]))
				{
					djst[a][ptr->pointplace].linenum = 0;
					d[ptr->pointplace] = d[k] + ptr->minmoney.money;
					for (j = 1; j <= djst[a][k].linenum; j++)
					{
						djst[a][ptr->pointplace].line[j] = djst[a][k].line[j];
						djst[a][ptr->pointplace].linenum++;
					}
					djst[a][ptr->pointplace].line[j] = ptr->minmoney;
					djst[a][ptr->pointplace].linenum++;
					djst[a][ptr->pointplace].summoney = d[ptr->pointplace];
				}
					ptr = ptr->nextcar;
			}
		}
	}
}

Traveler mintime(int a, int b,int starttime)//aΪ�����ر�ţ�bΪĿ�ĵر��
{
	int  min,i,k;
	Traveler hold,hbc, minsum;
	minsum.arrivetime = INFINITY;
	stack<Traveler>zan;
	Car *ptr = mygraph.citymap[a].firstcar;
	hold.startplace = a;
	hold.endplace = b;
	hold.starttime = starttime;
	hold.arrivetime = 0;
	hold.summoney = 0;
	for (int i = 1; i <= VEXNUM; i++)
	{
		hold.visited[i] = 0;
	}
	hold.visited[a] = 1;
	hold.linenum = 0;
	//hold.summoney = 0;
	while (NULL != ptr)
	{
		min = INFINITY;
		hbc = hold;
		hbc.currentplace = ptr->pointplace;
		hbc.visited[ptr->pointplace] = 1;
		for (i = 1; i <= ptr->carnum; i++)
		{
			if (((hbc.arrivetime%24 + hbc.starttime)%24)<= (ptr->truecar[i].starttime))
			{
				if ((ptr->truecar[i].arrivetime- ((hbc.arrivetime % 24 + hbc.starttime) % 24)+hbc.arrivetime) < min)
				{
					min = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime;
					k = i;
				}
			}
			else
			{
				if ((ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime+24) < min)
				{
					min = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime+24;
					k = i;
				}
			}
		}
		hbc.arrivetime = min;
		hbc.linenum++;
		hbc.line[hbc.linenum] = ptr->truecar[k];
		hbc.summoney += ptr->truecar[k].money;
		zan.push(hbc);
		ptr = ptr->nextcar;
	}
	while (zan.empty()!=true)
	{
		hold = zan.top();
		zan.pop();
		if (hold.currentplace == hold.endplace)
		{
			if ((hold.arrivetime < minsum.arrivetime)&&(checktjd(hold.visited)==1))
			{
				minsum = hold;
			}
		}
		ptr = mygraph.citymap[hold.currentplace].firstcar;
		while (NULL != ptr)
		{
			min = INFINITY;
			if (hold.visited[ptr->pointplace] != 1)
			{
				hbc = hold;
				for (i = 1; i <= ptr->carnum; i++)
				{
					if (((hbc.arrivetime % 24 + hbc.starttime) % 24) <= (ptr->truecar[i].starttime))
					{
						if ((ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime) < min)
						{
							min = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime;
							k = i;
						}
					}
					else
					{
						if ((ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime + 24) < min)
						{
							min = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime + 24;
							k = i;
						}
					}
				}
				if (min <= minsum.arrivetime)
				{
					hbc.currentplace = ptr->pointplace;
					hbc.visited[ptr->pointplace] = 1;
					hbc.arrivetime = min;
					hbc.linenum++;
					hbc.line[hbc.linenum] = ptr->truecar[k];
					hbc.summoney += ptr->truecar[k].money;
					zan.push(hbc);
				}
			}
			ptr = ptr->nextcar;
		}
	}
	minsum.arrivetime = minsum.starttime + minsum.arrivetime;
	minsum.state = 1;
	minsum.currentplace = 1;
	minsum.strategy = 2;
	minsum.limittime = 0;
	return minsum;
}

Traveler limitmm(int a, int b, int starttime, int limittime)//��ʱ���ٷ��ò���
{
	int  i, mid, mid1,mid2;//�м��ݴ����
	Traveler hold, hbc, minsum;
	minsum.summoney = INFINITY;
	stack<Traveler>zan;
	Car *ptr = mygraph.citymap[a].firstcar;
	hold.startplace = a;
	hold.endplace = b;
	hold.starttime = starttime;
	hold.arrivetime = 0;
	hold.summoney = 0;
	for (int i = 1; i <= VEXNUM; i++)
	{
		hold.visited[i] = 0;
	}
	hold.visited[a] = 1;
	hold.linenum = 0;
	while (NULL != ptr)
	{
		hbc = hold;
		for (i = 1; i <= ptr->carnum; i++)
		{
			if (((hbc.arrivetime % 24 + hbc.starttime) % 24) <= (ptr->truecar[i].starttime))
			{
				if ((ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime) < limittime)
				{
					if ((hbc.summoney + ptr->truecar[i].money) < minsum.summoney)
					{
						mid = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24);
						hbc.arrivetime = hbc.arrivetime + mid;
						hbc.linenum++;
						hbc.line[hbc.linenum] = ptr->truecar[i];
						mid2 = ptr->truecar[i].money;
						hbc.summoney = hbc.summoney + mid2;
						hbc.visited[ptr->pointplace] = 1;
						mid1 = hbc.currentplace;
						hbc.currentplace = ptr->pointplace;

						zan.push(hbc);

						hbc.arrivetime = hbc.arrivetime - mid;
						hbc.linenum--;
						hbc.summoney = hbc.summoney - mid2;
						hbc.visited[ptr->pointplace] = 0;
						hbc.currentplace = mid1;
					}
				}
			}
			else
			{
				if ((ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime + 24) < limittime)
				{
					if ((hbc.summoney + ptr->truecar[i].money) < minsum.summoney)
					{
						mid = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + 24;
						hbc.arrivetime = hbc.arrivetime + mid;
						hbc.linenum++;
						hbc.line[hbc.linenum] = ptr->truecar[i];
						mid2 = ptr->truecar[i].money;
						hbc.summoney = hbc.summoney + mid2;
						hbc.visited[ptr->pointplace] = 1;
						mid1 = hbc.currentplace;
						hbc.currentplace = ptr->pointplace;

						zan.push(hbc);

						hbc.arrivetime = hbc.arrivetime - mid;
						hbc.linenum--;
						hbc.summoney = hbc.summoney - mid2;
						hbc.visited[ptr->pointplace] = 0;
						hbc.currentplace = mid1;
					}
				}
			}
		}
		ptr = ptr->nextcar;
	}
	while (zan.empty() != true)
	{
		hold = zan.top();
		zan.pop();
		if (hold.currentplace == hold.endplace)
		{
			if ((hold.summoney < minsum.summoney) && (checktjd(hold.visited) == 1))
			{
				minsum = hold;
			}
		}
		ptr = mygraph.citymap[hold.currentplace].firstcar;
		while (NULL != ptr)
		{
			if (hold.visited[ptr->pointplace] != 1)
			{
				hbc = hold;
				for (i = 1; i <= ptr->carnum; i++)
				{
					if (((hbc.arrivetime % 24 + hbc.starttime) % 24) <= (ptr->truecar[i].starttime))
					{
						if ((ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime) < limittime)
						{
							if ((hbc.summoney + ptr->truecar[i].money) < minsum.summoney)
							{
								mid = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24);
								hbc.arrivetime = hbc.arrivetime + mid;
								hbc.linenum++;
								hbc.line[hbc.linenum] = ptr->truecar[i];
								mid1 = hbc.currentplace;
								hbc.currentplace = ptr->pointplace;
								hbc.visited[ptr->pointplace] = 1;
								mid2 = ptr->truecar[i].money;
								hbc.summoney = hbc.summoney + mid2;

								zan.push(hbc);

								hbc.arrivetime = hbc.arrivetime - mid;
								hbc.linenum--;
								hbc.currentplace = mid1;
								hbc.visited[ptr->pointplace] = 0;
								hbc.summoney = hbc.summoney - mid2;
							}
						}
					}
					else
					{
						if ((ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + hbc.arrivetime + 24) < limittime)
						{
							if ((hbc.summoney + ptr->truecar[i].money) < minsum.summoney)
							{
								mid = ptr->truecar[i].arrivetime - ((hbc.arrivetime % 24 + hbc.starttime) % 24) + 24;
								hbc.arrivetime = hbc.arrivetime + mid;
								hbc.linenum++;
								hbc.line[hbc.linenum] = ptr->truecar[i];
								mid1 = hbc.currentplace;
								hbc.currentplace = ptr->pointplace;
								hbc.visited[ptr->pointplace] = 1;
								mid2 = ptr->truecar[i].money;
								hbc.summoney = hbc.summoney + mid2;

								zan.push(hbc);

								hbc.arrivetime = hbc.arrivetime - mid;
								hbc.linenum--;
								hbc.currentplace = mid1;
								hbc.visited[ptr->pointplace] = 0;
								hbc.summoney = hbc.summoney - mid2;
							}
						}
					}
				}
			}
			ptr = ptr->nextcar;
		}
	}
	minsum.arrivetime = minsum.starttime + minsum.arrivetime;
	minsum.state = 1;
	minsum.currentplace = 1;
	minsum.strategy = 3;
	minsum.limittime = limittime;
	if (minsum.summoney == INFINITY)
	{
		minsum.startplace = a;
		minsum.endplace = b;
		minsum.starttime = starttime;
		minsum.arrivetime = 0;
		minsum.summoney = 0;
		minsum.linenum = 0;
		minsum.state = 3;
	}
	return minsum;
}






