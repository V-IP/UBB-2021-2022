from Domain.entitati import Carte
from Business.Service import Service
from Infrastructura.repozitorii import FileRepo

class Teste(object):
    
    def __test_creaza_carte(self):
        '''
        Functie de test
        '''
        id = 1
        titlu = "Examen"
        autor = "Iulia"
        anAparitie = 2022
        carte = Carte(id,titlu,autor,anAparitie)
        assert(carte.get_id() == id)
        assert(carte.get_titlu() == titlu)
        assert(carte.get_autor() == autor)
        assert(carte.get_anAparitie() == anAparitie)
        alt_titlu = "FP"
        alt_autor = "Paula"
        alt_anAparitie = 2003
        acelasi_id = Carte(id,alt_titlu,alt_autor,alt_anAparitie)
        assert(carte == acelasi_id)
        assert(str(carte) == "[1] Examen de Iulia - anul: 2022\n")

    def __test_adauga_carte(self):
        '''
        Functie de test
        '''
        file = open("teste.txt", "w")
        file.close()
        
        repo = FileRepo("teste.txt")
        carte = Carte(1,"Examen","Iulia",2022)
        repo.adauga_carte(carte)
        assert(repo.get_all()[0].get_id() == 1)
        assert(repo.get_all()[0].get_titlu() == "Examen")
        assert(repo.get_all()[0].get_autor() == "Iulia")
        assert(repo.get_all()[0].get_anAparitie() == 2022)
        
        file.close()

    def __test_get_all(self):
        '''
        Functie de test
        '''
        file = open("teste.txt", "w")
        file.close()

        repo = FileRepo("teste.txt")
        carte = Carte(1,"Examen","Iulia",2022)
        repo.adauga_carte(carte)
        assert(repo.get_all().__len__() == 1)

    def __test_sterge_carti(self):
        '''
        Functie de test
        '''
        repo = FileRepo("teste.txt")
        carte = Carte(2,"FP","Paula",2013)
        repo.adauga_carte(carte)
        carte = Carte(3,"Practic","Vincze",2010)
        repo.adauga_carte(carte)
        
        repo.sterge_carti(1)
        assert(repo.get_all().__len__() == 1)
        assert(repo.get_all()[0].get_id() == 1)

    def __test_filtrare_carti(self):
        '''
        Functie de test
        '''
        repo = FileRepo("teste.txt")
        carte = Carte(2,"FP","Paula",2013)
        repo.adauga_carte(carte)
        carte = Carte(3,"Practic","Vincze",2010)
        repo.adauga_carte(carte)
        
        l = repo.filtrare_carti("a", 2015)
        assert(len(l) == 1)
        
    def __test_undo(self,l):
        '''
        Functie de test
        '''
        repo = FileRepo("teste.txt")
        repo.undo(l)
        assert(len(repo.get_all()) == len(l))

    def ruleaza_teste(self):
        print("start teste...")
        repo = FileRepo("teste.txt")
        l = repo.get_all()
        self.__test_creaza_carte()
        self.__test_adauga_carte()
        self.__test_get_all()
        self.__test_sterge_carti()
        self.__test_filtrare_carti()
        self.__test_undo(l)
        print("stop teste...")

