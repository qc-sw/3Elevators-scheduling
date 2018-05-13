#include "Elevator.h"

extern Passenger man[1005];
Elevator::Elevator() {}
Elevator::~Elevator(){}
int Elevator::currentTime() {
	return time;
}
int Elevator::currentFloor() {
	return floor;
}
bool Elevator::isEmpty() {
	if (load == 0) return 1;
	return 0;
}
void Elevator::get(int index) {
	man[index].status = "in";
	status = 0;
	load++;
	ofstream outfile2("./output2.txt", ios::app);
	outfile2 << time << " " << floor << endl;
	outfile2.close();
	//cout << "Elevator 2 in time" << time << " get in floor" << floor << endl;//待删除
}
void Elevator::put(int n, int index_of_man) {
	load -= n;
	man[index_of_man].status = "out";
	status = 0;
	ofstream outfile2("./output2.txt", ios::app);
	outfile2 << time << " " << floor << endl;
	outfile2.close();
	//cout << "Elevator 2 in time" << time << " put in floor" << floor << endl;//待删除
	n = 1;
	while(destination_queue[2].empty())
		destination_queue[2].pop();
}
int Elevator::numToPut(int index ) {
	int ans = 0;
	for (int i = 1;i<=index;i++) {
		if (floor == man[i].destination&&man[i].status == "in")
			ans++;
	}
	return ans;
}
bool Elevator::stop(int index) {
	return true;
}
bool ElevatorOdd::stop(int index) {
	if (man[index].location % 2 + man[index].destination % 2 == 2)
		return true;
	return false;
}
bool ElevatorEven::stop(int index) {
	if (man[index].location % 2 + man[index].destination % 2 == 0 || man[index].location == 1 && man[index].destination % 2 == 0 || man[index].location % 2 == 0 && man[index].destination == 1)
		return true;
	return false;
}
void ElevatorOdd::get(int index) {
	man[index].status = "in";
	status = 0;
	load++;
	ofstream outfile1("./output1.txt", ios::app);
	outfile1 << time << " " << floor << endl;
	outfile1.close();
	//cout << "Elevator 1 in time" << time << " get in floor" << floor << endl;//待删除
}
void ElevatorOdd::put(int n, int index) {
	load -= n;
	man[index].status = "out";
	status = 0;
	ofstream outfile1("./output1.txt", ios::app);
	outfile1 << time << " " << floor << endl;
	outfile1.close();
	//cout << "Elevator 1 in time" << time << " put in floor" << floor << endl;//待删除
	n = 1;
	while (destination_queue[2].empty())
		destination_queue[1].pop();
}
void ElevatorEven::get(int index) {
	man[index].status = "in";
	status = 0;
	load++;
	ofstream outfile3("./output3.txt", ios::app);
	outfile3 << time << " " << floor << endl;
	outfile3.close();
	//cout << "Elevator 3 in time" << time << " get in floor" << floor << endl;//待删除
}
void ElevatorEven::put(int n, int index) {
	load -= n;
	man[index].status = "out";
	status = 0;
	ofstream outfile3("./output3.txt", ios::app);
	outfile3 << time << " " << floor << endl;
	outfile3.close();
	//cout << "Elevator 3 in time" << time << " put in floor" << floor << endl;//待删除
	n = 1;
	while (destination_queue[2].empty())
		destination_queue[3].pop();
}
int Elevator::priority(int index) {
	if (!stop(index))
	{
		Priority = -1;
		return Priority;
	}
	if (man[index].direction == direction)
		Priority = 1;

	return Priority;
}
void Elevator::run(int index,int i) {
	if (destination_queue[i].empty())
		return;
	//还没接到客前
	if (man[index].status == "wait")
	{
		
		if (man[index].location > floor)
		{
			floor++;
			status = 1;
		}
		else
			if (man[index].location < floor)
			{
				floor--;
				status = 1;
			}
			else
				if (man[index].location == floor )
				{
					if (status == 0)
					{
						load++;
						man[index].status = "in";
					}
					else
						get(index);
				}
	}
	else	//接到客后
		if (man[index].status == "in")
		{
			if (destination_queue[i].front() > floor)
			{
				floor++;
				status = 1;
			}
			else
				if (destination_queue[i].front() < floor)
				{
					floor--;
					status = 1;
				}
				else
					if (destination_queue[i].front() == floor && man[index].status == "in")
						put(numToPut(index), index);
			
		}
}
void ElevatorOdd::run(int index, int i) {
	if (destination_queue[i].empty())
		return;
	//还没接到客前
	if (man[index].status == "wait")
	{

		if (man[index].location > floor)
		{
			floor++;
			status = 1;
		}
		else
			if (man[index].location < floor)
			{
				floor--;
				status = 1;
			}
			else
				if (man[index].location == floor)
				{
					if (status == 0)
					{
						load++;
						man[index].status = "in";
					}
					else
						get(index);
				}
	}
	else	//接到客后
		if (man[index].status == "in")
		{
			if (destination_queue[i].front() > floor)
			{
				floor++;
				status = 1;
			}
			else
				if (destination_queue[i].front() < floor)
				{
					floor--;
					status = 1;
				}
				else
					if (destination_queue[i].front() == floor && man[index].status == "in")
						put(numToPut(index), index);

		}
}
void ElevatorEven::run(int index, int i) {
	if (destination_queue[i].empty())
		return;
	//还没接到客前
	if (man[index].status == "wait")
	{

		if (man[index].location > floor)
		{
			floor++;
			status = 1;
		}
		else
			if (man[index].location < floor)
			{
				floor--;
				status = 1;
			}
			else
				if (man[index].location == floor)
				{
					if (status == 0)
					{
						load++;
						man[index].status = "in";
					}
					else
						get(index);
				}
	}
	else	//接到客后
		if (man[index].status == "in")
		{
			if (destination_queue[i].front() > floor)
			{
				floor++;
				status = 1;
			}
			else
				if (destination_queue[i].front() < floor)
				{
					floor--;
					status = 1;
				}
				else
					if (destination_queue[i].front() == floor && man[index].status == "in")
						put(numToPut(index), index);

		}
}