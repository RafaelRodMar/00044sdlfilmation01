/*****************************************************************************/
/*                      TECNICA FILMATION (2¦ PARTE)                         */
/*                                                                           */
/*      por: Jos‚ Antonio Acedo Mart¡n-Grande, miembro de "GOLDY GAMES"      */
/*                                                                           */
/*                      TEL: (91) 6 11 72 71 (MADRID)                        */
/*****************************************************************************/

/**************************** FICHEROS A INCLUIR  ****************************/

#include <dos.h>
#include <bios.h>
#include <conio.h>
#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>

/******************************* DEFINICIONES ********************************/

#define ALFANUMERICO     3
#define GRAFICO     	19
#define COLOR            0
#define NUM_OBJETOS	 5

#define AUM_X		25
#define AUM_Z		30
#define DIS_X		24
#define DIS_Z		16
#define SALTO           57
#define ESC		 1

#define ULTIMO		-1

/*********************** DECLARACIONES DE FUNCIONES **************************/

void  BORRA_ZONA_MEMORIA(char *, int);
void  COPIA_ZONA_MEMORIA(char *, char *);
void  DIBUJA_BLOQUE    (int *, char *, char *);
void  DIBUJA_BLOQUE_CUT(int *, char *, char *);
void  VUELCA_PANTALLA(int,int, int,int, int,int, char *);
void  SET_VECTORES(volatile char *);
void  UNSET_VECTORES(void);
void  asigna_modo_video(char);
void  lee_ficheros(const char *, char *);
void  descomprime_dibujo(char *);
void  asigna_rgb(char *);
void  asigna_memoria(void);
void  libera_memoria(void);
void  error_memoria(void);
void  error_fichero(void);
void  salir_al_dos(void);

/*************************** VARIABLES GLOBALES /*****************************/

char *dir_carga_dibujos;
char *dir_dibujo1;
char *dir_muestra_dibujo1;
char *dir_zona_pantalla;
FILE *handle_dibujos;
char  mapa_teclado[256];
char  dibujo1[] = "filma_2.pcx";
int   logotipo_filmation  [6] = {   0,31,   0,182, 133,14 };
int   logotipo_parte2     [6] = { 133,31,   0,  0,  75,18 };
int   logotipo_goldy_games[6] = {   0,46, 206,182, 114,18 };

int   mapa_zona_1[][6] = {   0,  0, 144, 36, 32,15, /* suelo rojo */
			     0,  0, 112, 52, 32,15,
			     0,  0, 144, 52, 32,15,
			     0,  0, 176, 52, 32,15,
			     0,  0,  80, 68, 32,15,
			     0,  0, 112, 68, 32,15,
			     0,  0, 144, 68, 32,15,
			     0,  0, 176, 68, 32,15,
			     0,  0, 208, 68, 32,15,
			     0,  0,  48, 84, 32,15,
			     0,  0,  80, 84, 32,15,
			     0,  0, 112, 84, 32,15,
			     0,  0, 144, 84, 32,15,
			     0,  0, 176, 84, 32,15,
			     0,  0, 208, 84, 32,15,
			     0,  0, 240, 84, 32,15,
			     0,  0,  16,100, 32,15,
			     0,  0,  48,100, 32,15,
			     0,  0,  80,100, 32,15,
			     0,  0, 112,100, 32,15,
			     0,  0, 144,100, 32,15,
			     0,  0, 176,100, 32,15,
			     0,  0, 208,100, 32,15,
			     0,  0, 240,100, 32,15,
			     0,  0, 272,100, 32,15,
			     0,  0,  16,116, 32,15,
			     0,  0,  48,116, 32,15,
			     0,  0,  80,116, 32,15,
			     0,  0, 112,116, 32,15,
			     0,  0, 144,116, 32,15,
			     0,  0, 176,116, 32,15,
			     0,  0, 208,116, 32,15,
			     0,  0, 240,116, 32,15,
			     0,  0, 272,116, 32,15,
			     0,  0,  48,132, 32,15,
			     0,  0,  80,132, 32,15,
			     0,  0, 112,132, 32,15,
			     0,  0, 144,132, 32,15,
			     0,  0, 176,132, 32,15,
			     0,  0, 208,132, 32,15,
			     0,  0, 240,132, 32,15,
			     0,  0,  80,148, 32,15,
			     0,  0, 112,148, 32,15,
			     0,  0, 144,148, 32,15,
			     0,  0, 176,148, 32,15,
			     0,  0, 208,148, 32,15,
			     0,  0, 112,164, 32,15,
			     0,  0, 144,164, 32,15,
			     0,  0, 176,164, 32,15,
			     0,  0, 144,180, 32,15,

			    32,  0, 128, 44, 32,15, /* suelo amarillo */
			    32,  0, 160, 44, 32,15,
			    32,  0,  96, 60, 32,15,
			    32,  0, 128, 60, 32,15,
			    32,  0, 160, 60, 32,15,
			    32,  0, 192, 60, 32,15,
			    32,  0,  64, 76, 32,15,
			    32,  0,  96, 76, 32,15,
                            32,  0, 128, 76, 32,15,
			    32,  0, 160, 76, 32,15,
			    32,  0, 192, 76, 32,15,
			    32,  0, 224, 76, 32,15,
			    32,  0,  32, 92, 32,15,
			    32,  0,  64, 92, 32,15,
			    32,  0,  96, 92, 32,15,
			    32,  0, 128, 92, 32,15,
			    32,  0, 160, 92, 32,15,
			    32,  0, 192, 92, 32,15,
			    32,  0, 224, 92, 32,15,
			    32,  0, 256, 92, 32,15,
			    32,  0,   0,108, 32,15,
			    32,  0,  32,108, 32,15,
			    32,  0,  64,108, 32,15,
			    32,  0,  96,108, 32,15,
			    32,  0, 128,108, 32,15,
			    32,  0, 160,108, 32,15,
			    32,  0, 192,108, 32,15,
			    32,  0, 224,108, 32,15,
			    32,  0, 256,108, 32,15,
			    32,  0, 288,108, 32,15,
			    32,  0,  32,124, 32,15,
			    32,  0,  64,124, 32,15,
			    32,  0,  96,124, 32,15,
			    32,  0, 128,124, 32,15,
			    32,  0, 160,124, 32,15,
			    32,  0, 192,124, 32,15,
			    32,  0, 224,124, 32,15,
			    32,  0, 256,124, 32,15,
			    32,  0,  64,140, 32,15,
			    32,  0,  96,140, 32,15,
			    32,  0, 128,140, 32,15,
			    32,  0, 160,140, 32,15,
			    32,  0, 192,140, 32,15,
			    32,  0, 224,140, 32,15,
			    32,  0,  96,156, 32,15,
			    32,  0, 128,156, 32,15,
			    32,  0, 160,156, 32,15,
			    32,  0, 192,156, 32,15,
			    32,  0, 128,172, 32,15,
			    32,  0, 160,172, 32,15,

			     0, 15,   0,116, 16,12, /* borde suelo izq */
			     0, 15,  16,124, 16,12,
			     0, 15,  32,132, 16,12,
			     0, 15,  48,140, 16,12,
			     0, 15,  64,148, 16,12,
                             0, 15,  80,156, 16,12,
			     0, 15,  96,164, 16,12,
			     0, 15, 112,172, 16,12,
			     0, 15, 128,180, 16,12,
			     0, 15, 144,188, 16,12,

			    16, 15, 304,116, 16,12, /* borde suelo der */
			    16, 15, 288,124, 16,12,
			    16, 15, 272,132, 16,12,
                            16, 15, 256,140, 16,12,
			    16, 15, 240,148, 16,12,
			    16, 15, 224,156, 16,12,
			    16, 15, 208,164, 16,12,
			    16, 15, 192,172, 16,12,
			    16, 15, 176,180, 16,12,
			    16, 15, 160,188, 16,12,

			   288,  0, 128,-28, 32,79, /* pared izq */
			   288,  0,  96,-12, 32,79,
			   288,  0,  64,  4, 32,79,
			   288,  0,  32, 20, 32,79,
			   288,  0,   0, 36, 32,79,

			   256,  0, 160,-28, 32,79, /* pared der */
			   256,  0, 192,-12, 32,79,
			   256,  0, 224,  4, 32,79,
			   256,  0, 256, 20, 32,79,
			   256,  0, 288, 36, 32,79,
			   ULTIMO
			 };

int   pos_objeto[6];
int   dist[NUM_OBJETOS][2];
int   sentido=AUM_X;

int   objetos_zona_1[NUM_OBJETOS][7] = { 64,  0,  0, 0, 0, 32,30, /*BOLA*/
					  0,170, 28, 0,44, 32,30,
					 32,170, 28, 8,44, 32,30,
					 64,170, 52, 0,44, 32,30,
					 96,170, 52, 8,44, 32,30
				       };

int   xyz_bola_a_zona_1[7] = {  64,  0,  0, 0, 0, 32,30 };
int   xyz_bola_b_zona_1[7] = {  96,  0,  0, 0, 0, 32,30 };
int   xyz_bola_c_zona_1[7] = { 128,  0,  0, 0, 0, 32,30 };
int   xyz_bola_d_zona_1[7] = { 160,  0,  0, 0, 0, 32,30 };

/********************************* PROGRAMA **********************************/

void main(void)
{
	int bloq, x, y, z, temp, n, m, x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, x4,y4,z4;

	asigna_memoria();
	asigna_modo_video(GRAFICO);
	lee_ficheros(dibujo1, dir_dibujo1);
	SET_VECTORES(mapa_teclado);
	BORRA_ZONA_MEMORIA(dir_muestra_dibujo1, COLOR);
	DIBUJA_BLOQUE(logotipo_filmation,   dir_dibujo1, dir_muestra_dibujo1);
	DIBUJA_BLOQUE(logotipo_parte2,      dir_dibujo1, dir_muestra_dibujo1);
	DIBUJA_BLOQUE(logotipo_goldy_games, dir_dibujo1, dir_muestra_dibujo1);

	for(bloq=0; mapa_zona_1[bloq][0]!=ULTIMO; bloq++)
	  DIBUJA_BLOQUE_CUT(&mapa_zona_1[bloq][0], dir_dibujo1, dir_muestra_dibujo1);

	while(mapa_teclado[0]!=ESC)
	{
	  COPIA_ZONA_MEMORIA(dir_muestra_dibujo1, dir_zona_pantalla);

	  x0=objetos_zona_1[0][2];
	  y0=objetos_zona_1[0][3];
	  z0=objetos_zona_1[0][4];

	  x1=objetos_zona_1[1][2];
	  y1=objetos_zona_1[1][3];
	  z1=objetos_zona_1[1][4];

	  x2=objetos_zona_1[2][2];
	  y2=objetos_zona_1[2][3];
	  z2=objetos_zona_1[2][4];

	  x3=objetos_zona_1[3][2];
	  y3=objetos_zona_1[3][3];
	  z3=objetos_zona_1[3][4];

	  x4=objetos_zona_1[4][2];
	  y4=objetos_zona_1[4][3];
	  z4=objetos_zona_1[4][4];

	  dist[0][0]=x0+y0+z0; dist[0][1]=0;
	  dist[1][0]=x1+y1+z1; dist[1][1]=1;
	  dist[2][0]=x2+y2+z2; dist[2][1]=2;
	  dist[3][0]=x3+y3+z3; dist[3][1]=3;
	  dist[4][0]=x4+y4+z4; dist[4][1]=4;

	  for(n=NUM_OBJETOS-1; n>0; n--)
	  {
	    for(m=0; m<n; m++)
	    {
	      if(dist[m][0] > dist[m+1][0])
	      {
		temp=dist[m][0]; dist[m][0]=dist[m+1][0]; dist[m+1][0]=temp;
		temp=dist[m][1]; dist[m][1]=dist[m+1][1]; dist[m+1][1]=temp;
	      }
	    }
	  }

	  for(n=0; n<NUM_OBJETOS; n++)
	  {
	    if(dist[n][1]==0)
	    {
	      x=objetos_zona_1[0][2];
	      y=objetos_zona_1[0][3];
	      z=objetos_zona_1[0][4];

	      if(mapa_teclado[0]==AUM_X) {
		sentido=AUM_X;
		if(x<72 &&
		  (x1>x0+8 || x1<x0+8 || y1-y0>=8 || y0-y1>=8 || z1-z0>=8 || z0-z1>=8) &&
		  (x2>x0+8 || x2<x0+8 || y2-y0>=8 || y0-y2>=8 || z2-z0>=8 || z0-z2>=8) &&
		  (x3>x0+8 || x3<x0+8 || y3-y0>=8 || y0-y3>=8 || z3-z0>=8 || z0-z3>=8) &&
		  (x4>x0+8 || x4<x0+8 || y4-y0>=8 || y0-y4>=8 || z4-z0>=8 || z0-z4>=8)) {
		    x++; objetos_zona_1[0][2]++;
		}
	      }
	      if(mapa_teclado[0]==AUM_Z) {
		sentido=AUM_Z;
		if(z<72 &&
		  (x1-x0>=8 || x0-x1>=8 || y1-y0>=8 || y0-y1>=8 || z1>z0+8 || z1<z0+8) &&
		  (x2-x0>=8 || x0-x2>=8 || y2-y0>=8 || y0-y2>=8 || z2>z0+8 || z2<z0+8) &&
		  (x3-x0>=8 || x0-x3>=8 || y3-y0>=8 || y0-y3>=8 || z3>z0+8 || z3<z0+8) &&
		  (x4-x0>=8 || x0-x4>=8 || y4-y0>=8 || y0-y4>=8 || z4>z0+8 || z4<z0+8)) {
		    z++; objetos_zona_1[0][4]++;
		}
	      }
	      if(mapa_teclado[0]==DIS_X) {
		sentido=DIS_X;
		if(x> 0 &&
		  (x1<x0-8 || x1>x0-8 || y1-y0>=8 || y0-y1>=8 || z1-z0>=8 || z0-z1>=8) &&
		  (x2<x0-8 || x2>x0-8 || y2-y0>=8 || y0-y2>=8 || z2-z0>=8 || z0-z2>=8) &&
		  (x3<x0-8 || x3>x0-8 || y3-y0>=8 || y0-y3>=8 || z3-z0>=8 || z0-z3>=8) &&
		  (x4<x0-8 || x4>x0-8 || y4-y0>=8 || y0-y4>=8 || z4-z0>=8 || z0-z4>=8)) {
		    x--; objetos_zona_1[0][2]--;
		}
	      }
	      if(mapa_teclado[0]==DIS_Z) {
		sentido=DIS_Z;
		if(z> 0 &&
		  (x1-x0>=8 || x0-x1>=8 || y1-y0>=8 || y0-y1>=8 || z1<z0-8 || z1>z0-8) &&
		  (x2-x0>=8 || x0-x2>=8 || y2-y0>=8 || y0-y2>=8 || z2<z0-8 || z2>z0-8) &&
		  (x3-x0>=8 || x0-x3>=8 || y3-y0>=8 || y0-y3>=8 || z3<z0-8 || z3>z0-8) &&
		  (x4-x0>=8 || x0-x4>=8 || y4-y0>=8 || y0-y4>=8 || z4<z0-8 || z4>z0-8)) {
		    z--; objetos_zona_1[0][4]--;
		}
	      }
	      if(mapa_teclado[0]==SALTO) {
		if(y<32 &&
		  (x1-x0>=8 || x0-x1>=8 || y1>y0+8 || y1<y0+8 || z1-z0>=8 || z0-z1>=8) &&
		  (x2-x0>=8 || x0-x2>=8 || y2>y0+8 || y2<y0+8 || z2-z0>=8 || z0-z2>=8) &&
		  (x3-x0>=8 || x0-x3>=8 || y3>y0+8 || y3<y0+8 || z3-z0>=8 || z0-z3>=8) &&
		  (x4-x0>=8 || x0-x4>=8 || y4>y0+8 || y4<y0+8 || z4-z0>=8 || z0-z4>=8)) {
		    y+=4; objetos_zona_1[0][3]+=4;
		}
	      }

	      if(sentido==AUM_X) {
		pos_objeto[0]=xyz_bola_b_zona_1[0];
		pos_objeto[1]=xyz_bola_b_zona_1[1];
	      }
	      if(sentido==AUM_Z) {
		pos_objeto[0]=xyz_bola_a_zona_1[0];
		pos_objeto[1]=xyz_bola_a_zona_1[1];
	      }
	      if(sentido==DIS_X) {
		pos_objeto[0]=xyz_bola_d_zona_1[0];
		pos_objeto[1]=xyz_bola_d_zona_1[1];
	      }
	      if(sentido==DIS_Z) {
		pos_objeto[0]=xyz_bola_c_zona_1[0];
		pos_objeto[1]=xyz_bola_c_zona_1[1];
	      }
	      pos_objeto[4]=objetos_zona_1[0][5];
	      pos_objeto[5]=objetos_zona_1[0][6];
	    }

	    m=dist[n][1];

	    if(m==1 || m==2 || m==3 || m==4)
	    {
	      x=objetos_zona_1[m][2];
	      y=objetos_zona_1[m][3];
	      z=objetos_zona_1[m][4];

	      pos_objeto[0]=objetos_zona_1[m][0];
	      pos_objeto[1]=objetos_zona_1[m][1];
	      pos_objeto[4]=objetos_zona_1[m][5];
	      pos_objeto[5]=objetos_zona_1[m][6];
	    }

	    pos_objeto[2]=144+((x-z)    << 1);
	    pos_objeto[3]= 21+ (x+z)-(y << 1);

	    DIBUJA_BLOQUE_CUT(pos_objeto, dir_dibujo1, dir_zona_pantalla);
	  }

	  VUELCA_PANTALLA(0,0, 0,0, 320,200, dir_zona_pantalla);

	  if(mapa_teclado[0]!=SALTO && objetos_zona_1[0][3]>0 && y>0 &&
	    (x1-x0>=8 || x0-x1>=8 || y1<y0-8 || y1>y0-8 || z1-z0>=8 || z0-z1>=8) &&
	    (x2-x0>=8 || x0-x2>=8 || y2<y0-8 || y2>y0-8 || z2-z0>=8 || z0-z2>=8) &&
	    (x3-x0>=8 || x0-x3>=8 || y3<y0-8 || y3>y0-8 || z3-z0>=8 || z0-z3>=8) &&
	    (x4-x0>=8 || x0-x4>=8 || y4<y0-8 || y4>y0-8 || z4-z0>=8 || z0-z4>=8)) {
	      objetos_zona_1[0][3]--;
	  }
	}
	salir_al_dos();
}

void salir_al_dos(void)
{
        asigna_modo_video(ALFANUMERICO);
        libera_memoria();
	UNSET_VECTORES();
	textcolor(WHITE); textbackground(BLUE);
	cprintf("Copyright (c) Goldy Games 1994. Jos‚ Antonio Acedo Mart¡n-Grande. Continuar  ...");
	gotoxy(1,24);
        exit(0);
}

void asigna_memoria(void)
{
	if((dir_carga_dibujos  =(char *)malloc(320*200))==NULL) error_memoria();
	if((dir_dibujo1        =(char *)malloc(320*200))==NULL) error_memoria();
	if((dir_muestra_dibujo1=(char *)malloc(320*200))==NULL) error_memoria();
	if((dir_zona_pantalla  =(char *)malloc(320*200))==NULL) error_memoria();
}

void libera_memoria(void)
{
	free(dir_carga_dibujos);
	free(dir_dibujo1);
	free(dir_muestra_dibujo1);
	free(dir_zona_pantalla);
}

void error_memoria(void)
{
        asigna_modo_video(ALFANUMERICO);
        libera_memoria();
        printf("No hay suficiente memoria. Libere programas residentes.");
        exit(1);
}

void error_fichero(void)
{
        asigna_modo_video(ALFANUMERICO);
        libera_memoria();
        printf("Error leyendo fichero .PCX");
        exit(1);
}

void asigna_modo_video(char modo)     /* asigna el modo de v¡deo indicado */
{                                     /* en la variable "modo"            */
        union REGS ent, sal;

        ent.h.al = modo;
        ent.h.ah = 0;
	int86(16, &ent, &sal);        /* funci¢n para asignar el modo de video */
}

void lee_ficheros(const char *file, char *dir_dibujo)
{
        char *dir;

        dir=dir_carga_dibujos;
        if((handle_dibujos = fopen(file, "rb"))==NULL) error_fichero();
        while(!feof(handle_dibujos)) { *dir++=getc(handle_dibujos); }
        fclose(handle_dibujos);
        descomprime_dibujo(dir_dibujo);
}

void descomprime_dibujo(char *dir_escritura)
{
        unsigned char  byte;
                 char *dir_lectura;
                 int   columnas, filas, contador;

	dir_lectura=dir_carga_dibujos+128;   /* inicio del dibujo comprimido */

	for(filas=200; filas>0; filas--)
	{
          columnas=320;
          dir_escritura-=columnas; dir_escritura+=320;
	  while(columnas>0)
	  {
            byte=(unsigned)*dir_lectura++;
	    if(byte<=192)
	    {
	      *dir_escritura++=byte; columnas--;
	    }
	    else
	    {
              contador=byte&63; byte=*dir_lectura++;
	      for(; contador>0; contador--)
	      {
		*dir_escritura++=byte; columnas--;
	      }
            }
          }
        }
	asigna_rgb(dir_lectura+1);     /* remapea los 256 colores del dibujo */
}

void asigna_rgb(char *dir_lectura)
{
        struct   SREGS  seg;
        union     REGS  ent, sal;
        unsigned  int   n;
        long      int   dir;
                  char *dir_col;

	dir_col=dir_lectura;                      /* divide entre  */
	for(n=256*3; n>0; n--) {                  /* 4 los colores */
          *dir_col=*dir_col >> 2; dir_col++;
        }

	dir   =(long)dir_lectura;                 /* obtiene el segmento     */
	seg.es=(int)(dir >> 16);                  /* donde estan los colores */

        ent.h.al =  18;
        ent.h.ah =  16;
        ent.x.bx =   0;
        ent.x.cx = 256;
	ent.x.dx = (int)dir_lectura;       /* offset de los colores            */
	int86x(0x10, &ent, &sal, &seg);    /* funci¢n para asignar los colores */
}
