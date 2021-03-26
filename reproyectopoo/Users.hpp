#ifndef User_hpp
#define User_hpp
#include <fstream>
#include <string.h>
using std::string;

enum permisos{
        ND, ESTUDIANTE, PROFESOR, DIR_ASI
};

enum MODALIDAD{
   INTERNO, EXTERNO
};

const int STORAGE_USERSYS = 100;
const int STORAGE_USERSYS_ACTA = 10;
const int STORAGE_USERSYS_STRINGS = 51;

class Usuario{
   protected:
      char usuario[ STORAGE_USERSYS_STRINGS ];
      char contra[ STORAGE_USERSYS_STRINGS ];
      char nombres[ STORAGE_USERSYS_STRINGS ];
      char apellidos[ STORAGE_USERSYS_STRINGS ];
      permisos type;
      MODALIDAD modalidad;
      int listaActas[ STORAGE_USERSYS_ACTA ];
      int numeroActas;
   public:
      Usuario( );
      Usuario( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad );
      void crearUsuario( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad );
      char * getUsuario( );
      char * getContra( );
      char * getNombres( );
      char * getApellidos( );
      int * getListaActas( );
      int getNumeroActas( );
      permisos getType();
      MODALIDAD getModalidad( );
      void setUsuario( char * usuario );
      void setContra( char * contra );
      void setType( permisos type );
      void setModalidad( MODALIDAD modalidad );
      void asociarActa( int dirActa );
};
class Estudiante: public Usuario{
   public:
      Estudiante( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad );
};

class Docente: public Usuario{
   public:
      Docente( char * usuario, char * contra, char * nombres, char * apellidos,  permisos type, MODALIDAD modalidad );
};

class Dir_Asis: public Usuario{
   public:
      Dir_Asis( char * usuario, char * contra, char * nombres, char * apellidos,  permisos type, MODALIDAD modalidad );
      void validarUsuario( class Usuario *validar, permisos type, MODALIDAD modalidad );
};
#endif