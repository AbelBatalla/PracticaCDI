## Requisitos:
### Entorno de compilación:
 Un entorno de compilación para C++ con las librerias enumeradas en la sección siguiente. 
 El entorno de compilación recomendado para este projecto es gcc.
 Se recomienda el uso de un sistema operativo Linux aunque funcione en otros.

### Librerias necesarias:
 De STD: iostream, fstream, map, string y vector

## Instrucciones:
### Compilación:
 Teniendo los 3 archivos presentes en el zip compress.src.zip (main.cpp, huffman.h i huffman.cpp) 
 extraidos en la misma carpeta ejecutar en un terminal el siguiente comando:
 ```shell
 g++ -Os -s main.cpp huffman.cpp -o compress.cdi 
 ```
 Esto generará un binario ejecutable compress.cdi listo para ser usado.
### Uso:
#### Comprimir:
 En un terminal en la misma carpeta que nuestro binario ejecutar el siguiente comando:
 ```shell
  ./compress.cdi -c /Ruta/Al/Fichero 
  ```
 Modificando /Ruta/Al/Fichero con la ruta del fichero DNA que queremos comprimir.
 A continuación esperaremos a que el terminal nos indique que ha terminado.

#### Descomprimir
 En un terminal en la misma carpeta que nuestro binario ejecutar el siguiente comando:
 ```shell
  ./compress.cdi -d /Ruta/Al/Fichero.cda 
  ```
 Modificando /Ruta/Al/Fichero con la ruta del fichero en formato comprimido CDA que queremos descomprimir.
 A continuación esperaremos a que el terminal nos indique que ha terminado.

 ### Ejemplos:
 #### Compilar, comprimir, descomprimir y comparar
  En este ejemplo ejecutaremos todos los comandos necesarios para compilar, comprimir y descomprimir un fichero BuEb ubicado en una carpeta 
  DNA en la misma ubicación y por último comparar que el fichero comprimido es igual al original. (No se recomienda un fichero grande)
  Primero ejecutamos el siguiente comando en una terminal que apunte a la carpeta que contiene nuestros archivos fuente y la carpeta de DNA.
  ```shell 
  g++ -Os -s main.cpp huffman.cpp -o compress.cdi 
  ```
  En cuanto termine procederemos a comprimir con:
  ```shell 
  ./compress.cdi -c ./DNA/BuEb 
  ```
  Que nos retornará un Compressed para indicarnos el éxito de la operación. Proseguimos con la descompresión:
  ```shell 
  ./compress.cdi -d ./DNA/BuEb.cda 
  ```
  El mensaje será Decompressed i notemos que el archivo comprimido tiene la extensión .cda en el comando.
  Por último compararemos con un diff nuestro fichero original y el descomprimido.
  ```shell 
  diff -u ./DNA/BuEb ./DNA/BuEb.dcp 
  ```
  Si todo ha salido correcto este comando no deberia retornar nada ya que no hay diferencias.

## Agradecimientos:
 Este proyecto no habría sido posible sin las enseñanzas del prof. Martinez Saez, Fernando, nuestro profesor de CDI que nos ha ayudado a navegar
 por estos mares de bits cambiantes que se encojen y ensanchan al compás de nuestros algoritmos.