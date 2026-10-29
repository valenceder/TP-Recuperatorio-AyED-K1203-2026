
#include <iostream>
using namespace std;

struct Socio {
    int idSocio;
    char nombre[50];
    int categoria;
    float cuotaMensual;
    bool activo;
};

struct Pago {
    int idSocio;
    char mes[8];
    float monto;
};


