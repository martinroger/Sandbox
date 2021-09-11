import can
import cantools
can0 = can.interface.Bus(channel='can0', bustype='socketcan_ctypes')
print(can0.channel_info)
db = cantools.database.load_file('C2_Body.dbc')
SWCU_message = db.get_message_by_frame_id(848)
#print(SWCU_message.signals)
temp = {}
for signal in SWCU_message.signals :
    temp[signal.name] = signal.minimum
request = SWCU_message.encode(temp)
print(request)
print(SWCU_message.decode(request))
message = can.Message(arbitration_id=SWCU_message.frame_id,data=request)
can0.send(message)
temp['SWCU_indicator_REQ'] = 1
request = SWCU_message.encode(temp)
print(request)
print(SWCU_message.decode(request))
message = can.Message(arbitration_id=SWCU_message.frame_id,data=request)
can0.send(message)
