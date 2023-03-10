FROM ubuntu

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install -y libqt5network5 qt5-qmake qtbase5-dev-tools
RUN apt-get install -y build-essential

WORKDIR /root/
RUN mkdir server
WORKDIR /root/server/
COPY *.cpp /root/server/
COPY *.h /root/server/
COPY *.pro /root/server/

RUN qmake echoServer.pro
RUN make

ENTRYPOINT ["./echoServer"]
