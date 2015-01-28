JC = javac
JFLAGS = -g

SOURCES = $(wildcard *.java) $(wildcard odeint/*.java)
CLASSES = $(SOURCES:.java=.class)

all : $(CLASSES)

%.class : %.java
	$(JC) $(JFLAGS) $<

clean :
	rm $(CLASSES)
