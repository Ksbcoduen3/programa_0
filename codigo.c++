#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class Producto {
private:
    int id;
    string nombre;
    string sabor;
    double precioNormal;
    double precioVenta;
    int existencia;
    string codigo;

public:
    Producto() : id(0), nombre(""), sabor(""), precioNormal(0.0), precioVenta(0.0), existencia(0), codigo("") {}
    Producto(int i, string n, string s, double pn, double pv, int e, string c)
        : id(i), nombre(n), sabor(s), precioNormal(pn), precioVenta(pv), existencia(e), codigo(c) {}

    void anadirProducto() {
        cout << "\n=== Añadir Producto al Inventario ===\n";
        cout << "ID del producto: ";
        cin >> id;
        cout << "Nombre del producto: ";
        cin >> nombre;
        cout << "Sabor: ";
        cin >> sabor;
        cout << "Precio normal: $";
        cin >> precioNormal;
        cout << "Precio de venta: $";
        cin >> precioVenta;
        cout << "Existencia: ";
        cin >> existencia;
        cout << "Código de producto: ";
        cin >> codigo;

        ofstream archivo("productos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << id << "," << nombre << "," << sabor << "," << precioNormal << "," 
                    << precioVenta << "," << existencia << "," << codigo << endl;
            archivo.close();
            cout << "✅ Producto agregado correctamente.\n";
        } else {
            cerr << "❌ Error al guardar el producto.\n";
        }
    }

    void mostrar() const {
        cout << left << setw(5) << id
             << setw(15) << nombre
             << setw(15) << sabor
             << setw(12) << precioNormal
             << setw(12) << precioVenta
             << setw(10) << existencia
             << setw(10) << codigo << endl;
    }

    string getNombre() const { return nombre; }
    string getSabor() const { return sabor; }
    double getPrecioVenta() const { return precioVenta; }
    int getExistencia() const { return existencia; }

    void venderProducto(int cantidad) {
        if (cantidad <= existencia) {
            existencia -= cantidad;
            cout << "✅ Venta realizada. Se vendieron " << cantidad << " unidades de " << nombre << ".\n";
        } else {
            cout << "❌ No hay suficiente existencia.\n";
        }
    }
};

class Empleado {
private:
    string nombre;
    string puesto;
    int edad;

public:
    Empleado() : nombre(""), puesto(""), edad(0) {}
    Empleado(string n, string p, int e) : nombre(n), puesto(p), edad(e) {}

    void anadirEmpleado() {
        cout << "\n=== Registro de Empleado ===\n";
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Puesto (Gerente/Empleado): ";
        cin >> puesto;
        cout << "Edad: ";
        cin >> edad;

        ofstream archivo("empleados.txt", ios::app);
        if (archivo.is_open()) {
            archivo << nombre << "," << puesto << "," << edad << endl;
            archivo.close();
            cout << "✅ Empleado registrado correctamente.\n";
        } else {
            cerr << "❌ Error al guardar empleado.\n";
        }
    }

    string getPuesto() const { return puesto; }
    string getNombre() const { return nombre; }
};

void mostrarInventario(const vector<Producto>& productos) {
    cout << "\n=== INVENTARIO DE HELADOS ===\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "Nombre"
         << setw(15) << "Sabor"
         << setw(12) << "Precio N."
         << setw(12) << "Precio V."
         << setw(10) << "Stock"
         << setw(10) << "Código" << endl;
    for (const auto& p : productos)
        p.mostrar();
}

void emitirTicket(const Producto& p, int cantidad) {
    double total = cantidad * p.getPrecioVenta();
    cout << "\n========== TICKET DE VENTA ==========\n";
    cout << "Producto: " << p.getNombre() << " (" << p.getSabor() << ")\n";
    cout << "Cantidad: " << cantidad << endl;
    cout << "Precio unitario: $" << p.getPrecioVenta() << endl;
    cout << "Total a pagar: $" << total << endl;
    cout << "=====================================\n";

    ofstream ticket("ventas.txt", ios::app);
    if (ticket.is_open()) {
        ticket << p.getNombre() << "," << p.getSabor() << "," << cantidad << "," << total << endl;
        ticket.close();
    }
}

int main() {
    vector<Producto> productos = {
        {1, "Helado", "Chocolate", 30, 25, 15, "CH-01"},
        {2, "Helado", "Fresa", 28, 23, 10, "FR-02"},
        {3, "Helado", "Vainilla", 27, 22, 12, "VA-03"},
        {4, "Helado", "Oreo", 32, 28, 8, "OR-04"}
    };

    string usuario;
    int pass, opcion = 0;
    cout << "=== SISTEMA DE GESTIÓN DE HELADOS ===\n";
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contraseña: ";
    cin >> pass;

    if (usuario == "Gerente" && pass == 1234) {
        do {
            cout << "\n*** PANEL GERENTE ***\n";
            cout << "1. Ver inventario\n";
            cout << "2. Agregar producto\n";
            cout << "3. Registrar empleado\n";
            cout << "4. Emitir ticket\n";
            cout << "5. Salir\n";
            cout << "Opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    mostrarInventario(productos);
                    break;
                case 2: {
                    Producto p;
                    p.anadirProducto();
                    productos.push_back(p);
                    break;
                }
                case 3: {
                    Empleado e;
                    e.anadirEmpleado();
                    break;
                }
                case 4: {
                    string nombre;
                    int cantidad;
                    cout << "Nombre del sabor vendido: ";
                    cin >> nombre;
                    cout << "Cantidad: ";
                    cin >> cantidad;

                    bool encontrado = false;
                    for (auto& p : productos) {
                        if (p.getSabor() == nombre) {
                            encontrado = true;
                            p.venderProducto(cantidad);
                            emitirTicket(p, cantidad);
                        }
                    }
                    if (!encontrado)
                        cout << "❌ Sabor no encontrado.\n";
                    break;
                }
                case 5:
                    cout << "Saliendo...\n";
                    break;
                default:
                    cout << "Opción no válida.\n";
            }
        } while (opcion != 5);
    } else if (usuario == "Empleado" && pass == 1234) {
        do {
            cout << "\n*** PANEL EMPLEADO ***\n";
            cout << "1. Ver inventario\n";
            cout << "2. Emitir ticket\n";
            cout << "3. Salir\n";
            cout << "Opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    mostrarInventario(productos);
                    break;
                case 2: {
                    string nombre;
                    int cantidad;
                    cout << "Nombre del sabor vendido: ";
                    cin >> nombre;
                    cout << "Cantidad: ";
                    cin >> cantidad;

                    bool encontrado = false;
                    for (auto& p : productos) {
                        if (p.getSabor() == nombre) {
                            encontrado = true;
                            p.venderProducto(cantidad);
                            emitirTicket(p, cantidad);
                        }
                    }
                    if (!encontrado)
                        cout << "❌ Sabor no encontrado.\n";
                    break;
                }
                case 3:
                    cout << "Saliendo...\n";
                    break;
                default:
                    cout << "Opción no válida.\n";
            }
        } while (opcion != 3);
    } else {
        cout << "❌ Usuario o contraseña incorrectos.\n";
    }

    return 0;
}
