//
// Created by marco on 23/10/2025.
//

#ifndef FARMACIA_H
#define FARMACIA_H
#include <iostream>
#include "PaMedicamento.h"
#include "VDinamico.h"
class MediExpress;


class Farmacia {
private:
    std::string cif_="-",provincia_="-",localidad_="-",
    nombre_="-",direccion_="-",codPostal_="-";
    MediExpress* linkMedi;
    VDinamico<PaMedicamento*> dispense;
public:
    Farmacia(std::string cif="-",std::string provincia="-",std::string localidad="-",
    std::string nombre="-",std::string direccion="-",std::string codPostal="-");
    Farmacia(const Farmacia &orig);
    virtual ~Farmacia();

    std::string get_cif() const;
    void set_cif(const std::string &cif);
    std::string get_provincia() const;
    void set_provincia(const std::string &provincia);
    std::string get_localidad() const;
    void set_localidad(const std::string &localidad);
    std::string get_nombre() const;
    void set_nombre(const std::string &nombre);
    std::string get_direccion() const;
    void set_direccion(const std::string &direccion);
    std::string get_cod_postal() const;
    void set_cod_postal(const std::string &cod_postal);
    PaMedicamento* buscaMedicam(const int &ID);
    void pedidoMedicam(const int ID);
    void dispensaMedicam(PaMedicamento pa);

    Farmacia &operator=(const Farmacia& orig);
    bool operator==(const Farmacia &orig) const;
    bool operator<(const Farmacia &orig) const;
    bool operator>(const Farmacia &orig) const;
};




#endif //FARMACIA_H
