#!/bin/bash

# Create directories
mkdir -p cpp_core/{include,src,tests,utils}
mkdir -p odoo_module/{controllers,models,data}
mkdir -p api_gateway
mkdir -p docs
mkdir -p scripts
mkdir -p docker

# Create base files
touch README.md .gitignore CMakeLists.txt

# cpp_core files
cat > cpp_core/include/booking.hpp <<EOF
#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>
#include <vector>

struct Booking {
    int id;
    std::string customerName;
    int roomNumber;
    std::string checkIn;
    std::string checkOut;
};

#endif // BOOKING_HPP
EOF

cat > cpp_core/src/main.cpp <<EOF
#include <iostream>
#include "booking.hpp"

int main() {
    std::cout << "SmartHotel C++ Core Running..." << std::endl;
    return 0;
}
EOF

cat > cpp_core/CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.10)
project(SmartHotelCore)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(smarthotel
    src/main.cpp
)
EOF

# odoo_module
cat > odoo_module/__manifest__.py <<EOF
{
    'name': 'SmartHotel Integration',
    'version': '1.0',
    'summary': 'Connects Odoo ERP with SmartHotel C++ backend',
    'depends': ['base'],
    'data': ['data/demo.xml'],
    'installable': True,
}
EOF

cat > odoo_module/controllers/main.py <<EOF
from odoo import http
import requests

class SmartHotelController(http.Controller):
    @http.route('/smarthotel/sync', auth='user', type='json')
    def sync_booking(self, **kwargs):
        response = requests.get('http://api_gateway:8000/status')
        return {'status': response.text}
EOF

cat > odoo_module/models/booking.py <<EOF
from odoo import models, fields

class Booking(models.Model):
    _name = 'smarthotel.booking'
    name = fields.Char("Customer Name")
    room_number = fields.Integer("Room Number")
    check_in = fields.Date("Check In")
    check_out = fields.Date("Check Out")
EOF

cat > odoo_module/data/demo.xml <<EOF
<odoo>
    <data>
        <record id="demo_booking" model="smarthotel.booking">
            <field name="name">John Doe</field>
            <field name="room_number">101</field>
            <field name="check_in">2025-10-14</field>
            <field name="check_out">2025-10-16</field>
        </record>
    </data>
</odoo>
EOF

# API Gateway
cat > api_gateway/server.py <<EOF
from fastapi import FastAPI

app = FastAPI()

@app.get("/status")
def read_root():
    return {"message": "SmartHotel API Gateway Running"}
EOF

cat > api_gateway/requirements.txt <<EOF
fastapi
uvicorn
requests
EOF

# Docker setup
cat > docker/Dockerfile.cpp <<EOF
FROM gcc:latest
WORKDIR /app
COPY ../cpp_core /app
RUN apt-get update && apt-get install -y cmake && \
    cmake . && make
CMD ["./smarthotel"]
EOF

cat > docker/Dockerfile.gateway <<EOF
FROM python:3.10
WORKDIR /app
COPY ../api_gateway /app
RUN pip install -r requirements.txt
CMD ["uvicorn", "server:app", "--host", "0.0.0.0", "--port", "8000"]
EOF

cat > docker/Dockerfile.odoo <<EOF
FROM odoo:17
COPY ../odoo_module /mnt/extra-addons/smarthotel
EOF

cat > docker/docker-compose.yml <<EOF
version: '3.8'

services:
  cpp_core:
    build:
      context: ..
      dockerfile: docker/Dockerfile.cpp
    container_name: smarthotel_cpp

  api_gateway:
    build:
      context: ..
      dockerfile: docker/Dockerfile.gateway
    ports:
      - "8000:8000"
    depends_on:
      - cpp_core

  odoo:
    build:
      context: ..
      dockerfile: docker/Dockerfile.odoo
    ports:
      - "8069:8069"
    depends_on:
      - api_gateway
EOF

# Makefile
cat > Makefile <<EOF
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
EOF

# docs
cat > docs/architecture.md <<EOF
# SmartHotel Architecture

## Components
1. **C++ Core** — Handles room logic, booking computation, and in-memory operations.
2. **API Gateway (FastAPI)** — Bridges Odoo with the C++ backend via HTTP/JSON.
3. **Odoo ERP Module** — Manages UI, customers, and accounting.

## Flow
Odoo → FastAPI → C++ → FastAPI → Odoo
EOF

echo "✅ SmartHotel project structure created successfully!"
