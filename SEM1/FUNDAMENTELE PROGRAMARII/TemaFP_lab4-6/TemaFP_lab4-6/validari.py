from datetime import date
from getteri import *

def valideaza_zi(zi,eroare):
    '''
    Functie care verifica daca ziua este o data calendaristica reala
    input: zi - ziua tranzactiei
           eroare - mesajul erorii in cazul invalidarii
    output: - , daca ziua este valida
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
    '''
    data_azi=date.today()
    ziua = obtine_ziuaData(zi)
    luna = obtine_lunaData(zi)
    an = obtine_anData(zi)
    if ziua>31 or ziua<0 or luna<0 or luna>12 or an<0 or an>data_azi.year:
        eroare += "Zi invalida!\n"
    elif luna>data_azi.month and an==data_azi.year:
        eroare += "Zi invalida!\n"
    elif an==data_azi.year and luna==data_azi.month and ziua > data_azi.day:
        eroare += "Zi invalida!\n"
    elif luna==2 and ziua>28:
        eroare += "Zi invalida!\n"
    return eroare

def verificaEroareZi(zi):
    '''
    Functie care verifica daca ziua este o data calendaristica reala
    input: zi - ziua tranzactiei
    output: - , daca ziua este valida
    raise - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
    '''
    eroare = ""
    eroare = valideaza_zi(zi,eroare)
    if len(eroare) > 0:
        raise Exception(eroare)

def valideaza_suma(suma, eroare):
    '''
    Functie care verifica daca suma este un numar natural
    input: suma - suma tranzactiei
           eroare - mesajul erorii in cazul invalidarii
    output: - , daca suma este valida
    exceptii - cu textul:
                        "Suma invalida!\n", daca suma<=0
    '''
    if suma<=0:
        eroare += "Suma invalida!\n"
    elif suma - suma//1 > 0.000001:
        eroare += "Suma invalida!\n"
    return eroare

def verificaEroareSuma(suma):
    '''
    Functie care verifica daca suma este un numar natural
    input: suma - suma tranzactiei
    output: - , daca suma este valida
    raise - cu textul:
                        "Suma invalida!\n", daca suma<=0
    '''
    eroare = ""
    eroare = valideaza_suma(suma,eroare)
    if len(eroare) > 0:
        raise Exception(eroare)

def valideaza_tip(tip,eroare):
    '''
    Functie care verifica daca ziua este o data calendaristica reala, suma este un numar natural si tipul este boolean
    input: tip - tipul tranzactiei
           eroare - mesajul erorii in cazul invalidarii
    output: - , daca tipul este valid
    exceptii - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    if tip!=0 and tip!=1:
        eroare += "Tip invalid!\n"
    return eroare

def verificaEroareTip(tip):
    '''
    Functie care verifica daca ziua este o data calendaristica reala, suma este un numar natural si tipul este boolean
    input: tip - tipul tranzactiei
    output: - , daca tipul este valid
    raise - cu textul:
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    eroare = ""
    eroare = valideaza_tip(tip,eroare)
    if len(eroare) > 0:
        raise Exception(eroare)

def valideaza_tranzactie(tnz):
    '''
    Functie care verifica daca ziua este o data calendaristica reala, suma este un numar natural si tipul este boolean
    input: tnz - tranzactia
    output: - , daca tranzactia este valida
    raise - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
                        "Suma invalida!\n", daca suma<=0
                        "Tip invalid!\n", daca tip!=0 si tip!=1
    '''
    eroare = ""
    zi = obtine_zi(tnz)
    suma = obtine_suma(tnz)
    tip = obtine_tipul(tnz)
    eroare = valideaza_zi(zi,eroare) + valideaza_suma(suma,eroare) + valideaza_tip(tip,eroare)
    if len(eroare)>0:
        raise Exception(eroare)
