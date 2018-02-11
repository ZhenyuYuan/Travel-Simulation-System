#include"basis.h"

int main()
{
	Initialize();
	InitWin();
	thread t1(settime);
	t1.detach();

	Operation();
	_getch();
	closegraph();
	return 0;
}
