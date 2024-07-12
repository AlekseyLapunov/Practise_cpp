#include <iostream>
#include <thread>

static bool sFinished = false;

void doWork()
{
	std::cout << "Started thread id = " << std::this_thread::get_id() << "\n";

	while (!sFinished)
	{
		using namespace std::literals::chrono_literals;
		std::cout << "Working...\n";
		std::this_thread::sleep_for(1s);
	}
}

int main()
{
	std::thread worker(doWork);

	std::cin.get();
	sFinished = true;

	if (worker.joinable())
		worker.join();

	std::cout << "Finished!\n";
	std::cout << "Started thread id = " << std::this_thread::get_id() << "\n";

	std::cin.get();
}




