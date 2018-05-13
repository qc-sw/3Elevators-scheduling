#include"Elevator.h"
#include<Windows.h>
int time=1;
queue <int> destination_queue[4];							//请求队列(为了方便建四个)
Passenger man[1005];
ifstream infile("input.txt");
ofstream outfile1("output1.txt");
ofstream outfile2("output2.txt");
ofstream outfile3("output3.txt");
int main() {
	outfile1.clear();
	outfile1.close();
	outfile2.clear();
	outfile2.close();
	outfile3.clear();
	outfile3.close();
	Elevator elevator;
	ElevatorOdd elevatorOdd;
	ElevatorEven elevatorEven;
	int n = 0, index[4] = { 0,0,0,0 }, max_time = 0;
	infile >> n;
	//读取数据
	for (int i = 1;i <= n;i++) {
		infile >> man[i].ask_time >> man[i].location >> man[i].destination;
		max_time = man[i].ask_time;
		if (man[i].destination - man[i].location > 0)
			man[i].direction = 1;
		else
			man[i].direction = 0;
	}
	infile.close();
	//给第0个乘客的终点赋值1
	man[0].destination = 1;						
	//时间轴外圈循环(max_time+20保证每个乘客都到达目的地)
	for (time = 1;time <= max_time + 20;++time) {
    	 //改变乘客状态并对等待乘客入列处理
		for (int i = 1;i <= n;i++) 		
			if (time == man[i].ask_time&&man[i].status=="unknown")
			{			
				man[i].status = "wait";
				//从二号电梯开始判断是否队列为空，若都为空或不能接客，则由2号电梯接客；
				if (destination_queue[2].empty())
				{
					destination_queue[2].push(man[i].destination);
					index[2] = i;
				}
				else
					if (destination_queue[1].empty() && elevatorOdd.stop(i))
					{
						destination_queue[1].push(man[i].destination);
						index[1] = i;
					}
					else
						if (destination_queue[3].empty() && elevatorEven.stop(i))
						{
							destination_queue[3].push(man[i].destination);
							index[3] = i;
						}
						else
						{
							destination_queue[2].push(man[i].destination);
							index[2] = i;
						}
			}
		//如果三个请求队列均为空，时间轴向前
		if (destination_queue[1].empty()&&destination_queue[2].empty()&&destination_queue[3].empty())
			continue;
		//否则电梯必定运行
		else
		{	
			elevatorOdd.run(index[1], 1);
			elevator.run(index[2], 2);
			elevatorEven.run(index[3], 3);
			/*
			if (elevatorOdd.priority(index[1]) > elevator.priority(index[1]) && elevatorOdd.priority(index[1]) > elevatorEven.priority(index[1]))
			{
				cout << time << " run 1" << endl;
				elevatorOdd.run(index[1], 1);
			}
			else
				if (elevatorEven.priority(index[3]) > elevator.priority(index[3]) && elevatorEven.priority(index[3]) > elevatorOdd.priority(index[3]))
				{
					cout << time << " run 3" << endl;
					elevatorEven.run(index[3], 3);
				}
			else
			{
				cout << time << " run 2" << endl;
				elevator.run(index[2], 2);
			}
			*/

		}
		
	}
	system("pause");
	return 0;
}