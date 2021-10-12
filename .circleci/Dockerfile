FROM ubuntu:latest
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt update && apt install -y git cmake ssh build-essential qt5-default && apt-get -qq clean	&& rm -rf /var/lib/apt/lists/*
ENTRYPOINT bash
