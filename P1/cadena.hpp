//
// Created by antonio on 12/07/22.
//

#ifndef P1_CADENA_HPP
#define P1_CADENA_HPP

#include <cstring>
#include <cstdlib>
#include <stdexcept>

class Cadena{
public:

    // Constructor de Cadena, lo ponemos explícito para cuando inicialicemos una cadena vacía.
    explicit Cadena(size_t tamanno = 0, char s = ' ');

    // Constructor de copia.
    Cadena(const Cadena& c);

    // Constructor de una cadena a partir de una cadena de caracteres de bajo nivel.
    Cadena(const char* cadenita);

    // Operador =, que copia una cadena en otra, destruyendo la original.
    Cadena& operator =(const Cadena& c1);
    Cadena& operator =(const char* c2);

    // Función observadora que devuelve el número de caracteres de una cadena.
    inline size_t length() const noexcept { return tam_; };

    // Operador +=, que nos sirve para poder concatenar dos cadenas, añadiendo al final de la primera cadena la segunda.
    Cadena& operator +=(const Cadena& c2);

    // FUncion observadora que nos devuelve la cadena.
    const char* c_str() const noexcept { return s_; };

    // Operador +, que nos permite concatenar dos cadenas, resultando una nueva.
    Cadena operator +(const Cadena& c2);
    Cadena operator +(const Cadena& c2) const;

    // Operadores lógicos para comparar cadenas
    bool operator ==(const Cadena& c2);
    bool operator !=(const Cadena& c2);
    bool operator >=(const Cadena& c2);
    bool operator <=(const Cadena& c2);
    bool operator >(const Cadena& c2);
    bool operator <(const Cadena& c2);

    // Conversores.
    operator const char* ();
    operator const char* () const;

    // Operador [], que nos permitirá obtener un caracter cualquiera de la cadena con solo su índice.
    char& operator [](size_t i) ;
    const char& operator [](size_t i) const;    // OJO!! FUNCIÓN OBSERVADORA.

    // Función at, que hará lo mismo que el operador [], solo que tendrá en cuenta si el número del tamaño que se le pase
    // está dentro del rango de la cadena, cosa que el operador [] no hace.
    char at(size_t i) const;       // OJO!! FUNCIÓN OBSERVADORA.
    char& at(size_t i);

    // clase out_of_range, para lanzar una excepción en el caso de que se exceda el límite de rango de la cadena.
    class out_of_range{
    public:
        out_of_range(const char * c): cadena(c) {}
        const char* what() { return cadena; };
    private:
        const char* cadena;
    };

    // Función substr, que, dando un índice y el tamaño, nos devuelve una cadena formada por tantos caracteres como
    // hayamos indicado en el tamaño a partir del índice.
    Cadena substr(size_t i, size_t tamanno);
    Cadena substr(size_t i, size_t tamanno) const;  // FUNCIÓN OBSERVADORA
    // Destructor.
    ~Cadena();
private:
    char* s_;
    size_t tam_;
};




#endif //P1_CADENA_HPP
