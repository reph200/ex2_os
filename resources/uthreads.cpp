#include<iostream>
#include<list>
#include "uthreads.h"
using namespace std;

int general_quantom_size;
int running_remaning_quantom;
enum Thread_State
{
    Running, Ready, Blocked
};

struct Thread
{
    int id;
    Thread_State state;

} Thread;

list <Thread> thread_list;
list <Thread> ready_list;
Thread running_thread;
Thread main_thread;
main_thread.
id = 0;
int uthread_init (int quantum_usecs)
{

}