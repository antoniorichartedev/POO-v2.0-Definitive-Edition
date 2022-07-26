//
// Created by antonio on 26/07/22.
//

#include "articulo.hpp"

Articulo::Articulo(const Cadena n_ref, const Cadena tit_, const Fecha fech_publi, double prec_, double n_ej_):
    cod_referencia_(n_ref),
    titulo_(tit_),
    f_de_publi(fech_publi),
    precio_(prec_),
    n_de_ejemplares_(n_ej_)
{}

std::ostream& operator << (std::ostream& os, const Articulo& a1){
    os << "[" << a1.referencia() << "] " << "''" << a1.titulo() << "'', " << a1.f_publi() << ". " << a1.precio() << " €";
}