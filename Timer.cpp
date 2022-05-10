/*
 * Timer.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: xuleilx
 */
#include"Timer.h"

using namespace std;

Timer::Timer(const Timer& ptimer) {
	timer_internal = ptimer.timer_internal;
	cb = ptimer.cb;
	timer_id = ptimer.timer_id;
	repeat = ptimer.repeat;
}
Timer & Timer::operator =(const Timer& ptimer) {
	if (this == &ptimer) {
		return *this;
	}
	timer_internal = ptimer.timer_internal;
	cb = ptimer.cb;
	timer_id = ptimer.timer_id;
	repeat = ptimer.repeat;
	return *this;
}
int Timer::timer_start() {
	struct itimerspec ptime_internal = { 0 };
	ptime_internal.it_value.tv_sec = (int) timer_internal;
	ptime_internal.it_value.tv_nsec = (timer_internal - (int) timer_internal)
			* 1000000;
	if (repeat) {
		ptime_internal.it_interval.tv_sec = ptime_internal.it_value.tv_sec;
		ptime_internal.it_interval.tv_nsec = ptime_internal.it_value.tv_nsec;
	}

	timerfd_settime(timer_id, 0, &ptime_internal, NULL);
	return 0;
}
int Timer::timer_stop() {
	int ret = 0;

	if(timer_id != -1)
	{
		ret = close(timer_id);
		timer_id = -1;
	}
	return ret;
}
int Timer::timer_modify_internal(double timer_internal) {
	this->timer_internal = timer_internal;
	return timer_start();
}



