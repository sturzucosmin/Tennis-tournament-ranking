# sda
C program which keeps track of the rankings of a tennis tournament using data structures

    %%%%%%%%%%README TEMA 1 SDA 2020 - ATP CUP%%%%%%%%%%

        Facultatea de Automatica si Calculatore UPB, specializarea Ingineria sistemelor
        Student: Sturzu Cosmin
        Grupa: 312AB
        AN: I

        Scopul programului: automatizarea desfasurarii unui turneu de tenis intre mai multe tari pentru realizarea de clasamente.

        Pentru fisierele de intrare, respectiv cel de iesire am folosit argumente in linia de comanda pentru functia main.

        Exista 3 fisiere: cerinte.in, date.in si out.out asociate lui argv[1],argv[2],argv[3] pe care le-am atribuit variabilelor de tip "char*" :cerinte, date si rezultate, urmad sa le folosesc in functia "fopen" pentru a deschide fisierele

        Programul este impartit in 5 cerinte care vor fi rezolvate in functie de ceea ce contine fisierul "cerinte.in" din care am citit datele in 5 variabile "int": c1,c2,c3,c4,c5.
        Aceste cerinte sunt puse in if-uri sub forma if(c1 == 1){rez cerinta}. Am ales ca if-urile pentru cerintele 4 si 5 sa le fac in interiolul if-ului pentru cerinta 3 deoarece acestea depind de acea cerinta.

    ///////Cerinta 1////////

        Ceinta 1 presupune crearea unei liste dublu inlantuita su santinela pentru stocarea tarilor participante impreuna cu jucatorii acestora.

        -Pentru a aloca dinamic datele si pentru a le citi (numele tarilor si a jucatorilor) am folosit initial 3 string-uri alocate static (lenth1[20], lenth2[20],lenth3[20]).Citirea se face in 2 bucle "for", prima pentru a repeta procesul de atata numar de ori cate tari sunt in fisier, iar cea de-a doua bucla, aflata in interiorul primei bucle este foslosita pentru citirea datelor despre jucator si se repeta de un numar de ori egal cu numarul de jucatori din fiecare tar, citit mai inainte.

        -pentru alocarea dinamica a spatiului necesar m-am folosit de functia "strlen()" din biblioteca string.h ex: aux->name = malloc((sizeof(char)*strlen(lenth1))+1);

        -datele sunt citite intr-o variabile "aux" de tip Country*, dupa care adaugate in lista prin intermediul functiei "addAtEnd(&head ,aux)" care adauga un nod la sfarsitul listei


    ////////Cerinta 2/////////

        Aceasta cerinta face o eliminare a tarilor in funcie de un scor initial (nefolosit mai departe, acesta este media aritmetica a scorurilor jucatorilor)
        -Ideea este de a ramane in lista un numar de tari egal cu cea mai apropiata putere de 2 

        -am folosit 2 vectori alocati dinamic pentru pastrarea si calcularea scorurilor sum_score si sum_vector

        --->eliminarea se va face in functie de pozitia valorii minime din vectorul de scoruri si implicit din lista de tari
        --->pentru aflarea indicelui minimului folosesc functia "indice_minim()" care ceea ce face e sa gaseasca o valoare minima intr-un vector si sa ii returneze poitia.
        --->dupa aflarea indicelui  elimin tara de pe pozitia "indice" cu functia "eliminateCountry(&head, indice)" 
        --->pasul urmator este sa elimin minimul din vector si sa realoc spatiul si sa decrementez numarul de tari 
        --->pentru REPETAREA procesului pentru a ajunge la numarul de tari dorit tot ce am zis mai sus am pus intr-o bucla while(1) pe care pentru a o intrerupe am folosit o variabila k care este egala cu rezultatul functiei is_power_of_two(nr_country), aceasta verificand la fiecare repetare daca numarul de tari devine, prin decrementare lui cu 1 unitate la fiecare eliminare, o putere de 2.

    /////////Cerinta 3////////////

        --->dupa ce in lista raman n^2 tari astea sunt adaugate intr-o stiva(am adaugat in stiva elemente de tip countryNode, noduri foloite si la lista)
        --->creez o coada pentru meciuri in care am ales sa am ca "Data" pe fiecare nod un vector de 2 jucatori

        --->scot din stiva cate 2 tari si formez jocurile intre jucatori (le combin cu 2 for-uri), dupa care adaug combinatile in coada 

        --->urmeaza afisarea meciurilor(le scot din coada) si calcularea scorurilor ***procesul se repeta pana cand se goleste stiva 

        --->dupa calcularea scorurilor se vor adauga intr-o stiva winner tarile castigatoare dupa care sunt afisate si introduse din nou in stiva initiala ***procesul se repeta folosind o bucla while(winner != 0), unde winner este egal cu nr de tari si se imparte la 2 la fiecare
        *****in principiu sunt 3 bucle una in cealalta fiecare cu conditie de oprire specifica

        ***pentru manipularea stivelor si a cozii am folosit functii dedicate: push, pop, enQueue, deQueue etc.


    /////////////Cerinta 4///////////////

        --->trebuie afisat clasamentul jucatorilor ultimelor 4 tari ramase in competitie

        --->pentru crearea BST-ului cu jucatorii ultimelor tari am creat o stiva "stack_BST" in care am adaugat ultimele 4 tari actualizate in timpul rularii cerintei 3
        --->pentru adaugarea in arbore am folosit functia "insert(bst_players, jucator)
        --->in interiorul acestei functii se afla si conditia daca 2 jucatori au scor egal sa le fie comparate numele (am folosit functia compare_players(player1, player2) )
        --->Pentru afisarea lor in ordinea descrescatoare a scorurilor m-am folosit de functia recursva inorder(care afiseaza crescator) pe care am modificat-o sa imi parcurga fix in ordine inversa, inversand left si right



    ////////////Cerinta 5/////////////

        --->Afisarea numarului de jucatori cuprins intre alti 2 jucatori(ca scor)

        --->am citit datele despre cei 2 jucatori din fisierul cerinte.in folosind principiul de la cerinta 1 cu alocarea dinamica folosindu-ma de functia strlen

        --->Pentru numararea jucatorilor am folosit functia "count_players_between()" care imi cauta jucatori cuprinsi intre scorurile a 2 jucatori iar in momentul in care gaseste o valoare cuprinsa intre imi incrementeaza o variabila declarata static cu 1, pe care o si returneaza
        *aceasta functie este preluata de pe www.geeksforgeeks.com si modificata pentru nevoile cerintei, initial afisa valorile cuprinse intre 2 "chei" 



