CPP = clang++
CPPFLAGS  = -Wall 

TARGET = example

all: $(TARGET)

$(TARGET): $(TARGET).cpp
		$(CPP) $(CPPFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
