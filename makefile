CPP_FILES := $(wildcard src/*.cpp)

OBJ_FILES := $(patsubst src/%.cpp, obj/%.o, $(CPP_FILES))

CC_FLAGS = -Wall -std=c++11 

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXX = g++


app: $(OBJ_FILES)
	$(CXX) $^ -o  $@ $(SFML_FLAGS) 


obj/%.o: src/%.cpp
	@mkdir -p obj	
	@$(CXX) $(CC_FLAGS) -c -o $@ $<	
	

clean:
	rm -rf obj/*.o app
