#include "loginSystem.hpp"
#include "UserSys.hpp"
#include "ActaSys.hpp"
#include <iostream>
#include <string>
#include <istream>
#include <string.h>
#include <stdio.h>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

void informarAplicados( class Acta * lisaActas, int numeroActas ){
    int contador = 0;
    cout<< "Actas aplicadas:" <<endl;
    for( int i = 0; i < numeroActas; i++ ){
        if( lisaActas[ i ].getTipoTrabajo() == APLICADO ){
            cout<< "Acta #" << lisaActas[ i ].getNumeroActa() <<endl;
            contador++;
        }
    }
    if( contador > 0 ){
        cout<< "Existen " << contador << " actas aplicadas" << endl;
    }
    else{
        cout<< "No hay actas de tipo aplicado en existencia" << endl;
    }
}

void informarInvestigacion( class Acta * lisaActas, int numeroActas ){
    int contador = 0;
    cout<< "Actas de investigacion:" <<endl;
    for( int i = 0; i < numeroActas; i++ ){
        if( lisaActas[ i ].getTipoTrabajo() == INVESTIGACION ){
            cout<< "Acta #" << lisaActas[ i ].getNumeroActa() <<endl;
            contador++;
        }
    }
    if( contador > 0 ){
        cout<< "Existen " << contador << " actas de investigacion" << endl;
    }
    else{
        cout<< "No hay actas de tipo investigacion en existencia" << endl;
    }
}

void contarDirecciones( class Acta * listaActas, int numeroActas, class Usuario * listaProfes, int numeroProfesores){
    int contador = 0, pasar = 0, profesor;
    cout<< "Lista de profesores: " << endl;
    for( int i = 0; i < numeroProfesores; i++){
        if( listaProfes[ i ].getType() ==  PROFESOR ){
            cout<< i + 1 << ". profesor " << listaProfes[ i ].getNombres() << listaProfes[ i ].getApellidos() << endl;
        }
    }
    do{
        cout<< "por favor ingrese el numero del profesor del cual desea revisar sus trabajos como director:" << endl;cin>>profesor;
        profesor = profesor - 1;
        if( listaProfes[ profesor ].getType() == ESTUDIANTE || profesor < 0  ){
            cout<< "El usuario escogido no es un profesor." << endl;
        }
        else{
            int * listaActasProfesor = listaProfes[ profesor ].getListaActas();
            int numeroActasProfesor = listaProfes[ profesor ].getNumeroActas();
            pasar = 1;
            for( int i =  0; i < numeroActasProfesor; i++){
                for( int j = 0; j < numeroActas; j++){
                    if( j == listaActasProfesor[ i ]  && listaActas[j].getDirDirector() == profesor ){
                        contador++;
                    }
                }
            }
        }
    }while( pasar == 0 );
    if( contador == 0 ){
        cout<< "Este profesor no ha dirigido ningun acta" << endl;
    }
    else{
        cout<< "Este profesor ha dirigido " << contador << " actas." << endl;
    }
}

void mostrarActasJurados( class Acta * listaActas, int numeroActas, class Usuario * listaProfes, int numeroProfesores){
    int contador = 0, pasar = 0, profesor;
    cout<< "Lista de profesores: " << endl;
    for( int i = 0; i < numeroProfesores; i++){
        if( listaProfes[ i ].getType() ==  PROFESOR ){
            cout<< i + 1 << ". profesor " << listaProfes[ i ].getNombres() << listaProfes[ i ].getApellidos() << endl;
        }
    }
    do{
        cout<< "por favor ingrese el numero del profesor del cual desea revisar sus trabajos como director:" << endl;cin>>profesor;
        profesor = profesor - 1;
        if( listaProfes[ profesor ].getType() == ESTUDIANTE || profesor < 0  ){
            cout<< "El usuario escogido no es un profesor." << endl;
        }
        else{
            cout << "Actas en las que ha participado el profesor como jurado: " << endl;
            int * listaActasProfesor = listaProfes[ profesor ].getListaActas();
            int numeroActasProfesor = listaProfes[ profesor ].getNumeroActas();
            pasar = 1;
            for( int i =  0; i < numeroActasProfesor; i++){
                for( int j = 0; j < numeroActas; j++){
                    if( j == listaActasProfesor[ i ]  && ( listaActas[j].getDirJurado1() == profesor || listaActas[j].getDirJurado2() == profesor ) ){
                        cout << "Acta #" << listaActas[j ].getNumeroActa() << endl;
                        contador++;
                    }
                }
            }
        }
    }while( pasar == 0 );
    if( contador == 0 ){
        cout<< "Este profesor no ha trabajado como jurado en ningun acta" << endl;
    }
}

void crearUsuario( class UserSys * userSys ){
    char nombres[  STORAGE_USERSYS_STRINGS ], apellidos[  STORAGE_USERSYS_STRINGS ], usuario[  STORAGE_USERSYS_STRINGS ], contra[  STORAGE_USERSYS_STRINGS ];
    cout << "Ingrese sus nombres: " << endl;
    fflush( stdin );
    fgets( nombres,  STORAGE_USERSYS_STRINGS, stdin );
    nombres[strcspn(nombres, "\n")] = 0;
    cout << "Ingrese sus apellidos: " << endl;
    fflush( stdin );
    fgets( apellidos,  STORAGE_USERSYS_STRINGS, stdin );
    apellidos[strcspn(apellidos, "\n")] = 0;
    do{
        cout << "Ingrese su nombre de usuario: " << endl;
        fflush( stdin );
        fgets( usuario,  STORAGE_USERSYS_STRINGS, stdin );
        usuario[strcspn(usuario, "\n")] = 0;
        cout << "Ingrese su contrasena: " << endl;
        fflush( stdin );
        fgets( contra,  STORAGE_USERSYS_STRINGS, stdin );
        contra[strcspn(contra, "\n")] = 0;
    } while( userSys->crearUsuario( usuario, contra, nombres, apellidos, ND, INTERNO ) == -1 );
}

class Usuario verificar( class Usuario directora, class Usuario asistente, class Usuario *lista, int numeroUsuarios ){
    char username[  STORAGE_USERSYS_STRINGS ], password[  STORAGE_USERSYS_STRINGS ]; int paso = 0, i = 0;
    do{
        cout<< "Username: "; cin>>username;
        cout<< "password: "; cin>> password;
        if( strcmp( directora.getUsuario( ), username ) == 0 && strcmp( directora.getContra( ), password ) == 0 ){
            paso = 1;
            return directora;
        }
        else if( strcmp( asistente.getUsuario( ), username ) == 0 && strcmp( asistente.getContra( ), password ) == 0 ){
            paso = 1;
            return asistente;
        }
        else{
            for( i ; i < numeroUsuarios; i++ ){
                if( strcmp( lista[ i ].getUsuario( ), username ) == 0 && strcmp( lista[ i ].getContra( ), password ) == 0 ){
                    paso = 1;
                    break;
                }
            }
            if( paso == 0 ){
                cout<< "Username or password incorrect, try again" << endl;
            }
        }
    }while( paso == 0 );
    return lista[ i ];
}

void activarUsuario( class Dir_Asis userWAtrib, class Usuario* lista, int numeroUsuarios ){
    int i, opcion, type, modalidad, bandera = 0;
    cout<<"usuarios no validados:"<<endl;
    for( i = 0; i < numeroUsuarios; i++ ){
        if( lista[ i ].getType() == ND ){
            bandera++;
            cout << "Usuario numero: "<< i + 1 << ". " << lista[ i ].getNombres() << " " << lista[ i ].getApellidos() << endl;
        }
    }
    if( bandera == 0 ){
        cout<< "No hay usuarios por validar" <<endl;
    }
    else{
        do{
            cout << "Ingrese el numero del usuario que desea validar: ";cin >> opcion;
            opcion = opcion - 1;
            cout << "Ingrese el tipo de usuario que desea validar: \n1. estudiante \n2. docente"<<endl;cin >> type;
            switch( type ){
                case 1:
                    userWAtrib.validarUsuario( &lista[ opcion ], ESTUDIANTE, INTERNO );
                    break;
                case 2:
                    do{
                        cout << "El docente es interno o externo?\n1. Interno\n2. Externo" << endl;cin >> modalidad;
                        if( modalidad != 1 && modalidad != 2 ){
                            cout << "Opcion invalida. Por favor intentelo nuevamente..." << endl;
                        }
                    } while( modalidad != 1 && modalidad != 2 );
                    switch( modalidad ){
                        case 1:
                            userWAtrib.validarUsuario( &lista[ opcion ], PROFESOR, INTERNO );
                            break;
                        case 2:
                            userWAtrib.validarUsuario( &lista[ opcion ], PROFESOR, EXTERNO );
                            break;
                    }
                    break;
                default:
                    cout<< "opcion invalida" << endl;
            }
        }while( type!= 1 && type!=2);
    }
}

void creacionActa( class ActaSys * actaSys, class Usuario * listaUsuarios, int numeroUsuarios ){
    char fecha[ STRINGS_CAP ], nombreTrabajo[ STRINGS_CAP]; int hayCodirector, numeroEstudiante, i = 0, pasar = 0, tipo, numeroDirector = -1, numeroCodirector = -2, numeroJurado1 = -3, numeroJurado2 = -4;
    TIPOTRABAJO tipoTrabajo;
    cout<< "fecha del acta: ";cin>> fecha;
    cout<< "Lista de estudiantes:\n";
    for( i; i < numeroUsuarios; i++ ){
        if( listaUsuarios[ i ].getType() == ESTUDIANTE ){
            cout<< i + 1 << ". " << listaUsuarios[ i ].getNombres() << listaUsuarios[ i ].getApellidos() <<endl;
        }
    }
    do{
        cout<< "Digite el numero del estudiante: " <<endl;cin>>numeroEstudiante;
        numeroEstudiante = numeroEstudiante - 1;
        if( listaUsuarios[ numeroEstudiante ].getType() != ESTUDIANTE || numeroEstudiante < 0 ){
            cout<< "el numero digitado no pertenece a un estudiante." << endl;
        }
        else{
            pasar = 1;
        }
    }while( pasar == 0 );
    cout<< "nombre del trabajo: ";cin>> nombreTrabajo;
    pasar = 0;
    do{
        cout<< "por favor escoja el tipo de trabajo:\n1. Aplicado\n2. Investigacion " << endl; cin>> tipo;
        if( tipo == 1 ){
            tipoTrabajo = APLICADO;
            pasar = 1;
        }
        else if( tipo == 2 ){
            tipoTrabajo = INVESTIGACION;
            pasar = 1;
        }
        else{
            cout<< "La opcion digitada no es valida" <<endl;
        }
    }while( pasar == 0 );
    cout<< "Lista de profesores:\n";
    for( i = 0; i < numeroUsuarios; i++ ){
        if( listaUsuarios[ i ].getType() == PROFESOR ){
            cout<< i + 1 << ". " << listaUsuarios[ i ].getNombres() << listaUsuarios[ i ].getApellidos() <<endl;
        }
    }
    pasar = 0;
    do{
        cout<< "Digite el numero del director: " <<endl;cin>>numeroDirector;
        numeroDirector = numeroDirector - 1;
        if( listaUsuarios[ numeroDirector ].getType() != PROFESOR || numeroDirector < 0 ){
            cout<< "el numero digitado no pertenece a un profesor" <<endl;
        }
        else if( numeroDirector == numeroCodirector || numeroDirector == numeroJurado1 || numeroDirector == numeroJurado2 ){
            cout<< "el usuario digitado ya se encuentra en el acta" << endl;
        }
        else{
            pasar = 1;
        }
    }while( pasar == 0);
    pasar = 0;
    do{
        do{
            cout<< "Desea ingresar Co-Director?\n1. Si\n2. No" << endl;cin>> hayCodirector;
            if( hayCodirector == 1 ){
                cout<< "Digite el numero del codirector: " <<endl;cin>>numeroCodirector;
                numeroCodirector = numeroCodirector - 1;
                if( listaUsuarios[ numeroCodirector ].getType() != PROFESOR || numeroCodirector < 0 ){
                    cout<< "el numero digitado no pertenece a un profesor" <<endl;
                }
                else if( numeroCodirector == numeroDirector || numeroCodirector == numeroJurado1 || numeroCodirector == numeroJurado2 ){
                    cout<< "el usuario digitado ya se encuentra en el acta" << endl;
                }
                else{
                    pasar = 1;
                }
            }
            else if( hayCodirector == 2){
                numeroCodirector = -1;
                pasar = 1;
            }
            else{
                cout<< "Opcion invalida." << endl;
            }
        }while( hayCodirector != 1 && hayCodirector !=2 );
    }while( pasar == 0 );
    pasar = 0;
    do{
        cout<< "Digite el numero del jurado 1: " <<endl;cin>>numeroJurado1;
        numeroJurado1 = numeroJurado1 - 1;
        if( listaUsuarios[ numeroJurado1 ].getType() != PROFESOR || numeroJurado1 < 0 ){
            cout<< "el numero digitado no pertenece a un profesor" <<endl;
        }
        else if( numeroJurado1 == numeroDirector || numeroJurado1 == numeroCodirector || numeroJurado1 == numeroJurado2 ){
            cout<< "el usuario digitado ya se encuentra en el acta" << endl;
        }
        else{
            pasar = 1;
        }
    }while( pasar == 0 );
    pasar = 0;
    do{
        cout<< "Digite el numero del jurado 2: " <<endl;cin>>numeroJurado2;
        numeroJurado2 = numeroJurado2 - 1;
        if( listaUsuarios[ numeroJurado2 ].getType() != PROFESOR || numeroJurado2 < 0 ){
            cout<< "el numero digitado no pertenece a un profesor" <<endl;
        }
        else if( numeroJurado2 == numeroDirector || numeroJurado2 == numeroCodirector || numeroJurado2 == numeroJurado1 ){
            cout<< "el usuario digitado ya se encuentra en el acta" << endl;
        }
        else{
            pasar = 1;
        }
    }while( pasar == 0 );
    actaSys->crearActa( fecha , numeroEstudiante, nombreTrabajo, tipoTrabajo, numeroDirector, numeroCodirector, numeroJurado1, numeroJurado2 );
}

void cerrarActa( class Acta * listaActas, int numeroActas, int numeroCriterios ){
    int i, bandera = 0, actaCerrar, pasar = 0, faltaEvaluacion = 0, comentario;
    cout<< "Actas abiertas:" << endl;
    for( int i = 0; i < numeroActas; i++ ){
        if( listaActas[ i ].getEstado( ) == ABIERTA ){
            cout<< i + 1 << ". acta #" << listaActas[ i ].getNumeroActa() <<endl;
            bandera++;
        }
    }
    if( bandera == 0 ){
        cout<< "No hay actas abiertas" << endl;
    }
    else{
        do{
            cout<< "Selecione un acta:  "; cin>> actaCerrar;
            actaCerrar = actaCerrar - 1;
            if( listaActas[ actaCerrar ].getEstado() != ABIERTA || actaCerrar < 0 ){
                cout<< "El numero digitado no pertenece a un acta abierta." << endl;
            }
            else{
                pasar = 1;
            }
        }while( pasar == 0 );
        float * notasJ1 = listaActas[ actaCerrar ].getListaNotasJ1( );
        float * notasJ2 = listaActas[ actaCerrar ].getListaNotasJ2( );
        for( i = 0; i < numeroCriterios; i++ ){
            if( notasJ1[ i ] == -1 || notasJ2[ i ] == -1 ){
                faltaEvaluacion = 1;
            }
        }
        if( faltaEvaluacion ){
            cout<< "El acta no ha sido evaluada por completo, por lo cual no se puede cerrar." << endl;
        }
        else{
            do{
                cout<< "Desea anadir un comentario adicional?\n1. Si\n2. No" << endl;cin>>comentario;
                if( comentario == 1 ){
                    char * comment;
                    cin >> comment;
                    strcpy( listaActas[ actaCerrar ].getComAdi( ), comment );
                }
                else if( comentario == 2 ){
                    strcpy( listaActas[ actaCerrar ].getComAdi( ), "N.A." );
                }
                else{
                    cout<< "opcion invalida." << endl;
                }
            }while( comentario != 1 && comentario !=2 );
            listaActas[ actaCerrar ].setEstado( CERRADA );
        }
    }
}

void calcularNotaFinal( class Acta * acta, float * listaPorcentajesPonderacion, int numeroCriterios ){
    int i, bandera = 1;
    float * listaNotasJ1 = acta->getListaNotasJ1( );
    float * listaNotasJ2 = acta->getListaNotasJ2( );
    for( i = 0; i < numeroCriterios; i++ ){
        if( listaNotasJ1[ i ] == -1 || listaNotasJ2[ i ] == -1 ){
            bandera = 0;
            break;
        }
    }
    if( bandera ){
        float sumaJ1 = 0.0, sumaJ2 = 0.0;
        for( i = 0; i < numeroCriterios; i++ ){
            sumaJ1 += listaNotasJ1[ i ] * listaPorcentajesPonderacion[ i ];
            sumaJ2 += listaNotasJ2[ i ] * listaPorcentajesPonderacion[ i ];
        }
        acta->setNotaFinal( ( sumaJ1 + sumaJ2 ) / 2.0 );
        if( ( sumaJ1 + sumaJ2 ) / 2.0 > 3.5 ){
            acta->setEstadoCalif( APROBADA );
        }
        else{
            acta->setEstadoCalif( REPROBADA );
        }
    }
}

void evaluar( class ActaSys * actaSys, class Usuario ingresante, int numeroCriterios, float * listaPorcentajesPonderacion, char ** listaCriterios, class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios ){
    int i, seleccion, selector = 0, bandera = 0, jurado = 0;
    int listaSeleccion[ ACTAS_CAP ];
    for( i = 0; i < ACTAS_CAP; i++ ){
        listaSeleccion[ i ] = -1;
    }
    cout<< "=========Actas=========" <<endl;
    for( int i = 0; i < numeroActas; i++ ){
        if( strcmp( listaUsuarios[ listaActas[ i ].getDirJurado1( ) ].getUsuario( ), ingresante.getUsuario( ) ) == 0 ){
            if( listaActas[ i ].getEstado() == ABIERTA ){
                cout << "ACTA " << selector << ":" << endl;;
                cout << "Titulo del acta: " << listaActas[ i ].getNombreTrabajo( ) << endl;
                cout << "Estudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getNombres( ) << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getApellidos( )<< endl;
                listaSeleccion[ selector++ ] = i;
                bandera = 1;
                jurado = 1;
            }
            else{
                cout<< "No tiene actas abiertas" << endl;
            }
        }
        if( strcmp( listaUsuarios[ listaActas[ i ].getDirJurado2( ) ].getUsuario( ), ingresante.getUsuario( ) ) == 0 ){
            if(  listaActas[ i ].getEstado() == ABIERTA ){
                cout << "ACTA " << selector << ":\n";
                cout << "Titulo del acta: " << listaActas[ i ].getNombreTrabajo( ) << endl;;
                cout << "Estudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getNombres( ) << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getApellidos( )<< endl;
                listaSeleccion[ selector++ ] = i;
                bandera = 1;
                jurado = 2;
            }
            else{
                cout<< "No tiene actas abiertas" << endl;
            }
        }
    }
    if( bandera == 0 ){
        cout<< "El usuario no tiene actas abiertas donde sea jurado" <<endl;
    }
    else{
        bandera = 1;
        do{
            cout << "Ingrese el numero del acta que desea evaluar: ";
            cin >> seleccion;
            if( listaSeleccion[ seleccion ] != -1 ){
                bandera = 0;
            }
            else{
                cout << "El valor ingresado no es valido. Por favor intentelo nuevamente.";
            }
        } while( bandera );
        char * com;
        float * listaNotas;
        for( i = 0; i < numeroCriterios; i++ ){
            if( jurado == 1 ){
                com = listaActas[ listaSeleccion[ seleccion ] ].getComJ1( i );
                listaNotas = listaActas[ listaSeleccion[ seleccion ] ].getListaNotasJ1( );
            }
            else{
                com = listaActas[ listaSeleccion[ seleccion ] ].getComJ2( i );
                listaNotas = listaActas[ listaSeleccion[ seleccion ] ].getListaNotasJ2( );
            }
            cout << "Criterio " << i + 1 << ":" << endl << actaSys->getCriterio( i );
            cout << endl << "Comentario: " << endl;
            fflush( stdin );
            fgets( com, COMMENT_CHARS_CAP, stdin );
            com[strcspn(com, "\n")] = 0;
            cout << endl << "Nota: ";
            cin >> listaNotas[ i ];
        }
        calcularNotaFinal( &listaActas[ listaSeleccion[ seleccion ] ], listaPorcentajesPonderacion, numeroCriterios );
        cout << "No hay mas criterios por evaluar." << endl;
        cout << "Recuerde que hasta que el acta no sea cerrada podra realizar modificaciones.\n";
    }
}

void trabajosJurado( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios, int numeroUsuarios ){
    int i, j, seleccion, selector = 0;
    int listaSeleccion[ ACTAS_CAP ];
    for( i = 0; i < ACTAS_CAP; i++ ){
        listaSeleccion[ i ] = -1;
    }
    for( i = 0; i < numeroUsuarios; i++ ){
        int * listaActasUsuario = listaUsuarios[ i ].getListaActas( );
        for( j = 0; j < STORAGE_USERSYS_ACTA; j++ ){
            if( listaActas[ listaActasUsuario[ j ] ].getDirJurado1( ) == i || listaActas[ listaActasUsuario[ j ] ].getDirJurado2( ) == i ){
                listaSeleccion[ selector ] = i;
                cout << selector << ". " << listaUsuarios[ i ].getNombres( ) << " " << listaUsuarios[ i ].getNombres( ) << endl;
                selector++;
                break;
            }
        }
    }
    cout << "Ingrese el numero del jurado del que desea conocer las actas asociadas: ";
    do{
        cin >> seleccion;
        if( listaSeleccion[ seleccion ] == -1 ){
            cout << "El valor ingresado es invalido. por favor intentelo nuevamente...";
        }
    } while( listaSeleccion[ seleccion ] != -1 );
    int * listaActasUsuario = listaUsuarios[ listaSeleccion[ seleccion ] ].getListaActas( );
    for( i = 0; i < STORAGE_USERSYS_ACTA; i++ ){
        if( listaActasUsuario[ i ] != -1 ){
            cout << "Titulo trabajo: " << listaActas[ listaActasUsuario[ i ] ].getNombreTrabajo( ) << endl;
            cout << "Estudiante: " << listaUsuarios[ listaActas[ listaActasUsuario[ i ] ].getDirEstudiante( ) ].getNombres( ) << " " << listaUsuarios[ listaActas[ listaActasUsuario[ i ] ].getDirEstudiante( ) ].getApellidos( );
            cout << "====================================" << endl;
        }
    }
}

void juradosDeActas( class Acta * listaActas, class Usuario * listaUsuarios, int numeroUsuarios ){
    int i, j, existencia = 0;
    cout << "Jurados que han participado en la evaluacion de actas: " << endl;
    for( i = 0; i < numeroUsuarios; i++ ){
        int * listaActasUsuario = listaUsuarios[ i ].getListaActas( );
        for( j = 0; j < STORAGE_USERSYS_ACTA; j++ ){
            if( listaActas[ listaActasUsuario[ j ] ].getDirJurado1( ) == i || listaActas[ listaActasUsuario[ j ] ].getDirJurado2( ) == i ){
                existencia = 1;
            }
        }
        if( existencia ){
            cout << listaUsuarios[ i ].getNombres( ) << listaUsuarios[ i ].getApellidos( ) << endl;
        }
    }
}

void actasPendRepro( class Acta * listaActas, class Usuario * listaUsuarios, int numeroActas ){
    int i;
    for( i = 0; i < numeroActas; i++ ){
        if( listaActas[ i ].getEstadoCalif( ) == PENDIENTE || listaActas[ i ].getEstadoCalif( ) == REPROBADA ){
            cout << "Titulo del trabajo: " << listaActas[ i ].getNombreTrabajo( ) << endl;
            cout << "Estudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getNombres( ) << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getApellidos( ) << endl;
            cout << "Estado de la calificacion: " << listaActas[ i ].getEstadoCalif( ) << endl;
            cout << "==========================================" << endl;
        }
    }
}

void consultarCriterios( char ** listaCriterios, int numeroCriterios ){
    int i;
    cout << "Los criterios de evaluacion actualmente son:" << endl << endl;
    for( i = 0; i < numeroCriterios; i++ ){
        cout << "CRITERIO " << i << endl;
        cout << listaCriterios[ i ] << endl;
    }
}

void generarTxt( class Acta * listaActas, class Usuario * listaUsuarios, class ActaSys * actaSys ){
    int i, j, seleccion, selector = 0;
    int listaSeleccion[ ACTAS_CAP ];
    for( i = 0; i < ACTAS_CAP; i++ ){
        listaSeleccion[ i ] = -1;
    }
    for( i = 0; i < ACTAS_CAP; i++ ){
        if( listaActas[ i ].getEstado( ) == CERRADA ){
            cout << "ACTA " << selector << ". " << endl;
            cout << "Titulo del trabajo: " << listaActas[ i ].getNombreTrabajo( ) << endl;
            cout << "Estudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getNombres( ) << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante( ) ].getApellidos( ) << endl;
            listaSeleccion[ selector++ ] = i;
        }
    }
    do{
        cout << "Ingrese el numero del acta que desea exportar como txt: ";
        cin >> seleccion;
        if( listaSeleccion[ seleccion ] == -1 ){
            cout << "El valor ingresado es invalido. Por favor intentelo nuevamente...";
        }
    } while( listaSeleccion[ seleccion ] == -1 );
    class Acta actaExport = listaActas[ listaSeleccion[ seleccion ] ];
    ofstream output;
    char nombreArchivo[ STRINGS_CAP + 4 ];
    strcpy( nombreArchivo, actaExport.getNombreTrabajo( ) );
    char txtExt[ 5 ] = ".txt";
    txtExt[ 4 ] = '\0';
    for( i = 0; i < STRINGS_CAP; i++ ){
        if( nombreArchivo[ i ] == '\0' ){
            for( j = 0; j < 4; j++ ){
                nombreArchivo[ i + j ] = txtExt[ j ];
            }
            nombreArchivo[ i + j ] = txtExt[ j ];
            break;
        }
    }
    output.open( nombreArchivo );
    output << "ACTA DE EVALUACION # " << actaExport.getNumeroActa( ) << endl << endl;
    output << "Fecha: " << actaExport.getFecha( ) << endl << endl;
    output << "Titulo del Trabajo: " << actaExport.getNombreTrabajo( ) << endl << endl;
    if( actaExport.getTipoTrabajo( ) == APLICADO ){
        output << "Tipo de trabajo: APLICADO" << endl;
    }
    else{
        output << "Tipo de trabajo: INVESTIGACION" << endl;
    }
    output << "Estudiante: " << listaUsuarios[ actaExport.getDirEstudiante( ) ].getNombres( ) << " " << listaUsuarios[ actaExport.getDirEstudiante( ) ].getApellidos( ) << endl << endl;
    output << "Director: " << listaUsuarios[ actaExport.getDirDirector( ) ].getNombres( ) << " " << listaUsuarios[ actaExport.getDirDirector( ) ].getApellidos( ) << endl << endl;
    if( actaExport.getDirCodirector( ) != -1 ){
        output << "Codirector: " << listaUsuarios[ actaExport.getDirCodirector( ) ].getNombres( ) << " " << listaUsuarios[ actaExport.getDirCodirector( ) ].getApellidos( ) << endl << endl;
    }
    else{
        output << "Codirector: N.A." << endl << endl;
    }
    output << "Jurado #1: " << listaUsuarios[ actaExport.getDirJurado1( ) ].getNombres( ) << " " << listaUsuarios[ actaExport.getDirJurado1( ) ].getApellidos( ) << endl << endl;
    output << "Jurado #2: " << listaUsuarios[ actaExport.getDirJurado2( ) ].getNombres( ) << " " << listaUsuarios[ actaExport.getDirJurado2( ) ].getApellidos( ) << endl << endl;
    float * listaNotasJ1 = actaExport.getListaNotasJ1( );
    float * listaNotasJ2 = actaExport.getListaNotasJ2( );
    float notaFinal = actaExport.getNotaFinal( );
    for( i = 0; i < actaSys->getNumeroCriterios( ); i++ ){
        output << "CRITERIO " << i + 1 << endl << endl;
        output << "Definicion:" << endl << actaSys->getCriterio( i ) << endl << endl;
        output << "Comentario del jurado #1:" << endl << actaExport.getComJ1( i ) << endl << endl;
        output << "Calificacion del criterio segun el jurado #1: " << listaNotasJ1[ i ] << endl << endl;
        output << "Comentario del jurado #2:" << endl << actaExport.getComJ2( i ) << endl << endl;
        output << "Calificacion del criterio segun el jurado #2: " << listaNotasJ2[ i ] << endl << endl;
    }
    output << "Comentario adicional de los jurados: " << endl << actaExport.getComAdi( );
    output << endl << "Nota final: " << notaFinal << endl;
    if( actaExport.getEstadoCalif( ) == APROBADA ){
        output << "Estado de la calificacion: APROBADA";
    }
    else{
        output << "Estado de la calificacion: RECHAZADA";
    }
    output.close( );
}

void mostrarActas( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios ){
    int bandera = 0;
    cout<< "=========Actas=========" <<endl;
    for( int i = 0; i < numeroActas; i++ ){
        if( listaActas[ i ].getEstado() == ABIERTA ){
            cout<< "Acta #" << listaActas[ i ].getNumeroActa() << "\nFecha: " << listaActas[ i ].getFecha() << "\nEstudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getNombres() << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getApellidos()<< "\nEstado: Abierta\nNota: Pendiente" <<endl;
            bandera = 1;
        }
        else{
            if( listaActas[ i ].getEstadoCalif() == REPROBADA ){
                cout<< "Acta #" << listaActas[ i ].getNumeroActa() << "\nFecha: " << listaActas[ i ].getFecha() << "\nEstudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getNombres() << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getApellidos()<< "\nEstado: Cerrada y rechazada" <<endl;
            }
            else if( listaActas[ i ].getEstadoCalif() == APROBADA ){
                cout<< "Acta #" << listaActas[ i ].getNumeroActa() << "\nFecha: " << listaActas[ i ].getFecha() << "\nEstudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getNombres() << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getApellidos()<< "\nEstado: Cerrada y aprobada" <<endl;
            }
            bandera = 1;
        }
    }
    if( bandera == 0 ){
        cout<< "No hay actas en existencia" <<endl;
    }
}

void mostrarActasCerradas( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios ){
    int bandera = 0;
    cout<< "====Actas Cerradas=====" <<endl;
    for( int i = 0; i < numeroActas; i++ ){
        if( listaActas[ i ].getEstado() == CERRADA ){
            bandera = 1;
            if( listaActas[ i ].getEstadoCalif() == REPROBADA ){
                cout<< "Acta #" << listaActas[ i ].getNumeroActa() << "\nFecha: " << listaActas[ i ].getFecha() << "\nEstudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getNombres() << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getApellidos()<< "\nNota: " << listaActas[ i ].getNotaFinal()<< "\nEstado: Cerrada y rechazada" <<endl;
            }
            else if( listaActas[ i ].getEstadoCalif() == APROBADA ){
                cout<< "Acta #" << listaActas[ i ].getNumeroActa() << "\nFecha: " << listaActas[ i ].getFecha() << "\nEstudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getNombres() << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getApellidos()<< "\nNota: " << listaActas[ i ].getNotaFinal()<< "\nEstado: Cerrada y aprobada" <<endl;
            }
        }
    }
    if( bandera == 0 ){
        cout<< "No hay actas cerradas en existencia" <<endl;
    }
}

void mostrarActasAbiertas( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios ){
    int bandera = 0;
    cout<< "====Actas Abiertas=====" <<endl;
    for( int i = 0; i < numeroActas; i++ ){
        if( listaActas[ i ].getEstado() == ABIERTA ){
            bandera = 1;
            cout<< "Acta #" << listaActas[ i ].getNumeroActa() << "\nFecha: " << listaActas[ i ].getFecha() << "\nEstudiante: " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getNombres() << " " << listaUsuarios[ listaActas[ i ].getDirEstudiante() ].getApellidos()<< "\nEstado: Abierta\nNota: Pendiente" <<endl;
        }
    }
    if( bandera == 0 ){
        cout<< "No hay actas abiertas en existencia" <<endl;
    }
}

void mostrarActaEstudiante( int * listaActasEstudiante, int numeroActasEstudiante, class Acta * listaActas, int numeroActas ){
    int bandera = 0;
    cout<< "=========Acta=========" <<endl;
    for( int i =  0; i < numeroActasEstudiante; i++){
        for( int j = 0; j < numeroActas; j++){
            if( j == listaActasEstudiante[ i ] && listaActas[ j ].getEstado() == ABIERTA ){
                cout<< "Su acta está en estado: Abierta, por ende no se puede mostrar" << endl;
                bandera = 1;
            }
            else if( j == listaActasEstudiante[ i ] && listaActas[ j ].getEstado() == CERRADA ){
                if( listaActas[ j ].getEstadoCalif() == REPROBADA ){
                    cout<< "Nota: " << listaActas[ j ].getNotaFinal() << "\nEstado: rechazada"  <<endl;
                }
                else if( listaActas[ j ].getEstadoCalif() == APROBADA ){
                    cout<< "Nota: " << listaActas[ j ].getNotaFinal() << "\nEstado: aprovada"  <<endl;
                }
                bandera = 1;
            }
        }
    }
    if( bandera == 0 ){
        cout<< "Usted no tiene actas abiertas o cerradas" <<endl;
    }
}

void mostrarActasProfesor( int * listaActasProfesor, int numeroActasProfesor, class Acta * listaActas, int numeroActas ){
    int bandera = 0;
    cout<< "=========Actas=========" <<endl;
    for( int i =  0; i < numeroActasProfesor; i++){
        for( int j = 0; j < numeroActas; j++){
            if( j == listaActasProfesor[ i ] ){
                if( listaActas[ j ].getEstado() == ABIERTA ){
                    cout<< "Acta #" << listaActas[ j ].getNumeroActa() << "\nEstado: abierta" <<endl;
                    bandera = 1;
                }
                else{
                    cout<< "Acta #" << listaActas[ j ].getNumeroActa() << "\nEstado: cerrada" <<endl;
                    bandera = 1;
                }
            }
        }
    }
    if( bandera == 0 ){
        cout<< "Usted no participa en ninguna acta" <<endl;
    }
}

void mostrarActasProfesorAbiertos( int * listaActasProfesor, int  numeroActasProfesor, class Acta * listaActas, int numeroActas ){
    int bandera = 0;
    cout<< "====Actas Abiertas=====" <<endl;
    for( int i =  0; i < numeroActasProfesor; i++){
        for( int j = 0; j < numeroActas; j++){
            if( j == listaActasProfesor[ i ] && listaActas[ j ].getEstado() == ABIERTA ){
                cout<< "Acta #" << listaActas[ j ].getNumeroActa() << "\nEstado: abierta" <<endl;
                bandera = 1;
            }
        }
    }
    if( bandera == 0 ){
        cout<< "Usted no participa en ninguna acta abierta" <<endl;
    }
}

void mostrarActasProfesorCerrados( int * listaActasProfesor, int  numeroActasProfesor, class Acta * listaActas, int numeroActas ){
    int bandera = 0;
    cout<< "====Actas Cerradas=====" <<endl;
    for( int i =  0; i < numeroActasProfesor; i++){
        for( int j = 0; j < numeroActas; j++){
            if( j == listaActasProfesor[ i ] && listaActas[ j ].getEstado() == CERRADA ){
                cout<< "Acta #" << listaActas[ j ].getNumeroActa() << "\nEstado: cerrada" <<endl;
                bandera = 1;
            }
        }
    }
    if( bandera == 0 ){
        cout<< "Usted no participa en ninguna acta cerrada" <<endl;
    }
}

void menuEstudiante( class Usuario ingresante, class ActaSys * actaSys ){
    int menu;
    cout << "MENU ESTUDIANTE" << endl;
    class Estudiante userWAtrib( ingresante.getUsuario(), ingresante.getContra(), ingresante.getNombres(), ingresante.getApellidos(), ingresante.getType(), ingresante.getModalidad( ) );
    int * listaActasEstudiante = ingresante.getListaActas();
    int numeroActasEstudiante = ingresante.getNumeroActas();
    class Acta * listaActas = actaSys->getListaActas();
    int numeroActas = actaSys->getNumeroActas();
    do{
        cout<< "1. Cerrar sesion\n2. Mostrar acta" << endl; cin >> menu;
        switch( menu ){
            case 1:
                break;
            case 2:
                mostrarActaEstudiante( listaActasEstudiante, numeroActasEstudiante, listaActas, numeroActas );
                break;
            default:
            cout<< "Opcion invalida, intentelo de nuevo" << endl;
        }
    }while( menu != 1 );
    cout<<endl;
}

void menuProfesores( class Usuario ingresante, class ActaSys * actaSys, class Usuario * listaUsuarios ){
    int menu;
    cout << "MENU DOCENTE" << endl;
    class Docente userWAtrib( ingresante.getUsuario(), ingresante.getContra(), ingresante.getNombres(), ingresante.getApellidos(), ingresante.getType(), ingresante.getModalidad( ) );
    class Acta * listaActas = actaSys->getListaActas();
    int numeroActas = actaSys->getNumeroActas();
    int * listaActasProfesor = ingresante.getListaActas();
    int numeroActasProfesor = ingresante.getNumeroActas();
    char ** listaCriterios = actaSys->getListaCriterios();
    int numeroCriterios = actaSys->getNumeroCriterios();
    float * porcentajesPonderacion = actaSys->getPorcentajesPonderacion();

    do{
        cout<< "1. Cerrar sesion\n2. Mostrar actas\n3. Mostrar actas cerradas\n4. Mostrar actas cerradas\n5. Evaluar acta" << endl; cin >> menu;
        switch( menu ){
            case 1:
                break;
            case 2:
                mostrarActasProfesor( listaActasProfesor, numeroActasProfesor, listaActas, numeroActas );
                break;
            case 3:
                mostrarActasProfesorAbiertos( listaActasProfesor, numeroActasProfesor, listaActas, numeroActas );
                break;
            case 4:
                mostrarActasProfesorCerrados( listaActasProfesor, numeroActasProfesor, listaActas, numeroActas );
                break;
            case 5:
                evaluar( actaSys, ingresante, numeroCriterios, porcentajesPonderacion, listaCriterios , listaActas, numeroActas, listaUsuarios );
                break;
            default:
            cout<< "Opcion invalida, intentelo de nuevo" << endl;
        }
    }while( menu != 1 );
    cout<<endl;
}

void menuDirAsi( class Usuario ingresante, class Usuario *lista, int numeroUsuarios, class ActaSys * actaSys, int numeroCriterios ){
    int menu;
    cout << "MENU DIRECCION" << endl;
    class Dir_Asis userWAtrib( ingresante.getUsuario(), ingresante.getContra(), ingresante.getNombres(), ingresante.getApellidos(), ingresante.getType(), ingresante.getModalidad( ) );
    class Acta * listaActas = actaSys->getListaActas();
    int numeroActas = actaSys->getNumeroActas();
    do{
        cout<< "1. Cerrar sesion\n2. Activar Usuario\n3. Crear acta\n4. Cerrar acta\n5. Mostrar todas las actas\n6. Mostrar actas cerradas\n7. Mostrar actas abiertas\n8. Trabajos aplicados\n9. Trabajos de investigacion\n10. Cantidad de trabajos de grado dirigidos por un profesor\n11. Mostrar actas de un jurado\n12. Exportar acta" << endl; cin >> menu;
        switch( menu ){
            case 1:
                break;
            case 2:
                activarUsuario( userWAtrib, lista, numeroUsuarios );
                break;
            case 3:
                creacionActa( actaSys, lista, numeroUsuarios );
                break;
            case 4:
                cerrarActa( listaActas, numeroActas, numeroCriterios );
                break;
            case 5:
                mostrarActas( listaActas, numeroActas, lista);
                break;
            case 6:
                mostrarActasCerradas( listaActas, numeroActas, lista );
                break;
            case 7:
                mostrarActasAbiertas( listaActas, numeroActas, lista );
                break;
            case 8:
                informarAplicados( listaActas, numeroActas );
                break;
            case 9:
                informarInvestigacion( listaActas, numeroActas );
                break;
            case 10:
                contarDirecciones( listaActas, numeroActas, lista, numeroUsuarios );
                break;
            case 11:
            	mostrarActasJurados( listaActas, numeroActas, lista, numeroUsuarios );
            	break;
            case 12:
                generarTxt( listaActas, lista, actaSys );
                break;
        }
    }while( menu != 1 );
    cout<<endl;
}

void iniciarSesion( class UserSys * userSys, class ActaSys * actaSys){
    class Usuario * listaUsuarios = userSys->getListaUsuarios( );
    class Usuario directora = userSys->getDirectora( );
    class Usuario asistente = userSys->getAsistente( );
    int numeroUsuarios = userSys->getNumeroUsuarios( );
    int numeroCriterios = actaSys->getNumeroCriterios( );
    class Usuario ingresante = verificar( directora, asistente, listaUsuarios, numeroUsuarios );
    switch( ingresante.getType( ) ){
        case ESTUDIANTE:
            menuEstudiante( ingresante, actaSys );
            break;
        case PROFESOR:
            menuProfesores( ingresante, actaSys, listaUsuarios );
            break;
        case DIR_ASI:
            menuDirAsi( ingresante, listaUsuarios, numeroUsuarios, actaSys, numeroCriterios );
            break;
        case ND:
            cout<< "Su usuario no ha sido activado todavía. Por favor comuniquese con la direccion de la maestria para que su usuario sea activado" <<endl;
            default:
            break;     
        }
}

void inicio(){
    int menu;
    ActaSys actaSys;
    UserSys userSys;
    cout<< "------Javeriana cali sistema de actas------\n" <<endl;
    do{
        cout<< "por favor digite la opcion que desea realizar:\n1. Iniciar sesion\n2. Crear usuario\n3.terminar programa" << endl; cin>> menu;
        switch ( menu ){
            case 1:
                iniciarSesion( &userSys, &actaSys );
                break;
            case 2:
                crearUsuario( &userSys );
                break;
            case 3:
                cout<< "hasta la proxima." <<endl;
                break;
            default:
                cout<< "Opcion invalida, por favor digite una opcion valida" <<endl;
                break;
        }
    }while( menu != 3 );
}