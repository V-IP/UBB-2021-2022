import datetime
from erori.exceptii import ValidatorError,RepoError
from business.servicii import ServiciiFilme,ServiciiClienti,ServiciiInchirieri
from domain.dto import *
from domain.entitati import *

class consola(object):
    
    def __init__(self,srv_filme,srv_clienti,srv_inchirieri):
        self.__srv_filme = srv_filme
        self.__srv_clienti = srv_clienti
        self.__srv_inchirieri = srv_inchirieri

    def __ui_adaugaFilm(self):
        try:
            id_film = int(input("id film: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        titlu = input("titlu: ")
        descriere = input("descriere: ")
        gen = input("gen: ")
        self.__srv_filme.adauga_film(id_film,titlu,descriere,gen)
        print("Film adaugat cu succes!\n")

    def __ui_adaugaClient(self):
        try:
            id_client = int(input("id client: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        nume = input("nume: ")
        try:
            cnp = int(input("cnp client: "))
        except ValueError:
            print("CNP numeric invalid!")
            return
        self.__srv_clienti.adauga_client(id_client,nume,cnp)
        print("Client adaugat cu succes!\n")

    def __ui_adaugaInchiriere(self):
        try:
            id_film = int(input("id film: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        try:
            id_client = int(input("id client: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        try:
            data_inchiriere = input("data inchirierii (YYYY-MM-DD): ")
            data_inchiriere = data_inchiriere.split("-")
            data_inchiriere = datetime.date(int(data_inchiriere[0]),int(data_inchiriere[1]),int(data_inchiriere[2]))
            data_returnare = data_inchiriere + datetime.timedelta(days=14)
        except ValueError:
            print("Data numerica invalid!")
            return
        self.__srv_inchirieri.adauga_inchiriere(id_film,id_client,data_inchiriere,data_returnare)
        print("Inchiriere adaugata cu succes!\n")



    def __ui_afisareFilme(self):
        nr_filme = self.__srv_filme.nr_filme()
        if nr_filme == 0:
            print("Nu exista filme in baza de date!\n")
            return
        for film in self.__srv_filme.get_all_filme():
            print(film)

    def __ui_afisareClienti(self):
        nr_clienti = self.__srv_clienti.nr_clienti()
        if nr_clienti == 0:
            print("Nu exista clienti in baza de date!\n")
            return
        for client in self.__srv_clienti.get_all_clienti():
            print(client)

    def __ui_afisareInchirieri(self):
        nr_inchirieri = self.__srv_inchirieri.nr_inchirieri()
        if nr_inchirieri == 0:
            print("Nu exista inchirieri in baza de date!\n")
            return
        for inchiriere in self.__srv_inchirieri.get_all_dto():
            print(inchiriere)

    def __ui_afisareInchirieriTop(self):
        nr_inchirieri = self.__srv_inchirieri.nr_inchirieri()
        if nr_inchirieri == 0:
            print("Nu exista inchirieri in baza de date!\n")
            return
        print("\nTop 3 cele mai inchiriate filme sunt:\n")
        for inchiriere in self.__srv_inchirieri.top_inchiriate():
            print(inchiriere.get_titlu())
        print()

    def __ui_afisareOrdonat(self):
        nr_inchirieri = self.__srv_inchirieri.nr_inchirieri()
        if nr_inchirieri == 0:
            print("Nu exista inchirieri in baza de date!\n")
            return
        print("\nClientii ordonati dupa numar si numar de filme inchiriate sunt:\n")
        rez = self.__srv_inchirieri.get_all_dto()
        for inchiriere in self.__srv_inchirieri.ordonare_nume_numar(rez):
            print(inchiriere.get_nume())
        print()
       
    def __ui_afisareRaport30(self):
        nr_inchirieri = self.__srv_inchirieri.nr_inchirieri()
        if nr_inchirieri == 0:
            print("Nu exista inchirieri in baza de date!\n")
            return
        print("\nPrimi 30% clienti cu cele mai multe filme sunt:\n")
        rez = self.__srv_inchirieri.get_all_dto()
        for inchiriere in self.__srv_inchirieri.raport30(rez):
            print(inchiriere.get_nume(),"cu",len(inchiriere),"filme inchiriate")
        print()


    def __ui_stergereFilme(self):
        try:
            id_film = int(input("id film: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        self.__srv_filme.sterge_film(id_film)
        print("Film sters cu succes!\n")

    def __ui_stergereClienti(self):
        try:
            id_client = int(input("id client: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        self.__srv_clienti.sterge_client(id_client)
        print("Client sters cu succes!\n")

    def __ui_stergereInchirieri(self):
        try:
            id_film = int(input("id film: "))
            id_client = int(input("id client: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        try:
            data_inchiriere = input("data inchirierii (YYYY-MM-DD): ")
            data_inchiriere = data_inchiriere.split("-")
            data_inchiriere = datetime.date(int(data_inchiriere[0]),int(data_inchiriere[1]),int(data_inchiriere[2]))
        except ValueError:
            print("Data numerica invalid!")
            return
        self.__srv_inchirieri.sterge_inchiriere(id_film,id_client,data_inchiriere)
        print("Inchiriere stearsa cu succes!\n")



    def __ui_modificaFilm(self):
        try:
            id_film = int(input("id film: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        descriere = input("descriere: ")
        self.__srv_filme.modifica_film(id_film,descriere)
        print("Film modificat cu succes!\n")

    def __ui_modificaClient(self):
        try:
            id_client = int(input("id client: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        nume = input("nume: ")
        self.__srv_clienti.modifica_client(id_client,nume)
        print("Client modificat cu succes!\n")

    def __ui_modificaInchiriere(self):
        try:
            id_film = int(input("id film: "))
            id_client = int(input("id client: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        try:
            data_inchiriere = input("data inchirierii (YYYY-MM-DD): ")
            data_inchiriere = data_inchiriere.split("-")
            data_inchiriere = datetime.date(int(data_inchiriere[0]),int(data_inchiriere[1]),int(data_inchiriere[2]))
            data_returnare = input("data dorita a fi modificata pt returnare (YYYY-MM-DD): ")
            data_returnare = data_returnare.split("-")
            data_returnare = datetime.date(int(data_returnare[0]),int(data_returnare[1]),int(data_returnare[2]))
        except ValueError:
            print("Data numerica invalid!")
            return
        self.__srv_inchirieri.modifica_inchiriere(id_film,id_client,data_inchiriere,data_returnare)
        print("Inchiriere modificata cu succes!\n")



    def __ui_cautaFilm(self):
        optiune = input("Introduceti optiunea de cautare: ")
        if optiune == "id":
            try:
                id_film = int(input("id film: "))
            except ValueError:
                print("Id numeric invalid!")
                return
            film = self.__srv_filme.cauta_film_id(id_film)
        elif optiune == "titlu":
            titlu = input("titlu: ")
            film = self.__srv_filme.cauta_film_titlu(titlu)
        print(film)

    def __ui_cautaClient(self):
        optiune = input("Introduceti optiunea de cautare: ")
        if optiune == "id":
            try:
                id_client = int(input("id client: "))
            except ValueError:
                print("Id numeric invalid!")
                return
            client = self.__srv_clienti.cauta_client_id(id_client)
        elif optiune == "nume":
            nume = input("nume: ")
            client = self.__srv_clienti.cauta_client_nume(nume)
        elif optiune == "cnp":
            try:
                cnp = int(input("cnp: "))
            except ValueError:
                print("Id numeric invalid!")
                return
            client = self.__srv_clienti.cauta_client_cnp(cnp)
        print(client.__afisare_client__())

    def __ui_cautaInchiriere(self):
        try:
            id_film = int(input("id film: "))
            id_client = int(input("id client: "))
        except ValueError:
            print("Id numeric invalid!")
            return
        try:
            data_inchiriere = input("data inchirierii (YYYY-MM-DD): ")
            data_inchiriere = data_inchiriere.split("-")
            data_inchiriere = datetime.date(int(data_inchiriere[0]),int(data_inchiriere[1]),int(data_inchiriere[2]))
        except ValueError:
            print("Data numerica invalid!")
            return
        inchiriere = self.__srv_inchirieri.cauta_inchiriere_id(id_film,id_client,data_inchiriere)
        print(inchiriere.__afisare_inchiriere__())



    def __ui_adauga_random(self):
        self.__srv_filme.random_filme()

    def __ui_filme_clienttop(self):
        nr_inchirieri = self.__srv_inchirieri.nr_inchirieri()
        if nr_inchirieri == 0:
            print("Nu exista inchirieri in baza de date!\n")
            return
        print("\nFilmele de la clientul cu cele mai multe inchirieri sunt:\n")
        rez = self.__srv_inchirieri.get_all_dto()
        rez = self.__srv_inchirieri.raport30(rez)
        print(rez[0])



    def __ui_sortari(self):
        print("Doriti sa fie sortate crescator sau descrescator:")
        print("1. Crescator")
        print("2. Descrescator")
        p = int(input("Alegeti 1 sau 2: "))
        print("Sortati prin:")
        print("1. Bubble sort")
        print("2. Shell sort")
        n = int(input("Alegeti 1 sau 2: "))
        if n == 1:
            print("Doriti sa fie sortate lista de filme dupa:")
            print("1. Id-ul filmului")
            print("2. Titlul filmului")
            m = int(input("Alegeti 1 sau 2: "))
            if m == 1:
                lista = self.__srv_filme.get_all_filme()
                if p == 1:
                    for film in self.__srv_filme.bubble_sort_filme(lista, lambda x: x.get_id_film(), False, lambda x, y: (x >= y)):
                        print(film)
                else:
                    for film in self.__srv_filme.bubble_sort_filme(lista, lambda x: x.get_id_film(), True, lambda x, y: (x >= y)):
                        print(film)
            elif m == 2:
                lista = self.__srv_filme.get_all_filme()
                if p == 1:
                    for film in self.__srv_filme.bubble_sort_filme(lista, lambda x: x.get_titlu(), False, lambda x, y: (x >= y)):
                        print(film)
                else:
                    for film in self.__srv_filme.bubble_sort_filme(lista, lambda x: x.get_titlu(), False, lambda x, y: (x >= y)):
                        print(film)
            else:
                print("Comanda invalida!")
        elif n == 2:
            print("Doriti sa fie sortate lista de filme dupa:")
            print("1. Id-ul filmului")
            print("2. Titlul filmului")
            m = int(input("Alegeti 1 sau 2: "))
            if m == 1:
                lista = self.__srv_filme.get_all_filme()
                if p == 1:
                    for film in self.__srv_filme.shell_sort_filme(lista, lambda x: x.get_id_film(), True, lambda x,y: (x >= y)):
                        print(film)
                else:
                    for film in self.__srv_filme.shell_sort_filme(lista, lambda x: x.get_id_film(), False, lambda x,y: (x >= y)):
                        print(film)
            elif m == 2:
                lista = self.__srv_filme.get_all_filme()
                if p == 1:
                    for film in self.__srv_filme.shell_sort_filme(lista, lambda x: x.get_titlu(), True, lambda x, y: (x >= y)):
                        print(film)
                else:
                    for film in self.__srv_filme.shell_sort_filme(lista, lambda x: x.get_titlu(), True, lambda x, y: (x <= y)):
                        print(film)
            else:
                print("Comanda invalida!")
        else:
            print("Comanda invalida!")



    def run(self):
        while True:
            print("Comenzile disponibile sunt: exit, adauga, afisare, sterge, modifica, cauta + film/client/inchiriere")
            print("Comenzile pentru rapoarte sunt: raport nume, raport clienti, raport filme")
            print("Comenzi adaugate la laborator: adauga random filme, filme top client")
            print("Comanda pentru sortari: sortare filme")
            cmd = input(">>>")
            if cmd == "":
                continue
            elif cmd == "exit":
                return
            elif cmd == "adauga random filme":
                self.__ui_adauga_random()
            elif cmd == "filme top client":
                self.__ui_filme_clienttop()
            elif cmd == "sortare filme":
                self.__ui_sortari()



            elif cmd == "adauga film":
                try:
                    self.__ui_adaugaFilm()
                except ValidatorError as ve:
                    print("Eroare validare:\n"+str(ve))
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "adauga client":
                try:
                    self.__ui_adaugaClient()
                except ValidatorError as ve:
                    print("Eroare validare:\n"+str(ve))
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "adauga inchiriere":
                try:
                    self.__ui_adaugaInchiriere()
                except ValidatorError as ve:
                    print("Eroare validare:\n"+str(ve))
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))


            elif cmd == "afisare filme":
                self.__ui_afisareFilme()
            elif cmd == "afisare clienti":
                self.__ui_afisareClienti()
            elif cmd == "afisare inchirieri":
                self.__ui_afisareInchirieri()


            elif cmd == "sterge film":
                try:
                    self.__ui_stergereFilme()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "sterge client":
                try:
                    self.__ui_stergereClienti()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "sterge inchiriere":
                try:
                    self.__ui_stergereInchirieri()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))


            elif cmd == "modifica film":
                try:
                    self.__ui_modificaFilm()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "modifica client":
                try:
                    self.__ui_modificaClient()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "modifica inchiriere":
                try:
                    self.__ui_modificaInchiriere()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))


            elif cmd == "cauta film":
                try:
                    self.__ui_cautaFilm()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "cauta client":
                try:
                    self.__ui_cautaClient()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))
            elif cmd == "cauta inchiriere":
                try:
                    self.__ui_cautaInchiriere()
                except RepoError as re:
                    print("Eroare repository:\n"+str(re))


            elif cmd == "raport nume":
                self.__ui_afisareOrdonat()
            elif cmd == "raport filme":
                self.__ui_afisareInchirieriTop()
            elif cmd == "raport clienti":
                self.__ui_afisareRaport30()


            else:
                print("comanda invalida!\n")