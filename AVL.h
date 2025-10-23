

#ifndef PRACTICA3_AVL_H
#define PRACTICA3_AVL_H
#include "VDinamico.h"
#include <iostream>
template <class N>
 class Nodo
{
public:
    Nodo<N> *izq;
    Nodo<N> *der;
    N dato;
    Nodo(): izq(0), der(0){}
    Nodo(N &ele): izq(0), der(0), dato(ele){}
};


template<typename A>
class AVL {
private:
    Nodo<A> *raiz;
    unsigned int tam = 0, altura = 0, numEle = 0;

    void preorden (Nodo<T> *p, int nivel);
    void inorden (Nodo<T> *p, int nivel);
    void postorden (Nodo<T> *p, int nivel);
    int inserta(Nodo<A>* &n, A &dato);
    void rotDecha(Nodo<A>* &n);
    void rotIzqda(Nodo<A>* &n);
    void destruir(Nodo<A> *&p);
    Nodo<A>* copiar(Nodo<A> *&p);

public:
    AVL<A>(): raiz(0), tam(0){}
    AVL<A>(const AVL<A> &orig);
    virtual ~AVL<A>();

    bool insertar (A &elem) {
        tam++;
        return inserta(raiz, elem);
    }
    VDinamico<A*> recorreInorden(){inorden(raiz, 0);}

    AVL<A> &operator=(const AVL<A> &orig);
};
template <class T>
 void Abb<T>::preorden (Nodo<T> *p, int nivel){
    if (p){
        // Sustituir por procesamiento --
        cout << "Procesando nodo "<< p->dato ;
        cout << "en el nivel " << nivel << endl;
        // ----------
        preorden (p->izq, nivel+1);
        preorden (p->der, nivel+1);
    }
}

template <class T>
 void Abb<T>::inorden (Nodo<T> *p, int nivel){
    if (p){
        inorden (p->izq, nivel+1);
        // Sustituir por procesamiento ---
        cout << "Procesando nodo " << p->dato;
        cout << "en el nivel " << nivel << endl;
        // ----------
        inorden (p->der, nivel+1);
    }
}
template <class T>
void Abb<T>::postorden (Nodo<T> *p, int nivel){
    if (p){
        postorden (p->izq, nivel+1);
        postorden (p->der, nivel+1);
        // Sustituir por procesamiento ----
        cout << "Procesando nodo "<< p->dato;
        cout << "en el nivel " << nivel << endl;
        // ----------
    }
}


template<typename T>
void Avl<T>::rotIzqda(Nodo<T>* &p){
    Nodo<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
}
template<typename T>
void Avl<T>::rotDecha(Nodo<T>* &p){
    Nodo<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
}

template<typename T>
 int Avl<T>::inserta(Nodo<T>* &c, T &dato){
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p){
        p = new Nodo<T>(dato);
        c = p; deltaH=1;
    }
    else if (dato > p->dato){
        if (inserta(p->der, dato)){
            p->bal--;
            if (p->bal == -1) deltaH=1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDecha(p->der);
                rotIzqda(c);
            }  }   }
    else if (dato < p->dato){
        if (inserta(p->izq, dato)){
            p->bal++;
            if (p->bal==1) deltaH = 1;
            else if (p->bal == 2){
                if (p->izq->bal == -1) rotIzqda(p->izq);
                rotDecha(c);
            }   }   }
    return deltaH;
}
template<typename A>
void AVL<A>::destruir(Nodo<A> *&p) { //Ponemos *& porque modificamos el arbol
    if (p != nullptr) {
        destruir(p->izq);
        destruir(p->der);
        delete p;
        p = nullptr;
    }
    altura = tam = 0;
}

template<typename A>
Nodo<A>* AVL<A>::copiar(Nodo<A> *p) {
    if (!p) {
        return 0;
    }
        Nodo<A> *q = new Nodo<A>(p->dato); //Creamos un nodo y de ahi los hijos en caso de que los tenga
        q->izq = copiar(p->izq);
        q->der = copiar(p->der);
    return q;
}

template<typename A>
AVL<A>::AVL(const AVL<A> &orig):
altura(orig.altura),
tam(orig.tam)
{
    raiz = 0 ; //Aqui ponemos a null la raiz y con el metodo privado copiamos los nodos
    raiz = copiar(orig.raiz);
}

template<typename A>
AVL<A> &AVL<A>::operator=(const AVL<A> &orig) {
    if (this != &orig) {
        destruir(raiz);
        raiz = copiar(orig.raiz);
        altura = orig.altura;
        tam = orig.tam;
    }
    return *this;
}




#endif //PRACTICA3_AVL_H