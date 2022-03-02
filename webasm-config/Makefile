
BIN=./bin

#arquivos do arduino wrapper
ARDUINO_FOLDER=./arduino_wrapper
ARDUINO_SRC=$(wildcard $(ARDUINO_FOLDER)/src/*.cpp)
ARDUINO_BIN=$(ARDUINO_SRC:.cpp=.o)
ARDUINO_INCLUDE=$(ARDUINO_FOLDER)/include
ARDUINO_HEADERS=$(wildcard $(ARDUINO_INCLUDE)/*.h)

#arquivos vindos do frontend
TARGET_FOLDER=./src
TARGET_SRC=$(wildcard $(TARGET_FOLDER)/*.cpp)
TARGET_BIN=$(TARGET_SRC:.cpp=.o)
TARGET_INCLUDE=$(TARGET_FOLDER)

#arquivos responsáveis pela integração com javascript
JS_INTEGRATION_FOLDER=./js_integration
JS_INTEGRATION_SRC=$(wildcard $(JS_INTEGRATION_FOLDER)/src/*.cpp)
JS_INTEGRATION_BIN=$(JS_INTEGRATION_SRC:.cpp=.o)
JS_INTEGRATION_INCLUDE=$(JS_INTEGRATION_FOLDER)/include

CXX=emcc

#$(CXX) $(ARDUINO_BIN) $(TARGET_BIN) $(JS_INTEGRATION_BIN) -lembind -s ASYNCIFY --extern-pre-js $(JS_INTEGRATION_FOLDER)/pre.js --extern-post-js $(JS_INTEGRATION_FOLDER)/pos.js -o $(BIN)/exec.js 
all: exec
	$(CXX) $(ARDUINO_BIN) $(TARGET_BIN) $(JS_INTEGRATION_BIN) -lembind -s ASYNCIFY --extern-pre-js $(JS_INTEGRATION_FOLDER)/pre.js -o $(BIN)/exec.js 

clean: 
	rm -rf $(ARDUINO_BIN) $(TARGET_BIN) $(JS_INTEGRATION_BIN) $(BIN)/*

exec: arduino js_integration src

js_integration: $(JS_INTEGRATION_BIN)

arduino: $(ARDUINO_BIN) $(ARDUINO_HEADERS)

src: $(TARGET_BIN)

%.o: %.cpp
	$(CXX) -c -I$(TARGET_INCLUDE) -I$(ARDUINO_INCLUDE) -I$(JS_INTEGRATION_INCLUDE) $< -o $@