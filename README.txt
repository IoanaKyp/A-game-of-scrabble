PROIECT: Tema 2 - A Game of Scrabble
AUTOR: Chiper Ioana-Cristina
GRUPA: 312 CD

CERINTA 0: 
    - Pentru initializarea matricei s-a folosit functia memset.
CERINTA 1:
    - Pentru citire s-a folosit functia fgets(), iar pentru identificarea elementelor din stringul citit s-a construit o functie 
    intitulata read_word(). Partile care reprezinta numere au fost convertite utilizand functia atoi().
    - Scrierea unui cuvant in matrice se realizeaza in functie de directia acestuia, fiind utilizate doua functii construite intitulate
    sugestiv scrieOrizontala() si respectiv scrieVerticala.
CERINTA 2:
    - Dupa realizarea citirilor, se observa ca (in ordinea citirii), cuvintele de pe pozitii pare (deoarece incepem sa numaram de la 0)
    vor fi cuvinte amplasate de primul jucator, iar cele de pe pozitii impare vor fi amplasate de cel de al doilea jucator, fapt 
    important pentru alocarea punctajelor.
    - Vectorul scors contine punctele pentru fiecare litera a alfabetului (dupa cum a fost sugerat in enunt).
    - S-a construit functia scor() pentru a calcula punctajul adus de un cuvant, prin insumarea valorii fiecarei litere pe care 
    o contine.
CERINTA 3:
    - Dupa fiecare citire de cuvant, se calculeaza valoarea bonusului ce ii corespunde, bonusul reprezentand valoarea cu care se 
    multiplica punctele obtinute de functia scor().
    - condition_bonus_1 si condition_bonus_2 sunt variabile semafor care indica daca se poate aplica bonusul pentru sirul XX 
    sau respectiv YY. Valoarea lor este determiinata cu ajutorul a doua functii care au fost construite, intitulate check_cond_1 si 
    check_cond_2. check_cond_1 se foloseste de strstr(), iar check_cond_2 verifica egalitatea dintre ultimele doua litere ale 
    cuvantului si sirul YY.
    - Functia calculate_bonus returneaza valoarea bonusului dupa verificarea pozitiilor corespunzatoare cuvantului de pe bonus_board.
    - Conform enuntului punctajul final al unui cuvant este egal cu scors()*bonus.
CERINTA 4:
    - Matricea used_words este folosita pentru a tine evidenta cuvintelor care se afla pe tabla.
    - Vectorul aparitii_litere retine numarul de aparitii ale fiecarei litere pe tabla si este folosit pentru optimizarea cautarilor. 
    El este indentat la fel cu vectorul scors.
    - In cautarea unui cuvant trebuie tint seama deurmatoarele conditii:
        -cuvantul trebuie sa incapa pe tabla(lungimea cuvantului este mai mica sau egalitatea cu numarul de spatii de pe tabla ramase 
        de la pozitia de inceput a cuvantului pana la margine)
        -nu se intersecteaza cu alte cuvinte (daca l reprezinta lungimea cuvantului atunci urmatoarele l spatii de pe tabla in directia
        amplasarii trebuie sa fie goale)
    - Variabila scris este folosita pentru a nu se mai verifica posibilitatea scrierii pe verticala daca un cuvant a fost deja scris 
    pe orizontala.
    - Variabila am_gasit este utilizata pentru optimizarea si oprirea din verificarea in momentul gasirii si amplasarii primului cuvant 
    care vwrifica conditiile.
CERINTA 5:
    - used_words si aparitii_litere sunt folosite cu acelasi rol.
    - punctajele se calculeaza la fel ca la cerinta 3.
    - cautarea cuvantului este similara cu cea de la cerinta 4, cu precizarea ca un cuvant este ales doar daca valoarea punctajului sau
    este cel putin egala cu diferenta dintre scorurile actuale ale celor doi jucatori.
    - daca nu se gaseste un astfel de cuvant se afiseaza mesajul "Fail!", altfel se actualizeaza tabla de joc si punctajul celui de-al 
    doilea jucator.
CERINTA 6:
    - Se observa in primul rand ca aceasta cerinta se aseamana cu cerinta 5, doar ca algoritmul executat la 5 trebuie executat dupa 
    fiecare mutare a jucatorului 1. Singura diferenta a acestui algoritm fata de cerinta precedenta este adus de faptul ca nu se mai 
    cauta un cuvant care sa aduca victoria sau remiza jucatorului 2, ci cuvantul care aduce numarul maxim de puncte.
    - In acest caz used_words si aparitii_litere sunt actualizate dupa fiecare mutare a fiecarui jucator.
    - Scorurile sunt construite la fel ca la cerinta 3, iar la final, dupa executarea tuturor mutarilor, acestea se compara pentru 
    determinarea castigatorului.

