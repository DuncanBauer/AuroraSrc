#include "MapleCodec.h"

#include "../../tools/BitTools.h"


byte * MapleCodec::encode(Packet packet)
{
    byte * data = packet.bytes.data();
    for (int j = 0; j < 6; j++)
    {
		byte remember = 0;
		byte dataLength = (byte) (packet.length & 0xFF);
		// printByteArray(data);
		if (j % 2 == 0)
        {
			for (int i = 0; i < packet.length; i++)
            {
				byte cur = data[i];
				cur = BitTools::rollLeft(cur, 3);
				cur += dataLength;
				cur ^= remember;
				remember = cur;
				cur = BitTools::rollRight(cur, (int)dataLength & 0xFF);
				cur = ((byte) ((~cur) & 0xFF));
				cur += 0x48;
				dataLength--;
				data[i] = cur;
			}
		}
        else
        {
			for (int i = packet.length - 1; i >= 0; i--)
            {
				byte cur = data[i];
				cur = BitTools::rollLeft(cur, 4);
				cur += dataLength;
				cur ^= remember;
				remember = cur;
				cur ^= 0x13;
				cur = BitTools::rollRight(cur, 3);
				dataLength--;
				data[i] = cur;
			}
		}
	}
	return data;
}

byte * MapleCodec::decode(Packet packet)
{
    byte * data = packet.bytes.data();
    for (int j = 1; j <= 6; j++) {
        byte remember = 0;
        byte dataLength = (byte) (packet.length & 0xFF);
        byte nextRemember = 0;

        if (j % 2 == 0) {
            for (int i = 0; i < packet.length; i++) {
                byte cur = data[i];
                cur -= 0x48;
                cur = ((byte) ((~cur) & 0xFF));
                cur = BitTools::rollLeft(cur, (int)dataLength & 0xFF);
                nextRemember = cur;
                cur ^= remember;
                remember = nextRemember;
                cur -= dataLength;
                cur = BitTools::rollRight(cur, 3);
                data[i] = cur;
                dataLength--;
            }
        } else {
            for (int i = packet.length - 1; i >= 0; i--) {
                byte cur = data[i];
                cur = BitTools::rollLeft(cur, 3);
                cur ^= 0x13;
                nextRemember = cur;
                cur ^= remember;
                remember = nextRemember;
                cur -= dataLength;
                cur = BitTools::rollRight(cur, 4);
                data[i] = cur;
                dataLength--;
            }
        }
    }
    return data;
}
