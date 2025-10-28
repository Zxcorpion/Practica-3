//
// Created by marco on 22/10/2025.
//

#ifndef AVL_H
#define AVL_H

#include <iostream>
//Hay que saber cuantos nodos tiene un arbol usando un contador
template<typename U>
class NodoA {
    public:
    NodoA<U> *izq, *der;
    U dato;
    char bal;
    NodoA(U &ele): izq(0), der(0),dato(ele),bal("0"){}
    NodoA(const U &orig): izq(orig.izq), der(orig.der), dato(orig.dato),bal(orig.bal){}
};
template<typename A>
class AVL {
    NodoA<A> *raiz;
    unsigned int numEle=0, altura=0;
    private:
    void preorden (NodoA<A> *p, int nivel);
    void inorden (NodoA<A> *p, int nivel);
    void postorden (NodoA<A> *p, int nivel);
    int inserta(NodoA<A>* &n, A &dato);
    void rotDecha(NodoA<A>* &n);
    void rotIzqda(NodoA<A>* &n);
    void destruir(NodoA<A> *&p);
    NodoA<A>* copiar(NodoA<A> *&p);
    A* buscaRecursiva(A &dato,NodoA<A>* p);
    void numElem(NodoA<A>* p);
    unsigned int altu(NodoA<A>* p,int alturaactual);
    T* buscaIterativa(T &dato,Nodo<A>* p);
   public:
    AVL<A>(): raiz(0), numEle(0),altura(0){}
    AVL<A>(const AVL<A> &orig);
    virtual ~AVL<A>();
    bool insertar (A &elem) {
        numEle++;
        return inserta(raiz, elem);
    }
    VDinamico<A*> recorreInorden(){inorden(raiz, 0);}

    AVL<A> &operator=(const AVL<A> &orig);
    A* buscaRec(A &dato){return buscaRecursiva(dato,raiz);}
    unsigned int numElementos() {
        numElem(raiz);
        return numEle;
    }
    unsigned int altura() {
        altura=0;
        return altu(raiz,1);
    }
    T* buscaIt(T &dato){return buscaIterativa(dato,raiz);}
};
template <class A>
 void Abb<A>::preorden (NodoA<A> *p, int nivel){
    if (p){
        // Sustituir por procesamiento --
        cout << "Procesando nodo "<< p->dato ;
        cout << "en el nivel " << nivel << endl;
        // ----------
        preorden (p->izq, nivel+1);
        preorden (p->der, nivel+1);
    }
}

template <class A>
 void Abb<A>::inorden (NodoA<A> *p, int nivel){
    if (p){
        inorden (p->izq, nivel+1);
        // Sustituir por procesamiento ---
        cout << "Procesando nodo " << p->dato;
        cout << "en el nivel " << nivel << endl;
        // ----------
        inorden (p->der, nivel+1);
    }
}
template <class A>
void Abb<A>::postorden (NodoA<A> *p, int nivel){
    if (p){
        postorden (p->izq, nivel+1);
        postorden (p->der, nivel+1);
        // Sustituir por procesamiento ----
        cout << "Procesando nodo "<< p->dato;
        cout << "en el nivel " << nivel << endl;
        // ----------
    }
}


template<typename A>
void Avl<A>::rotIzqda(NodoA<A>* &p){
    NodoA<A> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
}
template<typename A>
void Avl<A>::rotDecha(NodoA<A>* &p){
    NodoA<A> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
}

template<typename A>
 int Avl<A>::inserta(NodoA<A>* &c, A &dato){
    NodoA<A> *p = c;
    int deltaH = 0;
    if (!p){
        p = new NodoA<A>(dato);
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
void AVL<A>::destruir(NodoA<A> *&p) { //Ponemos *& porque modificamos el arbol
    if (p != nullptr) {
        destruir(p->izq);
        destruir(p->der);
        delete p;
        p = nullptr;
    }
    altura = numEle = 0;
}

template<typename A>
NodoA<A>* AVL<A>::copiar(NodoA<A> *p) {
    if (!p) {
        return 0;
    }
        NodoA<A> *q = new NodoA<A>(p->dato); //Creamos un nodo y de ahi los hijos en caso de que los tenga
        q->izq = copiar(p->izq);
        q->der = copiar(p->der);
    return q;
}

template<typename A>
AVL<A>::AVL(const AVL<A> &orig):
altura(orig.altura),
numEle(orig.numEle)
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
        numEle = orig.numEle;
    }
    return *this;
}
template<typename A>
A *AVL<A>::buscaRecursiva(A &dato, NodoA<A> *p) {
    if(p->dato==dato) {
        return p->dato;
    }else {
        buscaRecursiva(dato, p->izq);
        buscaRecursiva(dato, p->der);
    }
    return 0;
}
template<typename A>
void AVL<A>::numElem(NodoA<A> *p) {
    if (p) {
        tam++;
        numElem(p->izq);
        numElem(p->der);
    }
}
template<typename A>
unsigned int AVL<A>::altu(NodoA<A> *p,int alturaactual) {
    if(p==raiz==nullptr) {
        return 0;//si el arbol está vacio entonces la altura es 0;
    }
    if(p) {
        //Actualizo la altura cada vez que se cumpla la siguiente condición
        if(alturaactual>altura) {
            altura=alturaactual;
        }
        altu(p->izq,alturaactual+1);
        altu(p->der,alturaactual+1);
    }
    return altura;
}
template<typename A>
T *AVL<A>::buscaIterativa(T &dato, NodoA<A> *p) {
    //Mediante un while comprobamos todos los datos de todos los nodos aprovechando que sabemos que un arbol AVL se encuentra en orden
    while(p) {
        if(p->dato==dato) {
            return p->dato;
        }
        if(p->dato>dato) {
            p = p->izq;
        }else {
            p = p->der;
        }
    }
    //Si no encuentra nada devuelvo un cero.
    return 0;
}












#endif //AVL_H
