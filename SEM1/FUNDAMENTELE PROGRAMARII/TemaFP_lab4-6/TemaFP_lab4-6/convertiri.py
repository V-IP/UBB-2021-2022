import datetime
from getteri import *
from datetime import date
from validari import verificaEroareZi

def convertireZi(zi):
    '''
    Functie care converteste informatiile despre zi intr-o data calendarisitca, daca aceasta este valida
    input: zi - dictionar, ziua tranzactiei
    output: data - data calendaristica a tranzactiei
    exceptii - cu textul:
                        "Zi invalida!\n", daca ziua>31 sau ziua<0 sau luna<0 sau luna>12 sau an<0 sau an>an curent
    '''
    verificaEroareZi(zi)
    ziua = obtine_ziuaData(zi)
    luna = obtine_lunaData(zi)
    an = obtine_anData(zi)
    data = datetime.date(an,luna,ziua)
    return data

def creeaza_zi(ziua,luna,an):
    '''
    Functie care stocheaza informatiile pentru o data calendarisitca
    input: ziua - intreg,
           luna - intreg
           an - intreg
    output: zi - data calendaristica a tranzactiei
    '''
    return {
        "zi":int(ziua),
        "luna":int(luna),
        "an":int(an)
        }

def creeaza_tranzactie(zi,suma,tip):
    '''
    Functie care creeaza o tranzactie
    input: zi - data calendaristica de forma zz.ll.aaaa
           suma - intreg
           tip - boolean intrare=1/iesire=0
    output: rezultat = tranzactie cu ziua zi, suma sumă si tipul tip
    '''
    return {
        "zi":zi,
        "suma":int(suma),
        "tipul":int(tip)
           }

def to_str_tnz(tnz):
    '''
    Functie care afiseaza datele dintr-o tranzactie
    input: tnz - o tranzactie
    output: Mesaj string, datele tranzactiei introduse
    '''
    if obtine_tipul(tnz) == 1:
        print("In data de " + str(tnz["zi"]["zi"]) + "." + str(tnz["zi"]["luna"]) + "." + str(tnz["zi"]["an"]) + " s-a depus suma de " + str(tnz["suma"]))
    else:
        print("In data de " + str(tnz["zi"]["zi"]) + "." + str(tnz["zi"]["luna"]) + "." + str(tnz["zi"]["an"]) + " s-a retras suma de " + str(tnz["suma"]))
