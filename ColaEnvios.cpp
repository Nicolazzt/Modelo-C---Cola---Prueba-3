#include "ColaEnvios.hpp"
#include <fstream>

#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Nicolas Lopez - C.I. V-30024260 - Rol: ColaEnvios (encolar, desencolar, vaciar, tamanio, guardarCSV, cargarCSV, limpiar, frente)
//   2. Diego Lopez - C.I. V-32451137 - Rol: ColaEnvios (constructor de copia, operator= de copia, constructor de movimiento, operator= de movimiento)
//   3. Alejandro Pena - C.I. V-32591935 - Rol: ColaEnvios (aVector, buscarPorId x2, cancelar, moverAlFrente, moverAlFinal, invertir)
// ====================================================================
// Completen la implementacion de esta estructura.
// ====================================================================

ColaEnvios::Nodo::Nodo(const TextMessage& mensaje)
    : dato(mensaje), siguiente(nullptr)
{
}

ColaEnvios::ColaEnvios()
    : frente_(nullptr), final_(nullptr), cantidad(0)
{
}

ColaEnvios::ColaEnvios(const ColaEnvios& otra)
    : frente_(nullptr), final_(nullptr), cantidad(0)
{
    std::shared_ptr<Nodo> actual = otra.frente_;
    while (actual != nullptr)
    {
        std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>(actual->dato);

        if(final_ == nullptr)
        {
            frente_= nuevo;
            final_= nuevo;
        }
        else
        {
            final_->siguiente= nuevo;
            final_= nuevo;
        }

        cantidad++;
        actual = actual->siguiente;
    }
}

ColaEnvios& ColaEnvios::operator=(const ColaEnvios& otra)
{
    if (this !=&otra)
    {
        limpiar();

    std::shared_ptr<Nodo> actual = otra.frente_;
    while (actual != nullptr)
    {
        std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>(actual->dato);

        if(final_ == nullptr)
        {
            frente_= nuevo;
            final_= nuevo;
        }
        else
        {
            final_->siguiente= nuevo;
            final_= nuevo;
        }

        cantidad++;
        actual = actual->siguiente;
    }
    }
    return *this;
}

ColaEnvios::ColaEnvios(ColaEnvios&& otra) noexcept
    : frente_(otra.frente_), final_(otra.final_), cantidad(otra.cantidad)
{
    
    otra.frente_ = nullptr;
    otra.final_ = nullptr;
    otra.cantidad = 0;
}

ColaEnvios& ColaEnvios::operator=(ColaEnvios&& otra) noexcept
{
    if (this != &otra)
    {
        limpiar();

        frente_=otra.frente_;
        final_=otra.final_;
        cantidad= otra.cantidad;

        otra.frente_=nullptr;
        otra.final_=nullptr;
        otra.cantidad=0;
    }
    return *this;
}

bool ColaEnvios::vacia() const
{
    if (cantidad == 0)
    {
        return true;
    }else
    {
        return false;
    }
}

std::size_t ColaEnvios::tamanio() const
{
    return cantidad;
    
}

bool ColaEnvios::encolar(const TextMessage& mensaje)
{
    std::shared_ptr<Nodo> actual = frente_;

    while(actual != nullptr)
    {
        if(actual->dato.getId() == mensaje.getId())
        {
            return false;
        }

        actual = actual->siguiente;
    }

    std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>(mensaje);
    if (final_ == nullptr)
    {
        final_ = nuevo;
        frente_= nuevo;
    }else
    {
        final_->siguiente = nuevo;
        final_= nuevo;
    }

    cantidad++;

    return true;
    
}

bool ColaEnvios::desencolar()
{
    if(final_ == nullptr)
    {
        return false;
    }

    frente_=frente_->siguiente;

     //En caso de que haya existido solo 1 elemento en la cola y lo hayamos eliminado final tambien debe pasar a apuntar a nullptr
    if(frente_ == nullptr)
    {
        final_ = nullptr;
    }

    cantidad--;

    return true;


   
}

const TextMessage* ColaEnvios::frente() const
{
    if(vacia() == true)
    {
        return nullptr;

    }else
    {
        return &frente_->dato;
    }
}

TextMessage* ColaEnvios::frente()
{
      if(vacia() == true)
    {
        return nullptr;

    }else
    {
        return &frente_->dato;
    }
}

void ColaEnvios::limpiar()
{
    while(vacia() == false)
    {
        desencolar();
    }
}

std::vector<TextMessage> ColaEnvios::aVector() const
{
 std::vector<TextMessage> vec;
    auto actual = frente_;
    while (actual != nullptr)
    {
        vec.push_back(actual->dato);
        actual = actual->siguiente;
    }
    return vec;
}

const TextMessage* ColaEnvios::buscarPorId(int id) const
{
    auto actual = frente_;
    while (actual != nullptr)
    {
        if (actual->dato.getId() == id)
        {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

TextMessage* ColaEnvios::buscarPorId(int id)
{
    auto actual = frente_;
    while (actual != nullptr)
    {
        if (actual->dato.getId() == id)
        {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}
bool ColaEnvios::cancelar(int id)
{
    if (vacia())
    {
        return false;
    }

    if (frente_->dato.getId() == id)
    {
        return desencolar();
    }

    auto actual = frente_;
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->dato.getId() == id)
        {
            auto aBorrar = actual->siguiente;
            actual->siguiente = aBorrar->siguiente;

            if (aBorrar == final_)
            {
                final_ = actual;
            }

            cantidad--;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool ColaEnvios::moverAlFrente(int id)
{
    if (vacia())
    {
        return false;
    }

    if (frente_->dato.getId() == id)
    {
        return true;
    }

    auto actual = frente_;
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->dato.getId() == id)
        {
            auto nodo = actual->siguiente;
            actual->siguiente = nodo->siguiente;

            if (nodo == final_)
            {
                final_ = actual;
            }

            nodo->siguiente = frente_;
            frente_ = nodo;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool ColaEnvios::moverAlFinal(int id)
{
    if (vacia())
    {
        return false;
    }

    if (final_->dato.getId() == id)
    {
        return true;
    }

    if (frente_->dato.getId() == id)
    {
        auto nodo = frente_;
        frente_ = frente_->siguiente;

        nodo->siguiente = nullptr;
        final_->siguiente = nodo;
        final_ = nodo;
        return true;
    }

    auto actual = frente_;
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->dato.getId() == id)
        {
            auto nodo = actual->siguiente;
            actual->siguiente = nodo->siguiente;

            nodo->siguiente = nullptr;
            final_->siguiente = nodo;
            final_ = nodo;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void ColaEnvios::invertir()
{
    if (vacia() || cantidad == 1)
    {
        return;
    }

    std::shared_ptr<Nodo> anterior = nullptr;
    std::shared_ptr<Nodo> actual = frente_;
    final_ = frente_;

    while (actual != nullptr)
    {
        auto siguienteNodo = actual->siguiente;
        actual->siguiente = anterior;
        anterior = actual;
        actual = siguienteNodo;
    }
    frente_ = anterior;
}

bool ColaEnvios::guardarCSV(const std::string& ruta) const
{
    std::ofstream archivo(ruta);

    if(archivo.is_open() == false)
    {
        return false;
    }

    std::shared_ptr<Nodo> actual = frente_;

    while(actual != nullptr)
    {
        archivo << actual->dato.toCSV() << std::endl;
        
        actual = actual->siguiente;
    }

    archivo.close();

    return true;
    
}

bool ColaEnvios::cargarCSV(const std::string& ruta)
{
    std::ifstream archivo(ruta);

    if(archivo.is_open() == false)
    {
        return false;
    }

    limpiar();
    std::string linea;

    while(std::getline(archivo,linea))
    {
        if(linea.empty())
        {
            continue;
        }

        TextMessage Mensaje = TextMessage::fromCSV(linea);
        encolar(Mensaje);
    }

    archivo.close();

    return true;
    
}
