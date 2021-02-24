#include <iostream>
#include "WebPage.h"
#include "WebList.h"

using namespace std;

int main()
{
	// TODO: Command line arguments for filename, seconds
	// TODO: HTTP host
	WebList webList;
	
	webList.uploadList("test.txt");
	webList.checkAll();
	webList.saveLog();

	return 0;
}