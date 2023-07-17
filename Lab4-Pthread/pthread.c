/*Write a multithreaded program to compute and display the sum of first N naturalnumbers,the sum of first N odd natural numbers
and the sum of first N even natural numbers.*/
#include<stdio.h>
 #include<stdlib.h>
 #include<pthread.h>
 void*sum_natural(void*arg);
 void*sum_odd(void*arg);
 void*sum_even(void*arg);
 intmain()
 {
 pthread_t tid1,tid2,tid3;
 int n;
 printf("Enter the value of n:");
 scanf("%d",&n);
 pthread_create(&tid1,NULL,sum_natural,&n);
 pthread_create(&tid2,NULL,sum_odd,&n);
 pthread_create(&tid3,NULL,sum_even,&n);
 pthread_join(tid1,NULL);
 pthread_join(tid2,NULL);
 pthread_join(tid3,NULL);
 return 0;
 }
 void*sum_natural(void*arg)
 {
 int n=*(int*)arg;
 int sum=0;
 for(int i=1;i<=n;i++)
 {
 sum+=i;
 }
 printf("Sum of first %d natural numbers: %d \n",n,sum);
 pthread_exit(NULL); 
 }
 void*sum_odd(void*arg)
 {
 int n=*(int*)arg;
 int sum=0;
 for(int i=1;i<=n;i+=2)
 {
 sum+=i;
 }
 printf("Sum of first %d odd natural numbers: %d \n",n,sum);
 pthread_exit(NULL);
 }
 void*sum_even(void*arg)
 {
 int n=*(int*)arg;
 int sum=0;
 for(int i=2;i<=n;i+=2)
 {
 sum+=i;
 }
 printf("Sum of first %d even natural numbers: %d \n",n,sum);
 pthread_exit(NULL);
 