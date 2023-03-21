from teste import ruleaza_teste
from convertiri import *
from meniuri import *
from functii_UI import *

def ui():
    l = []
    cmdvechi = "-"
    cmdNRvechi = "-"
    dictionar_undo = {
        "tnz": None,
        "tnz1": None,
        "tnz2": None,
        "undo": None}
    while True:
        afiseaza_meniu_principal()
        cmd = input("Alegeti o optiune: ")
        print()
        if cmd == "":
            continue
        elif cmd == "0":
            return
        elif cmd == "1":
            afiseaza_meniu_1()
            cmd1 = input("Alegeti o optiune: ")
            print()
            if cmd1 == "1":
                try:
                    ui_creeaza_tranzactie(l,dictionar_undo)
                except Exception as ex:
                    print(ex)
            elif cmd1 == "2":
                try:
                    ui_actualizeaza_tranzactie(l,dictionar_undo)
                except Exception as ex:
                    print(ex)
            else:
                print("Nu ati introdus o optiune existenta!")
                print()
            cmdNRvechi = cmd1
            print()
        elif cmd == "2":
            afiseaza_meniu_2()
            cmd2 = input("Alegeti o optiune: ")
            print()
            if cmd2 == "1":
                try:
                    ui_sterge_tranzactii_zi(l,dictionar_undo)
                except Exception as ex:
                    print(ex)
                print()
            elif cmd2 == "2":
                ui_sterge_tranzactii_perioada(l,dictionar_undo)
                print()
            elif cmd2 == "3":
                ui_sterge_tranzactii_tip(l,dictionar_undo)
                print()
            else:
                print("Nu ati introdus o optiune existenta!")
                print()
            cmdNRvechi = cmd2
        elif cmd == "3":
            afiseaza_meniu_3()
            cmd3 = input("Alegeti o optiune: ")
            print()
            if cmd3 == "1":
                ui_printeaza_tranzactii(l)
                print()
            elif cmd3 == "2":
                ui_printeaza_tranzactii_suma(l)
                print()
            elif cmd3 == "3":
                ui_printeaza_tranzactii_zi(l)
                print()
            elif cmd3 == "4":
                ui_printeaza_tranzactii_tip(l)
                print()
            else:
                print("Nu ati introdus o optiune existenta!")
                print()
            cmdNRvechi = cmd3
        elif cmd == "4":
            afiseaza_meniu_4()
            cmd4 = input("Alegeti o optiune: ")
            print()
            if cmd4 == "1":
                print("Suma este:",ui_raport_tranzactii_suma(l))
                print()
            elif cmd4 == "2":
                print("Soldul contului este:",ui_raport_tranzactii_sold(l))
                print()
            elif cmd4 == "3":
                ui_raport_tranzactii_tip(l)
                print()
            else:
                print("Nu ati introdus o optiune existenta!")
                print()
            cmdNRvechi = cmd4
        elif cmd == "5":
            afiseaza_meniu_5()
            cmd5 = input("Alegeti o optiune: ")
            print()
            if cmd5 == "1":
                ui_filtrare_tranzactii_tip(l)
                print()
            elif cmd5 == "2":
                ui_filtrare_tranzactii_suma(l)
                print()
            else:
                print("Nu ati introdus o optiune existenta!")
                print()
            cmdNRvechi = cmd5
        elif cmd == "6":
            print("Tranzactiile actuale:")
            ui_printeaza_tranzactii(l)
            l = ui_undo(l,cmdvechi,cmdNRvechi,dictionar_undo)
        else:
            print("Nu ati introdus o optiune existenta!")
            print()
        cmdvechi = cmd