#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

int main()
{
	auto printMessage = [](const string& message){
		cout << message << endl;
	};

	thread thread(printMessage, "Message from aa child thread.");
	printMessage("waiting thre child thread...");
	thread.join();

	return 0;
}
