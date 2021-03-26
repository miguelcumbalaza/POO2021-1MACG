#include "Users.hpp"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

Usuario::Usuario( ){
   this->usuario[ 50 ] = '\0';
   this->contra[ 50 ] = '\0';
   this->nombres[ 50 ] = '\0';
   this->apellidos[ 50 ] = '\0';
   this->numeroActas = 0;
   this->type = ND;
};

Usuario::Usuario( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad ){
   int i;
   strcpy( this->usuario, usuario );
   strcpy( this->contra, contra );
   strcpy( this->nombres, nombres );
   strcpy( this->apellidos, apellidos );
   this->type = type;
   for( i = 0; i < STORAGE_USERSYS_ACTA; i++ ){
      this->listaActas[ i ] = -1;
   }
}

void Usuario::crearUsuario( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad ){
   strcpy( this->usuario, usuario );
   strcpy( this->contra, contra );
   strcpy( this->nombres, nombres );
   strcpy( this->apellidos, apellidos );
   this->type = type;
   this->modalidad = modalidad;
}

char * Usuario::getUsuario( ){
   return this->usuario;
}

char * Usuario::getContra( ){
   return this->contra;
}

char * Usuario::getNombres( ){
   return this->nombres;
}

char * Usuario::getApellidos( ){
   return this->apellidos;
}

int * Usuario::getListaActas( ){
   return this->listaActas;
}

int Usuario::getNumeroActas( ){
   return this->numeroActas;
}

permisos Usuario::getType( ){
    return this->type;
}

MODALIDAD Usuario::getModalidad( ){
   return this-> modalidad;
}

void Usuario::setUsuario( char * usuario ){
   strcpy( this->usuario, usuario );
}

void Usuario::setContra( char * contra ){
   strcpy( this->contra, contra );
}

void Usuario::setType( permisos type ){
   this->type = type;
}

void Usuario::setModalidad( MODALIDAD type ){
   this->modalidad = modalidad;
}

void Usuario::asociarActa( int dirActa ){
   * ( this->listaActas + this->numeroActas++ ) = dirActa;
}

Estudiante::Estudiante( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad ): Usuario( usuario, contra, nombres, apellidos, type, modalidad ){ };

Docente::Docente( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad ): Usuario( usuario, contra, nombres, apellidos, type, modalidad ){ };

Dir_Asis::Dir_Asis( char * usuario, char * contra, char * nombres, char * apellidos, permisos type, MODALIDAD modalidad ): Usuario( usuario, contra, nombres, apellidos, type, modalidad ){ };

void Dir_Asis::validarUsuario( class Usuario * validar, permisos type, MODALIDAD modalidad ){
   validar->setType( type );
   validar->setModalidad( modalidad );
}