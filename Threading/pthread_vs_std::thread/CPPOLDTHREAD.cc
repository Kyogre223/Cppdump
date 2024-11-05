#include <pthread.h>
#include <iostream>
#include <chrono>



void threading() {

	
}
void* thread_function(void* arg) {
	
	threading();
	
	return ((void*)0);
}

int main() {
	size_t N;
	std::cout << "Number of threads using old POSIX call: "; std::cin >> N;

	double t_start = 0, t_join = 0;
	double t_start_max = 0, t_join_max = 0;
	

	for (size_t i = 0; i < N; ++i) {
		auto start = std::chrono::system_clock::now();
		auto thread_start = start;
		int err;
		pthread_t thread_id;
		err = pthread_create(&thread_id, NULL, thread_function, NULL);
		pthread_join(thread_id, NULL);
		auto end = std::chrono::system_clock::now();
		double diff = std::chrono::duration<double>(end - start).count();
		t_join_max = std::max(t_join_max, diff);
		t_join += diff;
	}
	std::cout << "Average time to join  a thread: " << t_join/N << '\n';
	std::cout << "Maximum time to join a thread: " << t_join_max << '\n';

	return 0;
}

