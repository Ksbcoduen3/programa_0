#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Estructura para representar un postre
struct Postre {
    int id;
    string nombre;
    float precio;
    int cantidad;
};

// -------------------- FUNCIONES ADMINISTRADOR --------------------

void agregarPostre() {
    ofstream archivo("postres.txt", ios::app);
    Postre p;

    cout << "\n--- Agregar nuevo postre ---\n";
    cout << "ID: ";
    cin >> p.id;
    cin.ignore();
    cout << "Nombre:    ";
    getline(cin, p.nombre); 
    cout << "Precio: ";
    cin >> p.precio;
    cout << "Cantidad: ";
    cin >> p.cantidad;

    archivo << p.id << "," << p.nombre << "," << p.precio << "," << p.cantidad << "\n";
    archivo.close();

    cout << "✅ Postre agregado correctamente.\n";
}

void mostrarPostres() {
    ifstream archivo("postres.txt");
    string linea;
#include <iostream>
    int opcion;
    do {
        cout << "\n--- MENÚ ADMINISTRADOR ---\n";
        cout << "1. Ver postres\n";
        cout << "2. Agregar postre\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: mostrarPostres(); break;
            case 2: agregarPostre(); break;
            case 3: cout << "Cerrando sesión...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 3);
}

void menuComprador() {
    int opcion;
    do {
        cout << "\n--- MENÚ COMPRADOR ---\n";
        cout << "1. Ver menú de postres\n";
        cout << "2. Comprar postre\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: verMenu(); break;
            case 2: comprarPostre(); break;
            case 3: cout << "Gracias por su compra!\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 3);
}

// -------------------- PROGRAMA PRINCIPAL --------------------

int main() {
    string usuario, contraseña;

    cout << "Ingrese usuario: ";
    cin >> usuario;
    cout << "Ingrese contraseña: ";
    cin >> contraseña;

    if (usuario == "admin" && contraseña == "12345678") {
        cout << "\nBienvenido, Administrador 🧑‍💼\n";
        menuAdmin();
    }
    else if (usuario == "comprador" && contraseña == "abc123") {
        cout << "\nBienvenido, Comprador 🛒\n";
        menuComprador();
    }
    else {
        cout << "\n❌ Usuario o contraseña incorrectos.\n";
    }

    return 0;
}
    cout << "\n--- Lista de postres disponibles ---\n";
    cout << "ID\tNombre\t\tPrecio\tCantidad\n";
    cout << "---------------------------------------------\n";

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, precio, cantidad;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, precio, ',');
        getline(ss, cantidad, ',');

        cout << id << "\t" << nombre << "\t\t" << precio << "\t" << cantidad << "\n";
    }

    archivo.close();
}

// -------------------- FUNCIONES COMPRADOR --------------------

void verMenu() {
    mostrarPostres();
}

void comprarPostre() {
    int id, cantidadCompra;
    vector<Postre> lista;
    Postre p;
    bool encontrado = false;

    ifstream archivo("postres.txt");
    string linea;

    // Leer todos los postres del archivo
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, nombre, precioStr, cantidadStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, precioStr, ',');
        getline(ss, cantidadStr, ',');

        p.id = stoi(idStr);
        p.nombre = nombre;
        p.precio = stof(precioStr);
        p.cantidad = stoi(cantidadStr);
        lista.push_back(p);
    }
    archivo.close();#include <iostream>
    int opcion;
    do {
        cout << "\n--- MENÚ ADMINISTRADOR ---\n";
        cout << "1. Ver postres\n";
        cout << "2. Agregar postre\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: mostrarPostres(); break;
            case 2: agregarPostre(); break;
            case 3: cout << "Cerrando sesión...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 3);
}

void menuComprador() {
    int opcion;
    do {
        cout << "\n--- MENÚ COMPRADOR ---\n";
        cout << "1. Ver menú de postres\n";
        cout << "2. Comprar postre\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: verMenu(); break;
            case 2: comprarPostre(); break;
            case 3: cout << "Gracias por su compra!\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 3);
}

// -------------------- PROGRAMA PRINCIPAL --------------------

int main() {
    string usuario, contraseña;

    cout << "Ingrese usuario: ";
    cin >> usuario;
    cout << "Ingrese contraseña: ";
    cin >> contraseña;

    if (usuario == "admin" && contraseña == "12345678") {
        cout << "\nBienvenido, Administrador 🧑‍💼\n";
        menuAdmin();
    }
    else if (usuario == "comprador" && contraseña == "abc123") {
        cout << "\nBienvenido, Comprador 🛒\n";
        menuComprador();
    }
    else {
        cout << "\n❌ Usuario o contraseña incorrectos.\n";
    }

    return 0;
}

    cout << "\nIngrese el ID del postre que desea comprar: ";
    cin >> id;
    cout << "Cantidad que desea comprar: ";
    cin >> cantidadCompra;

    // Buscar el postre
    for (auto &item : lista) {
        if (item.id == id) {
            if (cantidadCompra <= item.cantidad) {
                item.cantidad -= cantidadCompra;
                cout << "\n✅ Compra realizada con éxito.\n";
                cout << "Total a pagar: $" << (item.precio * cantidadCompra) << endl;
            } else {
                cout << "\n❌ No hay suficiente cantidad disponible.\n";
            }
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\n❌ No se encontró el postre con ese ID.\n";
        return;
    }

    // Reescribir archivo actualizado
    ofstream out("postres.txt");
    for (auto &item : lista) {
        out << item.id << "," << item.nombre << "," << item.precio << "," << item.cantidad << "\n";
    }
    out.close();
}

// -------------------- MENÚS --------------------

void menuAdmin() {
    int opcion;
    do {
        cout << "\n--- MENÚ ADMINISTRADOR ---\n";
        cout << "1. Ver postres\n";
        cout << "2. Agregar postre\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: mostrarPostres(); break;
            case 2: agregarPostre(); break;
            case 3: cout << "Cerrando sesión...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 3);
}

void menuComprador() {
    int opcion;
    do {
        cout << "\n--- MENÚ COMPRADOR ---\n";
        cout << "1. Ver menú de postres\n";
        cout << "2. Comprar postre\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: verMenu(); break;
            case 2: comprarPostre(); break;
            case 3: cout << "Gracias por su compra!\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 3);
}

// -------------------- PROGRAMA PRINCIPAL --------------------

int main() {
    string usuario, contraseña;

    cout << "Ingrese usuario: ";
    cin >> usuario;
    cout << "Ingrese contraseña: ";
    cin >> contraseña;

    if (usuario == "admin" && contraseña == "12345678") {
        cout << "\nBienvenido, Administrador 🧑‍💼\n";
        menuAdmin();
    }
    else if (usuario == "comprador" && contraseña == "abc123") {
        cout << "\nBienvenido, Comprador 🛒\n";
        menuComprador();
    }
    else {
        cout << "\n❌ Usuario o contraseña incorrectos.\n";
    }

    return 0;
}
