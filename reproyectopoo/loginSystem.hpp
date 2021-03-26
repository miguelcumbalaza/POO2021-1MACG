#ifndef UserSystem_hpp
#define UserSystem_hpp

void informarAplicados( class Acta * lisaActas, int numeroActas );
void informarInvestigacion( class Acta * lisaActas, int numeroActas );
void contarDirecciones( class Acta * listaActas, int numeroActas, class Usuario * listaProfes, int numeroProfesores);
void mostrarActasJurados( class Acta * listaActas, int numeroActas, class Usuario * listaProfes, int numeroProfesores);
void crearUsuario( class UserSys * userSys );
class Usuario verificar( class Usuario directora, class Usuario asistente, class Usuario *lista, int numeroUsuarios );
void activarUsuario( class Dir_Asis userWAtrib, class Usuario* lista, int numeroUsuarios );
void creacionActa( class ActaSys * actaSys, class Usuario * listaUsuarios, int numeroUsuarios );
void cerrarActa( class Acta * listaActas, int numeroActas, int numeroCriterios );
void calcularNotaFinal( class Acta * acta, float * listaPorcentajesPonderacion, int numeroCriterios );
void evaluar( class Usuario ingresante, int numeroCriterios, float * listaPorcentajesPonderacion, char ** listaCriterios, class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios );
void trabajosJurado( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios, int numeroUsuarios );
void juradosDeActas( class Acta * listaActas, class Usuario * listaUsuarios, int numeroUsuarios );
void actasPendRepro( class Acta * listaActas, class Usuario * listaUsuarios, int numeroActas );
void consultarCriterios( char ** listaCriterios, int numeroCriterios );
void generarTxt( class Acta * listaActas, class Usuario * listaUsuarios, char ** listaCriterios );
void mostrarActas( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios );
void mostrarActasCerradas( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios );
void mostrarActasAbiertas( class Acta * listaActas, int numeroActas, class Usuario * listaUsuarios );
void mostrarActaEstudiante( int * listaActasEstudiante, int numeroActasEstudiante, class Acta * listaActas, int numeroActas );
void mostrarActasProfesor( int * listaActasProfesor, int numeroActasProfesor, class Acta * listaActas, int numeroActas );
void mostrarActasProfesorAbiertos( int * listaActasProfesor, int  numeroActasProfesor, class Acta * listaActas, int numeroActas );
void mostrarActasProfesorCerrados( int * listaActasProfesor, int  numeroActasProfesor, class Acta * listaActas, int numeroActas );
void menuEstudiante( class Usuario ingresante, class ActaSys * actaSys );
void menuProfesores( class Usuario ingresante, class ActaSys * actaSys, class Usuario * listaUsuarios );
void menuDirAsi( class Usuario ingresante, class Usuario *lista, int numeroUsuarios, class ActaSys * actaSys, int numeroCriterios );
void iniciarSesion( class UserSys * userSys, class ActaSys * actaSys);
void inicio();

#endif