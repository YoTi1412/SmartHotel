Reservation:
  - Input guest details -> Check room availability -> Create Booking -> Notify (Python email sim).

Check-In:
  - Verify Booking -> Assign Room (update status) -> Log entry.

Service Usage:
  - Attach Service to Booking -> Update charges.

Housekeeping:
  - On check-out, mark Room as dirty -> Schedule clean (simple trigger).

Check-Out:
  - Generate Invoice (calculate totals) -> Process payment -> Update Room to available -> Notify bill.

Billing:
  - Sum: (days * roomRate) + sum(serviceCosts) + tax (e.g., 10%).
