#ifndef TIMER_HPP
#define TIMER_HPP

#include <time.h>

class Timer {
	clock_t _start, _end;
public:
	Timer() :_start(0), _end(0) {}
	~Timer() {}

	void start() {
		_start = clock();
	}

	void end() {
		_end = clock();
	}

	void restart() {
		_start = _end = 0;
	}

	double count() {
		return (_end - _start) / (double)CLOCKS_PER_SEC;
	}
};

#endif // !TIMER_HPP