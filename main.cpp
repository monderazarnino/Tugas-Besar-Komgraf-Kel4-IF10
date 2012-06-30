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