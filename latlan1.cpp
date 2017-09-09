#include <math.h>
#include<stdio.h>
#include<iostream>
#define pi 3.14159265358979323846
double deg2rad(double);
double rad2deg(double);
double distance(double lat1, double lon1, double lat2, double lon2);
int main()
{
	double lat[20]={32.44, 32.20, 30.4, 30.15, 27.00, 30.30, 27.40, 23.30, 23.00, 25.11, 21.30, 23.00, 23.45, 20.00, 26.00, 28.38, 15.00, 16.00, 10.00, 11.00};
	double lon[20]={74.54, 74.54, 75.5, 79.15, 74.00, 74.60, 80.00, 80.00, 72.00, 85.32, 82.00, 87.00, 85.30, 76.00, 94.20, 72.12, 75.00, 80.00, 76.25, 78.00};
	double dist[20][20];
	int i,j,l;
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			scanf("%d ",&l);
			if(l==1){
				dist[i][j] = distance(lat[i],lon[i],lat[j],lon[j]);			
			}
			else{
				dist[i][j] = 0;
			}
		}
	}
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			printf("%lf ",dist[i][j]);
		}
		printf("\n");
	}
/*	double lat1,lat2,lon1,lon2;
	scanf("%lf %lf %lf %lf",&lat1,&lon1,&lat2,&lon2);
	double dist=distance(lat1,lon1,lat2,lon2);
	printf("%lf\n",dist);*/
}
double distance(double lat1, double lon1, double lat2, double lon2) {
  double theta, dist;
  theta = lon1 - lon2;
  dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
  dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515 * 1.609344;
  return (dist);
}

double deg2rad(double deg) 
{
  return (deg * pi / 180);
}

double rad2deg(double rad) {
  return (rad * 180 / pi);
}
