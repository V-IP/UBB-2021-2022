import unittest

from domain.entitati import *
from erori.exceptii import RepoError
from infrastructura.repozitorii import *

class TestCaseRepoClient(unittest.TestCase):
    def setUp(self):
        self.__repo = RepoClienti

    def test_adauga(self):
        client1 = Client(1,"Nume",1234567890987)
        client2 = Client(2,"Nume",1234567890987)
        self.__repo.adauga_client(client1)
        self.assertEqual(len(self.__repo),1)
        self.__repo.adauga_client(client2)
        self.assertEqual(len(self.__repo),2)
        
        self.assertRaises(RepoError, self.__repo.adauga_client,client1)

    def test_stergere(self):
        client1 = Client(1,"Nume",1234567890987)
        client2 = Client(2,"Nume",1234567890987)
        client = Client(100,"Nume",1234567890987)
        self.__repo.adauga_client(client1)
        self.__repo.adauga_client(client2)

        client_sters = self.__repo.sterge_client(client1)
        self.assertEqual(client_sters.get_nume(),"Nume")
        self.assertEqual(client_sters.get_cnp(),1234567890987)
        self.assertRaises(RepoError, self.__repo.sterge_client,client)

    def test_modificare(self):
        client1 = Client(1,"Nume",1234567890987)
        client2 = Client(1,"Nume",1234567890987)
        client = Client(100,"Nume",1234567890987)
        self.__repo.adauga_client(client1)

        client_modificat = self.__repo.modifica_client(client1,"Alt nume")
        self.assertEqual(client_modificat.get_nume(),"Alt nume")
        self.assertEqual(client_modificat.get_cnp(),1234567890987)
        
        self.assertRaises(RepoError, self.__repo.modifica_client,client,"Alt nume")

    def test_get_all(self):
        client = Client(1,"Nume",1234567890987)
        self.__repo.adauga_client(client)

        clienti = self.__repo.get_all()
        self.assertIsInstance(clienti, list)
        self.assertEqual(len(clienti),1)
        self.assertEqual(clienti[0],client)

    def test_len(self):
        self.__repo.adauga_client(Client(1,"Nume",1234567890987))
        self.assertEqual(len(self.__repo),1)

    def test_cauta(self):
        client1 = Client(1,"Nume",1234567890987)
        client2 = Client(2,"Nume",1234567890987)
        client3 = Client(3,"Nume",1234567890987)
        self.__repo.adauga_client(client1)

        client = self.__repo.cauta_client_id(1)
        self.assertEqual(client.get_nume(),"Nume")
        self.assertEqual(client.get_cnp(),1234567890987)

        client_inexistent = self.__repo.cauta_client_id(100)
        self.assertIs(client_inexistent,None)