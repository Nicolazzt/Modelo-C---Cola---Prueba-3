# Practica Evaluada 03 - Modelo C (Cola de envios con cancelacion y prioridad)

Programacion 2 (PR2) - Seccion 02. C++17, sin librerias externas.

## Compilacion

```bash
make test    # verifica requisitos minimos
make main    # compila y ejecuta la demo
make clean
```

## Reparto de roles

| Integrante | C.I. | Rol |
| :--- | :--- | :--- |
| Santiago Zerpa | V-32451779 | ChatCola: encolarMensaje, procesarSiguiente, procesarTodos |
| Santiago Ruiz | V-32709123 | ChatCola: cancelarEnvio, subirPrioridad, bajarPrioridad |
| Nicolas Lopez | V-30024260 | ColaEnvios: encolar, desencolar, vaciar, tamanio, guardarCSV, cargarCSV, limpiar y frente |
| (completar) | | ColaEnvios |
| (completar) | | ColaEnvios |
| (completar) | | ColaEnvios |

## Uso de IA

- **Santiago Ruiz:** **Claude (Anthropic)** ayudó a Santiago Ruiz a escribir `cancelarEnvio`, `subirPrioridad` y `bajarPrioridad` en `ChatCola.cpp`, a completar sus datos en el encabezado y a redactar esta seccion del README. El codigo fue revisado y comprendido por el autor.
- **Nicolas Lopez:** **Claude y Gemini** Ayudaron a verificar uso y funcionamiento de std::shared_ptr y para aprender el uso de la sintaxis para archivos CSV (aprender a usar los metodos de la librería fstream) en `ColaEnvios.cpp`
