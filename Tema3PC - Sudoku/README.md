// TASK 1 //
- am ales biblioteca cJSON, ptc. este lightweight, pe github sunt prezentate
metodele de parsare, am reusit sa ii folosesc functiile pt. a citi intr-un timp
optim informatiile din json.

in bmphandlers.c :
getfromjson_file_header:
- functia primeste ca parametru un string, in care s-a retinut continutul
fisierului .json
- se parseaza cu cJSON_Parse string-ul
- se ia primul obiect al json-ului, adica file_header
- se extrage pe rand fiecare element si se pune in struct
- se elibereaza

getfromjson_info_header:
- primeste la fel un string, care contine continutul fisierului .json
- se parseaza string-ul
- se pun informatiile in struct
- se elibereaza

get_padding_size:
- primeste nr. de coloane al matricei de culori si nr. de biti per pixel
- daca dimensiunea unei linii in bytes nu este dizivibila cu 4,
atunci ea are nevoie de padding
- dimensiunea unei linii este egala cu nr. de coloane * nr. de bytes al unei
culori
- nr. de bytes se scoate din nr. de biti per pixel / 8
- obtin padding-ul necesar astfel:
4 - restul impartirii dim. unei linii la 4, astfel ma asigur ca fiecare linie
are o dimensiune divizibila cu 4.
- returnez padding-ul necesar

generate_img_task1:
- primeste ca argument un string, care, la fel are continutul fiiserului .json
si un pointer de tip void, care contine informatiile despre info_header si 
caruia ii fac cast la tipul bmp_infoheader.
- extrag campul bitmap din fisierul json intr-un vector, cu ajutorul
cJSON_ArrayForEach
- in fisierul utils.h este declarat un struct, color care contine 3 campuri:
blue, green, red, fiecare de tipul unsigned char pt. a reprezenta fiecare
culoare pe 1 octet.
- am extras astfel, ci nu direct in struct-ul de culori pt. a folosi cu
usurinta comanda ArrayForEach, care pt. fiecare valoare muta pointer-ul
la dreapta si nu se parcurge intreg vectorul pt. a extrage fiecare element
- pun informatiile extrase intr-un vector de struct-uri
- eliberez

print_bmp: 
- primeste matricea de culori, path-ul catre input-ul fisierului, 
2 void pointeri, care au informatiile despre infoheader si fileheader,
si 2 variabile de tip int care indica nr. taskului / bonusul
- se face cast
- se creeaza numele fisierului astfel:
- se ia string-ul dupa ultimul /
- daca nu suntem la task-ul bonus: 
- se pune cu sprintf numele : output_task<numar>_<board>.bmp,
unde nr. este taskid, iar <board> ce este inainte de "." dupa ultimul /
- daca suntem la task-ul bonus:
- analog, dar format-ul este de tip :output_bonus_<board>.bmp
- aloc vectorul de pixeli
- pun in el culorile, daca am padding adaug 0-uri.
- pun in fisierul de iesire informatiile date de cei 2 pointeri +
vectorul de pixeli

in main.c: 
- identific nr. task-ului (ce este dupa k in numele de input)
- iau toata informatia din json intr-un buffer
- apelez functiile prezentate mai sus

// TASK 2 //
in bmp_handlers.c:
- mirror_bmp : primeste ca argumente matricea de culori obtinuta anterior
- utilizand schema imaginei de pe ocw, am observat ca fiecare numar este
intr-un patrat 7x7, avand un chenar de dimensiune 1 pixel alb
- asa ca interschimb pt. fiecare patrat coloana numarului astfel:
prima din stanga -> ultima din dreapta
a doua din stanga -> penultima din dreapta
- returnez matricea de culori
in main.c : apelez functia, apelez print_bmp

// TASK 3 //
in bmp_handlers.c:
get_string:
- primeste ca argumente o matrice de culori, coordonatele primei pozitii ale
patratului
- daca avem un pixel alb : il memoram in sir ca fiind "."
- daca este rosu : il memoram in sir ca fiind "X"

learn_numbers: 
- m-am folosit de imaginea obtinuta la task-ul 2 pt. primul input
- iau fiecare patrat 7x7 de pe prima linie
- iau un vector de string-uri
- memorez reprezentarea fiecarui numar intr-un string(cu get_string)
* vector[1] - contine reprezentarea nr. 1
vector[2] - reprezentarea nr. 2 s.a.m.d *
- pe pozitia 0 am ales sa memorez cum arata un patrat care nu are un numar
- pe pozitia 10 am ales sa memorez cum arata patratul folosit la bonus pt.
input nerezolvabil.

sudoku_matrix:
- este o functie care construieste o matrice pe baza unei matrice de culori
- compar fiecare patrat cu sirurile retinute anterior
- cand se gaseste, se pune in matrice elementul corespunzator
- se returneaza matriea

sudoku_integrity:
- de tip bool, returneaza adevarat daca sudokul a fost completat corect,
fals in caz contrar
- iau un vector de frecventa pt. a retine nr. de aparitii al fiecarui numar
pe linii, respectiv pe coloane.
- se ia fiecare element al matricei
- se incrementeaza frecventa
(ex. avem in matrice nr.1, freq[1] se va mari cu 1)
- se verifica daca fiecare element a aparut doar o data.
- in caz contrar se elibereaza si se intoarce fals.

create_json:
- se procedeaza cu numele fisierului ca la print_bmp
- creez fisierul json, cu functia AddItemToObject, inserez pt. fiecare camp
- daca sudoku_integrity a returnat adevarat, atunci se pune Win!, astfel se
pune Loss!:(

in main.c:
se apeleaza functiile
se elibereaza.

// TASK 4 + BONUS //
in solver.c: 
- se extrag informatiile despre imagini din fisierele binare cu functiile
get_bmp_infoheader, get_bmp_fileheader, get_color_arr
- acestea primesc ca argument un pointer la fisier si din acesta extrag
valorile pt campurile structurilor.
- la get_color_arr se tine cont de padding, cand s-a ajuns la finalul liniei
a matricei de culori si avem padding, se incrementeaza contorul pana cand se
trece peste padding.
- se creeaza matricea de numere folosind procedeul de la task3.
- folosesc un algoritm de backtracking, care functioneaza astfel(asemanator
pseudocodului dat)

out_of_bounds 
verifica daca s-a parcurs ultimul element al matricei
,iar in caz favorabil, returneaza true, altfel verifica daca s-a parcurs
ultimul element al liniei si se trece pe urmatoarea si returneaza false
(primeste pointeri pt. a modifica la adresa valorile)

find_free_square
- cauta in matrice valori de 0(adica reprezentarea patratelor goale)

is_valid
- verifica daca plasarea elementului nu strica tabla(adica respecta cele 3
reguli ale sudokului)

solve_sudoku
- apeleaza out_of_bounds(pt. a incheia backtracking-ul daca este cazul)
- daca elementul la care ne aflam nu este 0, se trece peste
- daca nu se gasesc elemente de 0, se incheie backtracking-ul
- se incearca fiecare numar, se verifica cu is_valid daca nu strica
tabla si se verifica pt. urm element
- daca nu s-a gasit numar, se lasa 0

insert_val:
pune intr-un patrat 7x7 din matricea de culori un numar dat, dupa modelul
celor memorate. Astfel daca intalnim ".", va pune 255 pt. cele 3 campuri ale
structurii, daca intalnim "X", se pune valorile pt culoarea magenta.
(b:255, g:0, r:255)

generate_solution:
daca gasesc patratel gol, atunci pune nr. din matrice in matricea de culori
cu insert_val

insert_failure:
pune intr-un patrat 7x7 acel X care reprezinta esecul de a completa sudokul

generate_failure:
pt. fiecare patrat 7x7 se pune X

in main:
- apelez functiile de prelucrare a informatiilor din fisier din solver.c
- memorez numerele si fac matricea de numere ca la task-ul 3
- daca se poate rezolva sudokul se apeleaza generate_solution
- altfel se returneaza generate_failure
- daca nr. task-ului este 4, se creeaza fisier cu nume coresp. pt task 4
- altfel se creeaza fisier coresp. pt bonus
- se elibereaza
