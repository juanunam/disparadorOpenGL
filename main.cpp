#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <stack>
#include <set>
using namespace std;

#define PI 3.14159265

//================================================================
//================================================================
GLfloat mat_especular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat no_shininess[] = { 128.0 };
double rotate_z = 0;
double rotate_y = 0;
double rotate_x = 0;
double translate_x=0;
double translate_y=0;
int miraX=0;
int miraY=0;
int miraZ=0;
GLuint indice = glGenLists(55);
map<int,GLuint> mapaCubos;
map<int,int> tamanoCubos;
map<int, pair<int,int> > rotacionesCubo;
int numeroCubos=0;
double desplazamientosCubo[15][3]=
{
  {0,0,0},
  {15,0,0},
  {0,15,0},
  {-15,0,0},
  {2,-15,0},
  {3,0,0},
  {15,0,0},
  {0,15,0},
  {-15,0,0},
  {4,-15,0},
  {0,2,0},
  {15,0,0},
  {1,15,0},
  {-15,1,0},
  {0,-15,0}
};
//================================================================
//variables para poner tiempo en pantalla
//================================================================
time_t horaInicio;
time_t horaActual;
//================================================================
//================================================================

//================================================================
//variables vertices
//================================================================
int puntoRojo[8][3]=
{
  {-1,-1,-1},
  {-1,1,-1},
  {-1,1,1},
  {-1,-1,1},
  {1,-1,-1},
  {1,1,-1},
  {1,1,1},
  {1,-1,1}
  
};

int vertices[54][4][3]=
{
// Cara 1
 { //vertice 1
  {-3,-3,-3},  {-3,-3,-1},  {-3,-1,-3},  {-3,-1,-1}
 },
 { //vertice 4
  {-3,-3,-1},  {-3,-3,1},  {-3,-1,-1},  {-3,-1,1}
 },
 { //vertice 7
  {-3,-3,1},  {-3,-3,3},  {-3,-1,1},  {-3,-1,3}
 },
 { //vertice 2
  {-3,-1,-3},  {-3,-1,-1},  {-3,1,-3},  {-3,1,-1}
 },
 { //vertice 5
  {-3,-1,-1},  {-3,-1,1},  {-3,1,-1},  {-3,1,1}
 },
 { //vertice 8
  {-3,-1,1},  {-3,-1,3},  {-3,1,1},  {-3,1,3}
 },
 { //vertice 3
  {-3,1,-3},  {-3,1,-1},  {-3,3,-3},  {-3,3,-1}
 },
 { //vertice 6
  {-3,1,-1},  {-3,1,1},  {-3,3,-1},  {-3,3,1}
 },
 { //vertice 9
  {-3,1,1},  {-3,1,3},  {-3,3,1},  {-3,3,3}
 },
// Cara 2
 { //vertice 16
  {3,-3,1},  {3,-3,3},  {3,-1,1},  {3,-1,3}
 },
 { //vertice 13
  {3,-3,-1},  {3,-3,1},  {3,-1,-1},  {3,-1,1}
 },
 { //vertice 10
  {3,-3,-3},  {3,-3,-1},  {3,-1,-3},  {3,-1,-1}
 },
 { //vertice 17
  {3,-1,1},  {3,-1,3},  {3,1,1},  {3,1,3}
 },
 { //vertice 14
  {3,-1,-1},  {3,-1,1},  {3,1,-1},  {3,1,1}
 },
 { //vertice 11
  {3,-1,-3},  {3,-1,-1},  {3,1,-3},  {3,1,-1}
 },
 { //vertice 18
  {3,1,1},  {3,1,3},  {3,3,1},  {3,3,3}
 },
 { //vertice 15
  {3,1,-1},  {3,1,1},  {3,3,-1},  {3,3,1}
 },
 { //vertice 12
  {3,1,-3},  {3,1,-1},  {3,3,-3},  {3,3,-1}
 },

// Cara 3
 { //vertice 25
  {-3,-3,1},  {-3,-3,3},  {-1,-3,1},  {-1,-3,3}
 },
 { //vertice 22
  {-3,-3,-1},  {-3,-3,1},  {-1,-3,-1},  {-1,-3,1}
 },
 { //vertice 19
  {-3,-3,-3},  {-3,-3,-1},  {-1,-3,-3},  {-1,-3,-1}
 },
 { //vertice 26
  {-1,-3,1},  {-1,-3,3},  {1,-3,1},  {1,-3,3}
 },
 { //vertice 23
  {-1,-3,-1},  {-1,-3,1},  {1,-3,-1},  {1,-3,1}
 },
 { //vertice 20
  {-1,-3,-3},  {-1,-3,-1},  {1,-3,-3},  {1,-3,-1}
 },
 { //vertice 27
  {1,-3,1},  {1,-3,3},  {3,-3,1},  {3,-3,3}
 },
 { //vertice 24
  {1,-3,-1},  {1,-3,1},  {3,-3,-1},  {3,-3,1}
 },
 { //vertice 21
  {1,-3,-3},  {1,-3,-1},  {3,-3,-3},  {3,-3,-1}
 },
// Cara 4

 { //vertice 36
  {1,3,1},  {1,3,3},  {3,3,1},  {3,3,3}
 },
 { //vertice 33
  {1,3,-1},  {1,3,1},  {3,3,-1},  {3,3,1}
 },
 { //vertice 30
  {1,3,-3},  {1,3,-1},  {3,3,-3},  {3,3,-1}
 },

 { //vertice 35
  {-1,3,1},  {-1,3,3},  {1,3,1},  {1,3,3}
 },
 { //vertice 32
  {-1,3,-1},  {-1,3,1},  {1,3,-1},  {1,3,1}
 },
 { //vertice 29
  {-1,3,-3},  {-1,3,-1},  {1,3,-3},  {1,3,-1}
 },

 { //vertice 34
  {-3,3,1},  {-3,3,3},  {-1,3,1},  {-1,3,3}
 },
 { //vertice 31
  {-3,3,-1},  {-3,3,1},  {-1,3,-1},  {-1,3,1}
 },
 { //vertice 28
  {-3,3,-3},  {-3,3,-1},  {-1,3,-3},  {-1,3,-1}
 },
// Cara 5

 { //vertice 39
  {1,-3,-3},  {1,-1,-3},  {3,-3,-3},  {3,-1,-3}
  },
 { //vertice 38
  {-1,-3,-3},  {-1,-1,-3},  {1,-3,-3},  {1,-1,-3}
  },
 { //vertice 37
  {-3,-3,-3},  {-3,-1,-3},  {-1,-3,-3},  {-1,-1,-3}
  },

 { //vertice 42
  {1,-1,-3},  {1,1,-3},  {3,-1,-3},  {3,1,-3}
  },
 { //vertice 41
  {-1,-1,-3},  {-1,1,-3},  {1,-1,-3},  {1,1,-3}
  },

 { //vertice 40
  {-3,-1,-3},  {-3,1,-3},  {-1,-1,-3},  {-1,1,-3}
  },

 { //vertice 45
  {1,1,-3},  {1,3,-3},  {3,1,-3},  {3,3,-3}
},
 { //vertice 44
  {-1,1,-3},  {-1,3,-3},  {1,1,-3},  {1,3,-3}
  },
 { //vertice 43
  {-3,1,-3},  {-3,3,-3},  {-1,1,-3},  {-1,3,-3}
  },
// Cara 6
 { //vertice 46
  {-3,-3,3},  {-3,-1,3},  {-1,-3,3},  {-1,-1,3}
  },
 { //vertice 47
  {-1,-3,3},  {-1,-1,3},  {1,-3,3},  {1,-1,3}
  },
 { //vertice 48
  {1,-3,3},  {1,-1,3},  {3,-3,3},  {3,-1,3}
  },
 { //vertice 49
  {-3,-1,3},  {-3,1,3},  {-1,-1,3},  {-1,1,3}
  },
 { //vertice 50
  {-1,-1,3},  {-1,1,3},  {1,-1,3},  {1,1,3}
  },
 { //vertice 51
  {1,-1,3},  {1,1,3},  {3,-1,3},  {3,1,3}
  },
 { //vertice 52
  {-3,1,3},  {-3,3,3},  {-1,1,3},  {-1,3,3}
  },
 { //vertice 53
  {-1,1,3},  {-1,3,3},  {1,1,3},  {1,3,3}
  },
 { //vertice 54
  {1,1,3},  {1,3,3},  {3,1,3},  {3,3,3}
  }
};
 int colores[54]=
{ 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 3,
  4, 4, 4, 4, 4, 4, 4, 4, 4,
  5, 5, 5, 5, 5, 5, 5, 5, 5
};
GLfloat color[8][4] =
{
  {1.0,1.0,0.0,0.5}, //amarillo 0
  {1.0,1.0,1.0,0.5},//Blanco 1
  {0.0,1.0,0.0,0.5}, //Verde 2
  {0.0,0.0,1.0,0.5},//Azul 3
  {1.0,0.0,0.0,0.5}, // Rojo 4
  {0.9,0.38,0.0,0.5}, //naranja 5
  {1.0,1.0,1.0,0.5},//Blanco
  {0.0,0.0,0.0,1.0}//negro
};
//================================================================
//Funciones prototipo
//================================================================
void relizarAccion(string accion,int parametro);
bool completado();
string convierteColores();
void guardarArchivo();
void guardarPasos();
void dibujaVertice(int vertice);
void relizarAccion(string accion,int parametro);
void permutaVertices(int a,int b);
void permutaVerticesRenglon(int a,int b,int renglon);
void permutaVerticesColumna(int a,int b,int columna);
void giraDerecha(int renglon);
void giraIzquierda(int renglon);
void giraArriba(int columna);
void giraAbajo(int columna);
void arriba();
void abajo();
void derecha();
void izquierda();
string posible(string actual);
void hacerPuntoRojo();
void moverAleatoriamenteCubos();
void generaMira();
int cubosRestantes();
//================================================================
//================================================================
//================================================================
//Funciones consulta al cubo
//================================================================
bool completado(){
  int numeroInicial=0;
  for (int j = 0; j < 6; ++j)
  {
    numeroInicial=colores[j*9];
    for(int i=0;i<9;i++){
      if(numeroInicial!=colores[j*9+i])
        return false;
    }
  }
  return true;
}

bool pegarCubo(int cubo){
    if(miraX+1>=desplazamientosCubo[cubo][1] &&  miraX-1<=desplazamientosCubo[cubo][1] && miraY+1>=desplazamientosCubo[cubo][2] &&  miraY-1<=desplazamientosCubo[cubo][2]  )
      return true;
    return false;
}
string posible(string actual){
  
}

//=================================================================
//Funciones OpenGL
//=================================================================
void hacerPuntoRojo(){
 glBegin(GL_QUADS);
 glColor4fv(color[4]);
 glVertex3iv(puntoRojo[0]);
 glVertex3iv(puntoRojo[1]);
 glVertex3iv(puntoRojo[2]);
 glVertex3iv(puntoRojo[3]);

 glVertex3iv(puntoRojo[4]);
 glVertex3iv(puntoRojo[5]);
 glVertex3iv(puntoRojo[6]);
 glVertex3iv(puntoRojo[7]);

 glVertex3iv(puntoRojo[0]);
 glVertex3iv(puntoRojo[3]);
 glVertex3iv(puntoRojo[7]);
 glVertex3iv(puntoRojo[4]);

 glVertex3iv(puntoRojo[1]);
 glVertex3iv(puntoRojo[2]);
 glVertex3iv(puntoRojo[6]);
 glVertex3iv(puntoRojo[5]);

 glVertex3iv(puntoRojo[0]);
 glVertex3iv(puntoRojo[1]);
 glVertex3iv(puntoRojo[5]);
 glVertex3iv(puntoRojo[4]);

 glVertex3iv(puntoRojo[3]);
 glVertex3iv(puntoRojo[2]);
 glVertex3iv(puntoRojo[6]);
 glVertex3iv(puntoRojo[7]);
 glEnd();
}
void dibujaVertice(int vertice){

  glLineWidth(1.0);
  glBegin(GL_QUADS);

    glColor4fv(color[colores[vertice]]);

    glVertex3iv(vertices[vertice][0]);
    glVertex3iv(vertices[vertice][1]);
    glVertex3iv(vertices[vertice][3]);
    glVertex3iv(vertices[vertice][2]);

  glEnd();
  glLineWidth(4.0);
  glBegin(GL_LINE_STRIP);

    glColor4fv(color[7]);
    glVertex3iv(vertices[vertice][0]);
    glVertex3iv(vertices[vertice][1]);
    glVertex3iv(vertices[vertice][3]);
    glVertex3iv(vertices[vertice][2]);
    glVertex3iv(vertices[vertice][0]);
  glEnd();
}
void cuboRubik()
{

    glMaterialfv(GL_FRONT, GL_AMBIENT, color[7]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[7]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[7]);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    

  
  glColor3f(1.0,1.0,1.0);
  time(&horaActual);
  double segundos=difftime(horaActual,horaInicio);
  char segundosChar[50];

  sprintf (segundosChar, "%lf faltan %d cubos",segundos,cubosRestantes());
  string cadena="Puntaje : ";
  for (int i = 0; i < strlen(segundosChar); ++i)
  {
    cadena+=segundosChar[i];
  }
  if(!cubosRestantes())
    cadena="Ganaste!!";

  glRasterPos3i( 0,-15, 18);
  for (int i = 0; i < cadena.size(); ++i)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cadena[i]);
  }
  for (int k = 0; k < numeroCubos; ++k)
  for(int i=0;i<tamanoCubos[k];i=i+1){ 

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[colores[i]]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[colores[i]]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[colores[i]]);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glTranslatef(desplazamientosCubo[k][0],desplazamientosCubo[k][1],desplazamientosCubo[k][2]);
   
    glRotatef(rotacionesCubo[k].first,0,1,0);
    glRotatef(rotacionesCubo[k].second,0,0,1);
    glCallList(mapaCubos[k]+i+1); 
    glPopMatrix();
  }
 

}


//=================================================================
//=================================================================
//Funciones para operar en el cubo
//=================================================================
void moverAleatoriamenteCubos(){
  for(int i=0;i<numeroCubos;i++){
    int opcion=rand()%3;
    int orientacion=(rand()*i)%2;
    int orientacion2=(rand()*i+i)%3;
    double desplazamientoActual= i/10+0.5;
    if(orientacion2==0){
      if(orientacion==1){
        if(desplazamientosCubo[i][2]<10)
          desplazamientosCubo[i][2]+=desplazamientoActual;
  
      }else{
        if(desplazamientosCubo[i][2]>-10)
          desplazamientosCubo[i][2]-=desplazamientoActual;
      }
    }else if(orientacion2==1){
      if(orientacion==1){
        if(desplazamientosCubo[i][1]<30)
          desplazamientosCubo[i][1]+=desplazamientoActual;
  
      }else{
        if(desplazamientosCubo[i][1]>-30)
          desplazamientosCubo[i][1]-=desplazamientoActual;
      }
     
    }else if(orientacion2==2){
      if(orientacion==1){
        if(desplazamientosCubo[i][0]<25)
          desplazamientosCubo[i][0]+=desplazamientoActual;
  
      }else{
        if(desplazamientosCubo[i][0]>-25)
          desplazamientosCubo[i][0]-=desplazamientoActual;
      }
     
    }
   
      rotacionesCubo[i].first+=1; 
    
  }
}
int cubosRestantes(){
  int suma=0;
  for(int i=0;i<numeroCubos;i++)
    if(tamanoCubos[i]>0)
      suma++;

  return suma;
}
void specialKeys( int key, int x, int y )
{
    
    glutPostRedisplay();
}

void teclado(unsigned char key,int x, int y){
  if (key == 'd')
  translate_x-=1;
  else if (key == 'a')
  translate_x+=1;
  else if (key == 's')
  translate_y+=1;
  else if (key == 'w')
  translate_y-=1;
  glutPostRedisplay();
}
void myMouse(int x, int y){
    
    miraX=(x-320)/10;
    miraY=-(y-240)/10;
   
    miraZ=0;;
}
void display()
{

    /*for (int i = 0; i < numeroCubos; ++i)
    {
      rotacionesCubo[i].first+=1; 
      if(tamanoCubos[i]<20){
          if(desplazamientosCubo[i][2]<=10){
            desplazamientosCubo[i][2]+=0.2; 
          }else{
            desplazamientosCubo[i][2]=-10.0;
          }
      } 
    }*/
    moverAleatoriamenteCubos();
  //scanf("%d ",&numeroInicio);

    glClearColor(0.0,1.0,1.0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 300 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt
        (
        40, 4, 10,
        0, 0, 0,
        0, 0, 1
        );

glTranslatef(translate_x, translate_y, 0.0 );

    cuboRubik();
    glPointSize(7.0);
   

    generaMira();
    glutSwapBuffers();
}
void inicializaLuz(){
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat light_diffuse[] = { 0.8,  0.8, 0.8, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0.0, 0.0, 500.0, 1.0 };

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
     


  
   
}
void generaMira(){
  glMaterialfv(GL_FRONT, GL_AMBIENT, color[7]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[7]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[7]);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    
   glColor3f(1.0,1.0,1.0);
    set<int> listaMiras;
    std::set<int>::iterator it;
    for(int i=0;i<numeroCubos;i++){
      if(tamanoCubos[i]>0){
          listaMiras.insert(desplazamientosCubo[i][0]);
      }
    
    }
    
    for (it=listaMiras.begin(); it!=listaMiras.end(); ++it){
      glBegin(GL_LINE_LOOP);
      for(int i =0; i <= 300; i++){
        double angle = 2 * PI * i / 300;
        double x = cos(angle);
        double y = sin(angle);
        glVertex3d(*it,miraX+2*x,miraY+2*y);
      }
      glEnd(); 
    }
}
void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}
void motion(int x,int y){
  

  myMouse(x,y);
  cout<<"mira en x="<<x<<" y="<<y<<endl;
 glutPostRedisplay();
}

void mouseClickHandler(int button, int state, int x, int y)
{
  
    myMouse(x,y);
    for(int i=0;i<numeroCubos;i++){
      if(pegarCubo(i)){
        tamanoCubos[i]--;
        rotacionesCubo[i].second+=20.0;
      }
    }
    glutPostRedisplay();
}

void dibujaVerticeLista(int contenedor,int vertice){

  glLineWidth(1.0);
  if(!mapaCubos[contenedor]){
    mapaCubos[contenedor]=glGenLists(55);
    tamanoCubos[contenedor]=54;
    rotacionesCubo[contenedor].first=0.0;
    rotacionesCubo[contenedor].second=0.0;
  }
   glNewList( mapaCubos[contenedor]+vertice+1,GL_COMPILE);
    glBegin(GL_QUADS);

      glColor4fv(color[colores[vertice]]);

      glVertex3iv(vertices[vertice][0]);
      glVertex3iv(vertices[vertice][1]);
      glVertex3iv(vertices[vertice][3]);
      glVertex3iv(vertices[vertice][2]);

    glEnd();
    
        glLineWidth(4.0);
        glBegin(GL_LINE_STRIP);

          glColor4fv(color[7]);
          glVertex3iv(vertices[vertice][0]);
          glVertex3iv(vertices[vertice][1]);
          glVertex3iv(vertices[vertice][3]);
          glVertex3iv(vertices[vertice][2]);
          glVertex3iv(vertices[vertice][0]);
        glEnd();
    if(vertice==0){
      hacerPuntoRojo();
    }
  glEndList();

}
void init(){
  time(&horaInicio);
  for (int k = 0; k < numeroCubos; ++k)
  for(int i=0;i<54;i=i+1){ 
    dibujaVerticeLista(k,i);
  }
}
//=================================================================
//=================================================================
int main( int argc, char **argv )
{
    cout<<"Cuantos cubos quieres(1-15):";
    cin>>numeroCubos;
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "GLUT" );
    glutDisplayFunc( display );
    glutSpecialFunc( specialKeys );
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseClickHandler);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    glEnable( GL_DEPTH_TEST );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
  glutSetCursor(GLUT_CURSOR_NONE);
   init();
   inicializaLuz();
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
