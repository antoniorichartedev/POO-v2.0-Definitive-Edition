//
// Created by antonio on 26/07/22.
//

#ifndef P2_USUARIO_HPP
#define P2_USUARIO_HPP
#include "../P1/cadena.hpp"

class Clave{
public:
    Clave(const char* passwd);
    Cadena clave() const ;
    bool verifica(const char* clv);

    enum Razon{
        CORTA,
        ERROR_CRYPT
    };

    class Incorrecta{
    public:
        Incorrecta(const Razon clv): r(clv) {}
        Razon razon() const { return r; };
    private:
        Razon r;
    };

private:
    Cadena password_;
};
#endif //P2_USUARIO_HPP
