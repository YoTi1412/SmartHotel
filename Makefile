.PHONY: build run clean cpp api odoo

build:
\tdocker compose -f docker/docker-compose.yml build

run:
\tdocker compose -f docker/docker-compose.yml up

clean:
\tdocker compose -f docker/docker-compose.yml down -v

cpp:
\tmkdir -p build && cd build && cmake ../cpp_core && make && ./smarthotel

api:
\tcd api_gateway && uvicorn server:app --reload

odoo:
\tdocker compose -f docker/docker-compose.yml up odoo
