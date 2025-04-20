# CSEN 177 Assignment 1

## Information

# Logan Calder 00001635021 lcalder@scu.edu

## Results

# In what order were the integers printed?

The integers were displayed in the order of their generation and later insertion into the buffer. However, the exact sequence of their being consumed was dependent on the way in which the threads were scheduled. Every integer was produced just once so consumption was exact.

## Discussion

# 1. How many of each integer should you see printed?

The integers between 0 (inclusive) to the given maximum (exclusive) are printed exactly once.

# 2. In what order should you expect to see them printed? Why?

The integers are expected to appear in the sequence of their introduction to the buffer, thus the order of their creation. This would be a result of the circular buffer working on a FIFO protocol for the integers.

# 3. Did your results differ from your answers in (1) and (2)? Why or why not?

The results were the same. The program uses proper synchronization mechanisms through locks and condition variables to ensure that the producer does not overwrite buffer components before the consumers have accessed the elements in sequence. Although thread scheduling by the JVM may lead to minor differences in terms of which consumer processes each integer, the fundamental integrity of the sequence of data is preserved.

## IMPORTANT:

The assignment states to only have one argument in command line, the # of consumers. HOWEVER, it also says the producer should continue to create integers until
it reaches a maximum specified on the command line. Thus, I opted for two arguments. The instructions were unclear.

## How to compile and run

# To compile the code:

javac ProducerConsumer.java

# To make JAR

& "C:\Program Files\Java\jdk-22\bin\jar.exe" cfm "ProducerConsumer.jar" "manifest.txt" "*.class"

# To run the code (.class):

java ProducerConsumer {# Consumers} {# Producers}

# To run the executable (.jar):

java -jar ProducerConsumer.jar {# Consumers} {# Producers}
