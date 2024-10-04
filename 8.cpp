#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bebida {
protected:
    string nombreMarca;
    double costo;
    double volumenLitros;

public:
    Bebida(const string& nombreMarca, double costo, double volumenLitros)
        : nombreMarca(nombreMarca), costo(costo), volumenLitros(volumenLitros) {}

    string getNombreMarca() const {
        return nombreMarca;
    }

    double getCosto() const {
        return costo;
    }

    double getVolumenLitros() const {
        return volumenLitros;
    }

    virtual void mostrarDetalles() const {
        cout << "Marca: " << nombreMarca << ", Precio: $" << costo << ", Litros: " << volumenLitros << endl;
    }

    virtual ~Bebida() = default; 
};

class BebidaAzucarada : public Bebida {
private:
    double gramosAzucar;
    bool promocionDisponible;

public:
    BebidaAzucarada(const string& nombreMarca, double costo, double volumenLitros, double gramosAzucar, bool promocionDisponible)
        : Bebida(nombreMarca, costo, volumenLitros), gramosAzucar(gramosAzucar), promocionDisponible(promocionDisponible) {}

    double getGramosAzucar() const {
        return gramosAzucar;
    }

    bool tienePromocion() const {
        return promocionDisponible;
    }

    void mostrarDetalles() const override {
        Bebida::mostrarDetalles();
        cout << "Cantidad de Azúcar: " << gramosAzucar << "g, Promoción: " 
             << (promocionDisponible ? "Sí" : "No") << endl;
    }
};

class AguaMineral : public Bebida {
private:
    string fuenteOrigen;

public:
    AguaMineral(const string& nombreMarca, double costo, double volumenLitros, const string& fuenteOrigen)
        : Bebida(nombreMarca, costo, volumenLitros), fuenteOrigen(fuenteOrigen) {}

    string getFuenteOrigen() const {
        return fuenteOrigen;
    }

    void mostrarDetalles() const override {
        Bebida::mostrarDetalles();
        cout << "Origen: " << fuenteOrigen << endl;
    }
};

class Inventario {
private:
    vector<Bebida*> listaBebidas;

public:
    ~Inventario() {
        for (Bebida* bebida : listaBebidas) {
            delete bebida;
        }
    }

    void agregarBebida(Bebida* bebida) {
        listaBebidas.push_back(bebida);
    }

    double calcularCostoTotal() const {
        double totalCosto = 0;
        for (const Bebida* bebida : listaBebidas) {
            totalCosto += bebida->getCosto();
        }
        return totalCosto;
    }

    double calcularCostoPorMarca(const string& marcaBuscada) const {
        double totalCosto = 0;
        for (const Bebida* bebida : listaBebidas) {
            if (bebida->getNombreMarca() == marcaBuscada) {
                totalCosto += bebida->getCosto();
            }
        }
        return totalCosto;
    }

    void mostrarDetalles() const {
        for (const Bebida* bebida : listaBebidas) {
            bebida->mostrarDetalles();
            cout << "-------------------" << endl;
        }
    }
};

int main() {
    Inventario inventario;

    Bebida* bebida1 = new BebidaAzucarada("Coca-Cola", 1.5, 1.5, 35.0, true);
    Bebida* bebida2 = new BebidaAzucarada("Fanta", 1.3, 1.5, 30.0, false);
    Bebida* agua1 = new AguaMineral("Evian", 2.0, 1.0, "Montaña de los Alpes");

    inventario.agregarBebida(bebida1);
    inventario.agregarBebida(bebida2);
    inventario.agregarBebida(agua1);

    cout << "Información de todas las bebidas en el inventario:" << endl;
    inventario.mostrarDetalles();

    cout << "Costo total de todas las bebidas: $" << inventario.calcularCostoTotal() << endl;
    cout << "Costo total de las bebidas de la marca Coca-Cola: $" << inventario.calcularCostoPorMarca("Coca-Cola") << endl;

    return 0;
}
