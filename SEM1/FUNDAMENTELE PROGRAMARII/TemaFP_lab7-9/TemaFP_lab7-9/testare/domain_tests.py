import unittest

from domain.entitati import *
from validare.validatoare import *
from erori.exceptii import ValidatorError

class TestCaseClient(unittest.TestCase):
    def setUp(self):
        self.__validator = ValidareClienti

    def test_creeaza_client(self):
        client = Client(1,"Nume",1234567890987)
        self.assertEqual(client.get_nume(),"Nume")
        self.assertEqual(client.get_cnp(), 1234567890987)

        client.set_nume("Alt nume")
        self.assertEqual(client.get_nume(),"Alt nume")
        
    def test_identic(self):
        client1 = Client(1,"Nume",1234567890987)
        client2 = Client(1,"Nume",1234567890987)
        self.assertEqual(client1,client2)

        client_dif = Client(2,"Nume",1234567890987)
        self.assertNotEqual(client1,client_dif)

    def test_validare(self):
        client = Client(1,"Nume",1234567890987)
        self.__validator.valideaza(client)
        client_dif_nume = Client(2,"",1234567890987)
        self.assertRaises(ValidatorError, self.__validator.valideaza,client_dif_nume)
        client_dif_cnp = Client(2,"Nume",5)
        self.assertRaises(ValidatorError, self.__validator.valideaza,client_dif_cnp)
        self.assertRaises(ValidatorError, self.__validator.valideaza,client)

class TestCaseFilm(unittest.TestCase):
    def setUp(self):
        self.__validator = ValidareFilme

    def test_creeaza_film(self):
        film = Film(1,"Titlu","Descriere","gen")
        self.assertEqual(film.get_titlu(),"Titlu")
        self.assertEqual(film.get_descriere(),"Descriere")
        self.assertEqual(film.get_gen(),"gen")

        film.set_descriere("Alta descriere")
        self.assertEqual(film.get_descriere(),"Alta descriere")
        
    def test_identic(self):
        film1 = Film(1,"Titlu","Descriere","gen")
        film2 = Film(1,"Titlu","Descriere","gen")
        self.assertEqual(film1,film2)

        film_dif = Film(2,"Titlu","Descriere","gen")
        self.assertNotEqual(film1,film_dif)

    def test_validare(self):
        film = Film(1,"Titlu","Descriere","gen")
        self.__validator.valideaza(film)
        film_dif_titlu = Film(2,"","Descriere","gen")
        self.assertRaises(ValidatorError, self.__validator.valideaza,client_dif_titlu)
        film_dif_gen = Film(2,"Titlu","Descriere","")
        self.assertRaises(ValidatorError, self.__validator.valideaza,client_dif_gen)
        self.assertRaises(ValidatorError, self.__validator.valideaza,client)

class TestCaseInchiriere(unittest.TestCase):
    def setUp(self):
        self.__validator = ValidareInchirieri

    def test_creeaza_inchiriere(self):
        client = Client(1,"Nume",1234567890987)
        film = Film(1,"Titlu","Descriere","gen")
        inchiriere = Inchiriere(1,film,client,datetime.date(2020,2,2),datetime.date(2020,2,20))
        self.assertEqual(inchiriere.get_client(),client)
        self.assertEqual(inchiriere.get_film(),film)
        self.assertEqual(inchiriere.get_data_returnare,datetime.date(2020,2,20))

        inchiriere.set_data_returnare(datetime.date(2020,5,25))
        self.assertEqual(inchiriere.get_data_returnare(),datetime.date(2020,5,25))
        
    def test_identic(self):
        client = Client(1,"Nume",1234567890987)
        film = Film(1,"Titlu","Descriere","gen")
        inchiriere1 = Inchiriere(1,film,client,datetime.date(2020,2,2),datetime.date(2020,2,20))
        inchiriere2 = Inchiriere(1,film,client,datetime.date(2020,2,2),datetime.date(2020,2,20))
        self.assertEqual(inchiriere1,inchiriere2)

        inchiriere_dif = Inchiriere(2,film,client,datetime.date(2020,2,2),datetime.date(2020,2,20))
        self.assertNotEqual(inchiriere1,inchiriere_dif)

    def test_validare(self):
        client = Client(1,"Nume",1234567890987)
        film = Film(1,"Titlu","Descriere","gen")
        inchiriere1 = Inchiriere(1,film,client,datetime.date(2020,2,2),datetime.date(2020,2,20))
        self.__validator.valideaza(inchiriere)
        inchiriere_dif_data = Inchiriere(1,film,client,datetime.date(2030,2,2),datetime.date(2020,2,20))
        self.assertRaises(ValidatorError, self.__validator.valideaza,inchiriere_dif_data)
        self.assertRaises(ValidatorError, self.__validator.valideaza,inchiriere)