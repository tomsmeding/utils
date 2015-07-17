#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


int main(int argc,char **argv){
	ios_base::sync_with_stdio(false);
	if(argc<3){
		cerr<<"Usage: "<<argv[0]<<" <repcount> <command...>"<<endl;
		return 1;
	}
	unsigned long long int repcount=llabs(strtoll(argv[1],NULL,10));
	vector<char**> cmds;
	char **cmdstart=argv+2;
	for(int i=2;i<argc;i++){
		if(strcmp(argv[i],";")!=0)continue;
		argv[i]=NULL;
		cmds.push_back(cmdstart);
		i++;
		cmdstart=argv+i;
	}
	if(*cmdstart!=NULL)cmds.push_back(cmdstart);
	pid_t pid;
	int status;
	unsigned long long int iter;
	for(iter=0;iter<repcount;iter++){
		for(char **cmdargv : cmds){
			pid=fork();
			if(pid==-1){ //error
				perror("fork");
				return 2;
			}
			if(pid==0){ //child
				execvp(cmdargv[0],cmdargv);
				perror("execvp");
				return 2;
			}
			do wait(&status); while(!WIFEXITED(status));
			status=WEXITSTATUS(status);
			if(status!=0){
				cerr<<"q.repeat: Command '";
				for(int i=0;cmdargv[i];i++){
					if(i!=0)cerr<<' ';
					cerr<<cmdargv[i];
				}
				cerr<<"' exited with status "<<status<<" in iteration "<<iter<<endl;
				return status;
			}
		}
	}
	return 0;
}
