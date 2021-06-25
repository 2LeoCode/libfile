OS =		$(shell uname)
SHELL =		/bin/sh
NAME =		

.SUFFIXES =	.c .o .h .a .dylib

SRCDIR =	src
INCDIR =	inc
LIBDIR =	lib

OBJDIR =	.obj
OBJFOLD =	$(addprefix $(OBJDIR)/,\
			)

SRC =		$(addsuffix $(word 1, $(.SUFFIXES)),\
			main)
INC =		$(addsuffix $(word 3, $(.SUFFIXES)),\
			)
LIB =		
DLIB =		
LIBNAME =	$(foreach lib, $(LIB),\
				$(lib)$(word 4, $(.SUFFIXES)))\
			$(foreach lib, $(DLIB),\
				$(lib)$(word 5, $(.SUFFIXES)))
LIBMAKE =	$(addprefix $(LIBDIR)/, $(LIB))
DLIBMAKE =	$(addprefix $(LIBDIR)/, $(DLIB))


OBJ =		$(addprefix $(OBJDIR)/,\
				$(SRC:$(word 1, $(.SUFFIXES))=$(word 2, $(.SUFFIXES))))

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -I $(INCDIR) -fsanitize=address -g3
LCFLAGS =	-L . $(addprefix -l, $(LIB:lib%=%) $(DLIB:lib%=%))

ifeq ($(OS), Darwin)
	KNRM =		\x1B[0m
	KRED =		\x1B[31m
	KGRN =		\x1B[32m
	KYEL =		\x1B[33m
	KBLU =		\x1B[34m
	KMAG =		\x1B[35m
	KCYN =		\x1B[36m
	KWHT =		\x1B[37m
else
	KNRM =		\e[39mk/
	KRED =		\e[31m
	KGRN =		\e[32m
	KYEL =		\e[33m
	KBLU =		\e[34m
	KMAG =		\e[35m
	KCYN =		\e[36m
	KWHT =		\e[37m
endif

all: $(OBJFOLD) $(LIBNAME) $(NAME)
	@printf "$(KGRN)\`$(NAME)\` is up to date.\n$(KNRM)"

$(OBJFOLD):
	@printf "$(KYEL)➤ "
	mkdir -p $(OBJFOLD)
	@printf "$(KNRM)"

%$(word 4, $(.SUFFIXES)): $(LIBDIR)/%
	@echo "$(KCYN)➤ make -C $^$(KNRM)"
	@make -C $^
	@printf "$(KYEL)➤ "
	cp $^/$@ .
	@printf "$(KNRM)"

%$(word 5, $(.SUFFIXES)): $(LIBDIR)/%
	@echo "$(KCYN)➤ make -C $^$(KNRM)"
	@make -C $^
	@printf "$(KYEL)➤ "
	cp $^/$@ .
	@printf "$(KNRM)"

$(NAME): $(OBJ)
	@printf "$(KCYN)[  Linking  ]\n➤ "
	$(CC) $(CFLAGS) $^ -o $@ $(LCFLAGS)
	@printf "$(KNRM)"

$(OBJDIR)/%$(word 2, $(.SUFFIXES)): $(SRCDIR)/%$(word 1, $(.SUFFIXES)) $(addprefix $(INCDIR)/, $(INC))
	@printf "$(KMAG)[  Compiling  ]\n➤ "
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(KNRM)"

clean:
	@printf "$(KRED)➤ "
	rm -rf $(OBJDIR)
	@printf "$(KNRM)"
	$(foreach lib, $(LIBMAKE) $(DLIBMAKE),\
		$(MAKE) fclean -C $(lib);)
	@printf "$(KNRM)"

fclean: clean
	@printf "$(KRED)➤ "
	rm -f $(NAME)
	@printf "$(KRED)➤ "
	rm -rf $(LIBNAME)
	@printf "$(KNRM)"

re: fclean all
