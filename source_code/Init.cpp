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
		cout << "时刻表配置文件读取错误！" << endl;
	}
	
	map<string,int> City;
	City["北京"] = 1; 
	City["哈尔滨"] = 2;
	City["沈阳"] = 3;
	City["上海"] = 4;
	City["广州"] = 5;
	City["昆明"] = 6;
	City["成都"] = 7;
	City["西安"] = 8;
	City["拉萨"] = 9;
	City["乌鲁木齐"] = 10;

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
