CC=g++
CFLAGS=-c -g -O0 -Wall
LDFLAGS=-lopencv_core -lopencv_imgproc -lopencv_highgui -ltesseract
SOURCES=TesseractOpenCV.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ocr_tesseract_ocv

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)