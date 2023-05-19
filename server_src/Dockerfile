FROM ubuntu as core

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y \
            build-essential \
            qtbase5-dev \
            qt5-qmake \
            qtbase5-dev-tools \
            libargon2-0-dev

RUN rm -rf /var/lib/apt/lists/*


FROM core

RUN mkdir -p /var/server/build

COPY ./ /var/server/
WORKDIR /var/server/build/

RUN ls -l
RUN qmake ..
RUN make -j

ENTRYPOINT ["./server", "./configuration.json"]

