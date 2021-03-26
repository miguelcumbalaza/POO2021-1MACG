#include "ActaSys.hpp"

// CLASE ACTA

Acta::Acta( ){
   int i;
   this->estado = ABIERTA;
   this->estadoCalif = PENDIENTE;
   this->fecha[ 50 ] = '\0';
   this->numeroActa = -1;
   this->dirEstudiante = -1;
   this->nombreTrabajo[ 50 ] = '\0';
   this->tipoTrabajo = NA;
   this->dirDirector = -1;
   this->dirCodirector = -1;
   this->dirJurado1 = -1;
   this->dirJurado2 = -1;
   for( i = 1; i < CRITERIA_CAP; i++ ){
      listaComJ1[ i ][ 0 ] = '\0';
      listaNotasJ1[ i ] = -1.0;
      listaComJ2[ i ][ 0 ] = '\0';
      listaNotasJ2[ i ] = -1.0;
   }
}

char * Acta::getFecha( ){
   return this->fecha;
}

int Acta::getNumeroActa( ){
   return this->numeroActa;
}

int Acta::getDirEstudiante( ){
   return this->dirEstudiante;
}

char * Acta::getNombreTrabajo( ){
   return this->nombreTrabajo;
}

TIPOTRABAJO Acta::getTipoTrabajo( ){
   return this->tipoTrabajo;
}

int Acta::getDirDirector( ){
  return this->dirDirector;
}

int Acta::getDirCodirector( ){
   return this->dirCodirector;
}

int Acta::getDirJurado1( ){
   return this->dirJurado1;
}

int Acta::getDirJurado2( ){
   return this->dirJurado2;
}

char ** Acta::getListaComJ1( ){
   return ( char ** )( this->listaComJ1 );
}

char * Acta::getComJ1( int indice ){
   return ( char * )( this->listaComJ1[ indice ] );
}

float * Acta::getListaNotasJ1( ){
   return this->listaNotasJ1;
}

char ** Acta::getListaComJ2( ){
   return ( char ** )( this->listaComJ2 );
}

char * Acta::getComJ2( int indice ){
   return ( char * )( this->listaComJ2[ indice ] );
}

float * Acta::getListaNotasJ2( ){
   return this->listaNotasJ2;
}

char * Acta::getComAdi( ){
   return this->comAdi;
}

float Acta::getNotaFinal( ){
   return this->notaFinal;
}

ESTADO_CALIFICACION Acta::getEstadoCalif( ){
   return this->estadoCalif;
}

void Acta::crearActa( char * fecha, int numeroActa, int dirEstudiante, char * nombreTrabajo, TIPOTRABAJO tipoTrabajo, int dirDirector, int dirCodirector, int dirJurado1, int dirJurado2 ){
   strcpy( this->fecha, fecha );
   this->numeroActa = numeroActa;
   this->dirEstudiante = dirEstudiante;
   strcpy( this->nombreTrabajo, nombreTrabajo );;
   this->tipoTrabajo = tipoTrabajo;
   this->dirDirector = dirDirector;
   this->dirCodirector = dirCodirector;
   this->dirJurado1 = dirJurado1;
   this->dirJurado2 = dirJurado2;
}

ESTADO_ACTA Acta::getEstado( ){
   return this->estado;
}

void Acta::setEstado( ESTADO_ACTA estado ){
   this->estado = estado;
}

void Acta::setNotaFinal( float notaFinal ){
   this->notaFinal = notaFinal;
}

void Acta::setEstadoCalif( ESTADO_CALIFICACION estadoCalif ){
   this->estadoCalif = estadoCalif;
}

// CLASE ACTASYS

ActaSys::ActaSys( ){
   int i;
   listaActas = new class Acta[ ACTAS_CAP ];
   std::ifstream infile;
   infile.open( "actaSys.dat", std::ios::binary | std::ios::in );
   if( infile ){
      infile.read( ( char * ) &( this->numeroActas ), sizeof( int ) );
      infile.read( ( char * )( this->listaActas ), sizeof( class Acta ) * numeroActas );
      infile.close( );
   }
   else{
      this->numeroActas = 0;
   }
   this->porcentajesPonderacion[ 0 ] = 0.2;
   this->porcentajesPonderacion[ 1 ] = 0.15;
   this->porcentajesPonderacion[ 2 ] = 0.1;
   this->porcentajesPonderacion[ 3 ] = 0.1;
   this->porcentajesPonderacion[ 4 ] = 0.2;
   this->porcentajesPonderacion[ 5 ] = 0.1;
   this->porcentajesPonderacion[ 6 ] = 0.075;
   this->porcentajesPonderacion[ 7 ] = 0.075;
   strcpy( listaCriterios[ 0 ], "Desarrollo y profundidad del tema" );
   strcpy( listaCriterios[ 1 ], "Desafio academico y cientifico del tema" );
   strcpy( listaCriterios[ 2 ], "Complimiento de los objetivos propuestos" );
   strcpy( listaCriterios[ 3 ], "Creatividad e innovacion de las soluciones y desarrollos propuestos" );
   strcpy( listaCriterios[ 4 ], "Validez de los resultados y conclusiones" );
   strcpy( listaCriterios[ 5 ], "Manejo de procesamiento de la informacion y bibliografia" );
   strcpy( listaCriterios[ 6 ], "Calidad y presentacion del documento escrito" );
   strcpy( listaCriterios[ 7 ], "Presentacion oral" );
   this->numeroCriterios = 8;
}

ActaSys::~ActaSys( ){
   std::ofstream outfile;
   outfile.open( "actaSys.dat", std::ios::binary | std::ios::trunc | std::ios::out );
   outfile.write( ( char * ) &( this->numeroActas ), sizeof( int ) );
   outfile.write( ( char * )( this->listaActas ), sizeof( class Acta ) * numeroActas );
   outfile.close( );
   delete this->listaActas;
}

char ** ActaSys::getListaCriterios( ){
   return (char ** ) ( this->listaCriterios );
}

char * ActaSys::getCriterio( int indice ){
   return (char * ) ( this->listaCriterios[ indice ] );
}

float * ActaSys::getPorcentajesPonderacion( ){
   return this->porcentajesPonderacion;
}

int ActaSys::getNumeroCriterios( ){
   return this->numeroCriterios;
}

Acta * ActaSys::getListaActas( ){
   return this->listaActas;
}

int ActaSys::getNumeroActas( ){
   return this->numeroActas;
}

int ActaSys::crearActa( char * fecha, int dirEstudiante, char * nombreTrabajo, TIPOTRABAJO tipoTrabajo, int dirDirector, int dirCodirector, int dirJurado1, int dirJurado2 ){
   this->listaActas[ this->numeroActas++ ].crearActa( fecha, this->numeroActas, dirEstudiante, nombreTrabajo, tipoTrabajo, dirDirector, dirCodirector, dirJurado1, dirJurado2 );
   return this->numeroActas - 1;
}