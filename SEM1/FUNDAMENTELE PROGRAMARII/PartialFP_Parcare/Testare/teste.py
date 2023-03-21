from Domain.entitati import Loc
from Business.servicii import ServiceLoc
from Infrastructura.repozitorii import FileRepoLoc

# AM CREAT UN FISIER NOU TXT PENTRU TESTARE FIINDCA FOLOSESC TOT DATELE DIN FISIER IN TESTE, NECREAND FUNCTIE DE ADAUGARE IN REPO
# IAR DACA PASTREZ ACELASI FISIER, VA CRAPA DUPA MODIFICAREA DATELOR DIN EL

class Teste(object):

    def __test_creaza_loc(self):
        id = 97
        nume = "W903"
        strada = "Dorobantilor"
        numar_utilizari = 9
        loc = Loc(id,nume,strada,numar_utilizari)
        assert(loc.get_id() == id)
        assert(loc.get_nume() == nume)
        assert(loc.get_strada() == strada)
        assert(loc.get_nr() == numar_utilizari)
        alt_nume = "D3X2"
        alta_strada = "Teodor Mihali"
        alt_numar = 23
        loc_acelasi_id = Loc(id,alt_nume,alta_strada,alt_numar)
        assert(loc == loc_acelasi_id)
        assert(str(loc) == "[97] W903 pe Dorobantilor folosit de 9 ori\n")

    def __test_f1(self):
        repo_locuri = FileRepoLoc("locuri_test.txt")
        srv_locuri = ServiceLoc(repo_locuri)
        l = []
        srv_locuri.afisare_strada("Dorobantilor",l)
        assert(len(l) == 2)

    def __test_f2(self):
        repo_locuri = FileRepoLoc("locuri_test.txt")
        srv_locuri = ServiceLoc(repo_locuri)
        l1 = []
        l2 = []
        srv_locuri.afisare_best(l1,l2)
        assert(l2[0] == "W904")
        assert(l2[1] == "D3X2")

    def ruleaza_teste(self):
        print("start teste ...")
        self.__test_creaza_loc()
        self.__test_f1()
        self.__test_f2()
        print("stop teste ...")


