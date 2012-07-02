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
#define ATAS4'z'
#define BAWAH4 'x'
#define KIRI4 'c'
#define KANAN4 'v'
#define DEPAN4 'b'
#define BELAKANG4 'n'

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
			
			kubus[n].face[0].r=.6;
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

		
			
		}
	}
	void Draw()
	{
		for(int n=0;n<64;++n) kubus[n].Draw();
	}

	

	void MakeMove(char k,bool fast)
	{
		Matrix m;
		for(int x=0;x<4;++x)
			for(int y=0;y<4;++y)
				m.l[x][y]=0;
	
		double ang=fast?3.14159265/10.0:3.14159265/50.0;
	
		switch(k)
		{
		case(KIRI):
		case(KIRI2):
		case(KIRI3):
        case(KIRI4):            
        	m.l[0][0]=1;
			m.l[1][1]=cos(ang);
			m.l[1][2]=sin(ang);
			m.l[2][1]=-sin(ang);
			m.l[2][2]=cos(ang);
			m.l[2][2]=cos(ang);
			break;
		case(KANAN):
		case(KANAN2):
		case(KANAN3):
			m.l[0][0]=1;
			m.l[1][1]=cos(ang);
			m.l[1][2]=-sin(ang);
			m.l[2][1]=sin(ang);
			m.l[2][2]=cos(ang);
			break;
		case(ATAS):
		case(ATAS2):
		case(ATAS3):
			m.l[2][2]=1;
			m.l[0][0]=cos(ang);
			m.l[0][1]=-sin(ang);
			m.l[1][0]=sin(ang);
			m.l[1][1]=cos(ang);
			break;
		case(BAWAH):
		case(BAWAH2):
		case(BAWAH3):
  		case(BAWAH4):
			m.l[2][2]=1;
			m.l[0][0]=cos(ang);
			m.l[0][1]=sin(ang);
			m.l[1][0]=-sin(ang);
			m.l[1][1]=cos(ang);
			break;
		case(DEPAN):
		case(DEPAN2):
		case(DEPAN3):
        case(DEPAN4):
			m.l[1][1]=1;
			m.l[0][0]=cos(ang);
			m.l[0][2]=sin(ang);
			m.l[2][0]=-sin(ang);
			m.l[2][2]=cos(ang);
			break;
		case(BELAKANG):
		case(BELAKANG2):
		case(BELAKANG3):
			m.l[1][1]=1;
			m.l[0][0]=cos(ang);
			m.l[0][2]=-sin(ang);
			m.l[2][0]=sin(ang);
			m.l[2][2]=cos(ang);
			break;
		}

		long t0=glutGet(GLUT_ELAPSED_TIME);
		for(int t=0;t<(fast?5:25);++t)
		{
			for(int n=0;n<64;++n)
			switch(k)
			{
            case(KIRI):
			case(KANAN3):
				if(kubus[n].Centre().x<-1) kubus[n].MultiplyBy(m);
				break;
			case(KANAN):
			case(KIRI3):
				if(kubus[n].Centre().x>+1) kubus[n].MultiplyBy(m);
				break;
			case(KIRI2):
			case(KANAN2):
				if(kubus[n].Centre().x>-1 && kubus[n].Centre().x<+1) kubus[n].MultiplyBy(m);
				break;
			case(ATAS):
			case(BAWAH3):
				if(kubus[n].Centre().z>+1) kubus[n].MultiplyBy(m);
				break;
			case(BAWAH):
			case(ATAS3):
				if(kubus[n].Centre().z<-1) kubus[n].MultiplyBy(m);
				break;
			case(ATAS2):
			case(BAWAH2):
				if(kubus[n].Centre().z<+1 && kubus[n].Centre().z>-1) kubus[n].MultiplyBy(m);
				break;
			case(DEPAN):
			case(BELAKANG3):
				if(kubus[n].Centre().y<-1) kubus[n].MultiplyBy(m);
				break;
			case(BELAKANG):
			case(DEPAN3):
				if(kubus[n].Centre().y>+1) kubus[n].MultiplyBy(m);
				break;
			case(DEPAN2):
			case(BELAKANG2):
				if(kubus[n].Centre().y<+1 && kubus[n].Centre().y>-1) kubus[n].MultiplyBy(m);
				break;
			}
			KotakMoving();
			while(glutGet(GLUT_ELAPSED_TIME)<t0+t*10);
		}
	}
	Kubus kubus[64];
} RKubus;

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(300,100);
	glutCreateWindow("Rubik's Kubus");
	glutReshapeFunc(UkuranLayar);
	glutDisplayFunc(KotakMoving);
	glutKeyboardFunc(PutarRubik);
	glutMotionFunc(GerakMouse);
	glutMouseFunc(KlikDrag);

	RKubus.Reset();
	
	glutMainLoop();
	return 0;
}

void UkuranLayar(int x,int y)
{
	if(x!=500 || y!=500) //untuk mengunci ukuran window di 500x500
	{
		glutReshapeWindow(500,500);
		return;
	}
	
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60,1,1,100); 
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}


void KotakMoving() //fungsi membuat tanda kotak pergerakan 
{
	glClearColor(0,2,.4,.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();	
	gluLookAt(7*sin(phi)*cos(theta),-7*cos(phi)*cos(theta),7*sin(theta),0,0,0,0,0,1);


	glPushMatrix();
		glLineWidth(4); //tebal garis kotak moving
		glColor3d(0,0,0); //warna garisnya
		if(GerakanKotak<4) //kondisi pergerakannya
		{
			glScaled(1.1,4.7,4.7);
			glTranslated(GerakanKotak-1,0,0);
		}
		if(GerakanKotak>=4 && GerakanKotak<8)
		{
			glScaled(4.7,1.1,4.7);
			glTranslated(0,GerakanKotak-5,0);	
		}
		if(GerakanKotak>=8)
		{
			glScaled(4.7,4.7,1.1);
			glTranslated(0,0,GerakanKotak-9);
		}
		glutWireCube(1);
	glPopMatrix();
	RKubus.Draw();
	glutSwapBuffers();
}

void PutarRubik(unsigned char k,int x,int y) //fungsi untuk memutar warna-warna kubus
{
	if(k==CHANGEMOVE)
	{
		++GerakanKotak;
		GerakanKotak%=12;
		glutPostRedisplay();
		return;
	}
	if(k==MAKEMOVE)
	{
		if(GerakanKotak==0) RKubus.MakeMove(KIRI,false);
		if(GerakanKotak==1) RKubus.MakeMove(KIRI2,false);
		if(GerakanKotak==2) RKubus.MakeMove(KIRI3,false);
		if(GerakanKotak==3) RKubus.MakeMove(KIRI3,false);
		
		
		if(GerakanKotak==4) RKubus.MakeMove(DEPAN,false);
		if(GerakanKotak==5) RKubus.MakeMove(DEPAN2,false);
		if(GerakanKotak==6) RKubus.MakeMove(DEPAN3,false);
		if(GerakanKotak==7) RKubus.MakeMove(DEPAN3,false);
		
		if(GerakanKotak==8) RKubus.MakeMove(BAWAH,false);
		if(GerakanKotak==9) RKubus.MakeMove(BAWAH2,false);
		if(GerakanKotak==10) RKubus.MakeMove(BAWAH3,false);
		if(GerakanKotak==11) RKubus.MakeMove(BAWAH3,false);
		return;
	}
}

void GerakMouse(int x,int y)
{
	theta=(y-dragstarty)/100.0+theta0;
	phi=(dragstartx-x)/50.0+phi0;
	
	if(theta<-1.50) theta=-1.50;
	if(theta>1.50) theta=1.50;
	glutPostRedisplay();
}

void KlikDrag(int b,int s,int x,int y)
{
	if(s==GLUT_DOWN)
	{
		theta0=theta;
		phi0=phi;
		dragstartx=x;
		dragstarty=y;
	}
}
