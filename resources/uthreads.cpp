#include<iostream>
#include<list>
#include "uthreads.h"
using namespace std;

int general_quantom_size;
int running_remaning_quantom;
int next_id;

enum Thread_State
{
    Running, Ready, Blocked
};

struct Thread
{
    int id;
    Thread_State state;

} Thread;

void setup_thread(int tid, char *stack, thread_entry_point entry_point)
{
  // initializes env[tid] to use the right stack, and to run from the function 'entry_point', when we'll use
  // siglongjmp to jump into the thread.
  address_t sp = (address_t) stack + STACK_SIZE - sizeof(address_t);
  address_t pc = (address_t) entry_point;
  sigsetjmp(env[tid], 1);
  (env[tid]->__jmpbuf)[JB_SP] = translate_address(sp);
  (env[tid]->__jmpbuf)[JB_PC] = translate_address(pc);
  sigemptyset(&env[tid]->__saved_mask);
}


list <Thread> thread_list;
list <Thread> ready_list;
Thread running_thread;
Thread main_thread;

id = 0;
int uthread_init (int quantum_usecs)
{
  setup_thread(0, NULL, NULL);
}