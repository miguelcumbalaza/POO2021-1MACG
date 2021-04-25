#include "triangulo.h"

//CONSTRUCTORES TRIANGULO

Triangulo::Triangulo() {}

Triangulo::Triangulo(float base, float altura)
{

    this->base = base;
    this->altura = altura;
}

//METODOS TRIANGULO

void Triangulo::calcularArea()
{
    this->area = (base * altura) / 2;
}

void Triangulo::calcularPerimetro()
{
    float temp;
    temp = base / 2;
    this->perimetro = 2 * ((sqrt((temp * temp)) + (altura * altura))) + base;
}
void Triangulo:: mostrarFigura(){
    cout << "La base es: " << base << " -- "
         << "La altura es: " << altura << endl;
    if (this->area == 0) // si no he calculado el area
    {
        this->calcularArea();
    }
    if (this->perimetro == 0)
    {
        this->calcularPerimetro();
    }
    cout << "El area del triangulo es: " << this->area << endl;
    cout << "El perimetro del triangulo es : " << this->perimetro << endl;

    // LLamo al mostrarFigura delegado
    FiguraGeometrica::mostrarFigura();
}
float Triangulo:: getBase(){
    return this->base;
}
float Triangulo:: getAltura(){
    return this->altura;
}
void Triangulo:: setBase( float base ){
    this->base = base;
}
void Triangulo:: setAltura( float altura ){
    this->altura = altura;
}