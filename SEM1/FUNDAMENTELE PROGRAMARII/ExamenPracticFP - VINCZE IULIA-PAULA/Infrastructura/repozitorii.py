from Domain.entitati import Carte

class Repo(object):
    
    def __init__(self):
        '''
            Initializeaza un obiect de tip lista (lista de carti)
        '''
        self._carti = []
        
    def get_all(self):
        '''
        Returneaza toate cartile din lista
        :param:
        :return:
        '''
        return self._carti[:]
        
    def adauga_carte(self,carte):
        '''
        Adauga o carte noua in lista
        :param carte: cartea care se adauga (obiect)
        :return:
        '''
        self._carti.append(carte)

    def sterge_carti(self,cifra):
        '''
        Sterge cartile care au in anul aparitiei cifra introdusa
        :param cifra: cifra care se cauta a fi in anul aparitiei (int)
        :return:
        '''
        i=0
        while i<len(self._carti):
            carte = self._carti[i]
            if str(cifra) in str(carte.get_anAparitie()):
                self._carti.remove(carte)
                i -= 1
            i += 1
                
    def filtrare_carti(self,titlu,anAparitie):
        '''
        Filtreaza cartile care au titlul introdus in titlu si care au anul aparitiei mai mic decat anul introdus
        :param titlu: titlul care se cauta a fi in titlul cartii (string)
        :param anAparitiei: anul aparitiei care se doreste a fi mai mare decat anul cartilor din lista (int)
        :return: o lista cu cartile care satisfac conditiile impuse
        '''
        l = []
        if titlu != "" and anAparitie != -1:
            for carte in self._carti:
                if titlu in carte.get_titlu() and carte.get_anAparitie() < anAparitie:
                    l.append(carte)
        elif anAparitie == -1:
            for carte in self._carti:
                if titlu in carte.get_titlu():
                    l.append(carte)
        elif titlu == "":
            for carte in self._carti:
                if carte.get_anAparitie() < anAparitie:
                    l.append(carte)
        return l
                
    def undo(self,l):
        '''
        Reface ultima operatie de stergere
        :param l: lista memorata inainte de efectuarea stergerii (lista)
        :return:
        '''
        self._carti = l

class FileRepo(Repo):
    
    def __init__(self,filename):
        '''
        Mosteneste obiectul de tip Carte (repository)
        :param filename: numele fisierului (string)
        '''
        Repo.__init__(self)
        self.__filename = filename
        
    def __citeste_fisier(self):
        '''
        Citesc tot din fisier
        :param
        :return:
        '''
        with open(self.__filename, "r") as f:
            self._carti = []
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if len(linie) > 0:
                    parti = linie.split(",")
                    id = int(parti[0])
                    titlu = parti[1]
                    autor = parti[2]
                    anAparitie = int(parti[3])
                    obj = Carte(id,titlu,autor,anAparitie)
                    self._carti.append(obj)
                    
    def __adauga_fisier(self, carte):
        '''
        Scrie ultima carte adaugata in repo in fisier
        :param carte: cartea recent introdusa (obiect)
        :return:
        '''
        with open(self.__filename, "a") as f:
            string = str(carte.get_id())
            string += "," + carte.get_titlu()
            string += "," + carte.get_autor()
            string += "," + str(carte.get_anAparitie()) + "\n"
            f.write(string)
            
    def __suprascrie_fisier(self):
        '''
        Scrie tot in fisier
        :param:
        :return:
        '''
        with open(self.__filename, "w") as f:
            for carte in self._carti:
                string = str(carte.get_id())
                string += "," + carte.get_titlu()
                string += "," + carte.get_autor()
                string += "," + str(carte.get_anAparitie()) + "\n"
                f.write(string)
                
    def get_all(self):
        '''
        Mosteneste metoda de returnare a tuturor cartilor
        :param:
        :return:
        '''
        self.__citeste_fisier()
        return Repo.get_all(self)

    def adauga_carte(self, carte):
        '''
        Mosteneste metoda de adaugare carte
        :param carte: cartea care se doreste adaugat (obiect)
        :return:
        '''
        self.__citeste_fisier()
        Repo.adauga_carte(self, carte)
        self.__adauga_fisier(carte)
        
    def sterge_carti(self, cifra):
        '''
        Mosteneste metoda de sterge carti
        :param cifra: cifra care se cauta a fi in anul aparitiei (int)
        :return:
        '''
        self.__citeste_fisier()
        Repo.sterge_carti(self, cifra)
        self.__suprascrie_fisier()
        
    def undo(self,l):
        '''
        Mosteneste medota de undo
        :param l: lista memorata inainte de efectuarea stergerii (lista)
        :return:
        '''
        self.__citeste_fisier()
        Repo.undo(self, l)
        self.__suprascrie_fisier()