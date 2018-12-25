#include<stdio.h>
#include<conio.h>
#include<math.h>
#define rad 0.01745329
main()
{

double ang,Rang,z,a,Iyy,d,Myy,V,dl,ll,l,Rang1,m,m1,m2,m3,m4,M,Hsum=0,Vsum=0;
    int i,j,n;
    double zdist[20],Q[20],Nx[20],Nxq[20],ds[20],dy[20],dz[20],ss[20],ssh[20],ssv[20],dw[20],lw[20],v[20],Moment[20],Nq[20];
    printf("span of shell \n");
    scanf("%lf",&l);
    printf("enter radius \n");
    scanf("%lf",&a);
    printf("enter thickness\n");
    scanf("%lf",&d);
    printf("enter semicircular angle\n");
    scanf("%lf",&Rang);
    printf("enter deadload \n");
    scanf("%lf",&dl);
    printf("live load\n");
    scanf("%lf",&ll);

    ang=rad*Rang;                                                    //ang= main angle in radian in radian......Rang=main angle in degree
    z=a*(1-sin(ang)/ang);
    printf("depth of nutral axis %lf\n",z);
    Iyy=a*a*a*d*(ang+sin(ang)*(cos(ang)-(2*sin(ang)/ang)));
    printf("moment of inertia %lf \n",Iyy);
    printf("enter the perferred angular intervals \n");                   //n= no of angular interval
    scanf("%d",&n);
    Myy=(dl*2*ang*a+(ll*2*a*sin(ang)))*l*l*0.125;                         //Myy= longitudinal moment at mid span
    printf(" total load %lf \n",dl*ang*a+(ll*2*sin(ang)*a));
    printf("Myy=%lf \n",Myy);
    V=(dl*2*ang*a+ll*2*sin(ang)*a)*l*0.5;                                 //V=vertical shear force at transverse                       
    printf("shear %lf\n",V);
    for(i=0;i<=n;i++)
    {
        Rang1=Rang-(Rang*(i)/n);
        zdist[i]=a*(1-cos(Rang1*rad))-z;                                  //the angular interval.........Rang1=each interval angle
        Q[i]=2*a*a*d*(sin(Rang1*rad)-(sin(ang)*Rang1/Rang));              //Q= the first static moment upto any point under consideration
        Nx[i]=Myy*d*(a*(1-cos(Rang1*rad))-z)/Iyy;                         //Nx=axial force in x-direction
        Nxq[i]=0.5*V*Q[i]/Iyy;                                            //Nxq= shear force in x direction

        if(i==0 || i==n)
        {
            ds[i]=a*Rang*rad/(n*2);
        }
        else
        {
            ds[i]=a*Rang*rad/(n);
        }
        dy[i]=ds[i]*cos(Rang1*rad);
        dz[i]=ds[i]*sin(Rang1*rad);
        ss[i]=Nxq[i]*2/l;                          //ss[i]=specific shear
        ssh[i]=ss[i]*dy[i];                          //ssh[i]=horizontal force component of specific shear
        ssv[i]=-ss[i]*dz[i];                          //ssv[i]=vertical force component of specific shear
        dw[i]=dl*ds[i];                              //dw=dead weight
        lw[i]=ll*dy[i];                              //lw= live weight
        v[i]=ssv[i]+dw[i]+lw[i];
    }
for(i=0;i<=n;i++)
{
        printf("POINT%d Nx=%lf  Nxq=%lf\n",i,Nx[i],Nxq[i]);
}
// Transverse Moment Mθ
m=Rang/n;    //m= angular interval
for(i=0;i<n;i++)
{
   for(j=0;j<=i;j++)
   {
       m1=v[j]*cos((Rang-(i+1)*m)*rad)*a*sin((m*(i+1-j))*rad);
       m2=-v[j]*sin((Rang-(i+1)*m)*rad)*a*(1-cos((m*(i+1-j))*rad));
       m3=ssh[j]*cos((Rang-(i+1)*m)*rad)*a*(1-cos((m*(i+1-j))*rad));
       m4=ssh[j]*sin((Rang-(i+1)*m)*rad)*a*sin((m*(i+1-j))*rad);
       M=m1+m2+m3+m4+M;

   }
  Moment[i+1]=M;          //determinate transverse moment Mθ
   M=0;
}
Moment[0]=0;
for(i=0;i<=n;i++)
{

    printf("transverse moment%d %lf\n",i,Moment[i]);
}
//Axial force in θ direction i.e Nθ calculation
for(i=0;i<=n;i++)
{
    Rang1=Rang-(Rang*(i)/n);
    Hsum=-ssh[i]+Hsum;          //Hsum=cumulative summation of horizontal force
    Vsum=v[i]+Vsum;                                //Vsum=cumulative summation vertical force
    Nq[i]=Hsum*cos(Rang1*rad)+Vsum*sin(Rang1*rad);
    printf("Nq%d = %lf \n \n",i,Nq[i]);
}
getch();
}
