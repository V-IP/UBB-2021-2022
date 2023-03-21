import datetime
from stocare import *
from introducere_date import *
from datetime import date
from convertiri import creeaza_tranzactie
from validari import *
from undo import *

def srv_adaugare_tranzactie(l,zi,suma,tip,dictionar_undo):
    '''
    Functie care adauga o tranzactie tnz in lista l, daca aceasta este valida
    input: l - lista in care se pastreaza tranzactiile
           zi - ziua tranzactiei
           suma - valoarea tranzactiei
           tip - tipul tranzactiei 0=iesire(retragere numerar)/1=intrare(depunere numerar)
    output: - , daca tranzactia este valida
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
                        "Suma invalida!\n", daca suma<=0
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    tnz = creeaza_tranzactie(zi,suma,tip)
    valideaza_tranzactie(tnz)
    adauga_tranzactie_in_lista(l,tnz)
    dictionar_undo["tnz"] = tnz

def srv_actualizare_tranzactie(l,zi1,suma1,tip1,zi2,suma2,tip2,dictionar_undo):
    '''
    Functie care actualizeaza o tranzactie tnz in lista l, daca cea noua este valida
    input: l - lista in care se pastreaza tranzactiile
           zi - ziua noii tranzactii
           suma - valoarea noii tranzactii
           tip - tipul noii tranzactii 0=iesire(retragere numerar)/1=intrare(depunere numerar)
    output: - , daca tranzactia este valida si modificarea a avut succes
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
                        "Suma invalida!\n", daca suma<=0
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    i = -5
    tnz1 = creeaza_tranzactie(zi1,suma1,tip1)
    valideaza_tranzactie(tnz1)
    tnz2 = creeaza_tranzactie(zi2,suma2,tip2)
    valideaza_tranzactie(tnz2)
    i = cauta_tranzactie_in_lista(l,tnz1)
    try:
        l[i] = tnz2
    except:
        raise Exception()
    dictionar_undo["tnz1"] = tnz1
    dictionar_undo["tnz2"] = tnz2

def srv_sterge_tranzactii_zi(l,zi,dictionar_undo):
    '''
    Functie care sterge toate tranzactiile tnz din lista l de la ziua specificată
    input: l - lista in care se pastreaza tranzactiile
           zi - ziua introdusa
    output: - , daca ziua este reala si stergerea a avut succes
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
    '''
    undo = []
    data_introdusa = convertireZi(zi)
    for tnz in l:
        zi = obtine_zi(tnz)
        data_tranzactiei = convertireZi(zi)
        if data_tranzactiei == data_introdusa:
            l.remove(tnz)
            undo.append(tnz)
    dictionar_undo["undo"] = undo

def srv_sterge_tranzactii_perioada(l,zi1,zi2,dictionar_undo):
    '''
    Functie care sterge toate tranzactiile tnz din lista l dintr-o perioada data
    input: l - lista in care se pastreaza tranzactiile
           zi1 - ziua de inceput
           zi2 - ziua de sfarsit
    output: - , daca perioada este reala si stergerea a avut succes
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
    '''
    undo = []
    data_inceput = convertireZi(zi1)
    data_sfarsit = convertireZi(zi2)
    n = len(l)
    c = 0
    for i in range(n):
        tnz = l[c]
        zi = obtine_zi(tnz)
        data_tranzactiei = convertireZi(zi)
        if data_inceput < data_tranzactiei and data_tranzactiei < data_sfarsit:
            l.remove(tnz)
            undo.append(tnz)
        else:
            c = c+1
    dictionar_undo["undo"] = undo

def srv_sterge_tranzactii_tip(l,tip,dictionar_undo):
    '''
    Functie care sterge toate tranzactiile tnz din lista l de un tip
    input: l - lista in care se pastreaza tranzactiile
           tip - tipul tranzactiei introduse
    output: - , daca tipul este valid si stergerea a avut succes
    exceptii - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    undo = []
    verificaEroareTip(tip)
    n = len(l)
    c = 0
    for i in range(n):
        tnz = l[c]
        if obtine_tipul(tnz) == tip:
            l.remove(tnz)
            undo.append(tnz)
        else:
            c = c+1
    dictionar_undo["undo"] = undo

def srv_printeaza_tranzactii_suma(l,suma):
    '''
    Functie care tipareste toate tranzactiile tnz din lista l  cu sume mai mari decât o sumă dată
    input: l - lista in care se pastreaza tranzactiile
           suma - suma introdusa
    output: - , daca suma este valabila si tiparirea a avut succes
    exceptii - cu textul:
                        "Suma invalida!\n", daca suma<=0
    '''
    verificaEroareSuma(suma)
    for tnz in l:
        if obtine_suma(tnz) > suma:
            to_str_tnz(tnz)

def srv_printeaza_tranzactii_zi(l,zi,suma):
    '''
    Functie care tipareste toate tranzactiile tnz din lista l efectuate înainte de o zi și mai mari decât o sumă
    input: l - lista in care se pastreaza tranzactiile
           zi - ziua tranzactiei introduse
           suma - suma introdusa
    output: - , daca ziua si suma sunt valabile si tiparirea a avut succes
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
                        "Suma invalida!\n", daca suma<=0
    '''
    verificaEroareSuma(suma)
    data_introdusa = convertireZi(zi)
    for tnz in l:
        zi = obtine_zi(tnz)
        data_tranzactiei = convertireZi(zi)
        if obtine_suma(tnz) > suma and data_tranzactiei < data_introdusa:
            to_str_tnz(tnz)

def srv_printeaza_tranzactii_tip(l,tip):
    '''
    Functie care tipareste toate tranzactiile tnz din lista l de un anumit tip
    input: l - lista in care se pastreaza tranzactiile
           tip - tipul indrodus
    output: - , daca tipul este valabil si tiparirea a avut succes
    exceptii - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    verificaEroareTip(tip)
    for tnz in l:
        if obtine_tipul(tnz) == tip:
            to_str_tnz(tnz)

def srv_raport_tranzactii_suma(l,tip):
    '''
    Functie care afiseaza suma totală a tranzacțiilor de un anumit tip
    input: l - lista in care se pastreaza tranzactiile
           tip - tipul indrodus
    output: s - suma tranzactiilor
    exceptii - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    s = 0
    verificaEroareTip(tip)
    for tnz in l:
        if obtine_tipul(tnz) == tip:
            s += obtine_suma(tnz)
    return s

def srv_raport_tranzactii_sold(l,zi):
    '''
    Functie care afiseaza soldul contului la o dată specificată
    input: l - lista in care se pastreaza tranzactiile
           zi - ziua introdusa
    output: s - suma tranzactiilor
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
    '''
    s = 0
    data_introdusa = convertireZi(zi)
    for tnz in l:
        zi = obtine_zi(tnz)
        data_tranzactiei = convertireZi(zi)
        if data_tranzactiei < data_introdusa:
            if obtine_tipul(tnz) == 1:
                s += obtine_suma(tnz)
            else:
                s -= obtine_suma(tnz)
    return s

def srv_raport_tranzactii_tip(l,tip):
    '''
    Functie care tipărește toate tranzacțiile de un anumit tip ordonat după sumă
    input: l - lista in care se pastreaza tranzactiile
           tip - tipul indrodus
    output: - , daca tipul este valabil si tiparirea a avut succes
    exceptii - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    from operator import itemgetter
    l.sort(key=itemgetter("suma"))
    srv_printeaza_tranzactii_tip(l,tip)

def srv_filtrare_tranzactii_tip(l,tip):
    '''
    Functie care elimină toate tranzacțiile de un anumit tip
    input: l - lista in care se pastreaza tranzactiile
           tip - tipul indrodus
    output: l1 - listă nouă cu elementele eliminate, daca tipul este valabil
    exceptii - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    l1 = []
    for tnz in l:
        if obtine_tipul(tnz) != tip:
            l1.append(tnz)
    return l1

def srv_filtrare_tranzactii_suma(l,tip,suma):
    '''
    Functie care elimină toate tranzacțiile mai mici decât o sumă dată care au tipul specificat
    input: l - lista in care se pastreaza tranzactiile
           tip - tipul indrodus
           suma - suma introdusa
    output: l1 - listă nouă cu elementele eliminate, daca tipul si suma sunt valabile
    exceptii - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
                        "Suma invalida!\n", daca suma<=0
    '''
    l1 = []
    verificaEroareSuma(suma)
    verificaEroareTip(tip)
    for tnz in l:
        if obtine_tipul(tnz) != tip and obtine_suma(tnz) >= suma:
            l1.append(tnz)
    return l1

def srv_undo(l,cmd,cmdNR,dictionar_undo):
    '''
    Functie care reface ultima operație (lista de tranzacții revine la ce exista înainte de ultima operație care a modificat lista)
    input: l - lista in care se pastreaza tranzactiile
           cmd - ultima comanda accesata pt. meniul principal
           cmdNR - ultima comanda accesata pt. submeniu
    output: l_nou - listă nouă cu elementele de inaintea operatiei cmd si cmdNR
    '''
    l_nou = []
    if cmd == "1" and cmdNR == "1":
        tnz = dictionar_undo["tnz"]
        l_nou = undo1_1(l,tnz)
    elif cmd == "1" and cmdNR == "2":
        tnz1 = dictionar_undo["tnz1"]
        tnz2 = dictionar_undo["tnz2"]
        l_nou = undo1_2(l,tnz1,tnz2)
    elif cmd == "2":
        undo = dictionar_undo["undo"]
        l_nou = undo2(l,undo)
    return l_nou