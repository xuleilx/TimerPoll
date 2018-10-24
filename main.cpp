/*
 * File:   main.cpp
 * Author: Administrator
 */
#include <cstdlib>
#include <iostream>
#include "Timer.h"
#include "TimersPoll.h"
using namespace std;

static TimersPoll my_timers(128);

class TestA{
public:
	TestA(){
		printf("Construct!\n");
		m_n=1;
		pm_timer = NULL;
	}
	virtual ~TestA(){
		printf("Destruct!\n");
		if(pm_timer!=NULL){
			delete pm_timer;
			pm_timer = NULL;
		}
	}
	void setN(int n){
		m_n=n;
	}
	void info(int n){
	    printf("info: %d\n",n);
	}
	void send(int n){
		pm_timer = new Timer(1.10, std::bind(&TestA::info,this,n), 0);
	    my_timers.timers_poll_add_timer(*pm_timer);
	}
private:
	int m_n;
	Timer *pm_timer;
};

int callback(int n)
{
    printf("timer %d\n",n);
    return 0;
}

void *thread_fun(void *data)
{
    TimersPoll *my_timers = (TimersPoll *)data;
    my_timers->loop();
}
/*
 *
 */
int main(int argc, char** argv)
{
	// 启动epoll多路选择器
    pthread_t thread_id = 0;
    pthread_create(&thread_id, NULL, thread_fun, &my_timers);
 
    // 普通函数作为callback
    Timer timer1(1.05, std::bind(callback,1), 0);
    my_timers.timers_poll_add_timer(timer1);

    // 类的成员函数作为callback
    TestA a;
    Timer timer2(1.10, std::bind(&TestA::info,&a,2), 0);
    my_timers.timers_poll_add_timer(timer2);

    // 类的成员函数中创建timer对象，并调用类的另一个成员函数
    a.send(3);

    sleep(5);

    // 修改定时器触发时间，如果定时器已经expired，会以设定的时间再触发一次。
    timer1.timer_modify_internal(5.1);
    cout<<"modify complete"<<endl;

    // 删除定时器
    my_timers.timers_poll_del_timer(timer2);
    cout<<"del complete"<<endl;

    sleep(4);

    // 终止定时器循环，epoll_wait()会等待直到下一次事件触发才推出，需要设置timeout
    my_timers.timers_poll_deactive();

    pthread_join(thread_id,NULL);
    return 0;
}
