

OBJ := server.c test_web.c web.c
LB := -lwebsockets -lpthread
web:${OBJ}

	gcc -o $@ $^ ${LB}
