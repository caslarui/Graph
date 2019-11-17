# Graph

Aceasta aplicatie reprezinta un model de implementare a unui Graf neorientat prin intermediul unei liste de adiacenta. 

# Implementare
Am ales reprezentarea grafului printr-o liste de adiacenta din motiv ca initial nu se cunoaste dimensiunea grafului, iar pentru o 
administrare cat mai eficienta a memoriei, implementarea cu ajutorul unei matrici este contraindicata.

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
'''python
make            # Creaza executabilul graph
make leak       # Verifica daca nu exista leak errors
make origins    # Indica originea erorilor de memorie
make clean      # Sterge fisierele .o si executabilul
'''

# Compilator
gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1)

# Licence
MIT © [Caslaru Ion]()