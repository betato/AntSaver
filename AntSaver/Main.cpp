#include "Application.h"

int main()
{
	Application app = Application(60, 6000);
	app.runLoop();

	return 0;
}
