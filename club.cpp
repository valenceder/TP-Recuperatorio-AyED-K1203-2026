
#include <iostream>
using namespace std;

// socios.dat
struct Socio {
    int idSocio;
    char nombre[50];
    int categoria;
    float cuotaMensual;
    bool activo;
};

// pagos.dat (siempre ordenado por idSocio)
struct Pago {
    int idSocio;
    char mes[8];
    float monto;
};

