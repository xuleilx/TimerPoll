/*
 * Timer.h
 *
 *  Created on: Oct 23, 2018
 *      Author: xuleilx
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <unistd.h>
#include <fcntl.h>
#include <sys/timerfd.h>
#include <functional>

typedef std::function<void()> timer_callback;

class Timer {
public:
	Timer() :
			timer_internal(0.0), cb(0), timer_id(0), repeat(0){
	}
	Timer(double internal_value, const timer_callback &callback,
			int rep) :
			timer_internal(internal_value), cb(callback), repeat(
					rep) {
		timer_id = timerfd_create(CLOCK_REALTIME, 0);
		setNonBlock(timer_id);
	}
	Timer(const Timer &ptimer);
	Timer & operator=(const Timer &ptimer);
	int timer_start();
	int timer_stop();
	int timer_modify_internal(double timer_internal);
	int timer_get_id() {
		return timer_id;
	}
	void runCallback() const{
		cb();
	}
	~Timer() {
		timer_stop();
	}
private:
	bool setNonBlock(int fd) {
		int flags = fcntl(fd, F_GETFL, 0);
		flags |= O_NONBLOCK;
		if (-1 == fcntl(fd, F_SETFL, flags)) {
			return false;
		}
		return true;
	}
	int timer_id;
	double timer_internal;
	bool repeat; //will the timer repeat or only once
	timer_callback cb;
};

#endif /* TIMER_H_ */
