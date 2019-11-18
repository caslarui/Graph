# Graph

Aceasta aplicatie reprezinta un model de implementare a unui Graf neorientat prin intermediul unei liste de adiacenta. 

# Implementare
Am ales reprezentarea grafului printr-o liste de adiacenta din motiv ca initial nu se cunoaste dimensiunea grafului, iar pentru o 
administrare cat mai eficienta a memoriei, implementarea cu ajutorul unei matrici este contraindicata.

Am 3 clase de baza : Graph, VertexList si EdgeList. Clasele EdgeList si VertexList nu sunt altceva decat niste liste simplu inlantuite alocate dinamic. Prima are drept "Nod" clasa Edge, aceasta salveaza destinatia, adica Vertexul spre care indica legatura, si pointerul catre urmatorul Edge. In mod similar si clasa VertexList are drept "Nod" clasa Vertex, care are structura similara, insa fiecare instanta de Vertex are in sine si o instanta de EdgeList. Acest EdgeList salveaza informatia referitoare la legaturile care le are Vertexul curent din lista cu alte Vertexuri.
Graful este alcatuit dintr-o instanta a clasei VertexList, declarata Private, datele din graf fiind posibil de modificat doar prin intermediul metodelor publice puse la dispozitie si care pot fi analizate in fisierul Header. 

# Input Format
n  
tip_operatie_1 [nr1] [nr2]  
tip_operatie_2 [nr1] [nr2]  
tip_operatie_3 [nr1] [nr2]  
...  
tip_operatie_n [nr1] [nr2]  

unde:  
- n - numarul de operatii ce se vor efectua asupra grafului;  
- tip_operatie - 1, 2, 3, 4, sau 5 ce reprezinta adaugare nod, adaugare muchie,  
stergere nod, stergere muchie si respectiv este sau nu arbore;  
- nr1, nr2 - numere ce reprezinta numarul nodului, iar un functie de tipul operatiei  
nu va fi niciun numar, unul singur sau doua numere. Pt operatiile 2 si 4 cele doua noduri vor forma o muchie  

# Utilizare
```python
make            # Creaza executabilul graph
make leak       # Verifica daca nu exista leak errors
make origins    # Indica originea erorilor de memorie
make clean      # Sterge fisierele .o si executabilul
```

# Compilator
gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1)

# Licence
[MIT](https://choosealicense.com/licenses/mit/)