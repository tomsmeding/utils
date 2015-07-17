#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


int main(int argc,char **argv){
	ios_base::sync_with_stdio(false);
	if(argc<2){
		cerr<<"Usage: "<<argv[0]<<" <command...>"<<endl;
		return 1;
	}
	vector<char**> cmds;
	char **cmdstart=argv+1;
	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],";")!=0)continue;
		argv[i]=NULL;
		cmds.push_back(cmdstart);
		i++;
		cmdstart=argv+i;
	}
	if(*cmdstart!=NULL)cmds.push_back(cmdstart);
	pid_t pid;
	int status;
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
			cerr<<"q.seq: Command '";
			for(int i=0;cmdargv[i];i++){
				if(i!=0)cerr<<' ';
				cerr<<cmdargv[i];
			}
			cerr<<"' exited with status "<<status<<endl;
			return status;
		}
	}
	return 0;
}
