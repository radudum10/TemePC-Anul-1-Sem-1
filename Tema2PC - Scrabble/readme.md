Task 0
se parcurge matricea, fiecare element ia valoarea '.'

Task 1

functia word_inputter:
actioneaza in functie de directie
daca este 0, pune cuvantul pe orizontala de la coordonatele date
daca este 1, il pune pe verticala

se citeste input-ul cu ajutorul unui buffer
bufferul nu era necesar pt. citirea lui n
a ajutat insa la citirea coordonatelor + cuvantului
se foloseste strtok astfel: 
se ia fiecare token al lui strtok, folosindu-ne de delimitatorul spatiu
se apeleaza word_inputter, cu ajutorul lui atoi pentru a converti string-urile

Task 2

functia score_check:
are un vector care retine scorul pentru fiecare litera
se parcurge cuvantul
se obtine pozitia alfabetica prin ASCII(LITERA) - ASCII(A)
se aduna punctajul pentru fiecare litera

se citeste input-ul
analog task1, se foloseste strtok
se calculeaza scorul din runda corespunzatoare cu functia score_check
daca nr. rundei este impar, se adauga la scorul lui player1
altfel se adauga la scorul lui player2

Task 3

functia simple_bonus:
parcurge matricea de la anumite coordonate
returneaza 2 la puterea nr. de aparitii ale lui 1

functia double_bonus:
parcurge matricea de la anumite coordonate
returneaza 3 la puterea nr. de aparitii ale lui 2

se citeste inputul, se foloseste strtok
se procedeaza analog task2, insa se verifica si bonusurile
daca substringul contine primul bonus dat(XX), verifica cu simple_bonus
daca are ca ultimele 2 litere, al doilea bonus dat(YY), cu double_bonus
se printeaza scorurile

Task 4

functia word_remover:
cauta un cuvant in vector(se parcurge acesta, si se fol. strcmp)
daca il gaseste, atunci se muta cuvintele incepand cu pozitia + 1 a cuv. gasit
si se scade lungimea cu o unitate

functia vert_check:
se parcurge matricea de la anumite coordonate
se verifica daca un anumit cuvant se poate pune pe tabla, astfel:
incepand cu coordonatele date, tabla trebuie sa aiba '.', de atatea ori
cate litere are cuvantul
daca se gaseste parcurgand astfel tabla, o litera sau se iese din tabla
se returneaza fals
altfel, daca s-a parcurs cu succes
se returneaza adevarat

functia horiz_check:
analog, functiei precedente, dar se parcurge pe orizontala

functia word_picker:
se ia fiecare cuvant din vectorul din cuvinte(sau ce a mai ramas din el)
se ia un vector care ajuta la memorarea pozitiilor
se verifica daca prima litera a cuvantului este pe tabla parcurgand matricea
daca se gaseste litera pe tabla, se memoreaza pozitia acesteia
se parcurge vectorul
se verifica daca, pornind de la litera respectiva, cuvantul se poate pune
fie pe verticala (vert_check), fie pe orizontala (horiz_check)
cand se gaseste primul cuvant care convine, se printeaza tabla, 
respectiv, se iese din functie
altfel se trece la cuvantul urmator

se ia input-ul
se pune pe tabla
daca exista cuvinte din vectorul dat, se elimina
se alege cuvantul, se printeaza tabla

Task 5

functia perfect_move:
functioneaza asemanator functiei word_picker, pe acelasi principiu
insa se calculeaza si scorul pe care il produce cuvantul(ca la task 3)
se foloseste un algoritm banal de maxim, care retine atat scorul maxim
cat si cuvantul si coordonatele acestuia
+ daca cuvantul se pune pe verticala, se pune directia implicita 1
+ daca cuvantul se pune pe orizontala, se pune directia implicita 0
se verifica si cazul in care un scor maxim este produs de 2 cuvinte
si se ia cel cu linia mai mica, sau daca si acestea sunt egale
pe cel cu coloana mai mica
se verifica daca maximul posibil este mai mare sau egal decat diferenta de scor
se printeaza tabla, daca se acopera diferenta, sau daca nu "Fail"

se ia input-ul
se pun cuvintele pe tabla si se calculeaza scorurile
se face diferenta de scor
se apeleaza perfect_move

Bonus

functia player2_move
functioneaza exact ca perfect_move, dar are in plus 
word_remover, care elimina cuvintele folosite din vector
aduna la scorul lui player2, maximul posibil pe runda

se ia input-ul
pentru turele pare, se face scorul lui player1
pentru cele impare, se apeleaza player2_move
pentru a gasi miscarea optima a lui player2
se printeaza tabla si se verifica castigatorul





