--- GATES.C ---

### TASK 1 ###

1. get_bit
-> se face shiftare, bitul dorit din numar se muta pe ultima pozitie
-> operatia SI pe biti cu 1 verifica daca acesta este 0 sau 1.

2. flip_bit
-> se muta singurul bit de 1 al lui 1 pe pozitia dorita
-> se efectueaza XOR intre numar si 1 shiftat
-> daca numarul are pe bitul dorit 1, facand XOR intre 1 si 1, bitul se va face 0, iar daca are 0, se va face 1
-> operatia nu va afecta ceilalti biti pentru ca facand XOR cu 0 nu se schimba bitii.

3. activate_bit
-> utilizand get_bit (^^) se afla valoarea bitului dorit
-> daca bitul dorit este 0, cu flip_bit(^) se schimba valoarea lui

4. clear_bit
-> se procedeaza identic ca la activate_bit(^), insa conditia de verificare este bit = 1

### TASK 2 ###

1. and_gate
-> NAND = AND negat ; se foloseste !

2. not_gate
-> introducand intr-un AND valoarea lui a, se va returna tot valoarea lui a, negand(NAND) se obtine a negat.

3. or_gate
-> conform formulei lui De Morgan : !(A+B) = !A * !B ; se neaga => A+B = !(!A *!B) <=> A sau B = nand (!A si !B)

4. xor_gate
-> se verifica daca elementele sunt distincte si daca unul este egal cu 1 prin nand-uri.

### TASK 3 ###

1. full adder 
-> conceptul full adderului : aduna 2 biti, returneaza suma si transportul (transportul se obtine in cazul in care se aduna 2 biti egali cu 1)
-> suma este egala cu XOR intre A, B, Co (care se poate scrie ca XOR(XOR(A,B), Co)) (Co = C output = transport)
-> transportul se obtine facand sau intre A si B, A si C si C si B, adica verifica daca gasim 2 biti egali cu 1.
-> s-a codat in urmatorul mod : - s-a shiftat suma cu o pozitie la stanga si s-a facut sau pe biti
-> rezultatul va avea, eventual, ultimii 2 biti modificati, penultimul reprezentand suma, ultimul transportul.

2. half adder
-> half adderul este adunarea pe biti.
-> se scoate cate un bit de la fiecare numar (de pe aceeasi pozitie), folosind get_bit
-> se utilizeaza full adder-ul pentru a aduna bitii scosi.
-> conform codarii full adder-ului (^), pentru a obtine suma, se shifteaza la dreapta cu o pozitie, se face SI pe biti cu 1 si apoi se shifteaza rezultatul cu i
-> shiftarea cu i este necesara pentru a muta bitul pe pozitia curenta
-> se face SI pe biti cu 1 (ultimul bit al adder-ului reprezinta transportul), se obtine transportul
-> se repeta pentru toti bitii numerelor a si b (definiti pe 8 bytes)
-> daca ultimul transport este 1, avem exceptie pentru overflow

--- COMMUNICATION.C ---

### TASK 1 ###

1. send_byte_message 
-> codarea caracterului = pozitia lui din alfabet => cod caracter = COD ASCII - 64

2. recv_byte_message
-> se procedeaza invers, caracter = pozitia lui din alfabet + 64

3. comm_byte
-> se primeste caracterul si se printeaza de 2 ori ¯\_(ツ)_/¯

### TASK 2 ###

1. send_message
-> se initializeaza un sir de caracter cu mesajul cerut : HELLOTHERE
-> lungimea este de forma 0000 BIT1BIT2BIT3BIT4
-> se shifteaza la stanga cu 4 biti, pentru a avea ultimii 4 biti 0.
-> apoi se shifteaza cu 2 biti la dreapta pentru a se aduce la codarea dorita. (de forma BITXBITX BIT1BIT2BIT3BIT4 BITXBITX)
-> se codeaza fiecare caracter ca la send_byte_message

2. recv_message
-> se decodeaza lungimea aplicand inversand codarea. (se shifteaza mai intai la stanga cu 2 biti, apoi la dreapta cu 4)
-> se decodeaza fiecare caracter ca la recv_byte_message

3. comm_message
-> se decodeaza lungimea (^)
-> se memoreaza ultimul caracter
-> daca ultimul caracter este "P" (care are poz. alfabetica 16), mesajul este "PICKLERICK"
-> altfel mesajul este "VINDICATORS"
-> se codeaza lungimea mesajului
-> se trimite codat

### TASK 3 ###

1. send_squanch2
-> se ia cate un bit de la c1, respectiv de la c2.
-> se asaza bitul lui c1 pe prima pozitie impara (1)
-> se asaza bitul lui c2 pe prima pozitie para (0)
-> se adauga bitii la rezultat
-> se repeta pana cand se acopera cei 8 biti (folosind un contor care numara din 2 in 2)

2. decode_squanch2 
-> se extrag cate 2 biti, unul de pe o pozitie para si unul de o pozitie impara
-> biti de pe pozitiile pare se asaza pe pozitile 5-8
-> bitii de pe pozitiile impare se asaza pe pozitiile 0-4

--- HUNT.C. ---

### TASK 1 ###

1. find_spell
-> se va parcurge numarul comparand bitul curent cu cel anterior
-> bitul anterior se initializeaza cu primul bit al numarului
-> daca bitul curent si cel anterior sunt egale cu 1, contorul se mareste
-> daca nu, se reseteaza.
-> spellul incepe dupa 5 biti consecutivi de 1, astfel cand contorul este 5, se retine pozitia urmatoare ultimului bit de 1
-> se iau 16 biti incepand cu pozitia retinuta.

2. find_key
-> se procedeaza asemanator(^), gasind de aceasta data 3 biti de 1. 
-> se retine pozitia celui de al 3 lea bit de 1.
-> pozitia de la care incepe key-ul este calculata altfel : pozitia ultimului bit de 1 - 18 (numarul are 16 biti + inca 2 biti de 1).
-> se iau 16 biti incepand cu pozitia retinuta.

3. spell_key
-> se face XOR intre spell si key (¯\_(ツ)_/¯)

### TASK 2 ###

1. choose_sword
-> se numara bitii activi ai lui enemy
-> daca are un numar par de biti activi, tipul inamicului este "MONSTER", care are type-ul 9 (1001(2))
-> de asemenea, din ecuatia pt. aflarea valorii => value = enemy & (1-enemy) (xor intre value si acea expresie este 0 daca expresiile sunt egale)
-> daca are un numar impar de biti activi, tipul inamicului este "HUMAN", care are type-ul 6 (0110(2))
-> valoarea se afla din value + enemy = 0 => value = -enemy
-> se trece type-ul pe ultimii 4 biti, iar valoarea pe primii 16

### TASK 3 ###

1. trial_of_the_grasses
-> din a 2 a ecuatie => antibodies_high diferit de antibodies_low

Presupunerea 1.0 : 
-> bit cocktail = 1 => din ec.3, bit antibodies_high = 1 sau bit antibodies_low = 1
-> pt. bit antibodies_high = 1 => bit antibodies_low = 0
-> aplicand in prima ecuatie => (1 & 1) ^ (0 | 1) = 0, Adevarat

Presupunerea 1.1 :
-> bit antibodies_high = 0 => bit antibodies_low = 0
-> aplicand in prima ecuatie => (0 & 1) ^ ( 1 | 1) = 0, Fals

Presupunea 2 :
-> bit cocktail = 0 => bit antibodies_high = 0  => antibodies_high = antibodies_low = 0
-> convine ec. 2 si 1

Concluzie : 
-> daca bitul lui cocktail = 1 => bitul lui antibodies_high este 1, iar cel al lui antibodies_low este 0
-> daca bitul lui cocktail = 0 => atat bitul lui antibodies_high este 0, cat si al lui antibodies_low 
-> adica antibodies_low este 0, oricare ar fi cocktail, iar antibodies_high este chiar cocktail
-> rezultatul este cocktail shiftat la stanga cu 16 biti (cocktail este pe 16 biti, iar rezultatul pe 32, asa ca este nevoie sa mutam bitii lui cocktail)

2. trial_of_the_forest
-> se verifica cele 2 cazuri speciale, cand map-ul are biti doar de 1 (map = -1) sau cand are bitii doar de 0 (map = 0)
-> se numara bitii de 1 ai lui map
-> daca sunt 2 biti de 1, padurea are tipul Hindar
-> se verifica daca se pot grupa bitii cate 4, daca nu => nu poate fi Brokilon, adica ramane doar Caed Dhu
-> daca se pot grupa bitii cate 4, se verifica daca acestia sunt asezati caracteristic pt. Brokilon (grupari DOAR de cate 4 copaci)
-> daca nu sunt => Caed Dhu

3. trial_of_the_dreams
-> se gasesc pozitiile celor 2 biti de 1
-> se face diferenta pozitilor


