#include<stdio.h>
#include<conio.h>
#include<math.h>
#define rad 0.01745329
main()
{

double ang,Rang,z,a,Iyy,d,Myy,V,dl,ll,l,Rang1,m,m1,m2,m3,m4,M,s1=0,s2=0,Marea=0,MMarea=0,Carea,Icc,Hsum=0,Vsum=0;
    int i,j,n;
    double zdist[20],Q[20],Nx[20],Nxq[20],ds[20],dy[20],dz[20],ss[20],ssh[20],ssv[20],dw[20],lw[20],v[20],Moment[20],Mid[20],Mact[20],Nq[20];
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
    Iyy=a*a*a*d*(ang+sin(ang)*(cos(ang)-(2*sin(ang)/ang)));            //Iyy=moment of iertia
    printf("enter the perferred angular intervals \n");                   //n= no of angular interval
    scanf("%d",&n);
    Myy=(dl*2*ang*a+(ll*2*a*sin(ang)))*l*l*0.125;                          //longitudinal moment at midspan
    V=(dl*2*ang*a+ll*2*sin(ang)*a)*l*0.5;                                 //longitudinal shear at traverse
    for(i=0;i<=n;i++)
    {
        Rang1=Rang-(Rang*(i)/n);
        zdist[i]=a*(1-cos(Rang1*rad))-z;                                  //the angular interval.........Rang1=each interval angle
        Q[i]=2*a*a*d*(sin(Rang1*rad)-(sin(ang)*Rang1/Rang));
        Nx[i]=Myy*d*(a*(1-cos(Rang1*rad))-z)/Iyy;                         //axial force at x direction Nx
        Nxq[i]=0.5*V*Q[i]/Iyy;                                            //Shear force at x direction Nxθ

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
        ssv[i]=-ss[i]*dz[i];                          //ssh[i]=vertical force component of specific shear
        dw[i]=dl*ds[i];                              //dw=dead weight
        lw[i]=ll*dy[i];                              //lw= live weight
        v[i]=ssv[i]+dw[i]+lw[i];
    }
 for(i=0;i<=n;i++)
{
        printf("POINT%d Nx=%lf  Nxq=%lf\n",i,Nx[i],Nxq[i]);
}
//Calculation of Transverse moment Mθ
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
  Moment[i+1]=M;          //determinate part of moment Mθ
   M=0;

}
Moment[0]=0;
  //column analogy for calculation of indeterminate part of Mθ
  for(i=1;i<n;i++)
  {
      if(i%2==1)
      {
          s1=s1+Moment[i];
      }
      else
      {
          s2=s2+Moment[i];
      }
  }
Marea=-2*(Moment[0]+Moment[n]+4*s1+2*s2)*a*m*rad/3;
for(i=0;i<=n;i++)
{
    if(i==0 || i==n)
    {
    MMarea=-a*m*rad*(Moment[i]*(-zdist[i]))+MMarea;     //MMarea=moment of moment area about z-axis
    }
    else
    MMarea=-2*a*m*rad*(Moment[i]*(-zdist[i]))+MMarea;
}
Carea=2*a*ang;                        //Carea=equivalent column area
Icc=Iyy/d;                            //Icc=euivalent column moment of inertia
for(i=0;i<=n;i++)
{
    Mid[i]=(Marea/Carea)+(-MMarea*zdist[i]/Icc);    //Mid=indeterminate moment from colimn analogy
    Mact[i]=-Moment[i]-Mid[i];                      //Mact=actual transverse moment
    printf("transverse moment%d %lf \n \n",i,Mact[i]);
}
//Nq calculation
for(i=0;i<=n;i++)
{
    Rang1=Rang-(Rang*(i)/n);
    if(i==0)
    {
       Hsum=-ssh[i]+Hsum+(-MMarea/Icc);          //Hsum=cumulative summation of horizontal force
    }
    else
    {
       Hsum=-ssh[i]+Hsum;
    }
    Vsum=v[i]+Vsum;                                //Vsum=cumulative summation vertical force
    Nq[i]=Hsum*cos(Rang1*rad)+Vsum*sin(Rang1*rad);
    printf("Nq%d = %lf \n \n",i,Nq[i]);
}
getch();
}
