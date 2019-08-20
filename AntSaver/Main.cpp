#include "Application.h"

int main()
{
	Application app = Application(60, 10000);
	app.runLoop();

	return 0;
}
