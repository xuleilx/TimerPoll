# TimerPoll
Use One epoll to select which timer is expired.
timerfd is impl in Kernel.

# Compile
g++ main.cpp timer_poll.cpp -lpthread

# Comment
一个线程使用epoll去等待，注册监听所有的timerfd。
