#ifndef UserSys_hpp
#define UserSys_hpp
#include "Users.hpp"
class UserSys{
   private:
      class Usuario directora;
      class Usuario asistente;
      class Usuario * listaUsuarios;
      int numeroUsuarios;
   public:
      UserSys( );
      ~UserSys( );

      class Usuario getDirectora();
      class Usuario getAsistente();
      int getNumeroActas( int indice );
      class Usuario * getListaUsuarios( );
      int getNumeroUsuarios( );
      int crearUsuario( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad );
      void asociarActa( int dirActa, int dirEstudiante, int dirDirector, int dirCodirector, int dirJurado1, int dirJurado2 );
      int * getActasUsuario( class Usuario * usuario );
};
#endif