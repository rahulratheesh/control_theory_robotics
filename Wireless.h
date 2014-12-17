class Wireless
{
	public:
        
        struct command_t {
            enum key_t { keyNone, keyF1, keyF2, keyF3, keyF4 };
            int left;   
            int right;  
            key_t key;  
            
            command_t() : left(0), right(0), key(keyNone) {}
            
            void goForward()
            {
                left = right = 100;
            }
            
            void goBack()
            {
                left = right = -100;
            }
            
            void turnLeft()
            {
                left = 0;
                right = 100;
            }
            
            void turnRight()
            {
                left = 100;
                right = 0;
            }
            
            void stopMotor()
            {
                left = right = 0;
            }
        };
        
        ElectricRayWirelessControl() {}
        
        virtual bool getRemoteCommand(command_t& cmd) = 0;
};

