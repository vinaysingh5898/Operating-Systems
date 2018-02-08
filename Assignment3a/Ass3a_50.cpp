#include<bits/stdc++.h>
using namespace std;

void line()
{
    for(int i=1;i<55;i++)
    	cout<<"--";
	cout<<"\n";
}

float find_avg(float val[],int n)
{	float sum=0,avg;
	for (int i = 0; i < n; ++i)
	{
		sum=sum+val[i];
	}
	avg=sum*1.0/n;
	return avg;
}

float fcfs(float at[],float bt[],int N)
{
	float ct[N],tat[N],sum=0,avg;
	ct[0]=at[0]+bt[0];

	for (int i = 1; i < N; ++i)
	{
		if(at[i]<ct[i-1])
		{
			ct[i]=ct[i-1]+bt[i];
		}
		else
		{
			ct[i]=at[i]+bt[i];
		}
	}
	//cout<<"FCFS"<<endl;
	for (int j = 0; j < N; j++)
	{
		tat[j]=ct[j]-at[j];
		sum=sum+tat[j];
		//cout<<tat[j]<<endl;
	}
	avg=sum/N;
	return avg;
}

float psjf(float at[], float bt[], int N){
    float rem[N], complete[N],min;
    float time = 0, sum, runtime, prev = time;
    int i, flag, z;
    
    for(int i = 0; i < N; i++){
        rem[i] = bt[i];
    }

    while(1){
        min = numeric_limits<float>::max();
        flag = numeric_limits<int>::max();

        for(i = 0; i < N && at[i] <= time; i++){
            if(rem[i] < min && rem[i] > 0){
                min = rem[i];
                flag = i;
            }
        }
        if(z == 1 && flag ==  numeric_limits<int>::max() ){time = at[i]; continue;}

        if( min == numeric_limits<float>::max() ){
            for(int j = 0; j < N; j++)
                sum+=complete[j] - at[j];
            return sum*1.0/N;
        }
        else{
            if(i < N){
                runtime = at[i] - time;
                if(runtime > min) {runtime = min;z = 1;}
                else z = 0;
            }
            else{
                runtime = min;
                z = 0; 
            }
            
            time+= runtime;
            rem[flag] -= runtime;
            if(rem[flag] == 0)complete[flag] = time;
        }
    }

}

float rrobin(float at[],float bt[],int N,float quantum)
{
	
	float temp[N],wt[N],tat[N],sum=0,avg;int t=0;
	for (int i = 0; i < N; ++i)
	{
		temp[i]=bt[i];
	}

	while(1)
	{
		bool done=true;
		for (int j = 0; j < N; j++)
		{
			if (temp[j]>0)
			{
				done=false;

				if (temp[j]>quantum)
				{
					t=t+quantum;
					temp[j]=temp[j]-quantum;
				}
				else
				{
					t=t+temp[j];
					wt[j]=t-bt[j];
					temp[j]=0;
				}
			}
		}

		if(done==true) break;
	}
	//cout<<"Rrobin"<<endl;
	for (int k = 0; k < N; k++)
	{
		tat[k]=wt[k]+bt[k];
		sum=sum+tat[k];
		//cout<<tat[k]<<endl;
	}
	avg=sum/N;
	return avg;

}

int main()
{	int N;
	srand(time(0));

	cout<<"Enter the number of processes"<<endl;
	cin>>N;
	//cout<<"Enter the quantum"<<endl;
	//cin>>quantum;
	
	float val_fcfs[10],val_rrobin1[10],val_psjf[10],val_rrobin2[10],val_rrobin5[10];

	for(int t=0;t<10;t++)
	{	//tr=0;
		float at[N],bt[N],avg_rrobin1,avg_fcfs,avg_psjf,avg_rrobin2,avg_rrobin5;
		at[0]=0;

		random_device rd;  //Will be used to obtain a seed for the random number engine
    	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    	uniform_real_distribution<> dis1(0,1);
    	uniform_int_distribution<> dis2(1,19);

		for(int i=1;i<N;i++)
		{
		//float r = ((double) rand()/(RAND_MAX));
		float x = (log(dis1(gen))/(-0.2));  //lambda=0.2
		at[i]=at[i-1]+fmod(x,10);
		//cout<<at[i]<<endl;
		}

		for(int j=0;j<N;j++){

			//float p=((double) rand()/(RAND_MAX));
			bt[j]=dis2(gen);
			//cout<<bt[j]<<endl;
		}

		//at[1]=0;at[2]=0;at[3]=0;at[4]=0;
		//bt[0]=4;bt[1]=2;bt[2]=5;bt[3]=1;bt[4]=3;
		avg_fcfs= fcfs(at,bt,N);
		avg_rrobin1= rrobin(at,bt,N,1);
		avg_rrobin2= rrobin(at,bt,N,2);
		avg_rrobin5= rrobin(at,bt,N,5);
		avg_psjf=psjf(at,bt,N);

		val_fcfs[t]=avg_fcfs;
		val_rrobin1[t]=avg_rrobin1;
		val_rrobin2[t]=avg_rrobin2;
		val_rrobin5[t]=avg_rrobin5;
		val_psjf[t]=avg_psjf;
		
	}
	
	ofstream myfile;
  	myfile.open ("output.txt",ios::app);
  	myfile<<N<<endl;
  	myfile <<find_avg(val_fcfs,10)<<endl;
  	myfile<<find_avg(val_rrobin1,10)<<endl;
  	myfile<<find_avg(val_rrobin2,10)<<endl;
  	myfile<<find_avg(val_rrobin5,10)<<endl;
  	myfile<<find_avg(val_psjf,10)<<endl;
  	myfile.close();
  	
	cout<<"\n\n\n";
	cout<<setw(49)<<"Turn around time( N="<<N<<" )"<<endl;
	line();
	cout<<setw(15)<<"Number of times"<<setw(14)<<"FCFS"<<setw(16)<<"RR(d=1)"<<setw(13)<<"RR(d=2)"<<setw(13)<<"RR(d=3)"<<setw(20)<<"Pre-emptive SJF"<<endl;
	line();
	for(int i=0;i<10;i++)
	{
	cout<<setw(11)<<i+1<<setw(20)<<val_fcfs[i]<<setw(13)<<val_rrobin1[i]<<setw(13)<<val_rrobin2[i]<<setw(13)<<val_rrobin5[i]<<setw(13)<<val_psjf[i]<<endl;
	}
	line();
	return 0;
}