FROM debian:bookworm

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    python3-pip \
    python3 \
    python3-venv \
    freeglut3-dev \
    pkg-config \
    gcc \
    rsync\
    sudo \
    vim \
    xserver-xorg \
    xinit \
    x11-xserver-utils \
    bash

ENV DISPLAY=:0
RUN mkdir -p /tmp/.X11-unix

WORKDIR /home/simhub

COPY set-env /home/simhub
COPY .env/ /home/simhub/.env/
COPY source/ /home/simhub/source/

# RUN useradd -m -G sudo -s /bin/bash \
#     -p $(perl -e 'print crypt($ARGV[0], "password")' 'pass') simhub

# USER simhub

ENTRYPOINT ["/bin/bash"]

