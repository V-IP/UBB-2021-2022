class Consola(object):

    def __init__(self, srvLocuri):
        self.__srvLocuri = srvLocuri

    def __ui_afisare_strada(self):
    # Se afiseaza toate locurile de parcare de pe o anumita strada
    # se cere de la utilizator numele strazii
    # se afiseaza elementele listei daca exista locuri
    # se afiseaza mesaj daca nu exista locuri pe acea strada
        strada = input("Strada: ")
        l = []
        self.__srvLocuri.afisare_strada(strada,l)
        if len(l) > 0:
            for loc in l:
                print(loc)
        else:
            print("Nu exista locuri pe aceasta strada!\n")

    def __ui_afisare_best(self):
    # Se afiseaza numele locului cu cele mai multe utilizari de pe fiecare strada
    # se afiseaza elementele listei daca exista locuri
        l_strada = []
        l_nume = []
        self.__srvLocuri.afisare_best(l_strada,l_nume)
        for i in range(len(l_strada)):
            print(l_strada[i],": ",l_nume[i])

    def run(self):
        while True:
            print("Comenzile disponibile sunt: exit, afisare dupa strada, best of street")
            cmd  = input(">>>")
            if cmd == "":
                continue
            elif cmd == "exit":
                return
            elif cmd == "afisare dupa strada":
                self.__ui_afisare_strada()
            elif cmd == "best of street":
                self.__ui_afisare_best()
            else:
                prin("Comanda invalida!\n")