#include "Cuadrado.h"

Cuadrado:: Cuadrado(){
}
Cuadrado:: Cuadrado( float lado ) : Cuadrado(){
    this->lado = lado;
}
void Cuadrado:: calcularArea(){
    this->area = this->lado * this->lado;
}
void Cuadrado:: calcularPerimetro(){
    this->perimetro = this->lado * 4;
}
void Cuadrado::mostrarFigura(){
    cout << "El tamano de cada lado es: " << lado << endl;
    if (this->area == 0) // si no he calculado el area
    {
        this->calcularArea();
    }
    if (this->perimetro == 0)
    {
        this->calcularPerimetro();
    }
    cout << "El area del cuadrado es: " << this->area << endl;
    cout << "El perimetro del cuadrado es : " << this->perimetro << endl;

    // LLamo al mostrarFigura delegado
    FiguraGeometrica::mostrarFigura();
}
float Cuadrado:: getLado(){
    return this->lado;
}
void Cuadrado:: setLado( float lado){
    this->lado = lado;
}