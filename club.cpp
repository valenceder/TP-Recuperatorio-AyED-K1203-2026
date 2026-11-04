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

/*Creo el archivo binario, si es que no se encuentra en el disco.*/
void crearArchivo(const char *nombreArchivo){
    FILE *f = fopen(nombreArchivo, "rb");

    if (f == NULL) {
        f = fopen(nombreArchivo, "rb");

        if (f != NULL) {
            fclose(f);
        }

    } else {
        fclose(f);
    }
}

/*Calculo la cantidad de socios con fseek y ftell.*/
int cantidadtotaldesocios(FILE *f){
    fseek(f, 0, SEEK_END); /*Me ubico en el final del archivo.*/
    return ftell(f) / sizeof(Socio);
}

/*Uso una función auxiliar para mostrar la categoría (1,2 o 3)*/
const char *nombrecategoria(int cat){ /*La categoría no se modifica, sino luego.*/
    if (cat == 1) {
        return "Infantil";
    }

    if (cat == 2) {
        return "Activo";
    }

    if (cat == 3) {
        return "Vitalicio";
    }

    return "categoría desconocida";
}

/*1-Dar de alta un socio*/
void altadesocio(){
    FILE *f = fopen("socios.dat", "rb+");

    if (f == NULL) {
        return;
    }

    int total = cantidadtotaldesocios(f);

    Socio nuevo; /*Creo un socio*/
    nuevo.idSocio = total + 1;

    cout << "--Alta de socio--" << endl;
    cout << "Nombre completo: ";
    cin.ignore(); /*Ignora el enter ingresado*/
    cin.getline(nuevo.nombre, 50); /*Lee nombre con espacios*/

    cout << "Categoría (1 infantil, 2 activo, 3 vitalicio): ";
    cin >> nuevo.categoria;

    cout << "Cuota mensual: $";
    cin >> nuevo.cuotaMensual;

    nuevo.activo = true;

    /*La función de cantidad total de socios ubica el cursor al final, entonces se graba directo*/
    fwrite(&nuevo, sizeof(Socio), 1, f);
    fclose(f);

    cout << "Socio registrado. Número de socio que se asignó: " << nuevo.idSocio << endl;
}

/*2-Modificar socio a través de PUP.*/

void modificarsocio(){ /*Modifico categoría.*/
    int nro;
    cout << "--Modificar socio--" << endl;
    cout << "Número de socio: ";
    cin >> nro;

    FILE *f = fopen("socios.dat", "rb+");

    if (f == NULL) {
        return;
    }

    int total = cantidadtotaldesocios(f);

    if (nro < 1 || nro > total) {
        cout << "Error. El id de socio " << nro << " no existe.";
        fclose(f);
        return;
    }

    /*Accedo directo (PUP) a la posición idSocio - 1.*/

    fseek(f, (nro - 1) * sizeof(Socio), SEEK_SET);
    Socio s;
    fread(&s, sizeof(Socio), 1, f);

    if (!s.activo){
    
        cout << "Error. El socio " << s.nombre << " está dado de baja.";
        fclose(f);
        return;
    }

    cout << "Socio actual: " << s.nombre << endl;
    cout << "Categoría: " << nombrecategoria(s.categoria) << endl; /*Datos ya existentes*/
    cout << "Cuota: $" << s.cuotaMensual << endl;

    cout << "Nueva categoría (1 infantil, 2 activo, 3 vitalicio): "; /*Datos a modificar por el usuario*/
    cin >> s.categoria;
    cout << "Nueva cuota mensual: $";
    cin >> s.cuotaMensual;

    /*Se sobrescribe únicamente dicho registro, y reubico por PUP.*/

    fseek(f, (nro - 1) * sizeof(Socio), SEEK_SET);
    fwrite(&s, sizeof(Socio), 1, f);
    fclose(f);

    cout << "Datos del socio actualizados." << endl;
}

/*3-Dar de baja un socio mediante PUP.*/
void bajadesocio(){
    int nro;
    cout << "--Modificar socio--" << endl;
    cout << "Número de socio: ";
    cin >> nro;

    FILE *f = fopen("socios.dat", "rb+");

    if (f == NULL) {
        return;
    }

    int total = cantidadtotaldesocios(f);

    if (nro < 1 || nro > total) {
        cout << "Error. El id de socio " << nro << " no existe.";
        fclose(f);
        return;
    }

    fseek(f, (nro - 1) * sizeof(Socio), SEEK_SET);
    Socio s;
    fread(&s, sizeof(Socio), 1, f);

    if (!s.activo){
        cout << "El socio " << s.nombre << " ya se encontraba de baja.";
        fclose(f);
        return;
    }

    char confirmacion;
    cout << "¿Quiere dar de baja a " << s.nombre << "? (s/n): ";
    cin >> confirmacion;

    /*s= si, n=no*/

    if (confirmacion == 's' || confirmacion == 'S') {
        s.activo = false;
        fseek(f, (nro - 1) * sizeof(Socio), SEEK_SET);
        fwrite(&s, sizeof(Socio), 1, f);
        cout << "El socio " << s.nombre << " fue dado de baja." << endl;
    } else {
        cout << "Baja cancelada.";
    }

    fclose(f);
}

/*4-Lista del padrón(socios activos)*/
void listapadron(){
    FILE *f = fopen("socios.dat", "rb");

    if (f == NULL)
    {
        return;
    }

    cout << "--Padrón de socios activos--" << endl;
    cout << "Numero\tNombre\t\t\tCategoría\t\tCuota\n" << endl;

    Socio s;

    int activos = 0;

    while (fread(&s, sizeof(Socio), 1, f) == 1) {

        if (s.activo){
            cout << s.idSocio << "\t" << s.nombre << "\t\t" << nombrecategoria(s.categoria) << "\t\t$" << s.cuotaMensual << "\n";
            activos++;
        }
    }

    cout << "Total de los socios activos: " << activos << endl;
    fclose(f);
}

/*5-Registro del pago validado por PUP, e insertar ordenado en pagos.dat*/
void registrarpago(){
    int nro;
    cout << "--Registrar pago--" << endl;
    cout << "Numero de socio: ";
    cin >> nro;

    FILE *fSocios = fopen("socios.dat", "rb");

    if (fSocios == NULL) {
        return;
    }

    int total = cantidadtotaldesocios(fSocios);

    if (nro < 1 || nro > total) {
        cout << "Error. El socio de id " << nro << " no existe. Se rechazó el pago." << endl;
        fclose(fSocios);
        return;
    }

    fseek(fSocios, (nro - 1) * sizeof(Socio), SEEK_SET);
    Socio s;
    fread(&s, sizeof(Socio), 1, fSocios);
    fclose(fSocios);

    if (!s.activo) {
        cout << "Error. El socio " << s.nombre << "figura dado de baja. Pago rechazado." << endl;
        return;
    }

    Pago nuevo;
    nuevo.idSocio = nro;
    cout << "Mes que abona (mm-aaaa): ";
    cin >> nuevo.mes;
    cout << "Monto a pagar(0 para usar su cuota de $" << s.cuotaMensual << "):";
    cin >> nuevo.monto;

    if (nuevo.monto == 0) {
        nuevo.monto = s.cuotaMensual;
    }

    /*Inserto ordenado por idSocio, usando archvo auxiliar*/

    FILE *fPagos = fopen("pagos.dat", "rb");
    FILE *fAux = fopen("aux.dat", "wb");

    Pago p;
    bool insertado = false;

    if (fPagos != NULL) {

        while (fread(&p, sizeof(Pago), 1, fPagos) == 1) {

            if (!insertado && p.idSocio > nuevo.idSocio) {
                fwrite(&nuevo, sizeof(Pago), 1, fAux);
                insertado = true;
            }

            fwrite(&p, sizeof(Pago), 1, fAux);
        }

        fclose(fPagos);
    }

    if (!insertado) {
        fwrite(&nuevo, sizeof(Pago), 1, fAux);
    }
    fclose(fAux);

    /*Copio aux.dat a pagos.dat*/

    fAux = fopen("aux.dat", "rb");
    fPagos = fopen("pagos.dat", "wb");

    while (fread(&p, sizeof(Pago), 1, fAux) == 1){
        fwrite(&p, sizeof(Pago), 1, fPagos);
    }

    fclose(fAux);
    fclose(fPagos);

    cout << "Pago de $" << nuevo.monto << " registrado para " << s.nombre << endl;
}

/*6-Reporte de cobranza, usando corte de control y buscar por PUP.*/

void reportedecobranza(){
    FILE *fPagos = fopen("pagos.dat", "rb");
    FILE *fSocios = fopen("socios.dat", "rb");

    if (fPagos == NULL || fSocios == NULL) {

        if (fPagos) {
            fclose(fPagos);
        }

        if (fSocios) {
            fclose(fSocios);
        }

        return;
    }

    cout << "--Reporte de cobranza--" << endl;
    cout << "Socio\tNombre\t\t\t\t\tCuotas pagadas\t\tTotal" << endl;

    float totalrecaudado = 0;
    int sociosquepagaron = 0;

    Pago p;
    int leido = fread(&p, sizeof(Pago), 1, fPagos);

    while (leido == 1) {
        int socioactual = p.idSocio;
        int cuotaspagadas = 0;
        float totaldesocio = 0;

        while (leido == 1 && p.idSocio == socioactual) {
            cuotaspagadas++;
            totaldesocio += p.monto;
            leido = fread(&p, sizeof(Pago), 1, fPagos);
        }

        /*Traigo el nombre del socio y su estado por PUP.*/

        fseek(fSocios, (socioactual - 1) * sizeof(Socio), SEEK_SET);
        Socio s;
        fread(&s, sizeof(Socio), 1, fSocios);

        cout << socioactual << "\t" << s.nombre;

        if (!s.activo) {
        cout << "\n\t(dado de baja)";
        }

        cout <<  "\t\t\t\t" << cuotaspagadas << "\t\t\t$" << totaldesocio << endl;

        totalrecaudado += totaldesocio;
        sociosquepagaron++;
    }

    cout << "Total recaudado $" << totalrecaudado << " y " << sociosquepagaron << " son los socios que pagaron." << endl;
}

int main()
{
    crearArchivo("socios.dat");
    crearArchivo("pagos.dat");

    int opcion;
    do
    {
        cout << "1. Alta de socio." << endl;
        cout << "2. Modificar socio." << endl;
        cout << "3. Baja de socio." << endl;
        cout << "4. Padrón activo." << endl;
        cout << "5. Registrar pago." << endl;
        cout << "6. Reporte de cobranza." << endl;
        cout << "0. Finalizar." << endl;
        cout << "Elija una opción: ";
        cin >> opcion;

        switch (opcion)
        {

        case 1:
            altadesocio();
            break;
        case 2:
            modificarsocio();
            break;
        case 3:
            bajadesocio();
            break;
        case 4:
            listapadron();
            break;
        case 5:
            registrarpago();
            break;
        case 6:
            reportedecobranza();
            break;
        case 0:
            cout << "Fin del programa." << endl;
            break;
        default:
            cout << "No existe la opción." << endl;
        }
    } while (opcion != 0);

    return 0;
}
    fclose(f);
    cout << "Se creó el archivo." << endl;
}

