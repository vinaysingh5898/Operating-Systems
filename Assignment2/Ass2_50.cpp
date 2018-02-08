#include<bits/stdc++.h>
#include <sys/wait.h>
#include  <sys/types.h>
#include<unistd.h>
#include <errno.h>
#include <fcntl.h>
#include<stdio.h>
#include <sys/stat.h>
#include <termios.h>
#include<string.h>
#include<stdio.h>
using namespace std;
#define msize 100
#define LIMIT 256 
#define MAX_LINE 1024

void str_to_words(string cmd,string strWords[]){
 	int counter=0;
 	for (int i = 0; i<cmd.length(); i++){
	    if (cmd[i] == ' ')
	        counter++;
	    else
	        strWords[counter] += cmd[i];
	}
}

void str_to_words1(string cmd,string strWords[]){
 	int counter=0;
 	for (int i = 0; i<cmd.length(); i++){
	    if (cmd[i] == ' ')
	        counter++;
	    else
	    {
	    	if(cmd[i]=='&') break;
	        strWords[counter] += cmd[i];
	    }
	}
}

void  execute_pr1(char **argv)
{
     pid_t  prid;
     int    status;
     cout <<**argv;
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
        /*  while (wait(&status) != prid)       wait for completion  
               ;*/
     }
}

void repair(char * string)
{
        int last_index,last_space_index;
        int i,j;
        last_space_index = 0;
        while(string[last_space_index] == ' ' || string[last_space_index] == '\t' || string[last_space_index] == '\n')
        {
                last_space_index++;
        }
        i = 0;
        while(string[i + last_space_index] != '\0')
        {
                string[i] = string[i + last_space_index];
                i++;
        }
        string[i]='\0'; 
        i=0;
        while(string[i]!='\0')
        {
                if(string[i] != ' ' && string[i] != '\t' && string[i] != '\n')
                {
                	last_index = i;
                }
           i++;
        }
        string[last_index + 1]='\0';
}

char** initial_fun1(){
	string cmd_input;int rc;
	getline(cin,cmd_input);
	string strWords[msize];
	str_to_words1(cmd_input,strWords);

	for (int i = 0; i < msize; ++i)
	{
		if(strWords[i]==""){
			rc=i;
			break;
		}
	}
	char** argv = new char*[rc+1];
	for (int i = 0; i < rc; ++i) { 
		char* name = new char[20];
		for (int j = 0; j < strWords[i].length(); j++) {
			if(strWords[i][j]=='&') break;
			name[j] = strWords[i][j];
		}
		name[strWords[i].length()] = '\0';
		argv[i] = name;
	}
	argv[rc] = '\0';
	return argv;
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

char** initial_fun(){
	string cmd_input;int rc;
	getline(cin,cmd_input);
	string strWords[msize];
	str_to_words(cmd_input,strWords);

	for (int i = 0; i < msize; ++i)
			{
				if(strWords[i]==""){
					rc=i;
					break;
				}
			}
			char** argv = new char*[rc+1];
			for (int i = 0; i < rc; ++i) { 
				char* name = new char[20];
				for (int j = 0; j < strWords[i].length(); j++) {
					name[j] = strWords[i][j];
				}
				name[strWords[i].length()] = '\0';
				argv[i] = name;
			}
			argv[rc] = '\0';
			return argv;
	}

char** initial_fun2(string cmd_input){
	int rc;
	string strWords[msize];
	str_to_words(cmd_input,strWords);

	for (int i = 0; i < msize; ++i)
			{
				if(strWords[i]==""){
					rc=i;
					break;
				}
			}
			char** argv = new char*[rc+1];
			for (int i = 0; i < rc; ++i) { 
				char* name = new char[20];
				for (int j = 0; j < strWords[i].length(); j++) {
					name[j] = strWords[i][j];
				}
				name[strWords[i].length()] = '\0';
				argv[i] = name;
			}
			argv[rc] = '\0';
			return argv;
	}

int main(){
	while(1){
		int choice;
		//cin.clear();
		//cin.ignore(512,'\n');
		cout<<""<<endl;
		cout<<"1.Run an internal command "<<endl;
		cout<<"2.Run an external command "<<endl;
		cout<<"3.Run an external command by redirecting standard input from a file "<<endl;
		cout<<"4.Run an external command by redirecting standard output to a file"<<endl;
		cout<<"5.Run an external command in the background "<<endl;
		cout<<"6.Run several external commands in the pipe mode(give space after each '|') "<<endl;
		cout<<"7.Quit the shell "<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>choice;
		cin.clear();
    	cin.ignore(512, '\n');

		switch(choice){
			case 1:{
				cout<<""<<endl;
				cout<<"Now Enter an internal command"<<endl;
				//cout<<"@Group50:";
				system("echo $PWD");cout << "\033[1;32m$\033[0m";
				//cout<<current_path();
				//cin.ignore();
				char** argv=initial_fun();

				if(strcmp(argv[0],"mkdir")==0){
					if(mkdir(argv[1],0777))
					{
						cout<<"Error: "<<strerror(errno)<<endl;
					}
				}
				else if(strcmp(argv[0],"cd")==0){
	                if(chdir(argv[1]))
	    			{
	                   cout<<"Error: "<<strerror(errno)<<endl;
	                }

	            }
	            else if(strcmp(argv[0],"rmdir")==0){
	                if(rmdir(argv[1]))
	                {
	                    cout<<"Error: "<<strerror(errno)<<endl;
	                }
	            }
				break;
				}

			case 2:{
				cout<<""<<endl;
				cout<<"Now Enter an external command"<<endl;
				//cout<<"@Group50:";
				system("echo $PWD");cout << "\033[1;32m$\033[0m";
				//cin.ignore();
				char** argv=initial_fun();
				execute_pr(argv);
				break;
				}
			case 3:{
				int l;
				cout<<""<<endl;
				cout<<"Now Enter an external command by redirecting standard input from a file"<<endl;
				//cout<<"@Group50:";
				system("echo $PWD");cout << "\033[1;32m$\033[0m";
				string inp_redirect,fname,cmd;
				getline(cin,inp_redirect);
				l=inp_redirect.length();
				for(int i=0;i<inp_redirect.length();i++){
					if(inp_redirect[i]=='<'){
						int len=inp_redirect.length()-i-1;
						fname=inp_redirect.substr(i+1,len);
						cmd=inp_redirect.substr(0,i);
					}
				}
				
				char *inpfile = new char[fname.length() + 1];
				strcpy(inpfile, fname.c_str());
				
				char *str = new char[cmd.length() + 1];
				strcpy(str, cmd.c_str());
				repair(inpfile);
				repair(str);


                        int id = fork();
                        if(id==0) {
                                    int ifd = open(inpfile, O_RDONLY);
                                	if(ifd < 0)
                                    	fprintf(stderr, "Unable to open file\n");

                                	close(0);
                                	dup(ifd);
                                	close(ifd);

	                                char *argc[msize];
	                                //printf("%s\n",str);
	                                argc[0]=strtok(str," ");
	                                int ind=0;
	                                while(argc[++ind]=strtok(NULL," "));
	                                argc[ind]=NULL;
	                                execvp(argc[0],argc);
	                                perror("Error!!\n");
                        }
                        else{
                                if(inp_redirect[l-1]!='&') {
                                        wait(NULL);
                                }
                                else{
                                        printf("Process is running in the background!!\n");
                                }
                        }
				break;
				}
			case 4:{
				int l;
				cout<<""<<endl;
				cout<<"Now Enter an external command by redirecting standard output to a file"<<endl;
				//cout<<"@Group50:";
				system("echo $PWD");cout << "\033[1;32m$\033[0m";
				string inp_redirect,fname,cmd;
				getline(cin,inp_redirect);
				l=inp_redirect.length();
				for(int i=0;i<inp_redirect.length();i++){
					if(inp_redirect[i]=='>'){
						int len=inp_redirect.length()-i-1;
						fname=inp_redirect.substr(i+1,len);
						cmd=inp_redirect.substr(0,i);
					}
				}
				
				char *outfile = new char[fname.length() + 1];
				strcpy(outfile, fname.c_str());
				
				char *str = new char[cmd.length() + 1];
				strcpy(str, cmd.c_str());

				repair(str);
				repair(outfile);

                        int p_id = fork();
                        if(p_id==0) {
                                int op_fd = open(outfile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                            	if(op_fd < 0)
                                	fprintf(stderr, "Unable to open file\n");

                            	close(1);
                            	dup(op_fd);
                            	close(op_fd);

                                char *argc[msize];
                                //printf("%s\n",str);
                                argc[0]=strtok(str," ");
                                int ind=0;
                                while(argc[++ind]=strtok(NULL," "));
                                argc[ind]=NULL;
                                execvp(argc[0],argc);
                                perror("Error!\n");
                        }
                        else{
                                if(inp_redirect[l-1]!='&') {
                                        wait(NULL);
                                }
                                else{
                                        printf("Process is running in the background!!\n");
                                }
                        }
				break;
				}
			case 5:{
				cout<<""<<endl;
				cout<<"Now Enter an external command to run in background"<<endl;
				//cout<<"@Group50:";
				system("echo $PWD");cout << "\033[1;32m$\033[0m";
				//cin.ignore();
				char** argv=initial_fun1();
				execute_pr1(argv);
				break;
				}
			case 6:{
				string cmd_input_str;int count=0;
				int fd1[2],fd2[2];
				int j=0,i=0,k=0,l=0;
				int errr = -1;int p_id;
				int end_index = 0;
				char *arguments[256];
				char * tokens[msize];
				char line[MAX_LINE]; 
				int numTokens;

				cout<<""<<endl;
				cout<<"Now Enter a command to run several external commands in the pipe mode"<<endl;
				system("echo $PWD");cout << "\033[1;32m$\033[0m";	
	
				memset (line,'\0',MAX_LINE);
				fgets(line, MAX_LINE, stdin);
	
				if((tokens[0] = strtok(line," \n\t")) == NULL) continue;

				numTokens = 1;
				while((tokens[numTokens] = strtok(NULL," \n\t")) != NULL) numTokens++;

				while (tokens[l] != NULL){
						if (strcmp(tokens[l],"|") == 0){
							count++;
						}
						l++;
					}
				count=count+1;

				while (tokens[j] != NULL && end_index != 1){
						k = 0;
						while (strcmp(tokens[j],"|") != 0){
							arguments[k] = tokens[j];
							j++;	
							if (tokens[j] == NULL){
								end_index = 1;
								k++;
								break;
							}
							k++;
						}
						arguments[k] = NULL;
						j++;		

					for(int rd=0;rd<k;rd++){
						repair(arguments[rd]);
					}	

					if (i % 2 != 0){
						pipe(fd1); // for odd i
					}else{
						pipe(fd2); // for even i
					}
					
					p_id=fork();

					if(p_id==-1){			
						if (i != count - 1){
							if (i % 2 != 0){
								close(fd1[1]); // for odd i
							}else{
								close(fd2[1]); // for even i
							} 
						}			
						cout<<"Error in creating Child process"<<endl;
					}
					if(p_id==0){
						// For the first command
						if (i == 0){
							dup2(fd2[1], STDOUT_FILENO);
						}
						else if (i == count - 1){
							if (count % 2 == 0){ // for odd number of commands
								dup2(fd2[0],STDIN_FILENO);
							}else{ // for even number of commands
								dup2(fd1[0],STDIN_FILENO);
							}
						
						}else{ // for odd i
							if (i % 2 == 0){
								dup2(fd1[0],STDIN_FILENO); 
								dup2(fd2[1],STDOUT_FILENO);	
							}else{ // for even i
								dup2(fd2[0],STDIN_FILENO); 
								dup2(fd1[1],STDOUT_FILENO);			
							} 
						}
						
						if (execvp(arguments[0],arguments)==errr){
							kill(getpid(),SIGTERM);
						}		
					}
							
					if (i == 0){
						close(fd2[1]);
					}else if (i == count - 1){
						if (count % 2 != 0){					
							close(fd1[0]);
						}else{					
							close(fd2[0]);
						}
					}else{
						if (i % 2 != 0){					
							close(fd2[0]);
							close(fd1[1]);
						}else{					
							close(fd1[0]);
							close(fd2[1]);
						}
					}
					waitpid(p_id,NULL,0);			
					i++;	
				}
				break;
			}
			case 7:{
				cout<<"Are you sure(y/n)?"<<endl;
				char c;
				cin>>c;
				if(c=='y'||c=='Y'){
					exit(0);
				}else{
					
				}
				break;
			}	
			default:cout<<"Enter correct choice"<<endl;break;
		
			}
			//cout<<"just checking"<<endl;
				
	}
	return 0;
}	



