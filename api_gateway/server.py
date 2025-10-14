import requests
import json

url = "http://your-odoo-instance/jsonrpc"
headers = {"Content-Type": "application/json"}
data = {
    "jsonrpc": "2.0",
    "method": "call",
    "params": {
        "service": "object",
        "method": "execute",
        "args": ["db", "user", "password", "model.name", "create", {}],
    },
}

response = requests.post(url, headers=headers, data=json.dumps(data))
print(response.json())
