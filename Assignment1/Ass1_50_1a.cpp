#include<bits/stdc++.h>
using namespace std;
#include<unistd.h>
#include<time.h>
#include <cstdlib> 
#include <ctime> 
#include <iostream>



int main(int argc, char const *argv[])
{	srand((unsigned)time(0));
	
	int fd1[2];
	int arr1[100],arr2[100],arr3[100];

	if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
	
	pid_t pid=fork();
	if(pid==0){
		//child1
					for (int i = 0; i < 100; i++)
					{
						arr1[i]=(rand()%1000+200);
					}
					sort(arr1,arr1+100);
					for (int i = 0; i < 100; ++i)
					{
						cout<<arr1[i]<<" ";
					}
					cout<<endl;
					close(fd1[0]);
					write(fd1[1],arr1,100*sizeof(int));
					close(fd1[1]);		
		
	}
	
	else if(pid>0){
		//parent1
		pid_t pid1=fork();
		
		if(pid1==0){
			//child2
			for (int i = 0; i < 100; ++i)
				{
					arr2[i]=(rand()%600)+1;
				}
				sort(arr2,arr2+100);
				for (int i = 0; i < 100; ++i)
				{
					cout<<arr2[i]<<" ";
				}
				cout<<endl;
				close(fd1[0]);
				write(fd1[1],arr2,100*sizeof(int));
				close(fd1[1]);
		}

		else if(pid1>0){
			//parent2
			pid_t pid2=fork();
			
			if(pid2==0){
						//child3
				for (int i = 0; i < 100; ++i)
				{
					arr3[i]=(rand()%500)+50;
				}
				sort(arr3,arr3+100);
				for (int i = 0; i < 100; ++i)
				{
					cout<<arr3[i]<<" ";
				}
				cout<<endl;
				close(fd1[0]);
				write(fd1[1],arr3,100*sizeof(int));
				close(fd1[1]);
			}

			else if(pid2>0){
				//parent(4)
				close(fd1[1]);
				int op1[300];
				read(fd1[0],op1,100*sizeof(int));
				read(fd1[0],op1+100,100*sizeof(int));
				read(fd1[0],op1+200,100*sizeof(int));
				cout<<endl;
				cout<<"D:-"<<endl;
				sort(op1,op1+300);
				for (int i = 0; i < 300; ++i)
				{
					cout<<op1[i]<<" ";
				}
			}

			else{
				printf("fork failed\n");
			}
		}
		else{
			printf("fork failed\n");
		}
	}
	
	else{
		printf("fork failed\n");
	}

	return 0;
}