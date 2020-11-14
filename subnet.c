/**
    This code is design for calculate subnet by given ip address.
*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printoo(int *ptr)
{
  for(int i=0;i<4;i++)
  {
      if(i<3)
      {
          printf("%d",ptr[i]);
          printf(".");
      }
      else
      {
          printf("%d",ptr[i]);
      }
  }
}


void ranjoo(int *arr,int r,int crrPos){
       int nid=0,bid=r-1,i=crrPos+1,x=1;

       if(r==1){
         bid=255;
       }
        printf("\n\t\tNetwork\t\t  Network Id\t\t\t Broadcast Id");
        while(bid<=255){
                printf("\n\n\t\t  %d\t\t  ",x);
            arr[crrPos]=nid;
            i=crrPos+1;
                while(i<4){
                    arr[i]=0;
                    i++;
                }
            printoo(arr);
            printf("\t\t\t");
            arr[crrPos]=bid;
                i=crrPos+1;
                while(i<4){
                    arr[i]=255;
                    i++;
                }
            printoo(arr);
          nid=nid+r;
          bid=bid+r;
          x++;
        }
        printf("\n\n");
}



int main(int argc,char *argv[])
{
    int oct[4],cidr=0,i=0,count=0,tindex=0,x=0;
    int  error=0,subnetmask[4]={0,0,0,0},sub=0;
    int wildcard[4]={0,0,0,0},network=1,netbit;
    int hostbit,networkid[4]={0,0,0,0};
    long long int host=1,valid_host;
    char *ip=argv[1], temp[3];
    int gateway[4]={0,0,0,0};
    int netrange[4]={0,0,0,0},range=1;


    if(argc==3){
        if((strcmp(argv[2],"-h")!=0) && (strcmp(argv[2],"-a")!=0) && (strcmp(argv[2],"-n")!=0) && (strcmp(argv[2],"-r")!=0)){
            printf("\n\tERROR : Unknown switch used");
            printf("\n\n\tTry \"subnet help\" command for more detail\n\n");
            exit(0);
        }
    }

    if(argc==1||strcmp(argv[1],"help")==0)
    {
        printf("\n\tSubnet calculator:");
        printf(" Calculate the subneting by entring the ip with or without CIDR value");
        printf("\n\n\nUsages:");
        printf("\n\tsubnet [<IP>|<IP/CIDR>] [-a|-n|-h|-r|-g]");
        printf("\n\nSWITCHES:");
        printf("\n\t-a     Show all.");
        printf("\n\t-h     Display information about the Host.");
        printf("\n\t-n     Display the information about the Network.");
        printf("\n\t-r     Display information about the all network and it's range.");
        printf("\n\thelp   Display this help option");
        printf("\n\n\nEXAMPLES:");
        printf("\n\tsubnet 192.168.23.1 -a");
        printf("\n\tsubnet 192.168.23.1/24 -a");
        printf("\n\tsubnet 192.168.23.1/12 -n");
        printf("\n\n\nNOTE:  If you do not provide CIDR value in that condition the default will applied\n\n\n");
        return 0;
    }

    else if(argc>=2)
    {

        if((strlen(argv[1])>18) || (strlen(argv[1])<7))
        {
            printf("\n\n\t\t\tInvalid ip address entered !!!\n\n\n");
        }
        else
            {
                // Converting IP(String) to IP(int)
                while(count<4)
                {
                  while(ip[i]!='.' && i<(strlen(argv[1])))
                   {
                    if(ip[i]=='/')
                      {
                        cidr++;
                        break;
                      }
                    else
                      {
                        temp[tindex]=ip[i];
                        tindex++;
                        i++;
                      }
                   }
                    oct[count]=atoi(temp);
                    tindex=0;
                    temp[0]=0;
                    temp[1]=0;
                    temp[2]=0;
                    count++;
                    i++;
              }

for(int j=0;j<4;j++)
{
    if((oct[j]<0 || oct[j]>=256))
    {
        printf("\n\n\tInvalid IP Address Entered");
        error++;
        return 1;
    }
}
// Assigning cidr value for Classful ip address
        if(cidr==0)
              {
                if(oct[0]>=0 && oct[0]<=126)
                    {
                        cidr=8;
                    }
                else if(oct[0]>=128 && oct[0]<=191)
                    {
                        cidr=16;
                    }
                else if(oct[0]>=192 && oct[0]<=223)
                    {
                        cidr=24;
                    }
                else if(oct[0]>=224 && oct[0]<=239)
                    {
                        cidr=32;
                    }
                else if(oct[0]>=240 && oct[0]<=255)
                    {
                        printf("\n\nThis IP address belongs to class E and it is used by Militry");
                        return 1;
                    }
              }
        // Assigning cidr for Classless ip address
        else{
                while(strlen(argv[1])>i)
                 {
                    temp[tindex]=ip[i];
                    tindex++;
                    i++;
                 }
                 cidr=atoi(temp);
                netbit=cidr%8;
                for(i=0;i<netbit;i++)
                   {
                      network= network * 2;
                   }
            }
        }
    }
//Calculating number of Host
    hostbit=32-cidr;
    for(i=0;i<hostbit;i++)
      {
        host*=2;
      }
// Valid host
  valid_host=host-2;


  //Validate CIDR Value
    if(cidr<=0||cidr>=33)
    {
        printf("\n\n\t\t\tInvalid CIDR value Entered");
        error++;
        return 1;
    }

    if(cidr%8==0)
    {
        sub=255;
    }
    else if(cidr%8==1)
    {
        sub=128;
    }
    else if(cidr%8==2)
    {
        sub=192;
    }
    else if(cidr%8==3)
    {
        sub=224;
    }
    else if(cidr%8==4)
    {
        sub=240;
    }
    else if(cidr%8==5)
    {
        sub=248;
    }
    else if(cidr%8==6)
    {
        sub=252;
    }
    else if(cidr%8==7)
    {
        sub=254;
    }

// Finding subnet Mask
    i=cidr;
    while(i>8)
    {
        subnetmask[x]=255;
        x++;
        i=i-8;
    }
    subnetmask[x]=sub;
    x++;
    while(x<4)
    {
        subnetmask[x]=0;
        x++;
    }
//Setting Wild-card mask
for(x=0;x<4;x++)
    {
        wildcard[x]=255-subnetmask[x];
    }
// Network Id calculation
for(x=0;x<4;x++)
{
    networkid[x]=(subnetmask[x])&(oct[x]);
}


// Default Gateway Calculate

  for(x=0;x<4;x++)
  {
    gateway[x]=networkid[x];
  }
 gateway[3]=(networkid[3])+1;




if(error==0)
  {
    printf("\n\n\t\tIP Address = ");
    for(i=0;i<4;i++)
      {
          if(i<3)
          {
              printf("%d",oct[i]);
              printf(".");
          }
          else
          {
              printf("%d",oct[i]);
          }
      }
    //printf("/%d",cidr);

    printf("\n\t\tSubnet mask = ");
      for(i=0;i<4;i++)
      {
          if(i<3)
          {
              printf("%d",subnetmask[i]);
              printf(".");
          }
          else
          {
              printf("%d",subnetmask[i]);
          }
      }
  }

   // Network range calculation
        x=i=0;

        while(i<(hostbit%8))
            {
                range=range*2;
                i++;
            }
        range;

     i=0;
    while(i<4){
        if(subnetmask[i]==255){
            netrange[i]=oct[i];
            i++;
        }
        else{
            break;
        }
    }
        //i--;

    if(argc==3){
        if((strcmp(argv[2],"-h")==0) || (strcmp(argv[2],"-a")==0))
        {
            printf("\n\n\tInformation About Host:\n");
            printf("\n\t\tNumber of Host = %lli",host);
            printf("\n\t\tNumber of Valid Host = %lli",valid_host);
        }
       if((strcmp(argv[2],"-n")==0) || (strcmp(argv[2],"-a")==0))
        {
            printf("\n\n\tInformation About Network:\n");
            printf("\n\t\tNumber of Network = %d",network);
            printf("\n\t\tNetwork Id = ");
            printoo(networkid);
            printf("\n\t\tDefault Gateway = ");
            printoo(gateway);
            printf("\n\t\tWild-card address = ");
            printoo(wildcard);
        }
      if((strcmp(argv[2],"-r")==0) || (strcmp(argv[2],"-a")==0))
      {
        printf("\n\n\tInformation about Network Range:\n");
        ranjoo(netrange,range,i);
      }
    }

return 0;
}

