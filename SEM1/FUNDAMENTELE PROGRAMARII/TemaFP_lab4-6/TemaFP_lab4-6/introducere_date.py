from convertiri import *

def citeste_zi():
    '''
    Functie care citeste informatiile despre ziua tranzactiei
    '''
    print("Adaugati informatiile pentru data.\n")
    try:
        zi = int(input("Ziua: "))
    except:
        raise Exception("Nu ati introdus o valoare numerica valida!")
    try:
        luna = int(input("Luna: "))
    except:
        raise Exception("Nu ati introdus o valoare numerica valida!")
    try:
        an = int(input("Anul: "))
    except:
        raise Exception("Nu ati introdus o valoare numerica valida!")
    zi = creeaza_zi(zi,luna,an)
    return zi

def citeste_suma():
    '''
    Functie care citeste informatiile despre suma tranzactiei
    '''
    try:
        suma = int(input("Introduceti suma tranzactiei: "))
    except:
        print("Nu ati introdus o valoare numerica valida!")
        return
    return suma

def citeste_tip():
    '''
    Functie care citeste informatiile despre tipul tranzactiei
    '''
    try:
        tip = int(input("Introduceti tipul tranzactiei (0=Retragere numerar/1=Depunere numerar): "))
    except:
        print("Nu ati introdus o valoare numerica valida!")
        return
    return tip
