FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY cpp_core/ ./cpp_core/
COPY Makefile .

RUN make

CMD ["./smarthotel"]
