#include <iostream>
#include <sstream>
#include <fstream>
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include "VDinamico.h"
#include "AVL.h"
#include "Farmacia.h"


AVL<Farmacia> leeFicheroArbol(const std::string &fichero) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string cif_ = "";
    std::string provincia_= "";
    std::string localidad_= "";
    std::string nombre_= "";
    std::string direccion_= "";
    std::string codPostal_= "";

    AVL<Farmacia> arbolFarmacia;

    is.open(fichero); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia_,';');
                getline(columnas, localidad_,';');
                getline(columnas, nombre_,';');
                getline(columnas, direccion_,';');
                getline(columnas, codPostal_,';');


                Farmacia farmacia_(cif_,provincia_,localidad_,nombre_, direccion_, codPostal_);
                try {
                    arbolFarmacia.insertar(farmacia_);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.str(std::string());
                columnas.clear();
                columnas.str(fila);

                std::cout << ++contador
                          << " Farmacia: ( CIF = " << cif_
                          << " Provincia = " << provincia_ << " Localidad = " << localidad_
                          << " Nombre = " << nombre_ << " Direccion = " << direccion_ << " CodPostal = " << codPostal_
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    return arbolFarmacia;
}

VDinamico<Farmacia> leeFicheroVector(const std::string &fichero) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string cif_ = "";
    std::string provincia_="";
    std::string localidad_="";
    std::string nombre_="";
    std::string direccion_="";
    std::string codPostal_="";

    VDinamico<Farmacia> vectorFarmacia;

    is.open(fichero); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia_,';');
                getline(columnas, localidad_,';');
                getline(columnas, nombre_,';');
                getline(columnas, direccion_,';');
                getline(columnas, codPostal_,';');


                Farmacia farmacia_(cif_,provincia_,localidad_,nombre_, direccion_, codPostal_);
                try {
                    vectorFarmacia.insertar(farmacia_);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                std::cout << ++contador
                          << " Farmacia: ( CIF = " << cif_
                          << " Provincia = " << provincia_ << " Localidad = " << localidad_
                          << " Nombre = " << nombre_ << " Direccion = " << direccion_ << " CodPostal = " << codPostal_
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    return vectorFarmacia;
}
void calcularbusqueda(VDinamico<Farmacia> &vectorFarmacias,AVL<Farmacia> &arbol,std::string cifs[],float &tiempo) {
    clock_t t_ini = clock();
    for(int i=0;i<500;i++) {
        if(arbol.buscaRec(vectorFarmacias[i])==nullptr) {
            std::cout<<"No se encontro"<<std::endl;
        }else {
            if(arbol.buscaRec(vectorFarmacias[i])->get_cif()!=cifs[i]){
                std::cout<<"CIF no encontrado"<<std::endl;
            }else {
                std::cout<<cifs[i]<<std::endl;
            }
        }
    }
    std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    tiempo=((clock() - t_ini) / (float) CLOCKS_PER_SEC);
}
void busquedasegundotipo(VDinamico<Farmacia> &vectorFarmacias,std::string cifs[],float &tiempo) {
    clock_t t_ini = clock();
    for(int i=0;i<500;i++) {
        if(vectorFarmacias[i].get_cif()!=cifs[i]) {
            std::cout<<"No se encontro"<<std::endl;
        }else {
            std::cout<<cifs[i]<<std::endl;
        }
    }
    std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    tiempo=((clock() - t_ini) / (float) CLOCKS_PER_SEC);
}
int main() {
    //Prueba 1
    std::cout<<"Insercion de las farmacias en un arbol"<<std::endl;
    AVL<Farmacia> a1 = leeFicheroArbol("../farmacias.csv");
    std::cout<<"\n";
    std::cout<<"Insercion de las farmacias en un vector dinamico"<<std::endl;
    VDinamico<Farmacia> v1 = leeFicheroVector("../farmacias.csv");
    std::cout<<"\n";

    std::string vectorCIFS[500];
    for (int i=0; i<500; i++) {
        vectorCIFS[i] = v1[i].get_cif();
    }
    float tiempo1=0, tiempo2=0;
    calcularbusqueda(v1,a1,vectorCIFS,tiempo1);
    busquedasegundotipo(v1,vectorCIFS,tiempo2);
    if(tiempo1>tiempo2) {
        std::cout<<"Es mas eficiente buscar en AVL"<<std::endl;
    }else {
        if(tiempo2>tiempo1) {
            std::cout<<"Es mas eficiente buscar en un vector dinamico"<<std::endl;
        }
    }
    if(tiempo1==tiempo2) {
        std::cout<<"Igual de eficiente"<<std::endl;
    }
    return 0;
}
