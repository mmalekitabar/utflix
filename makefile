CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) utflixserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/StreamingService.o: StreamingService.cpp StreamingService.h Controller.h
	$(CC) $(CF) -c StreamingService.cpp -o $(BUILD_DIR)/StreamingService.o

$(BUILD_DIR)/Controller.o: Controller.cpp Controller.h UsersRepository.h CommentsRepository.h FilmsRepository.h Exceptions.h
	$(CC) $(CF) -c Controller.cpp -o $(BUILD_DIR)/Controller.o

$(BUILD_DIR)/UsersRepository.o: UsersRepository.cpp UsersRepository.h User.h Publisher.h Exceptions.h
	$(CC) $(CF) -c UsersRepository.cpp -o $(BUILD_DIR)/UsersRepository.o

$(BUILD_DIR)/FilmsRepository.o: FilmsRepository.cpp FilmsRepository.h Film.h Exceptions.h
	$(CC) $(CF) -c FilmsRepository.cpp -o $(BUILD_DIR)/FilmsRepository.o

$(BUILD_DIR)/CommentsRepository.o: CommentsRepository.cpp CommentsRepository.h Comment.h
	$(CC) $(CF) -c CommentsRepository.cpp -o $(BUILD_DIR)/CommentsRepository.o

$(BUILD_DIR)/Film.o: Film.cpp Film.h Exceptions.h
	$(CC) $(CF) -c Film.cpp -o $(BUILD_DIR)/Film.o

$(BUILD_DIR)/User.o: User.cpp User.h
	$(CC) $(CF) -c User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Publisher.o: Publisher.cpp Publisher.h User.h
	$(CC) $(CF) -c Publisher.cpp -o $(BUILD_DIR)/Publisher.o

$(BUILD_DIR)/Comment.o: Comment.cpp Comment.h
	$(CC) $(CF) -c Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/main.o: main.cpp StreamingService.h
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

utflixserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/StreamingService.o $(BUILD_DIR)/Controller.o $(BUILD_DIR)/UsersRepository.o $(BUILD_DIR)/FilmsRepository.o $(BUILD_DIR)/CommentsRepository.o $(BUILD_DIR)/Film.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/StreamingService.o $(BUILD_DIR)/Controller.o $(BUILD_DIR)/UsersRepository.o $(BUILD_DIR)/FilmsRepository.o $(BUILD_DIR)/CommentsRepository.o $(BUILD_DIR)/Film.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o utflixserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
