from datetime import date
from validari import *
from functii_srv import *
from convertiri import *
from stocare import *

def lista_de_testare():
    l = []
    tnz = creeaza_tranzactie(creeaza_zi(5,5,2003),500,1)
    adauga_tranzactie_in_lista(l,tnz)
    tnz = creeaza_tranzactie(creeaza_zi(10,10,2020),300,0)
    adauga_tranzactie_in_lista(l,tnz)
    tnz = creeaza_tranzactie(creeaza_zi(18,10,2021),100,0)
    adauga_tranzactie_in_lista(l,tnz)
    tnz = creeaza_tranzactie(creeaza_zi(1,1,2010),250,1)
    adauga_tranzactie_in_lista(l,tnz)
    return l

def test_creeaza_tranzactie():
    zi = date(2017,3,25)
    tnz = creeaza_tranzactie(zi,280,1)
    assert(obtine_zi(tnz)==zi)
    assert(obtine_suma(tnz)==280)
    assert(obtine_tipul(tnz)==1)

def test_valideaza_tranzactie():
    tnz = creeaza_tranzactie(creeaza_zi(23,5,2005),450,0)
    valideaza_tranzactie(tnz)
    zi_invalida = creeaza_tranzactie(creeaza_zi(57,4,2014),145,1)
    try:
        valideaza_tranzactie(zi_invalida)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")
    suma_invalida = creeaza_tranzactie(creeaza_zi(14,11,2018),-34,1)
    try:
        valideaza_tranzactie(suma_invalida)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Suma invalida!\n")
    tip_invalid = creeaza_tranzactie(creeaza_zi(24,12,2020),352,5)
    try:
        valideaza_tranzactie(tip_invalid)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Tip invalid!\n")
    zi_suma_invalide = creeaza_tranzactie(creeaza_zi(30,2,2008),0,1)
    try:
        valideaza_tranzactie(zi_suma_invalide)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\nSuma invalida!\n")
    zi_tip_invalide = creeaza_tranzactie(creeaza_zi(20,7,2023),890,4)
    try:
        valideaza_tranzactie(zi_tip_invalide)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\nTip invalid!\n")

def test_adauga_tranzactie_in_lista():
    l = []
    tnz = creeaza_tranzactie(creeaza_zi(24,6,2021),1100,1)
    assert(len(l)==0)
    adauga_tranzactie_in_lista(l,tnz)
    assert(len(l)==1)
    assert(obtine_zi(tnz)==obtine_zi(l[0]))
    assert(obtine_suma(tnz)==obtine_suma(l[0]))
    assert(obtine_suma(tnz)==obtine_suma(l[0]))
    tnz = creeaza_tranzactie(creeaza_zi(3,11,1876),20,0)
    adauga_tranzactie_in_lista(l,tnz)
    assert(len(l)==2)
    assert(obtine_zi(tnz)==obtine_zi(l[1]))
    assert(obtine_suma(tnz)==obtine_suma(l[1]))
    assert(obtine_suma(tnz)==obtine_suma(l[1]))

def test_cauta_tranzactie_in_lista():
    l= []
    tnz = creeaza_tranzactie(creeaza_zi(5,5,2003),500,1)
    adauga_tranzactie_in_lista(l,tnz)
    tnz = creeaza_tranzactie(creeaza_zi(10,10,2020),300,0)
    adauga_tranzactie_in_lista(l,tnz)
    i = cauta_tranzactie_in_lista(l,tnz)
    assert(i==1)
    tnz = creeaza_tranzactie(creeaza_zi(1,1,2000),800,1)
    i = cauta_tranzactie_in_lista(l,tnz)
    assert(i==None)

def test_srv_adaugare_tranzactie(dictionar_undo):
    l = []
    srv_adaugare_tranzactie(l,creeaza_zi(23,5,2005),450,0,dictionar_undo)
    assert(len(l) == 1)
    try:
        srv_adaugare_tranzactie(l,creeaza_zi(57,4,2014),145,1,dictionar_undo)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")
    try:
        srv_adaugare_tranzactie(l,creeaza_zi(14,11,2018),-34,1,dictionar_undo)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Suma invalida!\n")
    try:
        srv_adaugare_tranzactie(l,creeaza_zi(24,12,2020),352,5,dictionar_undo)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Tip invalid!\n")
    try:
        srv_adaugare_tranzactie(l,creeaza_zi(30,2,2008),0,1,dictionar_undo)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\nSuma invalida!\n")
    try:
        srv_adaugare_tranzactie(l,creeaza_zi(20,7,2023),890,4,dictionar_undo)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\nTip invalid!\n")

def test_srv_actualizare_tranzactie(dictionar_undo):
    l = []
    tnz = creeaza_tranzactie(creeaza_zi(5,5,2003),500,1)
    adauga_tranzactie_in_lista(l,tnz)
    tnz = creeaza_tranzactie(creeaza_zi(10,10,2020),300,0)
    adauga_tranzactie_in_lista(l,tnz)
    srv_actualizare_tranzactie(l,creeaza_zi(10,10,2020),300,0,creeaza_zi(1,1,1),1,1,dictionar_undo)
    tnz = creeaza_tranzactie(creeaza_zi(1,1,1),1,1)
    assert(l[1]==tnz)

def test_srv_sterge_tranzactii_zi(dictionar_undo):
    l = lista_de_testare()
    zi = creeaza_zi(10,10,2020)
    srv_sterge_tranzactii_zi(l,zi,dictionar_undo)
    tnz = creeaza_tranzactie(creeaza_zi(5,5,2003),500,1)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(18,10,2021),100,0)
    assert(l[1] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(1,1,2010),250,1)
    assert(l[2] == tnz)
    l = lista_de_testare()
    copie = l
    zi = creeaza_zi(14,2,1990)
    srv_sterge_tranzactii_zi(l,zi,dictionar_undo)
    assert(copie == l)

def test_srv_sterge_tranzactii_perioada(dictionar_undo):
    l = lista_de_testare()
    zi1 = creeaza_zi(1,1,2000)
    zi2 = creeaza_zi(12,12,2015)
    srv_sterge_tranzactii_perioada(l,zi1,zi2,dictionar_undo)
    tnz = creeaza_tranzactie(creeaza_zi(10,10,2020),300,0)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(18,10,2021),100,0)
    assert(l[1] == tnz)
    l = lista_de_testare()
    zi1 = creeaza_zi(1,1,1900)
    zi2 = creeaza_zi(25,10,2021)
    srv_sterge_tranzactii_perioada(l,zi1,zi2,dictionar_undo)
    assert(len(l) == 0)

def test_srv_sterge_tranzactii_tip(dictionar_undo):
    l = lista_de_testare()
    srv_sterge_tranzactii_tip(l,1,dictionar_undo)
    tnz = creeaza_tranzactie(creeaza_zi(10,10,2020),300,0)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(18,10,2021),100,0)
    assert(l[1] == tnz)
    l = lista_de_testare()
    srv_sterge_tranzactii_tip(l,0,dictionar_undo)
    tnz = creeaza_tranzactie(creeaza_zi(5,5,2003),500,1)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(1,1,2010),250,1)
    assert(l[1] == tnz)
    srv_sterge_tranzactii_tip(l,1,dictionar_undo)
    assert(len(l) == 0)

def test_srv_raport_tranzactii_suma():
    l = lista_de_testare()
    assert(srv_raport_tranzactii_suma(l,1) == 750)
    assert(srv_raport_tranzactii_suma(l,0) == 400)

def test_srv_raport_tranzactii_sold():
    l = lista_de_testare()
    assert(srv_raport_tranzactii_sold(l,creeaza_zi(12,12,2015)) == 750)
    assert(srv_raport_tranzactii_sold(l,creeaza_zi(27,10,2021)) == 350)
    assert(srv_raport_tranzactii_sold(l,creeaza_zi(1,1,2000)) == 0)

def test_srv_filtrare_tranzactii_tip():
    l = lista_de_testare()
    l = srv_filtrare_tranzactii_tip(l,1)
    tnz = creeaza_tranzactie(creeaza_zi(10,10,2021),100,0)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(18,10,2021),100,0)
    assert(l[1] == tnz)
    l = lista_de_testare()
    l = srv_filtrare_tranzactii_tip(l,)
    tnz = creeaza_tranzactie(creeaza_zi(5,5,2003),500,1)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(1,1,2010),250,1)
    assert(l[1] == tnz)

def test_srv_filtrare_tranzactii_suma():
    l = lista_de_testare()
    l = srv_filtrare_tranzactii_suma(l,1,400)
    tnz = creeaza_tranzactie(creeaza_zi(5,5,2003),500,1)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(18,10,2021),100,0)
    assert(l[1] == tnz)
    l = lista_de_testare()
    l = srv_filtrare_tranzactii_suma(l,tip,suma)
    tnz = creeaza_tranzactie(creeaza_zi(18,10,2021),100,0)
    assert(l[0] == tnz)
    tnz = creeaza_tranzactie(creeaza_zi(1,1,2010),250,1)
    assert(l[1] == tnz)

def test_srv_undo(dictionar_undo):
    l = lista_de_testare()
    srv_adaugare_tranzactie(l,creeaza_zi(1,1,2010),250,1,dictionar_undo)
    l_noua = srv_undo(l,"1","1",dictionar_undo)
    assert(l == l_noua)
    srv_actualizare_tranzactie(l,creeaza_zi(10,10,2020),300,0,creeaza_zi(1,1,1),1,1,dictionar_undo)
    l_noua = srv_undo(l,"1","2",dictionar_undo)
    assert(l == l_noua)
    srv_sterge_tranzactii_zi(l,creeaza_zi(10,10,2020),dictionar_undo)
    l_noua = srv_undo(l,"2","1",dictionar_undo)
    assert(l == l_noua)
    srv_sterge_tranzactii_perioada(l,creeaza_zi(1,1,2000),creeaza_zi(12,12,2015),dictionar_undo)
    l_noua = srv_undo(l,"2","2",dictionar_undo)
    assert(l == l_noua)
    srv_sterge_tranzactii_tip(l,1,dictionar_undo)
    l_noua = srv_undo(l,"2","3",dictionar_undo)
    assert(l == l_noua)

def ruleaza_teste():
    dictionar_undo = {
        "tnz": None,
        "tnz1": None,
        "tnz2": None,
        "undo": None}
    test_creeaza_tranzactie()
    test_valideaza_tranzactie()
    test_adauga_tranzactie_in_lista()
    test_cauta_tranzactie_in_lista()
    test_srv_adaugare_tranzactie(dictionar_undo)
    test_srv_actualizare_tranzactie(dictionar_undo)
    test_srv_sterge_tranzactii_zi(dictionar_undo)
    test_srv_sterge_tranzactii_perioada(dictionar_undo)
    test_srv_sterge_tranzactii_tip(dictionar_undo)
    test_srv_raport_tranzactii_suma()
    test_srv_raport_tranzactii_sold()
    test_srv_undo(dictionar_undo)