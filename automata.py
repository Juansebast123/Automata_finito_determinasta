import sys

# Lee el archivo de configuracion y construye el AFD
def leer_conf(archivo):
    with open(archivo, "r") as f:
        lineas = [l.strip() for l in f if l.strip()]

        
    estados = [e.strip() for e in lineas[0].split(":")[1].split(",")]
    alfabeto = [a.strip() for a in lineas[1].split(":")[1].split(",")]
    inicial = lineas[2].split(":")[1].strip()
    finales = [f.strip() for f in lineas[3].split(":")[1].split(",")]
    
    # A partir de la línea 5 vienen las transiciones
    transiciones = {}
    for linea in lineas[5:]:
        izquierda, derecha = linea.split("=")
        estado, simbolo = [x.strip() for x in izquierda.split(",")]
        transiciones[(estado, simbolo)] = derecha.strip()
    
    # retorna toda la configuración
    return estados, alfabeto, inicial, finales, transiciones

# Simula el AFD sobre una cadena de entrada
def procesar_cadena(cadena, inicial, finales, transiciones):
    estado = inicial
    for simbolo in cadena:
        if (estado, simbolo) in transiciones:
            estado = transiciones[(estado, simbolo)]
        else:
            return False
    return estado in finales

def main():
    
    conf_file = sys.argv[1]
    cadenas_file = sys.argv[2]

    # Leer configuración del AFD    
    estados, alfabeto, inicial, finales, transiciones = leer_conf(conf_file)
    
    with open(cadenas_file, "r") as f:
        cadenas = [l.strip() for l in f if l.strip()]

    # Procesar cada cadena y mostrar resultado    
    for c in cadenas:
        if procesar_cadena(c, inicial, finales, transiciones):
            print(f"{c} -> acepta")
        else:
            print(f"{c} -> NO acepta")

if __name__ == "__main__":
    main()
