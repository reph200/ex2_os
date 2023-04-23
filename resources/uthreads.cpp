#include<iostream>
#include<list>
#include <algorithm>
#include "uthreads.h"
using namespace std;
//TODO:ERROR messages
//TODO:actually run and jump from and save threads


typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5
address_t translate_address(address_t addr)
{
  address_t ret;
  asm volatile("xor    %%gs:0x18,%0\n"
               "rol    $0x9,%0\n"
  : "=g" (ret)
  : "0" (addr));
  return ret;
}
sigjmp_buf env[MAX_THREAD_NUM];

int general_quantom_size;
int running_remaning_quantom;

list<int> available_ids;
for (int i = 1; i <= MAX_THREAD_NUM; i++)
{
  available_ids.push_back(i);
}

sigjmp_buf env[MAX_THREAD_NUM];
enum Thread_State
{
    Running, Ready, Blocked
};

struct Thread
{
    int id;
    Thread_State state;
    char *sp;

};
list <Thread> *thread_list;
list <Thread> *ready_list;
Thread *running_thread;
Thread main_thread;
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



int id = 0;
int get_available_id ()
{
  if(available_ids.empty())
  {
    return -1;
  }
  id = available_ids.front();
  available_ids.pop_front();
  return id;
}

int uthread_init (int quantum_usecs)
{
  if (quantum_usecs < 0)
  {
    return -1;
  }
  main_thread = {0, Running};
  running_thread = &main_thread;
  thread_list = new list<Thread> ()
  ready_list = new list<Thread> ()
  return 0;
}

int uthread_spawn (thread_entry_point entry_point)
{
  int id = get_available_id();
  if (id == -1 || entry_point == NULL)
  {
    return -1;
  }
  char *stack = new char[STACK_SIZE];
  setup_thread (id, stack, entry_point);
  Thread * new_thread = new Thread {id, Ready, stack};
  thread_list->push_back (new_thread);
  ready_list->push_back (new_thread);
  return id;
}

int uthread_terminate (int tid)
{
  auto target_thread = std::find_if (thread_list->begin (), thread_list->end
  (),
                                     [&] (const Thread &t)
                                     { return t.id == tid; });
  if (target_thread != thread_list->end ())
  {
    return -1;
  }
  else if (tid == 0)
  {
    for (auto& thread : *thread_list)
    {
      ready_list->remove (thread);
      thread_list->remove (thread);
      delete[] thread.sp;
      delete thread;
    }
    delete ready_list;
    delete thread_list;
    return 0;
  }
  else
  {
    int new_available_id = target_thread->id;
    ready_list->remove (target_thread);
    thread_list->remove (target_thread);
    delete[] target_thread->sp;
    delete target_thread;
    auto it = std::lower_bound(available_ids.begin(), available_ids.end(), nwe_available_id);
    available_ids.insert(it, new_available_id);
    return 0;
  }
}
int uthread_block (int tid)
{
  if (tid == 0)
  {
    return -1;
  }
  if (tid == running_thread.id) // blocking itself
  {
    target_thread.state = Blocked;
    running_thread = &ready_list->front();
    ready_list->pop_front();
    running_thread->state = Running;
    return 0;
  }
  auto target_thread = std::find_if(thread_list.begin(), thread_list.end(),
                         [&](const Thread& t) { return t.id == tid; });

  if (target_thread != thread_list->end()) {
    if(target_thread->state == Blocked)
    {
      return 0;
    }
    target_thread->state = Blocked;
    ready_list->remove(target_thread);
  } else {
    return -1;
  }
  return 0;
}


int uthread_resume(int tid)
{
  auto target_thread = std::find_if(thread_list.begin(), thread_list.end(),
                                    [&](const Thread& t) { return t.id == tid; });

  if (target_thread != thread_list.end()) {
    if(target_thread->state != Blocked)
    {
      return 0;
    }
    target_thread->state = Ready;
    ready_list->push_back(target_thread);
  } else {
    return -1;
  }
  return 0;
}

int uthread_get_tid()
{
  return running_thread->id;
}