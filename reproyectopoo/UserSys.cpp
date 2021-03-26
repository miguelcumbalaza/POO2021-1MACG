#include "UserSys.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
UserSys::UserSys( ){
   int i;
   char usuarioDirectora[ 10 ] = "directora";
   usuarioDirectora[ 9 ] = '\0';
   char contraDirectora[ 14 ] = "dirMasIngSoft";
   contraDirectora[ 9 ] = '\0';
   char usuarioAsistente[ 10 ] = "asistente";
   usuarioAsistente[ 9 ] = '\0';
   char contraAsistente[ 14 ] = "asiMasIngSoft";
   contraAsistente[ 9 ] = '\0';
   listaUsuarios = new class Usuario[ STORAGE_USERSYS ];
   std::ifstream infile;
   infile.open( "userSys.dat", std::ios::binary | std::ios::in );
   if( infile ){
      infile.read( ( char * ) &( this->directora ), sizeof( class Usuario ) );
      infile.read( ( char * ) &( this->asistente ), sizeof( class Usuario ) );
      infile.read( ( char * ) &( this->numeroUsuarios ), sizeof( int ) );
      infile.read( ( char * )( this->listaUsuarios ), sizeof( class Usuario ) * numeroUsuarios );
      infile.close( );
   }
   else{
        this->directora.setUsuario( usuarioDirectora );
        this->directora.setContra( contraDirectora );
        this->directora.setType( DIR_ASI );
        this->asistente.setUsuario( usuarioAsistente );
        this->asistente.setContra( contraAsistente );
        this->asistente.setType( DIR_ASI ); // Al gusto del usuario
        this->numeroUsuarios = 0;
   }
}

UserSys::~UserSys( ){
   std::ofstream outfile;
   outfile.open( "userSys.dat", std::ios::binary | std::ios::trunc | std::ios::out );
   outfile.write( ( char * ) &( this->directora ), sizeof( class Usuario ) );
   outfile.write( ( char * ) &( this->asistente ), sizeof( class Usuario ) );
   outfile.write( ( char * ) &( this->numeroUsuarios ), sizeof( int ) );
   outfile.write( ( char * )( this->listaUsuarios ), sizeof( class Usuario ) * numeroUsuarios );
   outfile.close( );
   delete this->listaUsuarios;
}

int UserSys::getNumeroActas( int indice ){
   return this->listaUsuarios[ indice ].getNumeroActas( );
}

class Usuario * UserSys::getListaUsuarios( ){
   return this->listaUsuarios;
}

int UserSys::getNumeroUsuarios( ){
   return this->numeroUsuarios;
}

int UserSys::crearUsuario( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad ){
    int i, returnValue, existente = 0;
    for( i = 0; i < this->numeroUsuarios; i++ ){
        if( strcmp( this->listaUsuarios[ i ].getUsuario(), usuario ) == 0 ){
            std::cout << "Nombre de usuario ya existente. Por favor ingrese un nombre de usuario diferente..." << std::endl;
            existente = 1;
            break;
        }
    }
    if( existente == 0 ){
        this->listaUsuarios[ this->numeroUsuarios++ ].crearUsuario( usuario, contra, nombres, apellidos, type, modalidad );
        returnValue = this->numeroUsuarios -1;
    }
    else{
        returnValue = -1;
    }
    return returnValue;
}

void UserSys::asociarActa( int dirActa, int dirEstudiante, int dirDirector, int dirCodirector, int dirJurado1, int dirJurado2 ){
   ( * ( this->listaUsuarios + dirEstudiante ) ).asociarActa( dirActa );
   ( * ( this->listaUsuarios + dirDirector ) ).asociarActa( dirActa );
   ( * ( this->listaUsuarios + dirCodirector ) ).asociarActa( dirActa );
   ( * ( this->listaUsuarios + dirJurado1 ) ).asociarActa( dirActa );
   ( * ( this->listaUsuarios + dirJurado2 ) ).asociarActa( dirActa );
}

int * UserSys::getActasUsuario( class Usuario * usuario ){
   return usuario->getListaActas( );
}

class Usuario UserSys::getDirectora(){
    return this-> directora;
}

class Usuario UserSys::getAsistente(){
    return this-> asistente;
}