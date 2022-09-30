MODULOS = transaction \
	viewEquivalentSchedules \
	auxiliar \
	graphlib

OBJETOS = escalona.o $(addsuffix .o,$(MODULOS))

.PHONY : all clean

escalona : $(OBJETOS)

clean : 
	$(RM) $(OBJETOS)

purge : 
	$(RM) $(OBJETOS) escalona
