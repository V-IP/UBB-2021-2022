from introducere_date import *
from functii_srv import *
from validari import *

def ui_creeaza_tranzactie(l,dictionar_undo):
    zi = citeste_zi()
    suma = citeste_suma()
    tip = citeste_tip()
    srv_adaugare_tranzactie(l,zi,suma,tip,dictionar_undo)

def ui_actualizeaza_tranzactie(l,dictionar_undo):
    print("Introduceti datele tranzactiei pe care doriti sa o modificati.\n")
    zi1 = citeste_zi()
    suma1 = citeste_suma()
    tip1 = citeste_tip()
    print("Introduceti noile informatii ale tranzactiei.\n")
    zi2 = citeste_zi()
    suma2 = citeste_suma()
    tip2 = citeste_tip()
    srv_actualizare_tranzactie(l,zi1,suma1,tip1,zi2,suma2,tip2,dictionar_undo)

def ui_sterge_tranzactii_zi(l,dictionar_undo):
    zi = citeste_zi()
    srv_sterge_tranzactii_zi(l,zi,dictionar_undo)

def ui_sterge_tranzactii_perioada(l,dictionar_undo):
    print("Introduceti data inceput.")
    zi1= citeste_zi()
    print("Introduceti data sfarsit.")
    zi2= citeste_zi()
    srv_sterge_tranzactii_perioada(l,zi1,zi2,dictionar_undo)

def ui_sterge_tranzactii_tip(l,dictionar_undo):
    tip = citeste_tip()
    srv_sterge_tranzactii_tip(l,tip,dictionar_undo)

def ui_printeaza_tranzactii(l):
    if len(l) == 0:
        print("Nu exista tranzactii.\n")
        return
    for tnz in l:
        to_str_tnz(tnz)

def ui_printeaza_tranzactii_suma(l):
    suma = citeste_suma()
    srv_printeaza_tranzactii_suma(l,suma)

def ui_printeaza_tranzactii_zi(l):
    zi = citeste_zi()
    suma = citeste_suma()
    srv_printeaza_tranzactii_zi(l,zi,suma)

def ui_printeaza_tranzactii_tip(l):
    tip = citeste_tip()
    srv_printeaza_tranzactii_tip(l,tip)

def ui_raport_tranzactii_suma(l):
    tip = citeste_tip()
    s = srv_raport_tranzactii_suma(l,tip)
    return s

def ui_raport_tranzactii_sold(l):
    zi = citeste_zi()
    s = srv_raport_tranzactii_sold(l,zi)
    return s

def ui_raport_tranzactii_tip(l):
    tip = citeste_tip()
    srv_raport_tranzactii_tip(l,tip)

def ui_filtrare_tranzactii_tip(l):
    tip = citeste_tip()
    l1 = srv_filtrare_tranzactii_tip(l,tip)
    ui_printeaza_tranzactii(l)

def ui_filtrare_tranzactii_suma(l):
    tip = citeste_tip()
    suma = citeste_suma()
    l1 = srv_filtrare_tranzactii_suma(l,tip,suma)
    ui_printeaza_tranzactii(l)

def ui_undo(l,cmd,cmdNR,dictionar_undo):
    l_nou = []
    ok = 0
    if cmd == "-":
        print("\nNu exista operatie anterioara!\n")
        return
    elif cmd == "1" or cmd == "2":
        l_nou = srv_undo(l,cmd,cmdNR,dictionar_undo)
        ok = 1
    if ok == 1:
        print("\nTranzactiile dupa undo:")
        ui_printeaza_tranzactii(l_nou)
        print()
        return l_nou
    elif cmd == "6":
        print("\nOperatia undo a fost deja efectuata pentru ultima operatie!\n")
    else:
        print("\nNu s-au efectuat modificari pe tranzactii in operatia anterioara!\n")
    return l