//
// Created by antonio on 11/07/22.
//
#include <iostream>
#include "fecha.hpp"
using namespace std;

reloj r;

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

    if (d > DiasQueTieneUnMes[m] || d < 1){
        throw Invalida("Dia incorrecto");
    }
}

void Fecha::CorregirFecha(int dd, int mm, int anno) {

    if (dd == 0){
        d = r.diaact();
    }

    if (mm == 0){
        m = r.mesact();
    }

    if (anno == 0){
        a = r.annoact();
    }
}

Fecha::Fecha(const char *fe) {
    if (sscanf(fe, "%d/%d/%d", &d, &m, &a) != 3){
        throw Invalida("Formato incorrecto");
    }
}

bool operator == (const Fecha& f1, const Fecha& f2){
    return (f1 == f2);
}

bool operator != (const Fecha& f1, const Fecha& f2){
    return !(f1 == f2);
}

bool operator > (const Fecha& f1, const Fecha& f2){
    return (f1 > f2);
}

bool operator <(const Fecha& f1, const Fecha& f2){
    return !(f1 > f2);
}

bool operator >= (const Fecha& f1, const Fecha& f2){
    return (f1 > f2 || f1 == f2);
}

bool operator <= (const Fecha& f1, const Fecha& f2){
    return (!(f1 > f2) || f1 == f2);
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

const char *Fecha::cadena() const noexcept {
    const char* dias[] = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
    const char* meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    static char fecha[40];

    tm fech = {0};
    fech.tm_mday = dia();
    fech.tm_mon = mes() - 1;
    fech.tm_year = anno() - 1900;
    mktime(&fech);

    sprintf(fecha, "%s %d de %s de %d", dias[fech.tm_wday], fech.tm_mday, meses[fech.tm_mon], fech.tm_year + 1900);

    return fecha;
}
