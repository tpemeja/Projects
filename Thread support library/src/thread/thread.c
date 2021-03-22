#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <ucontext.h>
#include <assert.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
//#include <valgrind/valgrind.h>
#include <sched.h>
#include "thread.h"
#include "list.h"

typedef struct my_thread my_thread_t;

//Structure de thread et de la liste de threads
struct my_thread{
  TAILQ_ENTRY(my_thread) field;
  ucontext_t*  uc;
  void * retval;
  int status_exit;
  int status_join;
  int valgrind_stackid;
  int priority;
  struct my_thread* before;
};

struct threads_list{
  my_thread_t * main;
  my_thread_t * activ;
  TAILQ_HEAD(queue, my_thread) queue;
};

struct threads_list* threads_list = NULL;

//******************************************************* Partie de gestion de la preemption **************************
#ifdef PREEMPT
#define PREEMPT_SIG SIGALRM
#define PREEMPT_TIME 10000000 //en ns donc 10ms
#define errExit(msg) {perror(msg);exit(0);}

static struct sigevent event;
static struct itimerspec its;
static timer_t timerid;
static sigset_t mask;
int enable_to_preempt = OFF;

//Fonction qui sera eXécution quand on recoit le signal de preemption
void preemtion_func(int signum){
    (void)signum;
    if(enable_to_preempt){
        printf("preemption\n");
        thread_yield();
    }
}
void update_timer(){
     its.it_value.tv_sec = 0;
     its.it_value.tv_nsec = PREEMPT_TIME; //10ms
     its.it_interval.tv_sec = 0;
     its.it_interval.tv_nsec = PREEMPT_TIME;
     if(timer_settime(timerid,0,&its,NULL) == ERROR)
        errExit("timer_settime\n");
}

//initialisation des données pour la préemption
void initialize_preemption(){
    sigemptyset(&mask);
    sigaddset(&mask,PREEMPT_SIG);
    struct sigaction sa;

    //mise en place du gestionnaire de signal SIGALARM
    sa.sa_handler = preemtion_func;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(PREEMPT_SIG,&sa,NULL) == ERROR)
        errExit("sigaction\n");

    //creation de l'event
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = PREEMPT_SIG;
    event.sigev_value.sival_ptr = &timerid;
    if(timer_create(CLOCK_THREAD_CPUTIME_ID/*CLOCK_REALTIME*/,&event,&timerid) == ERROR)
        errExit("timer_create\n");

    //mise en place du timer pour la preemption
    update_timer();
}

void enable_preemption(){
   enable_to_preempt=ON;
}

void disable_preemption(){
    enable_to_preempt = OFF;
}
#endif


//****************************************************** FONCTIONS INTERNES ***************************************
//creation d'un thread
my_thread_t * new_thread(){
  my_thread_t* tmp = (my_thread_t*)malloc(sizeof(struct my_thread));
  assert(tmp != NULL);
  ucontext_t * uc = (ucontext_t*)malloc(sizeof(ucontext_t));
  assert(uc != NULL);
  getcontext(uc);
  tmp->before = NULL;
  uc->uc_stack.ss_size = 64*1024;
  uc->uc_stack.ss_sp = malloc(uc->uc_stack.ss_size);
  //int valgrind_stackid = VALGRIND_STACK_REGISTER(uc->uc_stack.ss_sp,uc->uc_stack.ss_sp + uc->uc_stack.ss_size);
  int valgrind_stackid = 1;
  tmp->valgrind_stackid = valgrind_stackid;
  tmp->uc = uc;
  tmp->status_exit = OFF;
  tmp->status_join = OFF;
  tmp->priority = -1;
  return tmp;
}

//creation d'une thread pour le main

my_thread_t * new_main_thread(){
  my_thread_t* tmp = (my_thread_t*)malloc(sizeof(struct my_thread));
  assert(tmp != NULL);
  ucontext_t* uc = malloc(sizeof(ucontext_t));
  getcontext(uc);
  tmp->before = NULL;
  tmp->valgrind_stackid = -1;
  tmp->uc = uc;
  tmp->status_exit = OFF;
  tmp->status_join = OFF;
  tmp->priority = -1;
  return tmp;
}


//libération d'une thread
void free_mythread(my_thread_t* my_thread){
  if (my_thread == threads_list->main)
     return;
  //VALGRIND_STACK_DEREGISTER(my_thread->valgrind_stackid);
  free(my_thread->uc->uc_stack.ss_sp);
  free(my_thread->uc);
  free(my_thread);
  my_thread = NULL;
}

//libération du thread main
 void free_main(my_thread_t* my_thread){
      free(my_thread->uc);
      free(my_thread);
      my_thread = NULL;
  }

void thread_list_init() __attribute__((constructor));
void thread_list_free() __attribute__((destructor));

//initialisation de notre liste de thread
void thread_list_init() {
  threads_list = (struct threads_list*)malloc(sizeof(struct threads_list));
  TAILQ_INIT(&threads_list->queue);
  my_thread_t* new = new_main_thread();
  threads_list->main = new;
  threads_list->activ = new;
  TAILQ_INSERT_HEAD(&threads_list->queue,new,field);

#ifdef PREEMPT
  initialize_preemption();
  enable_preemption();
#endif
}

//libération de notre liste de thread
void thread_list_free(){
 #ifdef PREEMPT
 disable_preemption();
 #endif
 if(!TAILQ_EMPTY(&threads_list->queue)){
    my_thread_t *var;
    my_thread_t *next;
    TAILQ_FOREACH_SAFE(var,&threads_list->queue,field,next)
      free_mythread(var);
  }
  free_mythread(threads_list->activ);
  free_main(threads_list->main);
  free(threads_list);

 #ifdef PREEMPT
    timer_delete(timerid);
  #endif
}

//fonction d'exécution au lancement d'un thread
void* exec(void *(*func)(void *), void *funcarg){
  #ifdef PREEMPT
    enable_preemption();
  #endif
  void * result = func(funcarg);
  thread_exit(result);   //Appel a exit si le thread n'y fait pas appel pendant son exécution
  return NULL;
}

//****************************************** ZONE DES FONCTIONS DE thread.h ******************************************
thread_t thread_self(void){
  return (thread_t)(threads_list->activ);
}

int thread_create(thread_t *newthread, void *(*func)(void *), void *funcarg){
  #ifdef PREEMPT
    disable_preemption();
  #endif

  my_thread_t* new = new_thread(); //Création d'un nouveau thread
  *newthread = (thread_t*) new;
  makecontext(new->uc, (void (*)(void)) exec, 2, func,funcarg);
  #ifdef HEAD
    TAILQ_INSERT_HEAD(&threads_list->queue,new,field); //Ajout du thread en fin de liste
  #else
    TAILQ_INSERT_TAIL(&threads_list->queue,new,field); //Ajout du thread en fin de liste
  #endif

  #ifdef PREEMPT
    enable_preemption();
  #endif
  return 0;
}

int thread_setschedprio(thread_t *thread, int priority){
  int old_priority = -1;
  if (priority < 0 && priority > 99)
    return ERROR;
  my_thread_t* me = *thread;

  old_priority = me->priority;
  me->priority = priority;

  // plus on a une prio vers 99 plus on insere à l'avant de la queue
  // plus on a une prio vers  1 plus on insere à l'arrière de la queue

  // si je suis pas en train de m'exécuter alors je peux bouger dans la file
  if (thread_self() != me) {
  // If the priority is raised, the thread becomes the tail of the thread list.
  if ((old_priority == -1 && me->priority < 50) || (me->priority < old_priority)) {
    TAILQ_REMOVE(&threads_list->queue, me, field);
    TAILQ_INSERT_TAIL(&threads_list->queue,me,field); //Ajout du thread en fin de liste
  }
  else if ((old_priority == -1 && me->priority >= 50) || (me->priority > old_priority)) {
    TAILQ_REMOVE(&threads_list->queue, me, field);
    TAILQ_INSERT_HEAD(&threads_list->queue,me,field); //Ajout du thread en fin de liste
  }
  // If the priority is unchanged, the thread does not change position in the thread list.
  else {
    // Nothing
  }
}
else {
  thread_yield();
  thread_setschedprio(thread,priority);
}
  return 0;

}

int thread_yield(void){
  #ifdef PREEMPT
    disable_preemption();
  #endif

  my_thread_t* current = threads_list->activ;
  my_thread_t* next = TAILQ_NEXT(current,field);

  //Si on est à la fin de la liste, on repart au début
  if(next == NULL){
    next =  TAILQ_FIRST(&threads_list->queue);
  }

  //Parcours jusqu'à trouver un thread n'attendant pas un join
  while(current!=next&&next->status_join==ON){
    next = TAILQ_NEXT(next,field);
    if(next == NULL){
      next =  TAILQ_FIRST(&threads_list->queue);
    }
  }

  // S'il existe un autre thread n'ayant pas fait de join, on swapcontext avec celui-ci
  if(next != NULL && next !=current){
    threads_list->activ = next;
    //Avant de passer la main à un autre thread, on réinitialise le timer
    #ifdef PREEMPT
    update_timer();
    #endif
    swapcontext(current->uc, threads_list->activ->uc);
  }

  #ifdef PREEMPT
  enable_preemption();
  #endif
  return 0;
}


int thread_join(thread_t thread, void **retval){
  #ifdef PREEMPT
  disable_preemption();
  #endif
  my_thread_t* tmp = (my_thread_t*)(thread);

  if(tmp->status_exit != ON){
    my_thread_t* current = threads_list->activ;
    current->status_join = ON;

    //le thread actuel attend que le thread en argument termine
    while(tmp != NULL && tmp->status_exit==OFF){
	      threads_list->activ = tmp;
	      threads_list->activ->before = current;
	      swapcontext(current->uc, threads_list->activ->uc);
    }
   }

   if(retval != NULL){
     *retval = tmp->retval;
   }

   free_mythread(tmp); //libération du thread founi en argument


   #ifdef PREEMPT
    enable_preemption();
  #endif
   return 0;
}

void thread_exit(void *retval) {
  #ifdef PREEMPT
  disable_preemption();
  #endif

  my_thread_t* prev = threads_list->activ;
  my_thread_t* next;
  prev->retval = retval;
  prev->status_exit = ON;

  //Test pour savoir si le thread est issu d'un join
  if(prev->before==NULL){
    TAILQ_REMOVE(&threads_list->queue,prev,field); //On retire notre thread de la liste
    next = TAILQ_NEXT(prev,field);

    //On regarde si on est à la fin de la liste
    if(next==NULL){
      if(!TAILQ_EMPTY(&threads_list->queue)){
        next = TAILQ_FIRST(&threads_list->queue);
      }else{
        setcontext(threads_list->main->uc); //On redonne la main au thread main si on est le dernier thread
        exit(0);
      }
    }

  // On donne la main au thread du join qui nous a donné la main
  }else{
      next = prev->before;
      next->status_join = OFF;
      TAILQ_REMOVE(&threads_list->queue,prev,field); //On retire notre thread de la liste
    }

  threads_list->activ = next;
  //Si on est le thread main et s'il existe un autre thread dans la liste
  //alors on swapcontext avec celui-ci
  if(prev == threads_list->main && !TAILQ_EMPTY(&threads_list->queue)){
    swapcontext(prev->uc,threads_list->activ->uc);

  //Sinon on donne la main au prochain thread
  }else{
    setcontext(threads_list->activ->uc);
  }
  exit(0);
}//__attribute__ ((__noreturn__)){}

int thread_mutex_init(thread_mutex_t *mutex){
    if(mutex == NULL)
        return ERROR;
    mutex->available = ON;
    mutex->owner = NULL;
    return 0;
}

int thread_mutex_destroy(thread_mutex_t *mutex){
    (void) mutex;
    mutex = NULL;
    return 0;
}

int thread_mutex_lock(thread_mutex_t *mutex){
    while(!mutex->available){
        my_thread_t* tmp = threads_list->activ;
        threads_list->activ = (my_thread_t*)mutex->owner;
        swapcontext(tmp->uc,threads_list->activ->uc);
    }
    mutex->available = OFF;
    mutex->owner = thread_self();
    return 0;
}

int thread_mutex_unlock(thread_mutex_t *mutex){
    mutex->available = ON;
    mutex->owner = NULL;
    thread_yield();
    return 0;
}
