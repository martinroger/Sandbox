import can
import cantools
vcan0 = can.interface.Bus('VCAN0', bustype='virtual')
print(vcan0.channel_info)
db = cantools.database.load_file('C2_body.dbc')
SWCU_message = db.get_message_by_frame_id(848)
#print(SWCU_message.signals)
temp = {}
for signal in SWCU_message.signals :
    temp[signal.name] = signal.minimum
request = SWCU_message.encode(temp)
print(request)
print(SWCU_message.decode(request))