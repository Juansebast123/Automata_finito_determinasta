Juan Sebastian Gonzalez Alvarez

# ¿Qué hace el programa?

Este programa implementa un simulador de AFD (Automata Finito Determinista).
Lee un archivo de configuración donde se definen los estados.

Luego lee otro archivo con cadenas de prueba.
Procesa cada cadena con el autómata y dice si es acepta o NO acepta.

# Diseño del autómata (AFD)

Estados: q0, q1, q2
Alfabeto: 0, 1
Estado inicial: q0
Estados de aceptacion: q2

# Transiciones

* Desde q0:
  - con 0 → q1
  - con 1 → q0
* Desde q1:
  - con 0 → q1
  - con 1 → q2 (acabamos de ver 01)
* Desde q2:
  - con 0 → q1
  - con 1 → q0

# ¿Como funciona el codigo?
- Empieza en el estado inicial.
- Lee cada símbolo de la cadena:
- Si existe una transición (estado, simbolo) → cambia de estado.
- Si no existe → rechaza.
- Al final: acepta si termino en un estado final.
