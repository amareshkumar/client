#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>


using namespace std; 

mutex mtx; 
condition_variable cond;

int current = 1;

void print_even() {
	unique_lock <mutex> lock (mtx);
	
	for (; current < 20;) {
		cond.wait(lock, []() { return (current % 2 == 0);  });
		cout << "print_even: " << current << endl;
		current++;
		lock.unlock();
		cond.notify_all();
	}
}

void print_odd() {
	unique_lock <mutex> lock (mtx);
	for (; current < 20;) {
		cond.wait(lock, []() { return current % 2 == 1; });
		cout << "print_odd: " << current << endl;
		current++;
		lock.unlock();
		cond.notify_all();
	}
}

int main(int argc, char* argv[]) {
	thread th1(print_even);
	thread th2(print_odd);
	
	th1.join();
	th2.join();

	return 0;
}
