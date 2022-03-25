#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include <ctype.h>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;
int main()
{

  FILE *rd = popen("./c2","r");
  char buff[100];
  if(rd!= NULL)
  {
      int x = read(fileno(rd),buff, 100);
      if(x>0) cout<<"Message received: "<<buff<<endl;
      else cout<<"Message received failure"<<endl;
  }
  pclose(rd);
}