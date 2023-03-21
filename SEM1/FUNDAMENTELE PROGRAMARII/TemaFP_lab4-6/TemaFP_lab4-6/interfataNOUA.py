from functii_srv import *
from convertiri import *
from functii_UI import ui_printeaza_tranzactii

def meniu():
    print("adauga zi luna an suma tip")
    print("sterge tip")
    print("tipareste > suma")
    print("sold zi luna an")
    print("exit")

def citire_enunt():
    dictionar_undo = {
        "tnz": None,
        "tnz1": None,
        "tnz2": None,
        "undo": None}
    l = []
    while True:
        print()
        meniu()
        cmd = input("Introduceti comanda: ")
        print()
        if cmd == "exit":
            return
        cmd = cmd.split()
        if cmd[0] == "adauga":
            zi = creeaza_zi(cmd[1],cmd[2],cmd[3])
            suma = cmd[4]
            tip = cmd[5]
            try:
                srv_adaugare_tranzactie(l,zi,suma,tip,dictionar_undo)
            except Exception as ex:
                print(ex)
            print("Lista este:")
            ui_printeaza_tranzactii(l)
        elif cmd[0] == "sterge":
            tip = int(cmd[1])
            try:
                srv_sterge_tranzactii_tip(l,tip,dictionar_undo)
            except Exception as ex:
                print(ex)
            print("Lista este:")
            ui_printeaza_tranzactii(l)
        elif cmd[0] == "tipareste":
            suma = int(cmd[2])
            try:
                srv_printeaza_tranzactii_suma(l,suma)
            except Exception as ex:
                print(ex)
        elif cmd[0] == "sold":
            zi = creeaza_zi(cmd[1],cmd[2],cmd[3])
            try:
                s = srv_raport_tranzactii_sold(l,zi)
                print("Soldul este:",s)
            except Exception as ex:
                print(ex)
        else:
            print("Comnada invalida!/n")