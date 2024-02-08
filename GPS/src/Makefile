# Compiler
CC = gcc
# Options de compilation
CFLAGS = -Wall -Wextra -std=c99 -Wconversion

# Répertoire source
SRCDIR = code
# Répertoire des en-têtes
INCDIR = header
# Répertoire des fichiers objets
OBJDIR = objet

# Fichiers source
SRCS = $(wildcard $(SRCDIR)/*.c)
# Fichiers d'en-tête
HDRS = $(wildcard $(INCDIR)/*.h)
# Fichiers objets générés
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Nom de l'exécutable
EXEC = script_trajectoire

# Règle de construction de l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm 

# Règle de construction des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDRS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) $(EXEC)
	clear
