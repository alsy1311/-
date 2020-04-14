#include<iostream>
#include<string>
#include<thread>
#include<vector>
#include<thread>
#include<set>
#include <functional>
#include <algorithm>
#include <mutex>
std::mutex		   mutex;
void find(size_t s, int& result, std::string findStr) {
	std::lock_guard < std::mutex > lock(mutex);
	result = 0;
	std::string str("AGTCAAAGTCGGAGTCTTAGTCCCAGTC");
	result = str.find(findStr,s);
	//std::cout << result << std::endl;
}
void parallel(size_t N, std::string findStr ) {
	const std::size_t length = N;
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t num_threads = hardware_threads != 0 ? hardware_threads : 2;
	std::size_t block_size = length / num_threads + 1;
	std::vector < int > results(num_threads + 1);
	std::vector < std::thread > threads;
	for (std::size_t i = 0; i < num_threads ; ++i) {
		threads.push_back(std::thread(find, i * block_size, std::ref(results[i]), findStr));
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	std::set <int> myset;
	for (int i = 0; i < results.size(); i++) {
		myset.insert(results[i]);
		
	}

	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
	{
		std::cout << *it << ' ';
	}
}
int main() {
	parallel(19, "AGTC");
	return 0;
}