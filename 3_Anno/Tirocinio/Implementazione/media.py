class MediaMobile:
    def __init__(self):
        self.somma = 0.0
        self.conteggio = 0

    def aggiungi(self, valore):
        """Aggiunge un numero al calcolo."""
        self.somma += valore
        self.conteggio += 1

    def media(self):
        """Restituisce la media attuale. Restituisce 0 se non ci sono dati."""
        if self.conteggio == 0:
            return 0.0
        return self.somma / self.conteggio

    def reset(self):
        """Ripristina l'oggetto allo stato iniziale."""
        self.somma = 0.0
        self.conteggio = 0