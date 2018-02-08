#include<bits/stdc++.h>
#include <sys/wait.h>
#include  <sys/types.h>
#include<unistd.h>
using namespace std;
#define msize 100

void str_to_words(string cmd,string strWords[]){
 	int counter=0;
 	for (int i = 0; i<cmd.length(); i++){
    if (cmd[i] == ' ')
        counter++;
    else
        strWords[counter] += cmd[i];
	}
}

void  execute_pr(char **argv)
{
     pid_t  prid;
     int    status;

     if ((prid = fork()) < 0) {     /* fork child process */
          cout<<"*****ERROR: Forking Child Failed*****"<<endl;
          exit(1);
     }
     else if (prid == 0) {          /* for the child process:         */
          if (execvp(*argv,argv)<0) {     /* run command  */
               cout<<"*****ERROR: EXEC FAILED*****"<<endl;
               exit(1);
          }
     }
     else {                                  /* for parent:  */
          while (wait(&status) != prid)      /* wait for completion  */
               ;
     }
}

int main(){
	while(1){
		cout<<"@Group50:";
		string cmd;int rc;
		getline(cin,cmd);
		string strWords[msize];
		str_to_words(cmd,strWords);
		for (int i = 0; i < msize; ++i)
		{
			if(strWords[i]==""){
				rc=i;
				break;
			}
		}
		char *argv[rc+1];
		for (int i = 0; i < rc; ++i) { 
			char* name = new char[20];
			for (int j = 0; j < strWords[i].length(); j++) {
				name[j] = strWords[i][j];
			}
			name[strWords[i].length()] = '\0';
			argv[i] = name;
		}
		argv[rc] = '\0';
		 if (strWords[0]=="quit")  
              exit(0);      

          execute_pr(argv); 
}
}