FROM ubuntu:latest
WORKDIR /home/files/
RUN apt update; \
	apt install -y \
	make build-essential libmysqlclient-dev default-libmysqlclient-dev sqlite3

COPY . .
CMD {"cd /api", "make", "run", "cd ..", "cd /cli", "make", "run"}
