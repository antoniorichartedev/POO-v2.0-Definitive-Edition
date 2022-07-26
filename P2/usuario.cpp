//
// Created by antonio on 26/07/22.
//

#include "usuario.hpp"
#include <unistd.h>
#include <random>

/* ----------------- CLASE CLAVE ----------------- */
Clave::Clave(const char *passwd) {

    static const char* caracteres = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char* salt = new char[2];

    if (strlen(passwd) < 5){
        throw Incorrecta(Razon::CORTA);
    }

    std::random_device num;
    std::uniform_int_distribution<int> randomrandom(0, strlen(caracteres));
    salt[2] = {caracteres[randomrandom(num), randomrandom(num)]};

    if (crypt(passwd, salt) == nullptr){
        throw Incorrecta(Razon::ERROR_CRYPT);
    }
    else{
        password_ = crypt(passwd, salt);
    }
}

bool Clave::verifica(const char *clv) {
    return strcmp(password_.c_str(), crypt(clv, password_.c_str())) == 0;
}
