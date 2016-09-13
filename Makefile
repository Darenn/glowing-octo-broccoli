## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb
# Règle de compilation

test_chaines : test_chaines.o chaine.o
	$(CC) $(CFLAGS) -o $@ $^	

jeu : jeu.o chaine.o motus.o
	$(CC) $(CFLAGS) -o $@ $^

chaine.o : chaine.h
motus.o : chaine.h motus.h
jeu.o : chaine.h motus.h

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

test : test_chaines
	./test_chaines; diff -s test_chaines_out_acomparer.txt test_chaines_out.txt

test_jeu : jeu
	./jeu 6 6 test_jeu_in.txt

# Débogage (de ok)
debug_chaines : test_chaines
	nemiver test_chaines
debug_jeu : jeu
	nemiver jeu	

# Vérification mémoire (de ok)
memoire_chaines : test_chaines
	valgrind --leak-check=full ./test_chaines
memoire_jeu : jeu
	valgrind --leak-check=full ./jeu 6 6 test_jeu_in.txt

clean:
	rm *.o


TP_NUMERO := 1
TGZ_FILES :=  *.c *.h ?akefile cr.pdf
TP_DIR := TD$(TP_NUMERO)

rendu :
	[ -e cr.pdf ] || cat > cr.pdf
	cd .. ; tar czf $(TP_DIR)/rendu.tgz $(TGZ_FILES:%=$(TP_DIR)/%)
