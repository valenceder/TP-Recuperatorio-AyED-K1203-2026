#include <iostream>
using namespace std;

// socios.dat
struct Socio {
    int idSocio;         // 1, 2, 3, ... sin huecos
    char nombre[50];
    int categoria;      // 1 Infantil, 2 Activo, 3 Vitalicio
    float cuotaMensual;
    bool activo;        // false = dado de baja
};

// pagos.dat (siempre ordenado por idSocio)
struct Pago {
    int idSocio;
    char mes[8];        // "MM-AAAA"
    float monto;
};


