#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/time.h>
#include "thread.h"

/* test de la préemption.
 *
 * le programme doit terminer correctement (faire le printf et s'arreter entièrement).
 * valgrind doit être content.
 * Le fils avec la priorité max doit quasi monopoliser 
 * l'éxécution malgré les yields
 *
 *
 * support nécessaire:
 * - thread_create()
 * - thread_join() du main par un autre thread
 * Priority is between 1 and 99
 */

#define NB_THREADS 10

char * id_to_name(int id){
    char * name;
    switch (id)
    {
    case 1:
        name = "SCHED_FIFO";
        break;
    case 2:
        name = "SCHED_RR";
        break;
    default:
        name = "SCHED_OTHER";
        break;
    }
    return name;
}

static void * thfunc(void *id)
{
  int err, i;
  int nb_occ[NB_THREADS];
  for (i=0; i<NB_THREADS; i++)
    nb_occ[i] = 0;
  int *name = (int *) id;
  for(i=0; i<10; i++) {
     printf("%d yield vers un autre fils...\n",*name);
    nb_occ[*name]++;
    err = thread_yield();
    assert(!err);
  
  }
  printf("\n");
  printf("%d terminé et vu %d fois\n", *name,  nb_occ[*name]);

  thread_exit(NULL);
  return (void*) 0xdeadbeef; /* unreachable, shut up the compiler */
  return NULL;
}

int main()
{
  int err, ret, p1,p2;
  p1 = 1;
  p2 = 99;

  printf("Lancement de 10 threads...\n\n");

  //On modidifie la policy et la priorité par défaut
  

  #ifdef USE_PTHREAD
    pthread_t threads[NB_THREADS];
    int arg[NB_THREADS];
    pthread_attr_t tattr;
    //int inheritsched = PTHREAD_EXPLICIT_SCHED;
    int policy = SCHED_FIFO;
    struct sched_param param;

    printf("Création de 10 threads (0->9) Policy: %s Priority: %d\n", id_to_name(policy),p1);
    printf("Création de 10 threads (10->19) Policy: %s Priority: %d\n", id_to_name(policy),p2);


    /* initialized with default attributes */
    ret = pthread_attr_init(&tattr);
    assert(ret == 0);
    
    //ret = pthread_attr_setinheritsched(&tattr, inheritsched);
    //assert(ret == 0);
    ret = pthread_attr_setschedpolicy(&tattr, policy);
    assert(ret == 0);

    param.sched_priority = p1;

    ret = pthread_attr_setschedparam(&tattr, &param);
    assert(ret == 0);
    int i;
    for (i=0; i<NB_THREADS/2; i++){
      arg[i]=i;
      ret = pthread_create(&(threads[i]),&tattr,&thfunc,(void *) &(arg[i]));
      assert(ret == 0);
    }
    ret = pthread_attr_getschedpolicy(&tattr,&policy); // 1= FIFO 2 = Round Robin 
    assert(ret == 0);
    ret = pthread_attr_getschedparam(&tattr,&param);
    assert(ret == 0);
    //printf("Création thread: fils 1 Policy: %d Priority: %d\n", id_to_name(policy),param.sched_priority);

    param.sched_priority = p2;
    ret = pthread_attr_setschedparam(&tattr,&param);
    assert(ret == 0);
    int j;
    for (j=10; j<NB_THREADS; j++){
      arg[j]=j;
      ret = pthread_create(&(threads[j]),&tattr,&thfunc,(void *) &(arg[j]));
      assert(ret == 0);
    }
    pthread_attr_getschedpolicy(&tattr,&policy); // 1= FIFO 2 = Round Robin 
    pthread_attr_getschedparam(&tattr,&param);

   // printf("Création thread: fils 2 Policy: %d Priority: %d\n", id_to_name(policy),param.sched_priority);
   int c;
  for(c=0;c<NB_THREADS;c++) {
    err=pthread_join(threads[c],NULL);
    assert(err == 0);
  }

  #else
    thread_t threads[NB_THREADS];
    int arg[NB_THREADS];
    int priority = p1;
    int i;
    for (i=0; i<NB_THREADS; i++){
      if (i>=NB_THREADS/2)
        priority = p2;
      arg[i]=i;
      ret = thread_create(&(threads[i]),&thfunc,(void *) &(arg[i]));
      assert(ret == 0);
      ret = thread_setschedprio(&(threads[i]),priority);
      if (ret == 0)
        printf("Fils %d à la prioritée (%d)...\n",i,priority);
      else
        printf("Impossible de modifier la priorité du fils 1...\n");
    }
  int c;
  for(c=0;c<NB_THREADS;c++) {
    err=thread_join(threads[c],NULL);
    assert(err == 0);
  }

   #endif
  return 0;
}

