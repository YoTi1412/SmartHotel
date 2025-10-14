from odoo import http
import requests

class SmartHotelController(http.Controller):
    @http.route('/smarthotel/sync', auth='user', type='json')
    def sync_booking(self, **kwargs):
        response = requests.get('http://api_gateway:8000/status')
        return {'status': response.text}
