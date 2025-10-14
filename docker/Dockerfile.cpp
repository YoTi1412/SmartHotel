FROM gcc:latest
WORKDIR /app
COPY ../cpp_core /app
RUN apt-get update && apt-get install -y cmake &&     cmake . && make
CMD ["./smarthotel"]
