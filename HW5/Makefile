JC = javac
.SUFFIXES:.java .class
.java.class:
	$(JC) $*.java

CLASSES = Buffer.java Consumer.java Coordinator.java Generator.java 

default: classes

classes: $(CLASSES:.java=.class)

clean:
	rm -f *.class