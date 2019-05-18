CC = g++ --std=c++11

all: a.out

a.out: main.o StreamingService.o Controller.o UsersRepository.o CommentsRepository.o FilmsRepository.o User.o Publisher.o Film.o Comment.o
	$(CC) main.o StreamingService.o Controller.o UsersRepository.o CommentsRepository.o FilmsRepository.o User.o Publisher.o Film.o Comment.o -o a.out

main.o: main.cpp StreamingService.h
	$(CC) -c main.cpp -o main.o

StreamingService.o: StreamingService.cpp StreamingService.h Controller.h
	$(CC) -c StreamingService.cpp -o StreamingService.o

Controller.o: Controller.cpp Controller.h UsersRepository.h CommentsRepository.h FilmsRepository.h Exceptions.h
	$(CC) -c Controller.cpp -o Controller.o

UsersRepository.o: UsersRepository.cpp UsersRepository.h User.h Publisher.h Exceptions.h
	$(CC) -c UsersRepository.cpp -o UsersRepository.o

FilmsRepository.o: FilmsRepository.cpp FilmsRepository.h Film.h
	$(CC) -c FilmsRepository.cpp -o FilmsRepository.o

CommentsRepository.o: CommentsRepository.cpp CommentsRepository.h Comment.h
	$(CC) -c CommentsRepository.cpp -o CommentsRepository.o

Film.o: Film.cpp Film.h
	$(CC) -c Film.cpp -o Film.o

User.o: User.cpp User.h
	$(CC) -c User.cpp -o User.o

Publisher.o: Publisher.cpp Publisher.h User.h
	$(CC) -c Publisher.cpp -o Publisher.o

Comment.o: Comment.cpp Comment.h
	$(CC) -c Comment.cpp -o Comment.o

.PHONY: clean
clean:
	rm *.o 
	rm a.out