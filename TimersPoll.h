/*
 * File:   timer_poll.h
 * Author: Administrator
 */
#ifndef TIMER_POLL_H
#define TIMER_POLL_H
#include <sys/epoll.h>
#include <map>

#define MAXFDS 128

class Timer;

class TimersPoll {
public:
	TimersPoll(int max_num = 128) {
		active = 1;
		epfd = epoll_create(max_num);
	}
	int timers_poll_add_timer(Timer *ptimer);
	int timers_poll_del_timer(Timer *ptimer);
	void loop();
	void timers_poll_deactive() {
		active = 0;
	}
	~ TimersPoll() {
	}
private:
	int epfd;
	int active;
	std::map<int, Timer*> timers_map;
	/* data */
};
#endif /* TIMER_POLL_H */
