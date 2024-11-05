#include <chrono>
#include <thread>
#include <iostream>

int main() {

	size_t N;
	std::cout << "Number of threads: "; std::cin >> N;
	double t_start = 0, t_join = 0;
	double t_start_max = 0, t_join_max = 0;
	for (size_t i = 0; i < N; ++i) {
		auto start = std::chrono::system_clock::now();
		auto thread_start = start;
		std::thread t([&]() {
			thread_start = std::chrono::system_clock::now();
		});
		t.join();
		auto end = std::chrono::system_clock::now();
		double t1 = std::chrono::duration<double>(end - start).count();
		double t2 = std::chrono::duration<double>(thread_start - start).count();
		t_join += t1;
		t_start += t2;
		t_join_max = std::max(t_join_max, t1);
		t_start_max = std::max(t_start_max, t2);

	}
	std::cout << "Average time to start a thread: " << t_start/N << '\n';
	std::cout << "Max time to start a thread: " << t_start_max << '\n';
	std::cout << "Average time to join a thread: " << t_join / N << '\n';
	std::cout << "Max time to join a thread: " << t_join_max << '\n';
	return 0;
}
