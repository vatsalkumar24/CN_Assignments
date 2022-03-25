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

  char s[100];
  strcpy(s,"hello c1");
  int x = write(1,s,sizeof(s)+1);
  if(x>0) cout<<"Message sent"<<endl;
  else cout<<"Message not sent"<<endl;
}