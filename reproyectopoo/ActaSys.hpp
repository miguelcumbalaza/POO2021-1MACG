#ifndef ActaSys_hpp
#define ActaSys_hpp

#include <iostream>
#include <fstream>
#include "userSys.hpp"

enum TIPOTRABAJO{
   NA, APLICADO, INVESTIGACION
};

enum ESTADO_ACTA{
   ABIERTA, CERRADA, ELIMINADA
};

enum ESTADO_CALIFICACION{
   PENDIENTE, REPROBADA, APROBADA
};

const int ACTAS_CAP = 100;
const int STRINGS_CAP = 51;
const int COMMENT_CHARS_CAP = 501;
const int CRITERIA_CHARS_CAP = 501;
const int CRITERIA_CAP = 20;

class Acta{
   private:
      ESTADO_ACTA estado;
      ESTADO_CALIFICACION estadoCalif;
      char fecha[ STRINGS_CAP ];
      int numeroActa;
      int dirEstudiante;
      char nombreTrabajo[ STRINGS_CAP ];
      TIPOTRABAJO tipoTrabajo;
      int dirDirector;
      int dirCodirector;
      int dirJurado1;
      int dirJurado2;
      char listaComJ1[ CRITERIA_CAP ][ COMMENT_CHARS_CAP ];
      float listaNotasJ1[ CRITERIA_CAP ];
      char listaComJ2[ CRITERIA_CAP ][ COMMENT_CHARS_CAP ];
      float listaNotasJ2[ CRITERIA_CAP ];
      char comAdi[ COMMENT_CHARS_CAP ];
      float notaFinal;
   public:
      Acta( );
      char * getFecha( );
      int getNumeroActa( );
      int getDirEstudiante( );
      char * getNombreTrabajo( );
      TIPOTRABAJO getTipoTrabajo( );
      int getDirDirector( );
      int getDirCodirector( );
      int getDirJurado1( );
      int getDirJurado2( );
      char ** getListaComJ1( );
      char * getComJ1( int indice );
      float * getListaNotasJ1( );
      char ** getListaComJ2( );
      char * getComJ2( int indice );
      float * getListaNotasJ2( );
      char * getComAdi( );
      float getNotaFinal( );
      ESTADO_CALIFICACION getEstadoCalif( );
      void crearActa( char * fecha, int numeroActa, int dirEstudiante, char * nombreTrabajo, TIPOTRABAJO tipoTrabajo, int dirDirector, int dirCodirector, int dirJurado1, int dirJurado2 );
      ESTADO_ACTA getEstado( );
      void setEstado( ESTADO_ACTA estado );
      void setNotaFinal( float notaFinal );
      void setEstadoCalif( ESTADO_CALIFICACION estadoCalif );
//      void generarTxtActa(  )
};

class ActaSys{
   public:
      char listaCriterios[ CRITERIA_CAP ][ CRITERIA_CHARS_CAP ];
      float porcentajesPonderacion[ CRITERIA_CAP ];
      int numeroCriterios;
      Acta * listaActas;
      int numeroActas;
   public:
      ActaSys( );
      ~ActaSys( );
      char ** getListaCriterios( );
      char * getCriterio( int indice );
      float * getPorcentajesPonderacion( );
      int getNumeroCriterios( );
      Acta * getListaActas( );
      int getNumeroActas( );
      int crearActa( char * fecha, int dirEstudiante, char * nombreTrabajo, TIPOTRABAJO tipoTrabajo, int dirDirector, int dirCdirector, int dirJurado1, int dirJurado2 );
};

#endif