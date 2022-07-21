FROM debian:11-slim

RUN apt update && \
    apt install -y cmake g++ git python3-pip && \
    pip3 install conan

COPY . /home/math_parser

RUN cd /home/math_parser &&  \
    mkdir -p build &&  \
    cd build &&  \
    rm -rf * && \
    conan install .. && \
    cmake .. &&  \
    cmake --build . &&  \
    ctest && \
    cmake --install .

FROM debian:11-slim

COPY --from=0 /usr/local/bin/math_parser-bin /usr/local/bin
COPY entrypoint.sh /

ENTRYPOINT [ "/entrypoint.sh" ]
CMD [ "math_parser-bin" ]
