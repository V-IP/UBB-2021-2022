def adauga_tranzactie_in_lista(l,tnz):
    '''
    Functie care adauga in lista o tranzactie valida
    input: l - lista tranzactiilor
           tnz - tranzactia
    output: - , daca adaugarea are loc
    '''
    l.append(tnz)

def cauta_tranzactie_in_lista(l,tnz):
    '''
    Functie care cauta in lista o tranzactie
    input: l - lista tranzactiilor
           tnz - tranzactia
    output: tnz , tranzactia cautata
    '''
    for i in range(len(l)):
        if tnz == l[i]:
            return i