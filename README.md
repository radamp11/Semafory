# Semafory
Realizacja algorytmu wzajemnego wykluczania za pomocą semaforów. Korzystałem z klasy monitor.h umieszczoniej na stornie prowadzącego przedmiot.
Treść zadania:
Zrealizować algorytm wzajemnego wykluczania dla dwóch producentów i dwóch konsumentów. Bufor jako kolejka FIFO, max. 9 elementów.
Jeden z producentów nie może produkować, gdy suma elementów w buforze przekracza 20.
Konsumenci mogą konsumować, gdy w buforze jest więcej niż 3 elementy.