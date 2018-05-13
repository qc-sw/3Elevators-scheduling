#ifndef _STDIO_H_
#define _STDIO_H_
#include<string>
#include<queue>
#include<iostream>
#include<fstream>
using namespace std;
extern queue  <int> destination_queue[4];							//请求队列
extern int time;
struct Passenger												//建立乘客结构体
	{
		int ask_time, location, destination, direction;
		string status = "unknown";
	};
class Elevator
{
public:
	int floor = 1;												//当前楼层
	int floor_last_second=1;									//上一秒电梯位置
	int direction;											//运行方向(1上0下)
	int load=0;												//当前负载
	int status = 0;										//0为停留，1为运行
	int Priority = 0;										//优先运行权
	Elevator() ;
	~Elevator();
	int currentTime();										//显示当前时间
	int currentFloor();										//显示当前楼层
	void get(int index);
	void put(int n, int index_of_man);
	bool isEmpty();
	int numToPut(int index);
	bool stop(int index);
	int priority(int index);
	void run(int index,int i);
};
class ElevatorOdd :public Elevator
{
public:
	bool stop(int index);
	void get(int index);
	void put(int n, int index);
	void run(int index, int i);
};
class ElevatorEven :public Elevator
{
public:
	bool stop(int index);
	void get(int index);
	void put(int n, int index);
	void run(int index, int i);
};
#endif