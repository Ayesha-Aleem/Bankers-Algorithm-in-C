#include <stdio.h>
#include <stdbool.h>

struct Processes{
    int process_ID;
    int need[50];
    int allocated[50];
    int max[50];
    bool Finish;
};

struct Resources{
    int resource_ID;
    int instances;
    int available;
};

void main( void )
{
    int no_of_Processes = 0 , no_of_Resources = 0;

    printf("\n%s","Enter Number of Processes: ");
    while( scanf("%d",&no_of_Processes) != 1 || no_of_Processes <= 0)
    {
        puts("Invalid Input");
        fflush(stdin);
        printf("\n%s","Enter Number of Processes: ");
    }

    printf("\n%s","Enter Number of Resources: ");
    while( scanf("%d",&no_of_Resources) != 1 || no_of_Resources <= 0 )
    {
        puts("Invalid Input");
        fflush(stdin);
        printf("\n%s","Enter Number of Resources: ");
    }


    struct Processes p[no_of_Processes];
    struct Resources r[no_of_Resources];


    for( int i = 0 ; i < no_of_Resources ; i++)
    {
        r[i].resource_ID = i+1;

        printf("\nEnter Instances of Resource %d: ",i + 1);
        while(scanf("%d",&r[i].instances)!= 1 || r[i].instances <= 0 )
        {
            puts("Invalid Input");
            fflush(stdin);
            printf("|n%s%d:","Enter Instances of Resource ",i + 1);
        }

        r[i].available = r[i].instances;

    }


    for( int i = 0 ; i < no_of_Processes ; i++)
    {
        p[i].process_ID = i;
        p[i].Finish = false;
        for(int j =0;j<no_of_Resources;j++)
        {
            p[i].need[j]=0;
        }
        for( int j = 0 ; j < no_of_Resources ; j++)
        {

            printf("\nEnter Max Instances of Resource %d Process %d want: ", j + 1 , i + 1);
            while( scanf("%d", &p[i].max[j]) != 1 || p[i].max[j] < 0 || p[i].max[j] > r[j].instances)
            {
                puts("Invalid Input");
                fflush(stdin);
                printf("\nEnter Max Instances of Resource %d Process %d want: ", j + 1 , i + 1);
            }

        }


        for( int j = 0 ; j < no_of_Resources ; j++)
        {
            printf("\nEnter Allocated Instances of Resource %d for Process %d: ", j + 1 , i + 1);
            while( scanf("%d", &p[i].allocated[j]) != 1 || p[i].allocated[j] < 0 || p[i].allocated[j] > p[i].max[j] || p[i].allocated[j] > r[j].available)
            {
                puts("Invalid Input");
                fflush(stdin);
                printf("\nEnter Allocated Instances of Resource %d for Process %d: ", j + 1 , i + 1);
            }
            r[j].available -= p[i].allocated[j];
        }
        for( int j = 0 ; j < no_of_Resources; j++)
        {
            p[i].need[j] = (p[i].max[j] - p[i].allocated[j]);
        }
        /*
        for(int j = 0 ;j<no_of_Resources;j++)
        {
            printf("\nAvailable Instances of Resource %d = %d\n",j+1,r[j].available);
        }


        printf("Process %d Need\n",i);
        for(int j = 0;j<no_of_Resources;j++)
        {
            printf("Resource %d = %d\n",j+1,p[i].need[j]);
        }*/
    }

    int safe_sequence_counter = 0;
    int safe_sequence[no_of_Processes];

    for(int l = 0;l<no_of_Processes;l++)
    {
        for(int i =0 ;i< no_of_Processes;i++)
        {
            int temp =0;
            for(int j=0;j<no_of_Resources;j++)
            {
                if(p[i].need[j]<=r[j].available)
                {
                    temp++;
                    if(temp == no_of_Resources && p[i].Finish == false)
                    {
                        for(int k=0;k<no_of_Resources;k++)
                        {
                            r[k].available += p[i].allocated[k];
                        }
                        p[i].Finish = true;
                        safe_sequence[safe_sequence_counter] = p[i].process_ID;
                        safe_sequence_counter++;
                    }
                }
            }

        }
    }
    printf("%20s","Processes");
    for(int i =0;i<no_of_Processes;i++)
    {
        printf("%15d",i);
    }
    for(int i = 0;i<no_of_Resources;i++)
    {
        printf("\n%20s%c","Max_",65+i);
        for(int j=0;j<no_of_Processes;j++)
        {
            printf("%15d",p[j].max[i]);
        }
    }
    for(int i = 0;i<no_of_Resources;i++)
    {
        printf("\n%20s%c","Allocate_",65+i);
        for(int j=0;j<no_of_Processes;j++)
        {
            printf("%15d",p[j].allocated[i]);
        }
    }
    for(int i = 0;i<no_of_Resources;i++)
    {
        printf("\n%20s%c","NEED_",65+i);
        for(int j=0;j<no_of_Processes;j++)
        {
            printf("%15d",p[j].need[i]);
        }
    }
    if(safe_sequence_counter == no_of_Processes)
    {
        printf("\nSafe Sequence of Processes is :");
        for(int i = 0;i<safe_sequence_counter;i++)
        {
            printf(" P%d ",safe_sequence[i]);
        }
    }
    else
        printf("\nDeadlock Occured\n");

}
