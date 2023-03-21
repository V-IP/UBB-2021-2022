from erori.exceptii import ValidatorError
import datetime

class ValidareFilme():
    
    def valideaza(self,film):
        '''
        Functie care verifica daca un film este valid
        input: film - un film
        output: - , daca filmul este valid
        exceptii - cu textul:
                            "Id invalid!\n", daca id<0
                            "Titlu invalid!\n", daca titlul este gol
                            "Gen invalid!\n", daca genul este gol
        '''
        eroare = ""
        if film.get_id_film()<0:
            eroare += "Id invalid!\n"
        if film.__len_titlu__() == 0:
            eroare += "Titlu invalid!\n"
        if film.__len_gen__() == 0:
            eroare += "Gen invalid!\n"
        if(len(eroare)>0):
            raise ValidatorError(eroare)

class ValidareClienti():
    
    def valideaza(self,client):
        '''
        Functie care verifica daca un client este valid
        input: client - un client
        output: - , daca clientul este valid
        exceptii - cu textul:
                            "Id invalid!\n", daca id<0
                            "Nume invalid!\n", daca numele este gol
                            "CNP invalid!\n", daca CNP este gol, negatic sau diferit de 13 cifre
        '''
        eroare = ""
        if client.get_id_client()<0:
            eroare += "Id invalid!\n"
        if client.__len_nume__() == 0:
            eroare += "Nume invalid!\n"
        if client.get_cnp() < 0 or len(str(client.get_cnp())) != 13:
            eroare += "CNP invalid!\n"
        if(len(eroare)>0):
            raise ValidatorError(eroare)


class ValidareInchirieri():

    def valideaza(self,inchiriere):
        '''
        Functie care verifica daca un client este valid
        input: inchiriere - o inchiriere
        output: - , daca inchirierea este valida
        exceptii - cu textul:
                            "Interval inchiriat invalid!\n", daca data returnarii este inainte de data inchirierii
                            "Data de inchiriere invalida!\n", daca data inchirierii este mai mare decat data de astazi
        '''
        eroare = ""
        if inchiriere.get_data_inchiriere() > inchiriere.get_data_returnare():
            eroare += "Interval inchiriat invalid!\n"
       # if inchiriere.get_data_inchiriere > datetime.date.today:
        #    eroare += "Data de inchiriere invalida!\n"
        if(len(eroare)>0):
            raise ValidatorError(eroare)