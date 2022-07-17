//
// Created by antonio on 12/07/22.
//


#include "cadena.hpp"
using namespace std;

Cadena::Cadena(size_t tamanno, char s):
    tam_(tamanno)
    {
        // creamos la cadena con el tamaño solicitado + 1, para el carácter terminador.
        s_ = new char[tam_ + 1];

        // vamos introduciendo el carácter de relleno hasta llegar al tamaño máximo, antes del carácter terminador
        for (size_t i = 0; i < tamanno; i++){
            s_[i] = s;
        }

        // luego, donde debería de ir el carácter terminador, lo colocamos donde le corresponde.
        s_[tam_] = '\0';
    }

    // NOTA: pienso que se podría hacer con strcpy.
Cadena::Cadena(const Cadena &c): s_(new char[c.tam_ + 1]), tam_(c.tam_) {

        // vamos copiando carácter a carácter a la nueva cadena.
        for (size_t i = 0; i < tam_; i++){
            s_[i] = c.s_[i];
        }
    s_[tam_] = '\0';
}

bool Cadena::operator<(const Cadena &c2) {
    return strcmp(s_, c2.s_) <= -1;
}

bool Cadena::operator>(const Cadena &c2) {
    return strcmp(s_, c2.s_) >= 1;
}

bool Cadena::operator<=(const Cadena &c2) {
    return !(*this > c2);
}

bool Cadena::operator>=(const Cadena &c2) {
    return (*this > c2 || *this == c2);
}

bool Cadena::operator!=(const Cadena &c2) {
    return !(*this == c2);
}

bool Cadena::operator==(const Cadena &c2) {
    return strcmp(s_, c2.s_) == 0;
}

char Cadena::at(size_t i) const {
    if (i < 0 || i >= tam_)
        throw std::out_of_range("Índice no válido");
    return s_[i];
}

char &Cadena::at(size_t i) {
    if (i < 0 || i >= tam_ )
        throw std::out_of_range("Índice no válido");
    return s_[i];
}

const char &Cadena::operator[](size_t i) const {
    return s_[i];
}

char &Cadena::operator[](size_t i)  {
    return s_[i];
}

Cadena::~Cadena() {
    delete[] s_;
}

Cadena::Cadena(const char *cadenita) {
    // asignamos el tamaño de la cadena que hemos introducido.
    tam_ = strlen(cadenita);

    // creamos la cadena con el espacio justo y necesario de la cadena.
    s_ = new char[tam_ + 1];

    // la copiamos.
    strcpy(s_, cadenita);
}

Cadena &Cadena::operator=(const Cadena &c1) {

    // Borramos lo que haya dentro de la cadena implícita.
    delete[] this->s_;

    // ahora, reservaremos memoria para la nueva cadena.
    this->tam_ = c1.tam_;
    this->s_ = new char[tam_ + 1];

    // Copiamos el contenido de la cadena que queríamos copiar.
    strcpy(this->s_, c1.s_);

    // devolvemos la cadena copiada.
    return *this;
}

Cadena &Cadena::operator+=(const Cadena &c2) {

    // creamos una variable de tipo char, que tendrá el tamaño de la primera cadena + el de la segunda + el carácter terminador.
    char* temporal = new char[tam_ + c2.tam_ + 1]();

    // copiamos la cadena primera en temporal.
    for (unsigned i = 0; i < tam_; i++){
        temporal[i] = s_[i];
    }

    // ahora la segunda cadena.
    for (unsigned i = tam_; i < tam_ + c2.tam_; i++){
        temporal[i] = c2.s_[i - tam_];
    }
    temporal[tam_ + c2.tam_] = '\0';

    // borramos la primera cadena.
    delete[] s_;

    // asignamos el tamaño
    tam_ = tam_ + c2.tam_;

    // le asignamos a la nueva cadena el espacio necesario para albergarla.
    s_ = new char[tam_ + 1];

    for(unsigned i = 0; i < tam_ + 1; i++){
        s_[i] = temporal[i];
    }

    // borramos la cadena temporal que hemos creado.
    delete[] temporal;

    // devolvemos esa cadena.
    return *this;
}

Cadena Cadena::substr(size_t ind, size_t tamanno) {

    // Comprobamos primero si está en un rango válido.
    if (ind < 0 || tamanno + 1 < ind){
        throw std::out_of_range("Límite de rango excedido.");
    }

    // ahora, vamos a comprobar si los caracteres que se han pedido, se pueden mostrar, es decir, si hay suficientes caracteres.
    unsigned int caractdifncia = tam_ - ind;
    if (caractdifncia < tamanno){
        throw std::out_of_range("Lo siento, no hay suficientes caracteres.");
    }

    // creamos una cadena nueva para albergar el resultado.
    Cadena CadNew{tamanno};

    // ahora, vamos a ir introduciendo carácter a carácter en la nueva cadena, desde el índice indicado hasta un tamaño ya determinado.
    for (unsigned int i = ind; i < ind + tamanno; i++){
        CadNew[i - ind] = s_[i];
    }

    return CadNew;
}

Cadena Cadena::substr(size_t ind, size_t tamanno) const {
    // Comprobamos primero si está en un rango válido.
    if (ind < 0 || tamanno + 1 < ind){
        throw std::out_of_range("Límite de rango excedido.");
    }

    // ahora, vamos a comprobar si los caracteres que se han pedido, se pueden mostrar, es decir, si hay suficientes caracteres.
    unsigned int caractdifncia = tam_ - ind;
    if (caractdifncia < tamanno){
        throw std::out_of_range("Lo siento, no hay suficientes caracteres.");
    }

    // creamos una cadena nueva para albergar el resultado.
    Cadena CadNew{tamanno};

    // ahora, vamos a ir introduciendo carácter a carácter en la nueva cadena, desde el índice indicado hasta un tamaño ya determinado.
    for (unsigned int i = ind; i < ind + tamanno; i++){
        CadNew[i - ind] = s_[i];
    }

    return CadNew;
}

Cadena Cadena::operator+(const Cadena &c2) {

    // Creamos una nueva cadena con el tamaño de la suma de los tamaños de las dos cadenas + 1 por el carácter terminador.
    char* CadSum = new char[tam_ + c2.tam_ + 1];

    // Copiamos la primera cadena en la cadena nueva.
    strcpy(CadSum, s_);

    // Luego, la concatenamos con la segunda cadena.
    strcat(CadSum, c2.s_);

    // por último, devolvemos esa cadena.
    return Cadena{CadSum};
}

Cadena Cadena::operator+(const Cadena &c2) const {
    // Creamos una nueva cadena con el tamaño de la suma de los tamaños de las dos cadenas + 1 por el carácter terminador.
    char* CadSum = new char[tam_ + c2.tam_ + 1];

    // Copiamos la primera cadena en la cadena nueva.
    strcpy(CadSum, s_);

    // Luego, la concatenamos con la segunda cadena.
    strcat(CadSum, c2.s_);

    // por último, devolvemos esa cadena.
    return Cadena{CadSum};
}

Cadena &Cadena::operator=(const char* c2) {

    // Borramos lo que haya en la cadena.
    delete[] this->s_;

    // ahora, reservamos memoria para la nueva cadena. También indicamos su tamaño.
    this->tam_ = strlen(c2);
    this->s_ = new char[tam_ + 1];

    // Copiamos el contenido de c2 en la nueva cadena.
    strcpy(this->s_, c2);
    return *this;

}

Cadena::operator const char *() {
    return s_;
}

Cadena::operator const char *() const {
    return s_;
}