#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include "thread.h"

/* test de la préemption.
 *
 * le programme doit terminer correctement (faire le printf et s'arreter entièrement).
 * valgrind doit être content.
 * le programme doit passer la main a l'autre thread apres 10ms
 * un des fils doit etre en avance sur l'autre
 *
 *
 *
 * support nécessaire:
 * - thread_create()
 * - thread_join() du main par un autre thread
 */


#define NB_LOOP_PREEMPT 8000000 //pour faire une exécution d'environ 15ms, illustre la preemption
#define NB_LOOP 4000000 //pour faire une exécution d'environ 8-9ms, pas de preemption
struct timeval tv1;

static void * thfunc(void *id)
{
  struct timeval tv2;
  struct timeval tv3;
  double s;
  int err,i,j;

  for(i=0; i<10; i++) {
    printf("Debut du tour numero %d du %s\n",i+1,(char*)id);
    gettimeofday(&tv2, NULL);
    for(j=0;j<NB_LOOP_PREEMPT ;j++)
        ;
    gettimeofday(&tv3, NULL);
    s = (tv3.tv_sec - tv2.tv_sec) + (tv3.tv_usec - tv2.tv_usec) * 1e-6;
    printf("Fin du tour numero %d du %s en %e s\n",i+1,(char*)id,s);
    err = thread_yield();
    assert(!err);
  }
  gettimeofday(&tv2, NULL);
  s = (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1e-6;
  printf("%s: EXECUTION TERMINÉE APRES %e s\n", (char*)id,s);
  return NULL;
}

int main()
{
  thread_t th1,th2;
  void *res;
  int err;
   gettimeofday(&tv1, NULL);
  err = thread_create(&th1, thfunc, "fils1");
  assert(!err);
  err = thread_create(&th2, thfunc, "fils2");
  assert(!err);
  printf("Le main a lancé deux threads\n\n");

  err = thread_join(th1, NULL); /* on ignore ce code de retour */
  assert(!err);
  err = thread_join(th2, &res);
  assert(!err);
  assert(res == NULL);

  printf("main terminé\n");
  return 0;
}

