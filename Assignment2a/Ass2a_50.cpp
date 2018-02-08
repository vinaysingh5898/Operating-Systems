#include<bits/stdc++.h>
#include <stdio.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<time.h>
#include<sys/wait.h>
using namespace std;

int isPrime(int num)
{
  for (int i=2; i<=num/2 ; i++) 
     if (num%i==0)
        return 0; //divider mod input number = 0 not prime

  return 1;
}

int main()
{
	int cloc = clock();
	int np,nc,shmid;
	//srand(time(0));
	shmid = shmget(IPC_PRIVATE, 7*sizeof(int), 0777|IPC_CREAT);
	
	cout<<"Enter No of Producer"<<endl;
	cin>>np;
	cout<<"Enter No of Consumer"<<endl;
	cin>>nc;
	int in=0,out=0;int *b;

	b = (int *) shmat(shmid, 0, 0);
	b[5]=0;b[6]=0;

	for(int j=0;j<nc;j++)
	{
			if(fork()==0){	
				srand(-getpid());
				while(1){
					int waitr=rand()%6;
					sleep(waitr);

					if(b[5]-b[6]){
					int x=b[b[6]%5];
					b[6]++;
					cout<<"Consumer "<<j+1<<":"<<x<<",time:"<<(clock())<<endl;

				}	
			}
		}
		
	}

	for (int i = 0; i<np; i++)
	{
		/* code */
		if(fork()==0){
				srand(-getpid());
				int waitr=rand()%6;
				sleep(waitr);

				while(1){
				int rd=rand()%1000000;
				if(isPrime(rd)==1){
					if(b[5]-b[6]<5){
					b[b[5]%5]=rd;
					b[5]++;
					cout<<"Producer "<<i+1<<":"<<rd<<",time:"<<(clock())<<endl;
				}
					break;
				}
			}
		}
	}

	sleep(30);
	kill(-getpid(),SIGKILL);

}