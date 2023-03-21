from domain.entitati import Film,Client,Inchiriere
from validare.validatoare import ValidareFilme,ValidareClienti,ValidareInchirieri
from erori.exceptii import ValidatorError,RepoError
from infrastructura.repozitorii import RepoFilme,RepoClienti,RepoInchirieri
from business.servicii import ServiciiFilme,ServiciiClienti,ServiciiInchirieri
import datetime

class Teste(object):

    def __test_creeaza_film(self):
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        assert(film.get_id_film() == id_film)
        assert(film.get_titlu() == titlu)
        assert(film.get_descriere() == descriere)
        assert(film.get_gen() == gen)
        alt_titlu = "Testare"
        alta_descriere = "Creez un film cu acelasi id"
        alt_gen = "comedie"
        film_acelasi_id = Film(id_film,alt_titlu,alta_descriere,alt_gen)
        assert(film == film_acelasi_id)
        assert(str(film) == "[1] De test - drama\n-> Creez un film inexistent pentru a testa functia\n")

    def __test_creeaza_client(self):
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890987
        client = Client(id_client,nume,cnp)
        assert(client.get_id_client() == id_client)
        assert(client.get_nume() == nume)
        assert(client.get_cnp() == cnp)
        alt_nume = "Prenume si Nume"
        alt_cnp = 1928374650111
        client_acelasi_id = Client(id_client,alt_nume,alt_cnp)
        assert(client == client_acelasi_id)
        assert(str(client) == "[1] Nume si Prenume -> 1234567890987\n")

    def __test_creeaza_inchiriere(self):
        id = 1
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890
        client = Client(id_client,nume,cnp)
        data_inchiriere = datetime.date(2010,12,10)
        data_returnare = datetime.date(2010,12,24)
        inchiriere = Inchiriere(id,film,client,data_inchiriere,data_returnare)
        assert(inchiriere.get_film() == film)
        assert(inchiriere.get_client() == client)
        assert(inchiriere.get_data_inchiriere() == data_inchiriere)
        assert(inchiriere.get_data_returnare() == data_returnare)
        alt_titlu = "Testare"
        alta_descriere = "Creez un film cu acelasi id"
        alt_gen = "comedie"
        film_acelasi_id = Film(id_film,alt_titlu,alta_descriere,alt_gen)
        alt_nume = "Prenume si Nume"
        alt_cnp = 1928374650
        client_acelasi_id = Client(id_client,alt_nume,alt_cnp)
        inchiriere_acelasi_id = Inchiriere(id,film_acelasi_id,client_acelasi_id,data_inchiriere,data_returnare)
        assert(inchiriere == inchiriere_acelasi_id)
        assert(str(inchiriere) == "[1] De test : 2010-12-10 -> 2010-12-24\n")

    def __test_valideaza_film(self):
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        valid = ValidareFilme()
        valid.valideaza(film)
        invalid_id_film = -30
        invalid_titlu = ""
        invalid_gen = ""
        film_id_invalid = Film(invalid_id_film,titlu,descriere,gen)
        try:
            valid.valideaza(film_id_invalid)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Id invalid!\n")
        film_invalid = Film(invalid_id_film,invalid_titlu,descriere,invalid_gen)
        try:
            valid.valideaza(film_invalid)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Id invalid!\nTitlu invalid!\nGen invalid!\n")

    def __test_valideaza_client(self):
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890987
        client = Client(id_client,nume,cnp)
        valid = ValidareClienti()
        valid.valideaza(client)
        invalid_id_client = -100
        invalid_nume = ""
        invalid_cnp = -34
        client_id_invalid = Client(invalid_id_client,nume,cnp)
        try:
            valid.valideaza(client_id_invalid)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Id invalid!\n")
        client_invalid = Client(invalid_id_client,invalid_nume,invalid_cnp)
        try:
            valid.valideaza(client_invalid)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Id invalid!\nNume invalid!\nCNP invalid!\n")

    def __test_valideaza_inchiriere(self):
        id = 1
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890
        client = Client(id_client,nume,cnp)
        data_inchiriere = datetime.date(2010,12,10)
        data_returnare = datetime.date(2010,12,24)
        inchiriere = Inchiriere(id,film,client,data_inchiriere,data_returnare)
        valid = ValidareInchirieri()
        valid.valideaza(inchiriere)
        invalida_data_inchiriere = datetime.date(2030,10,15)
        invalida_data_returnare = datetime.date(2030,2,25)
        inchiriere_invalida = Inchiriere(id,film,client,invalida_data_inchiriere,invalida_data_returnare)
        try:
            valid.valideaza(inchiriere_invalida)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Interval inchiriat invalid!\n")

    def __test_adauga_film_repo(self):
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        repo = RepoFilme()
        assert(repo.__len__() == 0)
        repo.adauga_film(film)
        assert(repo.__len__() == 1)
        film_gasit = repo.cauta_film_id(id_film)
        assert(film_gasit == film)
        assert(film.get_titlu() == film_gasit.get_titlu())
        assert(film.get_descriere() == film_gasit.get_descriere())
        assert(film.get_gen() == film_gasit.get_gen())
        id_film_inexistent = 100
        try:
            film_gasit = repo.cauta_film_id(id_film_inexistent)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id inexistent!\n")
        alt_titlu = "Testare"
        alta_descriere = "Creez un film cu acelasi id"
        alt_gen = "comedie"
        film_acelasi_id = Film(id_film,alt_titlu,alta_descriere,alt_gen)
        try:
            film_gasit = repo.adauga_film(film_acelasi_id)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id existent!\n")

    def __test_adauga_client_repo(self):
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890987
        client = Client(id_client,nume,cnp)
        repo = RepoClienti()
        assert(repo.__len__() == 0)
        repo.adauga_client(client)
        assert(repo.__len__() == 1)
        client_gasit = repo.cauta_client_id(id_client)
        assert(client_gasit == client)
        assert(client.get_nume() == client_gasit.get_nume())
        assert(client.get_cnp() == client_gasit.get_cnp())
        id_client_inexistent = 100
        try:
            client_gasit = repo.cauta_client_id(id_client_inexistent)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id inexistent!\n")
        alt_nume = "Prenume si Nume"
        alt_cnp = 1111111111111
        client_acelasi_id = Client(id_client,alt_nume,alt_cnp)
        try:
            client_gasit = repo.adauga_client(client_acelasi_id)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id existent!\n")

    def __test_adauga_inchiriere_repo(self):
        id = 1
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890
        client = Client(id_client,nume,cnp)
        data_inchiriere = datetime.date(2010,12,10)
        data_returnare = datetime.date(2010,12,24)
        inchiriere = Inchiriere(id,film,client,data_inchiriere,data_returnare)
        repo = RepoInchirieri()
        assert(repo.__len__() == 0)
        repo.adauga_inchiriere(inchiriere)
        assert(repo.__len__() == 1)
        inchiriere_gasita = repo.cauta_inchiriere_id(film,client,data_inchiriere)
        assert(inchiriere_gasita == inchiriere)
        assert(inchiriere.get_data_returnare() == inchiriere_gasita.get_data_returnare())
        id_client_inexistent = 100
        client_id_inexistent = Client(id_client_inexistent,nume,cnp)
        try:
            inchiriere_gasita = repo.cauta_inchiriere_id(film,client_id_inexistent,data_inchiriere)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id inexistent!\n")
        alt_nume = "Prenume si Nume"
        alt_cnp = 1111111111111
        client_acelasi_id = Client(id_client,alt_nume,alt_cnp)
        inchiriere_acelasi_id = Inchiriere(id,film,client_acelasi_id,data_inchiriere,data_returnare)
        try:
            inchiriere_gasita = repo.adauga_inchiriere(inchiriere_acelasi_id)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id existent!\n")
        
    def __test_adauga_film_service(self):
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        repo = RepoFilme()
        valid = ValidareFilme()
        srv = ServiciiFilme(valid, repo)
        assert(srv.nr_filme() == 0)
        srv.adauga_film(id_film,titlu,descriere,gen)
        assert(srv.nr_filme() == 1)
        try:
            srv.adauga_film(id_film,titlu,descriere,gen)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id existent!\n")
        invalid_id_film = -30
        invalid_titlu = ""
        invalid_gen = ""
        try:
            srv.adauga_film(invalid_id_film,invalid_titlu,descriere,invalid_gen)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Id invalid!\nTitlu invalid!\nGen invalid!\n")

    def __test_adauga_client_service(self):
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890987
        repo = RepoClienti()
        valid = ValidareClienti()
        srv = ServiciiClienti(valid, repo)
        assert(srv.nr_clienti() == 0)
        srv.adauga_client(id_client,nume,cnp)
        assert(srv.nr_clienti() == 1)
        try:
            srv.adauga_client(id_client,nume,cnp)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id existent!\n")
        invalid_id_client = -30
        invalid_nume = ""
        invalid_cnp = -34
        try:
            srv.adauga_client(invalid_id_client,invalid_nume,invalid_cnp)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Id invalid!\nNume invalid!\nCNP invalid!\n")

    def __test_adauga_inchiriere_service(self):
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        repo_filme = RepoFilme()
        repo_filme.adauga_film(film)
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890
        client = Client(id_client,nume,cnp)
        repo_clienti = RepoClienti()
        repo_clienti.adauga_client(client)
        data_inchiriere = datetime.date(2010,12,10)
        data_returnare = datetime.date(2010,12,24)
        repo = RepoInchirieri()
        valid = ValidareInchirieri()
        srv = ServiciiInchirieri(valid,repo,repo_filme,repo_clienti)
        assert(srv.nr_inchirieri() == 0)
        srv.adauga_inchiriere(id_film,id_client,data_inchiriere,data_returnare)
        assert(srv.nr_inchirieri() == 1)
        try:
            srv.adauga_inchiriere(id_film,id_client,data_inchiriere,data_returnare)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id existent!\n")
        id_film_inexistent = 8
        try:
            srv.adauga_inchiriere(id_film_inexistent,id_client,data_inchiriere,data_returnare)
            assert(False)
        except RepoError as re:
            assert(str(re) == "Id inexistent!\n")
        invalida_data_inchiriere = datetime.date(2030,10,15)
        invalida_data_returnare = datetime.date(2030,2,25)
        inchiriere_invalida = Inchiriere(1,film,client,invalida_data_inchiriere,invalida_data_returnare)
        try:
            valid.valideaza(inchiriere_invalida)
            assert(False)
        except ValidatorError as ve:
            assert(str(ve) == "Interval inchiriat invalid!\n")

    def __test_sterge_film_service(self):
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        repo = RepoFilme()
        valid = ValidareFilme()
        srv = ServiciiFilme(valid, repo)
        srv.adauga_film(id_film,titlu,descriere,gen)
        srv.sterge_film(id_film)
        assert(srv.nr_filme() == 0)
    
    def __test_sterge_client_service(self):
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890987
        repo = RepoClienti()
        valid = ValidareClienti()
        srv = ServiciiClienti(valid, repo)
        srv.adauga_client(id_client,nume,cnp)
        srv.sterge_client(id_client)
        assert(srv.nr_clienti() == 0)

    def __test_sterge_inchiriere_service(self):
        id_film = 1
        titlu = "De test"
        descriere = "Creez un film inexistent pentru a testa functia"
        gen = "drama"
        film = Film(id_film,titlu,descriere,gen)
        repo_filme = RepoFilme()
        repo_filme.adauga_film(film)
        id_client = 1
        nume = "Nume si Prenume"
        cnp = 1234567890
        client = Client(id_client,nume,cnp)
        repo_clienti = RepoClienti()
        repo_clienti.adauga_client(client)
        data_inchiriere = datetime.date(2010,12,10)
        data_returnare = datetime.date(2010,12,24)
        repo = RepoInchirieri()
        valid = ValidareInchirieri()
        srv = ServiciiInchirieri(valid,repo,repo_filme,repo_clienti)
        srv.adauga_inchiriere(id_film,id_client,data_inchiriere,data_returnare)
        srv.sterge_inchiriere(id_film,id_client,data_inchiriere)
        assert(srv.nr_inchirieri() == 0)
        

    def ruleaza_teste(self):
        print("start teste ...")
        self.__test_creeaza_film()
        self.__test_creeaza_client()
        self.__test_creeaza_inchiriere()
        self.__test_valideaza_film()
        self.__test_valideaza_client()
        self.__test_valideaza_inchiriere()
        self.__test_adauga_film_repo()
        self.__test_adauga_client_repo()
        self.__test_adauga_inchiriere_repo()
        self.__test_adauga_film_service()
        self.__test_adauga_client_service()
        self.__test_adauga_inchiriere_service()
        self.__test_sterge_film_service()
        self.__test_sterge_client_service()
        self.__test_sterge_inchiriere_service()
        print("stop teste succes!")

