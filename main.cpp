#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

#define ATAS '1'
#define BAWAH '2'
#define KIRI '3'
#define KANAN '4'
#define DEPAN '5'
#define BELAKANG '6'
#define ATAS2 'q'
#define BAWAH2 'w'
#define KIRI2 'e'
#define KANAN2 'r'
#define DEPAN2 't'
#define BELAKANG2 'y'
#define ATAS3 'a'
#define BAWAH3 's'
#define KIRI3 'd'
#define KANAN3 'f'
#define DEPAN3 'g'
#define BELAKANG3 'h'

#define CHANGEMOVE '\t' //tab
#define MAKEMOVE 13	//Enter


void UkuranLayar(int x,int y);
void KotakMoving();
void PutarRubik(unsigned char k,int x,int y);
void GerakMouse(int,int);
void KlikDrag(int,int,int,int);

int dragstartx,dragstarty;
double theta=.35;
double phi=.25;
double theta0,phi0;
int GerakanKotak=0;

class Matrix
{
public:
	double l[4][4];	//[baris][kolom]
};

class Vector3D
{
public:
	Vector3D():x(0),y(0),z(0){}
	double x,y,z;
	void MultiplyBy(Matrix m)
	{
		double xbaru,ybaru,zbaru;
		xbaru=m.l[0][0]*x+m.l[1][0]*y+m.l[2][0]*z;
		ybaru=m.l[0][1]*x+m.l[1][1]*y+m.l[2][1]*z;
		zbaru=m.l[0][2]*x+m.l[1][2]*y+m.l[2][2]*z;
		x=xbaru;y=ybaru;z=zbaru;
	}
	Vector3D& operator+=(Vector3D p){x+=p.x;y+=p.y;z+=p.z;return *this;}
};

class Face
{
public:
	void Draw()
	{
		glColor3d(r,g,b);
		glBegin(GL_QUADS);
			for(int n=0;n<5;++n)
				glVertex3d(v[n].x,v[n].y,v[n].z);
		glEnd();
	}
	void MultiplyBy(Matrix m){for(int n=0;n<5;++n)v[n].MultiplyBy(m);}
	Vector3D Centre()
	{
		Vector3D ret;
		for(int n=0;n<5;++n)
			ret+=v[n];
		return ret;
	}
	double r,g,b;
	Vector3D v[5];
};


class Kubus
{
public:
	void Draw(){for(int n=0;n<7;++n) face[n].Draw();}
	Vector3D Centre()
	{
		Vector3D ret;
		for(int n=0;n<7;++n)
			ret+=face[n].Centre();
		return ret;
	}
	void MultiplyBy(Matrix m){for(int n=0;n<6;++n)face[n].MultiplyBy(m);}
	Face face[7];
};

class Rubiks
{
public:
	void Reset()
	{
		for(int n=0;n<64;++n) //Jumlah kubus sebanyak 64
		{
			int xi=n%4-1;
			int yi=((n-xi)/4)%4-1;
			int zi=((n-xi)/4)/4-1;
			double x=xi*1.1;
			double y=yi*1.1;
			double z=zi*1.1;
			
			kubus[n].face[0].r=.8;
			kubus[n].face[0].g=kubus[n].face[0].b=0;
			kubus[n].face[0].v[0].x=x-.5;		//Bawah
			kubus[n].face[0].v[0].y=y-.5;
			kubus[n].face[0].v[0].z=z-.5;
			
			kubus[n].face[0].v[1].x=x+.5;
			kubus[n].face[0].v[1].y=y-.5;
			kubus[n].face[0].v[1].z=z-.5;
			
			kubus[n].face[0].v[2].x=x+.5;
			kubus[n].face[0].v[2].y=y+.5;
			kubus[n].face[0].v[2].z=z-.5;
			
			kubus[n].face[0].v[3].x=x-.5;
			kubus[n].face[0].v[3].y=y+.5;
			kubus[n].face[0].v[3].z=z-.5;

			kubus[n].face[0].v[4].x=x-.5;
			kubus[n].face[0].v[4].y=y+.5;
			kubus[n].face[0].v[4].z=z-.5;

			kubus[n].face[1].r=.10;
			kubus[n].face[1].g=.10;
			kubus[n].face[1].b=.10;
			kubus[n].face[1].v[0].x=x-.5;		//Atas
			kubus[n].face[1].v[0].y=y-.5;
			kubus[n].face[1].v[0].z=z+.5;
			
			kubus[n].face[1].v[1].x=x+.5;
			kubus[n].face[1].v[1].y=y-.5;
			kubus[n].face[1].v[1].z=z+.5;
			
			kubus[n].face[1].v[2].x=x+.5;
			kubus[n].face[1].v[2].y=y+.5;
			kubus[n].face[1].v[2].z=z+.5;
			
			kubus[n].face[1].v[3].x=x-.5;		
			kubus[n].face[1].v[3].y=y+.5;
			kubus[n].face[1].v[3].z=z+.5;

			kubus[n].face[1].v[4].x=x-.5;		
			kubus[n].face[1].v[4].y=y+.5;
			kubus[n].face[1].v[4].z=z+.5;			
			
			kubus[n].face[2].r=kubus[n].face[2].b=kubus[n].face[2].g=.9;
			kubus[n].face[2].v[0].x=x-.5;		//Kiri
			kubus[n].face[2].v[0].y=y-.5;
			kubus[n].face[2].v[0].z=z-.5;
			
			kubus[n].face[2].v[1].x=x-.5;
			kubus[n].face[2].v[1].y=y-.5;
			kubus[n].face[2].v[1].z=z+.5;
			
			kubus[n].face[2].v[2].x=x-.5;
			kubus[n].face[2].v[2].y=y+.5;
			kubus[n].face[2].v[2].z=z+.5;
			
			kubus[n].face[2].v[3].x=x-.5;
			kubus[n].face[2].v[3].y=y+.5;
			kubus[n].face[2].v[3].z=z-.5;

			kubus[n].face[2].v[4].x=x-.5;
			kubus[n].face[2].v[4].y=y+.5;
			kubus[n].face[2].v[4].z=z-.5;			

			kubus[n].face[3].r=kubus[n].face[3].g=.95;
			kubus[n].face[3].b=0;
			kubus[n].face[3].v[0].x=x+.5;		//Kanan
			kubus[n].face[3].v[0].y=y-.5;
			kubus[n].face[3].v[0].z=z-.5;
			
			kubus[n].face[3].v[1].x=x+.5;
			kubus[n].face[3].v[1].y=y-.5;
			kubus[n].face[3].v[1].z=z+.5;
			
			kubus[n].face[3].v[2].x=x+.5;
			kubus[n].face[3].v[2].y=y+.5;
			kubus[n].face[3].v[2].z=z+.5;
			
			kubus[n].face[3].v[3].x=x+.5;
			kubus[n].face[3].v[3].y=y+.5;
			kubus[n].face[3].v[3].z=z-.5;

			kubus[n].face[3].v[4].x=x+.5;
			kubus[n].face[3].v[4].y=y+.5;
			kubus[n].face[3].v[4].z=z-.5;			
			
			kubus[n].face[4].b=1;
			kubus[n].face[4].r=kubus[n].face[4].g=0;
			kubus[n].face[4].v[0].x=x-.5;		//Depan
			kubus[n].face[4].v[0].y=y-.5;
			kubus[n].face[4].v[0].z=z-.5;
			
			kubus[n].face[4].v[1].x=x-.5;
			kubus[n].face[4].v[1].y=y-.5;
			kubus[n].face[4].v[1].z=z+.5;
			
			kubus[n].face[4].v[2].x=x+.5;
			kubus[n].face[4].v[2].y=y-.5;
			kubus[n].face[4].v[2].z=z+.5;
			
			kubus[n].face[4].v[3].x=x+.5;
			kubus[n].face[4].v[3].y=y-.5;
			kubus[n].face[4].v[3].z=z-.5;

			kubus[n].face[4].v[4].x=x+.5;
			kubus[n].face[4].v[4].y=y-.5;
			kubus[n].face[4].v[4].z=z-.5;			
			
			kubus[n].face[5].g=.6;
			kubus[n].face[5].b=kubus[n].face[5].r=0;
			kubus[n].face[5].v[0].x=x-.5;	//Belakang
			kubus[n].face[5].v[0].y=y+.5;
			kubus[n].face[5].v[0].z=z-.5;
			
			kubus[n].face[5].v[1].x=x-.5;
			kubus[n].face[5].v[1].y=y+.5;
			kubus[n].face[5].v[1].z=z+.5;
			
			kubus[n].face[5].v[2].x=x+.5;
			kubus[n].face[5].v[2].y=y+.5;
			kubus[n].face[5].v[2].z=z+.5;
			
			kubus[n].face[5].v[3].x=x+.5;
			kubus[n].face[5].v[3].y=y+.5;
			kubus[n].face[5].v[3].z=z-.5;

			kubus[n].face[5].v[4].x=x+.5;
			kubus[n].face[5].v[4].y=y+.5;
			kubus[n].face[5].v[4].z=z-.5;			
			
			for(int f=0;f<7;++f)
				for(int v=0;v<5;++v)
					if(fabs(kubus[n].face[f].v[v].x)<1
						&& fabs(kubus[n].face[f].v[v].y)<1
						&& fabs(kubus[n].face[f].v[v].z)<1) 
						kubus[n].face[f].r=kubus[n].face[f].g=kubus[n].face[f].b=0;
		}
	}
	void Draw()
	{
		for(int n=0;n<64;++n) kubus[n].Draw();
	}
