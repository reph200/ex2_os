#include<iostream>
#include<list>
#include "uthreads.h"
using namespace std;

int general_quantom_size;
int running_remaning_quantom;
int next_id = 0;

enum Thread_State
{
    Running, Ready, Blocked
};

struct Thread
{
    int id;
    Thread_State state;

} Thread;

void setup_thread (int tid, char *stack, thread_entry_point entry_point)
{
  // initializes env[tid] to use the right stack, and to run from the function 'entry_point', when we'll use
  // siglongjmp to jump into the thread.
  address_t sp = (address_t) stack + STACK_SIZE - sizeof (address_t);
  address_t pc = (address_t) entry_point;
  sigsetjmp (env[tid], 1);
  (env[tid]->__jmpbuf)[JB_SP] = translate_address (sp);
  (env[tid]->__jmpbuf)[JB_PC] = translate_address (pc);
  sigemptyset (&env[tid]->__saved_mask);
}

list <Thread> *thread_list;
list <Thread> *ready_list;
Thread running_thread;
Thread main_thread;

id = 0;
void calulate_next_available_id ()
{
  next_id++;
  //notice!!!
}

int uthread_init (int quantum_usecs)
{
  if (quantum_usecs < 0)
  {
    return -1;
  }
  Thread main_thread{next_id, Running};
  calulate_next_available_id ();
  running_thread = main_thread;
  thread_list = new list<Thread> ()
  ready_list = new list<Thread> ()
  return 0;
}

int uthread_spawn (thread_entry_point entry_point)
{
  if (next_id > 100 || entry_point == NULL)
  {
    return -1;
  }
  char *stack = new char[STACK_SIZE];
  setup_thread (next_id, stack, entry_point);
  Thread *new_thread = new Thread (next_id, Ready);
  thread_list->push_back(new_thread);
  ready_list->push_back(new_thread);
  id = next_id;
  calulate_next_available_id ();
  return id;
}