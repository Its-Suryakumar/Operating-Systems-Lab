/*A group of students is studying for an exam. The students can study while eating pizza. Each student executes the following loop. 
While(TRUE) { 
Pick up a piece of pizza; 
Study while eating the pizza; 
} 
If a student finds that the pizza is over, the student goes to sleep until another pizza arrives. The first student to discover that the group is out of pizza phones Satisfactions at Dominos to order another pizza before going to sleep. Each pizza has S slices. 
Write code to synchronize the student threads and the pizza delivery thread. Your solution should avoid deadlock and phone Satisfaction (that is, wake up the delivery thread) exactly only once each time a pizza is exhausted. 
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_STUDENTS 5
#define SLICES_PER_PIZZA 8

int slices_left = SLICES_PER_PIZZA;
pthread_mutex_t pizza_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t need_pizza = PTHREAD_COND_INITIALIZER;
pthread_cond_t pizza_arrived = PTHREAD_COND_INITIALIZER;

void *student(void *arg) {
int id = *(int *)arg;
while (1) {
pthread_mutex_lock(&pizza_mutex);
while (slices_left == 0) {
printf("Student %d: No more pizza, going to sleep\n", id);
pthread_cond_signal(&need_pizza);
pthread_cond_wait(&pizza_arrived, &pizza_mutex);
printf("Student %d: Pizza arrived, waking up\n", id);
}
slices_left--;
printf("Student %d: Taking a slice, %d slices left\n", id, slices_left);
pthread_mutex_unlock(&pizza_mutex);
}
}

void *pizza_delivery(void *arg) {
while (1) {
pthread_mutex_lock(&pizza_mutex);
pthread_cond_wait(&need_pizza, &pizza_mutex);
printf("Pizza delivery: Delivering new pizza\n");
slices_left = SLICES_PER_PIZZA;
pthread_cond_broadcast(&pizza_arrived);
pthread_mutex_unlock(&pizza_mutex);
}
}

int main() {
pthread_t students[NUM_STUDENTS];
pthread_t delivery;
int ids[NUM_STUDENTS];

for (int i = 0; i < NUM_STUDENTS; i++) {
ids[i] = i;
if (pthread_create(&students[i], NULL, student, &ids[i]) != 0) {
perror("Error creating student thread");
exit(1);
}
}

if (pthread_create(&delivery, NULL, pizza_delivery, NULL) != 0) {
perror("Error creating delivery thread");
exit(1);
}

for (int i = 0; i < NUM_STUDENTS; i++) {
if (pthread_join(students[i], NULL) != 0) {
perror("Error joining student thread");
exit(1);
}
}

return 0;
}

