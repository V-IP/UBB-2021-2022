def undo1_1(l,tnz):
    '''
    Functie care realizeaza undo la operatia de creare a tranzactiei => sterge elementul adaugat
    input: l - lista in care se pastreaza tranzactiile
           tnz - tranzactia adaugata
    output: l - lista nouă
    '''
    for _tnz in l:
        if _tnz == tnz:
            l.remove(tnz)
    return l

def undo1_2(l,tnz1,tnz2):
    '''
    Functie care realizeaza undo la operatia de actualizare a tranzactiei => modifica elementul la vechile informatii
    input: l - lista in care se pastreaza tranzactiile
           tnz1 - vechile informatii ale tranzactiei
           tnz2 - tranzactia din lista modificata
    output: l - lista nouă
    '''
    for i in range(len(l)):
        if tnz2 == l[i]:
            l[i] = tnz1
    return l

def undo2(l,undo):
    '''
    Functie care realizeaza undo la operatiile de stergere a tranzactiilor => adauga inapoi in lista elementele sterse
    input: l - lista in care se pastreaza tranzactiile
           undo - o lista cu elementele sterse
    output: l - lista nouă
    '''
    for tnz in undo:
        l.append(tnz)
    return l