FROM ubuntu as core

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y \
            build-essential \
            qtbase5-dev \
            qt5-qmake \
            qtbase5-dev-tools

RUN rm -rf /var/lib/apt/lists/*


FROM core

RUN mkdir -p /var/server/

COPY ./ /var/server/
WORKDIR /var/server/

RUN ls -l
RUN qmake server.pro
RUN make

ENTRYPOINT ["./server"]
