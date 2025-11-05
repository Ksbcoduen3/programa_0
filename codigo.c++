#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

struct Postre {
    int id;
    string nombre;
    float precio;
    int cantidad;
};

// Leer postres del archivo
vector<Postre> leerPostres() {
    vector<Postre> lista;
    ifstream archivo("postres.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, precio, cantidad;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, precio, ',');
        getline(ss, cantidad, ',');

        if (id != "" && nombre != "" && precio != "" && cantidad != "") {
            Postre p;
            p.id = stoi(id);
            p.nombre = nombre;
            p.precio = stof(precio);
            p.cantidad = stoi(cantidad);
            lista.push_back(p);
        }
    }

    archivo.close();
    return lista;
}

// Guardar postres en archivo
void guardarPostres(const vector<Postre>& lista) {
    ofstream archivo("postres.txt");
    for (auto &p : lista) {
        archivo << p.id << "," << p.nombre << "," << p.precio << "," << p.cantidad << "\n";
    }
    archivo.close();
}

// Mostrar postres
void mostrarPostres() {
    auto lista = leerPostres();
    cout << "\nLista de postres disponibles:\n";
    cout << "----------------------------------------\n";
    for (auto &p : lista) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Precio: $" << p.precio
             << " | Cantidad: " << p.cantidad << endl;
    }
    cout << "----------------------------------------\n";
}

// Agregar postre
void agregarPostre() {
    vector<Postre> lista = leerPostres();
    Postre p;

    cout << "\nAgregar nuevo postre:\n";
    cout << "ID: ";
    cin >> p.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nombre: ";
    getline(cin, p.nombre);
    cout << "Precio: ";
    cin >> p.precio;
    cout << "Cantidad: ";
    cin >> p.cantidad;

    lista.push_back(p);
    guardarPostres(lista);

    cout << "Postre agregado correctamente.\n";
}

// Modificar postre
void modificarPostre() {
    auto lista = leerPostres();
    int idBuscar;
    bool encontrado = false;

    cout << "\nIngrese el ID del postre a modificar: ";
    cin >> idBuscar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto &p : lista) {
        if (p.id == idBuscar) {
            encontrado = true;
            cout << "\nPostre encontrado:\n";
            cout << "Nombre actual: " << p.nombre << endl;
            cout << "Precio actual: " << p.precio << endl;
            cout << "Cantidad actual: " << p.cantidad << endl;

            cout << "\nNuevo nombre (enter para dejar igual): ";
            string nuevoNombre;
            getline(cin, nuevoNombre);
            if (!nuevoNombre.empty()) p.nombre = nuevoNombre;

            cout << "Nuevo precio (0 para dejar igual): ";
            float nuevoPrecio;
            cin >> nuevoPrecio;
            if (nuevoPrecio != 0) p.precio = nuevoPrecio;

            cout << "Nueva cantidad (-1 para dejar igual): ";
            int nuevaCantidad;
            cin >> nuevaCantidad;
            if (nuevaCantidad != -1) p.cantidad = nuevaCantidad;

            break;
        }
    }

    if (encontrado) {
        guardarPostres(lista);
        cout << "Postre modificado correctamente.\n";
    } else {
        cout << "No se encontró el postre con ese ID.\n";
    }
}

// Eliminar postre
void eliminarPostre() {
    auto lista = leerPostres();
    int id;
    bool eliminado = false;

    cout << "\nIngrese el ID del postre a eliminar: ";
    cin >> id;

    vector<Postre> nuevaLista;
    for (auto &p : lista) {
        if (p.id == id) {
            eliminado = true;
            cout << "Postre eliminado: " << p.nombre << endl;
            continue;
        }
        nuevaLista.push_back(p);
    }

    guardarPostres(nuevaLista);

    if (eliminado)
        cout << "Postre eliminado correctamente.\n";
    else
        cout << "No se encontró el postre.\n";
}

// Comprar postre
void comprarPostre() {
    auto lista = leerPostres();
    int id, cantidadCompra;
    bool encontrado = false;

    cout << "\nIngrese el ID del postre a comprar: ";
    cin >> id;
    cout << "Cantidad a comprar: ";
    cin >> cantidadCompra;

    for (auto &p : lista) {
        if (p.id == id) {
            encontrado = true;
            if (cantidadCompra <= p.cantidad) {
                p.cantidad -= cantidadCompra;
                cout << "\nCompra realizada correctamente.\n";
                cout << "Total a pagar: $" << p.precio * cantidadCompra << endl;
            } else {
                cout << "No hay suficiente cantidad.\n";
            }
            break;
        }
    }

    if (encontrado) {
        guardarPostres(lista);
    } else {
        cout << "No se encontró el postre.\n";
    }
}

// Menú administrador
void menuAdmin() {
    int op;
    do {
        cout << "\n--- MENU ADMINISTRADOR ---\n";
        cout << "1. Ver postres\n";
        cout << "2. Agregar postre\n";
        cout << "3. Modificar postre\n";
        cout << "4. Eliminar postre\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (op) {
            case 1: mostrarPostres(); break;
            case 2: agregarPostre(); break;
            case 3: modificarPostre(); break;
            case 4: eliminarPostre(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (op != 0);
}

// Menú comprador
void menuComprador() {
    int op;
    do {
        cout << "\n--- MENU COMPRADOR ---\n";
        cout << "1. Ver menú de postres\n";
        cout << "2. Comprar postre\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> op;

        switch (op) {
            case 1: mostrarPostres(); break;
            case 2: comprarPostre(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (op != 0);
}

// Programa principal
int main() {
    string usuario, password;

    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contraseña: ";
    cin >> password;

    if (usuario == "admin" && password == "12345678") {
        menuAdmin();
    } else if (usuario == "comprador" && password == "abc123") {
        menuComprador();
    } else {
        cout << "Usuario o contraseña incorrectos.\n";
    }

    return 0;
}
