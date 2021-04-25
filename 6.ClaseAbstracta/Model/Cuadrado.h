//#ifndef CIRCULO_H
// Guardas
//#define CIRCULO_H
#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

#include "FiguraGeometrica.h"

class Cuadrado : public FiguraGeometrica{
    private:
        float lado;
    public:
        Cuadrado();
        Cuadrado( float );
        virtual void calcularArea();
        virtual void calcularPerimetro();
        virtual void mostrarFigura();
        float getLado();
        void setLado( float );
};
//#endif /* !CIRCULO_H */