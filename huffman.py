import time
import random
import itertools
import heapq


def CodeCanonico(L):
    sorted_lengths = sorted((length, index) for index, length in enumerate(L))

    current_code = 0
    last_length = sorted_lengths[0][0]

    codes = [None] * len(L)

    for length, index in sorted_lengths:
        if length > last_length:
            current_code <<= (length - last_length)
            last_length = length
        codes[index] = format(current_code, '0{}b'.format(length))
        current_code += 1

    return codes


def LongitudMedia(C, p):
    l = 0
    for i in range(len(p)):
        l += len(C[i]) * p[i]
    return l


def Huffman(p):
    longitudes_palabras = [0] * len(p)
    cola_prioridad = []
    for i in range(len(p)):
        heapq.heappush(cola_prioridad, (p[i], [i]))

    while len(cola_prioridad) > 1:
        primer_elemento = heapq.heappop(cola_prioridad)
        for indice in primer_elemento[1]:
            longitudes_palabras[indice] += 1

        segundo_elemento = heapq.heappop(cola_prioridad)
        for indice in segundo_elemento[1]:
            longitudes_palabras[indice] += 1

        heapq.heappush(cola_prioridad,
                       (primer_elemento[0] + segundo_elemento[0], primer_elemento[1] + segundo_elemento[1]))

    return CodeCanonico(longitudes_palabras)


def tablaFrecuencias(mensaje, numero_de_simbolos=1):
    frecuencias = {}

    for i in range(0, len(mensaje) - numero_de_simbolos + 1, numero_de_simbolos):
        tupla = mensaje[i:i + numero_de_simbolos]
        if tupla in frecuencias:
            frecuencias[tupla] += 1
        else:
            frecuencias[tupla] = 1

    return frecuencias


def EncodeHuffman(mensaje, numero_de_simbolos=1):
    freqs = tablaFrecuencias(mensaje, numero_de_simbolos)
    freqs_ordered = dict(sorted(freqs.items()))
    dist = {}
    for elem in freqs_ordered:
        dist[elem] = freqs_ordered[elem] / len(mensaje)

    codigo = Huffman(list(dist.values()))

    print('Longitud Media:', LongitudMedia(codigo, list(dist.values())))

    print(list(dist.keys()))
    print(codigo)

import os

# Define the path to the DNACorpus folder
folder_path = "C:/Users/abelb/Enginyeria/CDI/DNACorpus"

# Get the list of files in the folder
file_list = os.listdir(folder_path)

content_total = ""

#print("Reading files...")
print("open")
for root, dirs, files in os.walk(folder_path):
    for file in files:
        print(file)
        with open(os.path.join(root, file), "r") as _file:
            content_total += _file.read()

#print("Calculating Frequencies...")
if 'taula_frec' not in globals():
    taula_frec = tablaFrecuencias(content_total, 5)
    taula_frec.update({k: v for k, v in [('G', 1), ('A', 1), ('T', 1), ('C', 1)]})

print(taula_frec)

freqs_ordered = dict(sorted(taula_frec.items()))
dist = {}
for elem in freqs_ordered:
    dist[elem] = freqs_ordered[elem]

codigo = Huffman(list(dist.values()))

# Initialize an empty list to hold formatted strings
formatted_pairs = []

# Zip the lists and iterate over them
for item1, item2 in zip(list(dist.keys()), codigo):
    # Format each pair according to the given structure and add to the list
    code = ','.join(item2)
    formatted_pairs.append("{{"+ code +"},\"" + item1 +"\"}")

# Join all formatted pairs with commas and enclose in double curly braces
output_string = "{" + ", ".join(formatted_pairs) + "};"

# Print the final result
print(output_string)