#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "TextMessage.hpp"

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO C (COLA ENLAZADA)
// Integrantes:
//   1. Nicolas Lopez - C.I. V-30024260 - Rol: ColaEnvios (encolar, desencolar, vaciar, tamanio, guardarCSV, cargarCSV, limpiar, frente)
//   2. Diego Lopez - C.I. V-32451137 - Rol: ColaEnvios (constructor de copia, operator= de copia, constructor de movimiento, operator= de movimiento)
//   3. Alejandro Pena - C.I. V-32591935 - Rol: ColaEnvios (aVector, buscarPorId x2, cancelar, moverAlFrente, moverAlFinal, invertir)
// ====================================================================

class ColaEnvios
{
private:
    struct Nodo
    {
        TextMessage dato;
        std::shared_ptr<Nodo> siguiente;

        explicit Nodo(const TextMessage& mensaje);
    };

    std::shared_ptr<Nodo> frente_;
    std::shared_ptr<Nodo> final_;
    std::size_t cantidad;

public:
    ColaEnvios();
    ColaEnvios(const ColaEnvios& otra);
    ColaEnvios& operator=(const ColaEnvios& otra);
    ColaEnvios(ColaEnvios&& otra) noexcept;
    ColaEnvios& operator=(ColaEnvios&& otra) noexcept;
    ~ColaEnvios() = default;

    bool vacia() const;
    std::size_t tamanio() const;

    bool encolar(const TextMessage& mensaje);
    bool desencolar();

    const TextMessage* frente() const;
    TextMessage* frente();

    void limpiar();

    std::vector<TextMessage> aVector() const;

    const TextMessage* buscarPorId(int id) const;
    TextMessage* buscarPorId(int id);

    bool cancelar(int id);
    bool moverAlFrente(int id);
    bool moverAlFinal(int id);
    void invertir();

    bool guardarCSV(const std::string& ruta) const;
    bool cargarCSV(const std::string& ruta);
};
