#include "basis.h" 

int Initialize()
{
	Car *p,*ptr;
	realcar a,b;
	string city1,city2;
	ifstream init;
	init.open("text.txt");
	if (init.fail())
	{
		cout << "ʱ�̱������ļ���ȡ����" << endl;
	}
	
	map<string,int> City;
	City["����"] = 1; 
	City["������"] = 2;
	City["����"] = 3;
	City["�Ϻ�"] = 4;
	City["����"] = 5;
	City["����"] = 6;
	City["�ɶ�"] = 7;
	City["����"] = 8;
	City["����"] = 9;
	City["��³ľ��"] = 10;

	mygraph.places = VEXNUM;
	mygraph.cars = 0;
	
	//cout << "***";
	init >> b.line >> city1 >> city2 >> b.starttime >> b.arrivetime >> b.money >> b.kind;
	b.beginplace = City[city1];
	b.toplace = City[city2];
	mygraph.cars++;
	while(!init.eof())
	{
		a = b;
		p = new Car;
		p->pointplace = a.toplace;
		p->nextcar = NULL;
		p->minmoney = a;
		p->carnum = 1;
		p->truecar[1] = a;
		mygraph.citymap[a.beginplace].firstcar = p;
		mygraph.citymap[a.beginplace].name = cityname[a.beginplace];
		ptr = p;
		while (!init.eof())
		{
			init >> b.line >> city1 >> city2 >> b.starttime >> b.arrivetime >> b.money >> b.kind;
			b.beginplace = City[city1];
			b.toplace = City[city2];
			mygraph.cars++;
			if (b.beginplace == a.beginplace)
			{
				if (b.toplace == a.toplace)
				{
					ptr->carnum++;
					ptr->truecar[ptr->carnum] = b;
					if (b.money < ptr->minmoney.money)
					{
						ptr->minmoney = b;
					}
				}
				else
				{
					p = new Car;
					p->pointplace = b.toplace;
					p->nextcar = NULL;
					p->minmoney = b;
					p->carnum = 1;
					p->truecar[1] = b;
					ptr->nextcar = p;
					ptr = p;
					a = b;
				}
			}
			else
			{
				break;
			}
		}
	}
	init.close();
	dijkstra();
    return OK;
}
