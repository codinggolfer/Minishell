FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y build-essential gcc make libncurses5-dev libreadline-dev valgrind

WORKDIR /Users/halgordzibari/Desktop/minishell

COPY . .

RUN make

CMD ["./minishell"]