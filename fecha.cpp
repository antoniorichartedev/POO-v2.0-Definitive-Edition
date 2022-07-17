//
// Created by antonio on 11/07/22.
//

#include <cstdio>
#include <cstring>
#include "fecha.hpp"
using namespace std;

const int Fecha::DiasQueTieneUnMes[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Fecha::Fecha(int dd, int mm, int anno):
    d(dd),
    m(mm),
    a(anno)
{
    CorregirFecha(dd, mm, anno);
    ComprobarFecha();
}

bool Bisiesto (int anno){
    // Para saber si un año es bisiesto, utlizamos la siguiente expresión.
    bool bisi = (anno % 4 == 0 && (anno % 400 == 0 || anno % 100 != 0));
    return bisi;    // false si no es bisiesto, true si es bisiesto.
}

void Fecha::ComprobarFecha() {
    if (m == 2 && d == 29 && !Bisiesto(a)){
        throw Invalida("Este anno no es bisiesto.");
    }

    if (m < 1 || m > 12){
        throw Invalida("Mes introducido incorrecto!!");
    }

    if (a < Fecha::AnnoMinimo || a > Fecha::AnnoMaximo){
        throw Invalida("El anno se pasa de los límites");
    }

    if (d > DiasQueTieneUnMes[m - 1] || d < 1){
        throw Invalida("Dia no válido");
    }
}

void Fecha::CorregirFecha(int dd, int mm, int anno) {

    if (dd == 0){
        d = reloj::diaact();
    }

    if (mm == 0){
        m = reloj::mesact();
    }

    if (anno == 0){
        a = reloj::annoact();
    }
}

Fecha::Fecha(const char *fe) {
    if (sscanf(fe, "%d/%d/%d", &d, &m, &a) != 3){
        throw Invalida("Formato incorrecto");
    }

    CorregirFecha(d, m, a);
    ComprobarFecha();
}

bool operator == (const Fecha& f1, const Fecha& f2){
    bool res = true;

    if(f1.a != f2.a){
        res = false;
    }
    else if(f1.m != f2.m){
        res = false;
    }
    else if(f1.d != f2.d){
        res = false;
    }
    else res = true;

    return res;
}

bool operator != (const Fecha& f1, const Fecha& f2){
    bool res = true;

    if(f1.a == f2.a){
        res = false;
    }
    else if (f1.m == f2.m){
        res = false;
    }
    else if (f1.d == f2.d){
        res = false;
    }
    else res = true;
    return res;
}

bool operator > (const Fecha& f1, const Fecha& f2){
    bool res = true;

    if (f1.a < f2.a) {
        res = false;
    }
    else if(f1.a == f2.a){
        if (f1.m < f2.m){
            res = false;
        }
        else if(f1.m == f2.m) {
            if (f1.d <= f2.d) {
                res = false;
            }
        }
    }
    return res;
}

bool operator <(const Fecha& f1, const Fecha& f2){
    bool res = true;

    if (f1.a > f2.a) {
        res = false;
    }
    else if(f1.a == f2.a){
        if (f1.m > f2.m){
            res = false;
        }
        else if(f1.m == f2.m) {
            if (f1.d >= f2.d) {
                res = false;
            }
        }
    }
    return res;
}

bool operator >= (const Fecha& f1, const Fecha& f2){
    bool res = true;

    if (f1.a < f2.a) {
        res = false;
    }
    else if(f1.a == f2.a){
        if (f1.m < f2.m){
            res = false;
        }
        else if(f1.m == f2.m) {
            if (f1.d < f2.d) {
                res = false;
            }
        }
    }
    return res;
}

bool operator <= (const Fecha& f1, const Fecha& f2){
    bool res = true;

    if (f1.a > f2.a) {
        res = false;
    }
    else if(f1.a == f2.a){
        if (f1.m > f2.m){
            res = false;
        }
        else if(f1.m == f2.m) {
            if (f1.d > f2.d) {
                res = false;
            }
        }
    }
    return res;
}

Fecha &Fecha::operator++() {

    *this += 1;
    return *this;
}

Fecha Fecha::operator++(int) {
    Fecha f = *this;
    ++*this;
    return f;
}

Fecha &Fecha::operator--() {
    *this -= 1;
    return *this;
}

Fecha Fecha::operator--(int) {
    Fecha f = *this;
    --*this;
    return f;
}

Fecha Fecha::operator+(int n) const {
    Fecha f = *this;
    f += n;
    return f;
}

Fecha Fecha::operator-(int n) const {
    Fecha f = *this;
    f += -n;
    return f;
}

Fecha &Fecha::operator+=(int n) {
    if (n != 0){
        tm FechaAux = {};
        FechaAux.tm_mday = d + n;
        FechaAux.tm_mon = m - 1;
        FechaAux.tm_year = a - 1900;
        mktime(&FechaAux);
        d = FechaAux.tm_mday;
        m = FechaAux.tm_mon + 1;
        a = FechaAux.tm_year + 1900;
        ComprobarFecha();
    }

    return *this;
}

Fecha &Fecha::operator-=(int n) {
    return *this += -n;
}

const char *Fecha::obtenercadenita() const noexcept{

    char *cad = new char[50], *aux = new char[50];
    std::tm* fecha = new tm;

    memset(fecha, 0, sizeof(*fecha));
    fecha->tm_mday = d;
    fecha->tm_mon = m - 1;
    fecha->tm_year = a - 1900;

    mktime(fecha);

    switch(fecha->tm_wday){
        case 0: strcpy(cad, "domingo "); break;
        case 1: strcpy(cad, "lunes "); break;
        case 2: strcpy(cad, "martes "); break;
        case 3: strcpy(cad, "miércoles "); break;
        case 4: strcpy(cad, "jueves "); break;
        case 5: strcpy(cad, "viernes "); break;
        case 6: strcpy(cad, "sábado "); break;
    }

    sprintf(aux, "%d", d);
    strcat(cad, aux);
    strcat(cad, " de ");

    switch(m){
        case 1: strcat(cad, "enero de "); break;
        case 2: strcat(cad, "febrero de "); break;
        case 3: strcat(cad, "marzo de "); break;
        case 4: strcat(cad, "abril de "); break;
        case 5: strcat(cad, "mayo de "); break;
        case 6: strcat(cad, "junio de "); break;
        case 7: strcat(cad, "julio de "); break;
        case 8: strcat(cad, "agosto de "); break;
        case 9: strcat(cad, "septiembre de "); break;
        case 10: strcat(cad, "octubre de "); break;
        case 11: strcat(cad, "noviembre de "); break;
        case 12: strcat(cad, "diciembre de "); break;
    }

    sprintf(aux, "%d", a);
    strcat(cad, aux);

    delete[] aux;
    delete fecha;
    return cad;


    /*const char* dias[] = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
    const char* meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    static char fecha[40];

    tm fech = {0};
    fech.tm_mday = dia();
    fech.tm_mon = mes() - 1;
    fech.tm_year = anno() - 1900;
    mktime(&fech);

    sprintf(fecha, "%s %d de %s de %d", dias[fech.tm_wday], fech.tm_mday, meses[fech.tm_mon], fech.tm_year + 1900);

    return fecha;*/
}
