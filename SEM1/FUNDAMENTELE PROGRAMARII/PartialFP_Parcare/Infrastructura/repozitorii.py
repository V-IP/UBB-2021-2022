from Domain.entitati import Loc

class RepoLoc(object):

    def __init__(self):
        self._locuri = []

    def __len__(self):
    # returnez lungimea listei de locuri
        return len(self.__locuri)

    def get_all(self):
    #returnez lista de locuri
        return self._locuri[:]

class FileRepoLoc(RepoLoc):

    def __init__(self, filename):
        RepoLoc.__init__(self)
        self.__filename = filename

    def __citeste_fisier(self):
    # citesc toate datele din fisier
        with open(self.__filename, "r") as f:
            self._locuri = []
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if len(linie) > 0:
                    parti = linie.split(",")
                    id = int(parti[0])
                    nume = parti[1]
                    strada = parti[2]
                    nr_utilizari = int(parti[3])
                    loc = Loc(id,nume,strada,nr_utilizari)
                    self._locuri.append(loc)

    def __len__(self):
        self.__citeste_fisier()
        return RepoLoc.__len__(self)

    def get_all(self):
        self.__citeste_fisier()
        return RepoLoc.get_all(self)

