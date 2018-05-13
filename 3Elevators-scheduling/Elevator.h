#ifndef _STDIO_H_
#define _STDIO_H_
#include<string>
#include<queue>
#include<iostream>
#include<fstream>
using namespace std;
extern queue  <int> destination_queue[4];							//�������
extern int time;
struct Passenger												//�����˿ͽṹ��
	{
		int ask_time, location, destination, direction;
		string status = "unknown";
	};
class Elevator
{
public:
	int floor = 1;												//��ǰ¥��
	int floor_last_second=1;									//��һ�����λ��
	int direction;											//���з���(1��0��)
	int load=0;												//��ǰ����
	int status = 0;										//0Ϊͣ����1Ϊ����
	int Priority = 0;										//��������Ȩ
	Elevator() ;
	~Elevator();
	int currentTime();										//��ʾ��ǰʱ��
	int currentFloor();										//��ʾ��ǰ¥��
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