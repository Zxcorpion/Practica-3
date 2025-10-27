
#include "Farmacia.h"
#include "MediExpress.h"
Farmacia::Farmacia(std::string cif,std::string provincia,std::string localidad,
    std::string nombre,std::string direccion,std::string codPostal):
cif_(cif),
provincia_(provincia),
localidad_(localidad),
nombre_(nombre),
direccion_(direccion),
codPostal_(codPostal)
{}

Farmacia::Farmacia(const Farmacia &orig):
cif_(orig.cif_),
provincia_(orig.provincia_),
localidad_(orig.localidad_),
nombre_(orig.nombre_),
direccion_(orig.direccion_),
codPostal_(orig.codPostal_)
{}

Farmacia::~Farmacia() {}

std::string Farmacia::get_cif() const {
    return cif_;
}

void Farmacia::set_cif(const std::string &cif) {
    cif_ = cif;
}

std::string Farmacia::get_provincia() const {
    return provincia_;
}

void Farmacia::set_provincia(const std::string &provincia) {
    provincia_ = provincia;
}

std::string Farmacia::get_localidad() const {
    return localidad_;
}

void Farmacia::set_localidad(const std::string &localidad) {
    localidad_ = localidad;
}

std::string Farmacia::get_nombre() const {
    return nombre_;
}

void Farmacia::set_nombre(const std::string &nombre) {
    nombre_ = nombre;
}

std::string Farmacia::get_direccion() const {
    return direccion_;
}

void Farmacia::set_direccion(const std::string &direccion) {
    direccion_ = direccion;
}

std::string Farmacia::get_cod_postal() const {
    return codPostal_;
}

void Farmacia::set_cod_postal(const std::string &cod_postal) {
    codPostal_ = cod_postal;
}
Farmacia &Farmacia::operator=(const Farmacia &orig) {
    if (this!=&orig) {
        cif_=orig.cif_;
        provincia_=orig.provincia_;
        localidad_=orig.localidad_;
        nombre_=orig.nombre_;
        direccion_=orig.direccion_;
        codPostal_=orig.codPostal_;
    }
    return *this;
}
bool Farmacia::operator<(const Farmacia &orig) const{
    return cif_ < orig.cif_;
}
bool Farmacia::operator==(const Farmacia &orig) const{
    return cif_ == orig.cif_;
}
bool Farmacia::operator>(const Farmacia &orig) const {
    return cif_ > orig.cif_;
}


void Farmacia::pedidoMedicam(int ID) {
    linkMedi->suministrarFarmacia(*this, ID);
}

PaMedicamento Farmacia::buscaMedicam(int ID) {
    PaMedicamento *medicam;
    for (int i = 0; i < dispense.tamlog_(); i++) {
        if (ID == dispense[i]->get_id_num()) {
            return *dispense[i];
        }
    }
    if (medicam == 0) {
        pedidoMedicam(ID);
    }
}





