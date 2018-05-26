#include"Elevator.h"
#include<Windows.h>
int time=1;
queue <int> destination_queue[4];							//�������(Ϊ�˷��㽨�ĸ�)
Passenger man[1005];
int main(int argc, char** argv) {
	if (argc == 5)
		;
	else if (argc >5)
	{
		printf("Too many arguments supplied.\n");
		return 0;
	}
	else
	{
		printf("%d argument expected.\n",5-argc);
		return 0;
	}
	ifstream infile(argv[1]);
	if (!infile) {
		cout << "fatal: there is no such file named" << argv[1];
		return 0;
	}
	ofstream outfile1(argv[2]);
	ofstream outfile2(argv[3]);
	ofstream outfile3(argv[4]);
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
	//��ȡ����
	for (int i = 1;i <= n;i++) {
		infile >> man[i].ask_time >> man[i].location >> man[i].destination;
		max_time = man[i].ask_time;
		if (man[i].destination - man[i].location > 0)
			man[i].direction = 1;
		else
			man[i].direction = 0;
	}
	infile.close();
	//����0���˿͵��յ㸳ֵ1
	man[0].destination = 1;						
	//ʱ������Ȧѭ��(max_time+30��֤ÿ���˿Ͷ�����Ŀ�ĵ�)
	for (time = 1;time <= max_time + 30;++time) {
    	 //�ı�˿�״̬���Եȴ��˿����д���
		for (int i = 1;i <= n;i++) 		
			if (time == man[i].ask_time&&man[i].status=="unknown")
			{			
				man[i].status = "wait";
				//�Ӷ��ŵ��ݿ�ʼ�ж��Ƿ����Ϊ�գ�����Ϊ�ջ��ܽӿͣ�����2�ŵ��ݽӿͣ�
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
		//�������������о�Ϊ�գ�ʱ������ǰ
		if (destination_queue[1].empty()&&destination_queue[2].empty()&&destination_queue[3].empty())
			continue;
		//������ݱض�����
		else
		{	
			elevatorOdd.run(index[1], 1);
			elevator.run(index[2], 2);
			elevatorEven.run(index[3], 3);
		}
		
	}
	cout << "The program runs successfully!" << endl;
	system("pause");
	return 0;
}