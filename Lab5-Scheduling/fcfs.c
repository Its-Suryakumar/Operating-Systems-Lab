#include<stdio.h>
int main()
 {
 int pid[15];
 int at[15];
 int bt[15];
 int n;
 printf("Enter the number of processes: ");
 scanf("%d",&n);
 printf("Enter process id of all the processes: ");
 for(int i=0;i<n;i++)
 {
 scanf("%d",&pid[i]);
 }
 printf("Enter arrival time of all the processes: ");
 for(int i=0;i<n;i++)
 {
 scanf("%d",&at[i]);
 }
 printf("Enter burst time of all the processes: ");
 for(int i=0;i<n;i++)
 {
 scanf("%d",&bt[i]);
 }
 int i,wt[n];
 wt[0]=0;
 //for calculating waiting time of each process
 for(i=1;i<n;i++)
 {
 wt[i]=bt[i-1]+wt[i-1];
}
 printf("ProcessID  ArrivalTime     BurstTime   WaitingTime TurnAroundTime\n");
 float twt=0.0;
 float tat=0.0;
 for(i=0;i<n;i++)
 {
 printf("%d\t\t",pid[i]);
 printf("%d\t\t",at[i]);
 printf("%d\t\t",bt[i]);
 printf("%d\t\t",wt[i]);
 //calculatingandprintingturnaroundtimeofeachprocess
 printf("%d\t\t",bt[i]+wt[i]);
 printf("\n");
 //forcalculatingtotalwaitingtime
 twt+=wt[i];
 //forcalculatingtotalturnaroundtime
 tat+=(wt[i]+bt[i]);
 }
 float att,awt;
 //forcalculatingaveragewaitingtime
 awt=twt/n;
 //forcalculatingaverageturnaroundtime
 att=tat/n;
 printf("Avg.waitingtime = %f \n",awt);
 printf("Avg.turnaroundtime = %f \n",att);
 }
