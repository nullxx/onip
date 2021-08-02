# This is my first Make file so please don't get scared :)

NAME = onip

PREFIX = /usr/local

CC = cc
BUILD_FOLDER = build
LIBS = -lcurl -ljson-c
MODE := ${MODE}

LOGGER_FLAGS = -DLOG_USE_COLOR

ifeq ($(MODE), DEBUG)
	ADDITIONAL_FLAGS := -g
endif

build: main.o curl_utils.o network.o cloudflare.o filesystem.o notifier.o logger.o utils.o environment.o
	$(CC) $(BUILD_FOLDER)/main.o $(BUILD_FOLDER)/curl_utils.o $(BUILD_FOLDER)/network.o $(BUILD_FOLDER)/cloudflare.o $(BUILD_FOLDER)/filesystem.o $(BUILD_FOLDER)/notifier.o $(BUILD_FOLDER)/logger.o $(BUILD_FOLDER)/utils.o $(BUILD_FOLDER)/environment.o $(LIBS) $(FLAGS) -o $(BUILD_FOLDER)/$(NAME) $(ADDITIONAL_FLAGS)

install:
	mv $(BUILD_FOLDER)/$(NAME) $(PREFIX)/bin/$(NAME)

uninstall:
	rm $(PREFIX)/bin/$(NAME)

main.o:
	$(CC) -c src/main.c -o $(BUILD_FOLDER)/main.o $(ADDITIONAL_FLAGS)

curl_utils.o:
	$(CC) -c src/lib/curl_utils.c -o $(BUILD_FOLDER)/curl_utils.o $(ADDITIONAL_FLAGS)


network.o:
	$(CC) -c src/lib/network.c -o $(BUILD_FOLDER)/network.o $(ADDITIONAL_FLAGS)


cloudflare.o:
	$(CC) -c src/lib/cloudflare.c -o $(BUILD_FOLDER)/cloudflare.o $(ADDITIONAL_FLAGS)


filesystem.o:
	$(CC) -c src/lib/filesystem.c -o $(BUILD_FOLDER)/filesystem.o $(ADDITIONAL_FLAGS)

notifier.o:
	$(CC) -c src/lib/notifier.c -o $(BUILD_FOLDER)/notifier.o $(ADDITIONAL_FLAGS)

logger.o:
	$(CC) -c src/lib/logger.c $(LOGGER_FLAGS) -o $(BUILD_FOLDER)/logger.o $(ADDITIONAL_FLAGS)

utils.o:
	$(CC) -c src/lib/utils.c -o $(BUILD_FOLDER)/utils.o $(ADDITIONAL_FLAGS)

environment.o:
	$(CC) -c src/lib/environment.c -o $(BUILD_FOLDER)/environment.o $(ADDITIONAL_FLAGS)

init:
	mkdir -p $(BUILD_FOLDER)

clean:
	rm -rf $(BUILD_FOLDER)