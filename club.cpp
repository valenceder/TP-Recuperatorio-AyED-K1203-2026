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

void creararchivodesocio(const char* nombre){
    FILE* g = fopen(nombre, "wb");

    if (!g){
        cout << "El archivo no se encuentra." << endl;
        return;
    }

    Socio s;
    cout << "Cargue datos en el archivo (escriba 0 para terminar): ";
    cin >> s.idSocio;
    while (s.idSocio > 0){

        cout << "Nombre: ";
        cin >> s.nombre;
        cout << "Cuota mensual: ";
        cin >> s.cuotaMensual;
        fwrite(&s, sizeof(Socio), 1, g);
        cout << "Cargue datos en el archivo (escriba 0 para terminar): ";
        cin >> s.idSocio;

    }
    fclose(g);
    cout << "Se creó el archivo." << endl;
}

void creararchivodepago(const char* nombre){
    FILE* f = fopen(nombre, "wb");

    if (!f){
        cout << "El archivo no se encuentra." << endl;
        return;
    }

    Pago p;
    cout << "Cargue datos en el archivo (escriba 0 para terminar): ";
    cin >> p.idSocio;
    while (p.idSocio > 0){

        cout << "Mes: ";
        cin >> p.mes;
        cout << "Monto: ";
        cin >> p.monto;
        fwrite(&p, sizeof(Pago), 1, f);
        cout << "Cargue datos en el archivo (escriba 0 para terminar): ";
        cin >> p.idSocio;

    }
    fclose(f);
    cout << "Se creó el archivo." << endl;
}

