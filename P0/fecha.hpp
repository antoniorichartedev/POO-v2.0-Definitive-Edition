//
// Created by antonio on 11/07/22.
//

#ifndef P0_FECHA_HPP
#define P0_FECHA_HPP
#include <ctime>
#include <cassert>
using namespace std;

// Esta función nos permite saber si un año es bisiesto.
bool Bisiesto (int anno);

class Fecha{
public:

    // Constructor predeterminado de fecha, si no se le ponen parámetros,
    // dará la fecha del sistema en el momento de la ejecución. El explicit
    // está puesto porque nos sirve para describir la fecha de una fecha (Apartado e).
    explicit Fecha(int dd = 0, int mm = 0, int anno = 0);

    // Funciones observadoras
    int dia() const { return d; };
    int mes() const { return m; };
    int anno() const { return a; };

    // Fecha a partir de una cadena de caracteres. (Se hace con sscanf)
    Fecha(const char* fe);

    // Dos constantes, las cuales, definen el intervalo válido entre dos años.
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    // clase Invalida.
    class Invalida;

    // Funciones para incrementar o decrementar una fecha
    Fecha& operator ++();                   // Preincrementa
    Fecha operator ++(int);                 // Postincrementa
    Fecha& operator --();                   // Predecrementa
    Fecha operator --(int);                 // Postdecrementa
    Fecha operator +(int n) const;
    Fecha operator -(int n) const;
    Fecha& operator +=(int n);
    Fecha& operator -=(int n);

    operator const char*() { return cadena(); };
    operator const char*() const{ return cadena(); };

    const char* cadena() const noexcept { return obtenercadenita(); };
    // Esta clase reloj nos sirve para poder dar la fecha del sistema.
    class reloj{
    public:
        static int diaact(){
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mday;
        }

        static int mesact(){
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mon + 1;
        }

        static int annoact(){
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_year + 1900;
        }
    };

    // Operadores para comparar dos fechas.
    friend bool operator == (const Fecha& f1, const Fecha& f2);
    friend bool operator != (const Fecha& f1, const Fecha& f2);
    friend bool operator > (const Fecha& f1, const Fecha& f2);
    friend bool operator < (const Fecha& f1, const Fecha& f2);
    friend bool operator >= (const Fecha& f1, const Fecha& f2);
    friend bool operator <= (const Fecha& f1, const Fecha& f2);
private:

    // día, mes y año, respectivamente.
    int d, m, a;

    // Función que nos permite comprobar si una fecha es válida.
    void ComprobarFecha();

    // Función que nos permite arreglar la fecha
    void CorregirFecha(int d, int m, int a);

    // vector de los días que tiene cada mes;
    static const int DiasQueTieneUnMes[];

    // Esta función nos permite hacer la conversión de la fecha en números a una cadena con palabras.
    const char* obtenercadenita() const noexcept;
};

// clase Inválida, para que lance una excepción si introducimos una fecha errónea.
class Fecha::Invalida{
public:
    Invalida(const char* cadena): fallo(cadena) {}
    const char* por_que() const { return fallo; };
private:
    const char * fallo;
};


// Operadores para comparar dos fechas.
bool operator == (const Fecha& f1, const Fecha& f2);
bool operator != (const Fecha& f1, const Fecha& f2);
bool operator > (const Fecha& f1, const Fecha& f2);
bool operator < (const Fecha& f1, const Fecha& f2);
bool operator >= (const Fecha& f1, const Fecha& f2);
bool operator <= (const Fecha& f1, const Fecha& f2);




#endif //P0_FECHA_HPP
