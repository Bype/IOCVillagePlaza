from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import mm
#I"ll be generating code39 barcodes, others are available
from reportlab.graphics.barcode import code128
import random

# generate a canvas (A4 in this case, size doesn"t really matter)
c = canvas.Canvas("/tmp/barcode_example.pdf", pagesize=A4)
# create a barcode object
# (is not displayed yet)
# The encode text is "123456789"
# barHeight encodes how high the bars will be
# barWidth encodes how wide the "narrowest" barcode unit is
idtype = ('FAN', 'ATH', 'PRS', 'IOC')
x = 10
for i in idtype:
    for y in xrange(10):
        code = i + '%05d' % random.randint(0, 99999)
        barcode = code128.Code128(code, barWidth=0.3 * mm, barHeight=8 * mm)
        # drawOn puts the barcode on the canvas at the specified coordinates
        barcode.drawOn(c, x * mm, 30 + y * 30 * mm)
        c.drawString((x + 12) * mm, 20 + y * 30 * mm, code)
    x = x + 50
    
# now create the actual PDF
c.showPage()
c.save()
