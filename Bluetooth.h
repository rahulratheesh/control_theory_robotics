#include "Wireless.h"

class Bluetooth : public Wireless
{
    public:
        Bluetooth() : Wireless(), lastKey(command_t::keyNone) {}

        virtual bool getRemoteCommand(command_t& cmd)
        {
            cmd.stopMotor();
            cmd.key = command_t::keyNone;
            
            // no commands available
            if (BTSerial.available() <= 0)
                return false; 
                
            char ch = BTSerial.read();
            switch (ch) {
                case '8': // up
                    cmd.goForward();
                    break;
                case '2': // down
                    cmd.goBack();
                    break;
                case '4': // left
                    cmd.turnLeft();
                    break;
                case '6': // right
                    cmd.turnRight();
                    break;
                default:
                    break;
            }
            // repeated key, ignore it
            if (cmd.key != command_t::keyNone && cmd.key == lastKey) {
                return false; 
            }
            lastKey = cmd.key;
            return true;
        }
    
    private:
        command_t::key_t lastKey;
    
};
