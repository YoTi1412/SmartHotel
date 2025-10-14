# SmartHotel Architecture

## Components
1. **C++ Core** — Handles room logic, booking computation, and in-memory operations.
2. **API Gateway (FastAPI)** — Bridges Odoo with the C++ backend via HTTP/JSON.
3. **Odoo ERP Module** — Manages UI, customers, and accounting.

## Flow
Odoo → FastAPI → C++ → FastAPI → Odoo
