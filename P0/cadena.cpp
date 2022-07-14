//
// Created by antonio on 12/07/22.
//


#include "cadena.hpp"

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
Cadena::Cadena(const Cadena &c): tam_(c.tam_) {
    size_t i = 0;
    if (i < tam_){

        // vamos copiando carácter a carácter a la nueva cadena.
        for (i = 0; i < tam_; i++){
            s_[i] = c.s_[i];
        }
    }
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
    return (*this > c2);
}

bool Cadena::operator!=(const Cadena &c2) {
    return !(*this == c2);
}

bool Cadena::operator==(const Cadena &c2) {
    return strcmp(s_, c2.s_) == 0;
}

char Cadena::at(size_t i) const {
    if (i < 0 || tam_ == 0)
        throw out_of_range("Índice no válido");
    return s_[i];
}

char &Cadena::at(size_t i) {
    if (i < 0 || i > tam_ - 1)
        throw out_of_range("Índice no válido");
    return s_[i];
}

char Cadena::operator[](size_t i) const {
    return s_[i];
}

char &Cadena::operator[](size_t i) noexcept {
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
    strcpy(temporal, s_);

    // ahora concatenamos la segunda cadena.
    strcat(temporal, s_);

    // sumamos el tamaño de la segunda cadena al de la primera cadena.
    tam_ += c2.tam_;

    // borramos la primera cadena.
    delete[] s_;

    // y le asignamos la nueva cadena a s_
    s_ = temporal;

    // devolvemos esa cadena.
    return *this;
}

Cadena Cadena::substr(size_t ind, size_t tamanno) {

    // Comprobamos primero si está en un rango válido.
    if (ind < 0 || tamanno + 1 < ind){
        throw out_of_range("Límite de rango excedido.");
    }

    // ahora, vamos a comprobar si los caracteres que se han pedido, se pueden mostrar, es decir, si hay suficientes caracteres.
    unsigned int caractdifncia = tam_ - ind;
    if (caractdifncia < tamanno){
        throw out_of_range("Lo siento, no hay suficientes caracteres.");
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
        throw out_of_range("Límite de rango excedido.");
    }

    // ahora, vamos a comprobar si los caracteres que se han pedido, se pueden mostrar, es decir, si hay suficientes caracteres.
    unsigned int caractdifncia = tam_ - ind;
    if (caractdifncia < tamanno){
        throw out_of_range("Lo siento, no hay suficientes caracteres.");
    }

    // creamos una cadena nueva para albergar el resultado.
    Cadena CadNew{tamanno};

    // ahora, vamos a ir introduciendo carácter a carácter en la nueva cadena, desde el índice indicado hasta un tamaño ya determinado.
    for (unsigned int i = ind; i < ind + tamanno; i++){
        CadNew[i - ind] = s_[i];
    }

    return CadNew;
}

Cadena &Cadena::operator+(const Cadena &c2) {

    // Creamos una nueva cadena con el tamaño de la suma de los tamaños de las dos cadenas + 1 por el carácter terminador.
    char* CadSum = new char[this->tam_ + c2.tam_ + 1]();

    // Copiamos la primera cadena en la cadena nueva.
    strcpy(CadSum, this->s_);

    // Luego, la concatenamos con la segunda cadena.
    strcat(CadSum, c2.s_);

    // Borramos la primera cadena.
    delete[] s_;

    // y se le asignamos la nueva cadena concatenada.
    s_ = CadSum;

    // por último, devolvemos esa cadena.
    return *this;
}

