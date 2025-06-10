# Makefile

# Ottieni le variabili da terminale
FILE ?=
DIR ?=
EXE ?=

# Obiettivo principale
all:
	@if [ -z "$(FILE)" ] || [ -z "$(DIR)" ] || [ -z "$(EXE)" ]; then \
		echo "Errore: Devi specificare le variabili FILE=<path>, DIR=<path> ed EXE=<name>"; \
		exit 1; \
	fi

	@if [ ! -f "$(FILE)" ]; then \
		echo "Errore: Il file $(FILE) non esiste"; \
		exit 1; \
	fi

	@echo "Creazione della directory $(DIR)"
	@mkdir -p "$(DIR)"

	@echo "Copia del file $(FILE) in $(DIR)"
	@cp "$(FILE)" "$(DIR)/"

	@echo "Compilazione dei sorgenti"
	@$(MAKE) build -C "$(DIR)"

# Obiettivo build: compilazione dei sorgenti
.PHONY: build
build:
	# Sostituisci questi comandi con la tua compilazione specifica
	# Ad esempio: gcc -o $(EXE) *.c
	@echo "Compilo i sorgenti in $(EXE)"
	@gcc -o "$(EXE)" *.c

# Pulizia
.PHONY: clean
clean:
	@echo "Pulizia della cartella $(DIR)"
	@rm -rf "$(DIR)"
