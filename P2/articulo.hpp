//
// Created by antonio on 26/07/22.
//

#ifndef P2_ARTICULO_HPP
#define P2_ARTICULO_HPP
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iostream>

class Articulo{
public:
    // Ctor. de Artículo
    explicit Articulo(const Cadena n_ref, const Cadena tit_, const Fecha fech_publi, double prec_, double n_ej_ = 0);

    // Métodos observadores.
    Cadena referencia() const { return cod_referencia_; };
    Cadena titulo() const { return titulo_; };
    Fecha f_publi() const { return f_de_publi; };
    const double precio() const { return precio_; };
    double& precio() { return precio_; };
    const double stock() const { return n_de_ejemplares_; };
    double& stock() { return n_de_ejemplares_; };

private:
    const Cadena cod_referencia_;
    const Cadena titulo_;
    const Fecha f_de_publi;
    double precio_;
    double n_de_ejemplares_;

};

// Operador de inserción, con el que mostraremos los datos de un artículo en una sola línea.
std::ostream& operator << (std::ostream& os, const Articulo& a1);

#endif //P2_ARTICULO_HPP
