FILE =
DIR =
EXE =

all: check directory build

check:
	@if [ -z "$(FILE)" ] || [ -z "$(DIR)" ] || [ -z "$(EXE)" ]; then \
		echo "You must insert the necessary argument"; \
		exit 1; \
	fi

	@if [ ! -f "$(FILE)" ]; then \
		echo "An error occurred while opening the file"; \
		exit 1; \
	fi

directory:
	@mkdir -p "$(DIR)"
	@cp "$(FILE)" "$(DIR)/"

build:
	gcc main.c -o "$(DIR)/$(EXE)"

.PHONY: check directory build all