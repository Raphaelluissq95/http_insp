#---------------------------------------------------------------------
# Assume-se uma distribuição Linux como sistema operacional padrão
#---------------------------------------------------------------------

# O compilador
COMPILER = g++
# Comando para remover pastas
RMDIR = rm -rdf
# Comando para remover arquivos
RM = rm -f

# Flags para geração automática de dependências
DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@

# Bibliotecas a serem linkadas
LIBS = -lm -lpthread

# Diretivas de compilacao
FLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Werror=init-self
# Diretivas extras para debug
DFLAGS = -ggdb -O0 -DDEBUG
# Diretivas extras para release
RFLAGS = -O3 -mtune=native

INC_PATH = lib
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

# Uma lista de arquivos por extensão:
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

# Nome do executável
EXEC = aracne

#---------------------------------------------------------------------
# Caso o sistema seja windows
#---------------------------------------------------------------------
ifeq ($(OS),Windows_NT)

# Comando para remover um diretório recursivamente
RMDIR = rd /s /q

# Comando para deletar um único arquivo
RM = del /q

LINK_PATH = 
FLAGS += -mwindows
DFLAGS += -mconsole
LIBS := -lmingw32 $(LIBS)

# Nome do executável
EXEC := $(EXEC).exe

else

UNAME_S := $(shell uname -s)

#---------------------------------------------------------------------
# Caso o sistema seja Mac
#---------------------------------------------------------------------

ifeq ($(UNAME_S), Darwin)

LIBS = -lm -lpthread

endif
endif

INC_FLAGS = -I$(INC_PATH)
LINK_PATH := $(addprefix -L,$(LINK_PATH))

##############################################################################################

.PRECIOUS: $(DEP_FILES)

release: FLAGS += $(RFLAGS)
release: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	-$(RM) $(EXEC)

# Gera o executável
$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

# Gera os arquivos objetos
$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_FLAGS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

# Gera os arquivos de dependencia
$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_FLAGS) $< $(DEP_FLAGS) $(FLAGS)

folders:
ifeq ($(OS), Windows_NT)
	@if NOT exist $(DEP_PATH) ( mkdir $(DEP_PATH) )
	@if NOT exist $(BIN_PATH) ( mkdir $(BIN_PATH) )
	@if NOT exist $(INC_PATH) ( mkdir $(INC_PATH) )
	@if NOT exist $(SRC_PATH) ( mkdir $(SRC_PATH) )
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif

.PHONY: release debug clean folders help

# Regra pra debug
print-% : ; @echo $* = $($*)

help:
	@echo.
	@echo Available targets:
	@echo - release:  Builds the release version (default target)
	@echo - debug:    Builds the debug version
	@echo - help:     Shows this help
	@echo.

-include $(DEP_FILES)