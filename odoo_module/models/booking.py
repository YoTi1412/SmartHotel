from odoo import models, fields

class Booking(models.Model):
    _name = 'smarthotel.booking'
    name = fields.Char("Customer Name")
    room_number = fields.Integer("Room Number")
    check_in = fields.Date("Check In")
    check_out = fields.Date("Check Out")
